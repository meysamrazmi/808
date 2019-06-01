<?php

function festival_resource_index($parameter){
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/festival" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function festival_information_v_1($parameter){
    $info = array();
    $info["enable"] = true;
//    $info["text"] = '<div> ۵% شارژ رایگان   <br>  فقط برای کاربران ۸۰۸+ </div>';
    $info["text"] = '<div> ۲۵% شارژ رایگان   <br>  به مناسبت فرارسیدن عید سعید فطر </div>';
    $info["image"] = "https://civil808.com/sites/default/files/appfestival.jpg";
    $info["color"] = array("r" => 255, "g" => 255, "b" => 255, "alpha" => 255);
    return $info;
}