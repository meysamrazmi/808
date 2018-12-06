<?php

function contact_us_resource_index($parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "contactus"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/contactus" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function contact_us_information_v_1($parameter){
    $info = array();
    $info["address"] = "تهران، ابتدای گیشا، ابتدای فروزانفر، جنب بانک صادرات، پلاک 1، واحد 7";
    $info["map"] = array("latitude" => "35.726257" , "longtitude" => "51.378813");
    $info["phone"] = array("02188272694");
    $info["fax"] = array("02188275253");
    $info["email"] = array("saze808@gmail.com" , "info@civil808.com" , "edu@civil808.com");
    $info["sms"] = array("30009900666808");
    return $info;
}