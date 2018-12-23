<?php

/*--------------------actions part---------------------*/
function make_order_by_user_point($data){
    if(empty($data["hash"]) || !(hash_true($data["hash"] , "order"))) return services_error(t('Failed to access'), 10);
    $source_name = (isset($data["source"]) && !empty($data["source"])) ? $data["source"] : "android";
    $version = (isset($data["version"]) && !empty($data["version"])) ? (int)$data["version"] : 0;

    $function = get_compatible_function_name("/order/by_user_point" , "POST" , $source_name , $version);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }

    return services_error(t('This version is not supported'), 11);
}

function order_content_v_0($data){
    if(strcmp($data["type"] , "order_content") != 0) return services_error(t('Order type is not exist'), 12);
    if(!isset($data["nid"]) || empty($data["nid"])) return services_error(t('Nid is required!'), 15);
    $nid = $data["nid"];
    global $user;

    $order = pay_for_node($nid , True);
    if(gettype($order) != "string") {
        add_log($user->uid , "/order/by_user_point" , "buy" , "node" , $nid , empty($data["source"]) ? "android" : $data["source"] , empty($data["version"]) ? 0 : $data["version"] , "successful" , "User bought a node successfully!");
        return $order;
    }

    switch ($order) {
        case "LoginError":
            return services_error(t('User is not logged in!'), 13);
        case "NodeError":
            return services_error(t('Nid is not exist!'), 16);
        case "PriceError":
            return services_error(t('Error in getting the price'), 19);
        case "UserPointError":
            return services_error(t('User point is not enough'), 21);
        case "DatabaseError":
            return services_error(t('Error in Database'), 14);
        default:
            return services_error(t('Unknown Error'), 20);
    }

}