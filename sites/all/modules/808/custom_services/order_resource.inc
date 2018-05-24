<?php

/*--------------------actions part---------------------*/
function make_order_by_user_point($hash , $type , $data , $version){
    if(!(hash_true($hash , "order"))) return services_error(t('Failed to access'), 403);

    if($version == 0){
        if($type == "order_content"){
            if(isset($data["nid"]) && !empty($data["nid"]) && gettype($data["nid"]) == "integer") return order_content($data["nid"]);
            else return services_error(t('Nid is required!'), 401);
        }
    }
    return services_error(t('The Service is not supported'), 404);
}

function order_content($nid){
    $order = pay_for_node($nid , True);

    if(gettype($order) != "string") return $order;

    switch ($order) {
        case "LoginError":
            return services_error(t('User is not logged in!'), 401);
        case "NodeError":
            return services_error(t('Nid is not exist!'), 401);
        case "PriceError":
            return services_error(t('Error in getting the price'), 401);
        case "UserPointError":
            return services_error(t('User point is not enough'), 401);
        case "DatabaseError":
            return services_error(t('Error in Database'), 401);
        default:
            return services_error(t('Unknown Error'), 401);
    }

}