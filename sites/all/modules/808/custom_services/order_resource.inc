<?php

/*--------------------actions part---------------------*/
function make_order_by_user_point($hash , $type , $data){
    if(!(hash_true($hash , "order"))) return services_error(t('Failed to access'), 10);

    if($type == "order_content"){
        if(isset($data["nid"]) && !empty($data["nid"]) && gettype($data["nid"]) == "integer") return order_content($data["nid"]);
        else return services_error(t('Nid is required!'), 15);
    }
    return services_error(t('Order type is not exist'), 12);

}

function order_content($nid){
    $order = pay_for_node($nid , True);

    if(gettype($order) != "string") return $order;

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