<?php
/*-------------------------------encrypted_film--------------------------------------*/
/*---------------operations part----------------------------*/
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
    $nid = db_select("node" , "node")->fields("node" , array("nid"))->condition("nid" , $data["nid"])->execute()->fetch();
    if(empty($nid)) return services_error("Wrong nid!" , 400);

    $new_name = db_select("r" , "locked")->fields("locked" , array("new_name"))->condition("new_name" , $data["new_name"])->execute()->fetch();
    if(!empty($new_name)) return services_error("Duplicate new_name!" , 409);

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
/*----------------------------------------------------------*/
/*-------------------------------system_info--------------------------------------*/
/* This part is used for get the information of user system after login and logout
 * retrieve : send the data of record with id
 * create : insert user system in database or update it if the data is exist
 * delete : set the logout field, it means that user logout from the system
 * */

function system_info_retrieve($id , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "system_info"))) return services_error(t('Failed to access'), 403);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 400);

    $function = get_compatible_function_name("/system_info/id" , "GET" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        $parameter["id"] = $id;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 400);
}
function system_info_retrieve_v_1($parameter){
    $info = db_select("desktop_lock_systems_info" , "info")
        ->fields("info" , array())
        ->condition("id" , $parameter["id"])
        ->execute()->fetch();

    if(empty($info)) return services_error("Not Found!" , 404);

    return $info;
}

function system_info_create($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "system_info"))) return services_error(t('Failed to access'), 403);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 400);

    $function = get_compatible_function_name("/system_info" , "POST" , $data["source"] , $data["version"]);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 400);
}
function system_info_create_v_1($data){
    global $user;
    if($user->uid == 0) return services_error("User is not logged in!" , 406);

    $info = db_select("desktop_lock_systems_info" , "info")
        ->fields("info" , array())
        ->condition("uid" , $user->uid)
        ->condition("cpu_serial" , $data["cpu_serial"])
        ->condition("cpu_model" , $data["cpu_model"])
        ->condition("main_board_serial" , $data["main_board_serial"])
        ->condition("hdd_serial" , $data["hdd_serial"])
        ->execute()->fetch();

    if(empty($info)){
        $insert = db_insert("desktop_lock_systems_info")
            ->fields(array(
                "cpu_serial" => $data["cpu_serial"],
                "cpu_model" => $data["cpu_model"],
                "main_board_serial" => $data["main_board_serial"],
                "hdd_serial" => $data["hdd_serial"],
                "created" => REQUEST_TIME,
                "last_login" => REQUEST_TIME,
                "logout" => 0
            ))->execute();
        add_log($user->uid , "/system_info" , "insertSystemInfo" , "desktop_lock_systems_info" , $insert , "desktop" , "1" , "successful" , "New System Info is saved!");
        if($insert) return $insert;
        else return services_error("Internal Server Error!" , 500);
    }
    else{
        $update = db_update("desktop_lock_systems_info")
            ->condition('id', $info->id)
            ->fields(array(
                "last_login" => REQUEST_TIME,
                "logout" => 0
            ))->execute();
        add_log($user->uid , "/system_info" , "updateSystemInfo" , "desktop_lock_systems_info" , $info->id , "desktop" , "1" , "successful" , "Update New System Info!");
        if($update) return $info->id;
        else return services_error("Internal Server Error!" , 500);
    }
}

function system_info_delete($id , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "system_info"))) return services_error(t('Failed to access'), 403);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 400);

    $function = get_compatible_function_name("/system_info/id" , "DELETE" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        $parameter["id"] = $id;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 400);
}
function system_info_delete_v_1($parameter){
    $delete = db_update("desktop_lock_systems_info")
        ->fields(array(
            "logout" => REQUEST_TIME
        ))
        ->condition("id" , $parameter["id"])
        ->execute();

    global $user;
    if($delete){
        add_log($user->uid , "/system_info" , "deleteSystemInfo" , "desktop_lock_systems_info" , $parameter["id"] , "desktop" , "1" , "successful" , "Delete a System Info");
        return true;
    }
    else return services_error("This System Information is not Found!" , 404);
}
/*---------------operations part----------------------------*/