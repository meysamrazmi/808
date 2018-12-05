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
    $info["text"] = '<div> 5% شارژ رایگان برای 808+ <br> جشنواره روز دانشجو </div>';
    $info["image"] = "https://civil808.com/sites/default/files/appfestival.jpg";
    $info["color"] = array("r" => 0, "g" => 0, "b" => 0, "alpha" => 1);
    return $info;
}