<?php
/*--------------------operations part---------------------------*/
function encrypted_film_create($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "encrypted_film"))) return services_error(t('Failed to access'), 403);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 400);

    $function = get_compatible_function_name("/encrypted_film" , "POST" , $data["source"] , $data["version"]);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 400);
}
function encrypted_film_create_v_1($data){
    global $user;
    if($user->uid == 0) return services_error(t('You should logged in first!'), 403);
    if(empty($data["nid"]) || empty($data["title"]) || empty($data["password"]) ||
        empty($data["name"]) || empty($data["extension"]) || empty($data["new_name"]) || empty($data["new_extension"])
    ){
        return services_error("Data is not complete" , 400);
    }
    $nid = db_select("node")->fields("node" , array("nid"))->condition("nid" , $data["nid"])->execute()->fetch();
    if(empty($nid)) return services_error("Wrong nid!" , 400);

    $insert = db_insert("desktop_lock_encryption")->fields(array(
        "nid" => $data["nid"],
        "title" => $data["title"],
        "password" => $data["password"],
        "name" => $data["name"],
        "extension" => $data["extension"],
        "new_name" => $data["new_name"],
        "new_extension" => $data["new_extension"],
        "uid" => $user->uid,
        "active" => 1,
        "fid" => 0,
        "created" => REQUEST_TIME,
        "updated" => REQUEST_TIME,
    ))->execute();
    if(isset($insert)){
        add_log($user->uid , "/encrypted_film" , "encrypting" , "desktop_lock_encryption_table" , $insert , $data["source"] , $data["version"] , "successful" , "New film was encrypted with lock app");
        return true;
    }
    else return false;
}
/*--------------------------------------------------------------*/
