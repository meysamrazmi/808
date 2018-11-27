<?php

/*-----------------actions part----------------------------------*/
function payment_resource_pre_payment($data){
    if(!isset($data["hash"]) || !hash_true($data["hash"] , "payment")) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/payment/pre_payment" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function pre_payment_v1($data){
    if (strcmp($data["type"], 'charge') != 0) return services_error(t('This service is not supported'), 12);
    if(isset($data["price"])) $price = (int) $data["price"];
    else return services_error();

    global $user;
    if ($user->uid == 0) return services_error(t('User is not Login!'), 13);

    $attr = array('id' => time());
    $result = add_bank_event($price, 'charge', 'android_charge', $user->uid, $attr);
    if ($result == $attr['id']) {
        add_log($user->uid, "/payment/pre_payment", "pre_charging" , "charge" , $result , $data["source"] , $data["version"] , "successful" , "adding record in bank_events table was successful");
        $response['id'] = (int) $result;
        $response['uid'] = (int) $user->uid;
        $response['status'] = 'pending';
        $response['value'] = (int) $price;
        $response["zarinpal_id"] = variable_get('uc_zarinpal_MerchantID', '');
        return ["response" => $response];
    } else {
        add_log($user->uid, "/payment/pre_payment", "pre_charging" , "charge" , $result , $data["source"] , $data["version"] , "error" , "adding record in bank_events was failed");
        return services_error(t('Error in insert transaction in database'), 14);
    }
}

function payment_resource_final_payment($data){
    if(!isset($data["hash"]) || !hash_true($data["hash"] , "payment")) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/payment/final_payment" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);

}
function final_payment_v1($data){
    if(!isset($data['id']) || empty($data['id'])) return services_error(t('Transaction ID is required'), 15);
    if(!isset($data['status']) || empty($data['status'])) return services_error(t('Status is required'), 15);
    if($data['status'] != 'success' && $data['status'] != 'fail') return services_error(t('Status is not valid'), 15);
    if(!isset($data['refnumber']) || empty($data['refnumber'])) return services_error(t('reference number is required'), 15);

    $record = get_bank_event($data['id']);
    if(empty($record) || count($record) == 0) return services_error(t('Id is incorrect'), 16);
    if($record->status != "pending"){
        $response["description"] = "This record is completed before!";
        $response["status"] = $record->status;
        return ["response" => $response];
    }

    update_bank_event($data['id'], $data['status'], $data['refnumber']);

    $result = get_bank_event($data['id']);

    /*
     * @todo apply discount for festivals
     * */

    if($result->status == 'success'){
        add_log($result->user, "/payment/final_payment", "final_charging" , "charge" , $result->id , $data["source"] , $data["version"] , "successful" , "account charging was successful");
        $params = array(
            'uid' => $result->user,
            'points' => $result->value,
            'operation' => t('Charge from bank in application'),
        );
        userpoints_userpointsapi($params);
    }


    $response['id'] = (int) $result->id;
    $response['status'] = $result->status;
    return ["response" => $response];
}

/*-----------------relationships part----------------------------------*/
function payment_resource_get_status($id, $parameter){
    if(!isset($parameter["hash"]) || !hash_true($parameter["hash"] , "payment")) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/payment/id/status" , "GET" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        $parameter["id"] = $id;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function get_status_v1($parameter){
    $result = get_bank_event($parameter["id"]);
    if(empty($result)) return services_error(t('Id is incorrect'), 16);
    return ["status" => $result->status];
}
