<?php


/*-----------------actions part----------------------------------*/
function pre_payment($hash , $type , $price , $version){
    if(!(hash_true($hash , "payment"))) return services_error(t('Failed to access'), 403);

    if(strcmp($type , 'charge') == 0 && $version == 0){
        global $user;
        if($user->uid == 0) return services_error(t('User is not Login!'), 401);

        $attr = array('id' => time());
        $result =  add_bank_event($price, 'charge', 'android_charge', $user->uid, $attr);
        if($result == $attr['id'])
        {
            $response['id'] = $result;
            $response['uid'] = $user->uid;
            $response['status'] = 'pending';
            $response['value'] = $price;
            return ["response" => $response];
        }
        else{
            return services_error(t('Internal Server Error'), 500);
        }
    }
    return services_error(t('The Service is not supported'), 404);
}

function final_payment($hash , $data , $version){
    if(!(hash_true($hash , "payment"))) return services_error(t('Failed to access'), 403);

    if($version == 0){
        if(!isset($data['id']) || empty($data['id'])) return services_error(t('Transaction ID is required'), 401);
        if(!isset($data['status']) || empty($data['status'])) return services_error(t('Status is required'), 401);
        if($data['status'] != 'success' && $data['status'] != 'fail') return services_error(t('Status is not valid'), 401);
        if(!isset($data['refnumber']) || empty($data['refnumber'])) return services_error(t('reference number is required'), 401);

        update_bank_event($data['id'], $data['status'], $data['refnumber']);

        $query = db_select('bank_events' , 'bank');
        $query->fields('bank' , array('id' , 'user' , 'status' , 'value'));
        $query->condition('bank.id' , $data['id']);
        $result = $query->execute()->fetch();

        /*
         * @todo apply discount for festivals
         * */

        if($result->status == 'success'){
            $params = array(
                'uid' => $result->user,
                'points' => $result->value,
                'operation' => t('Charge from bank in application'),
            );
            userpoints_userpointsapi($params);
        }


        $response['id'] = $result->id;
        $response['status'] = $result->status;
        return ["response" => $response];
    }

    return services_error(t('The Service is not supported'), 404);
}

/*-----------------relationships part----------------------------------*/
function get_status($hash , $id , $version){
    if(!(hash_true($hash , "payment"))) return services_error(t('Failed to access'), 403);

    if($version == 0){
        $query = db_select('bank_events' , 'bank');
        $query->fields('bank' , array('status'));
        $query->condition('bank.id' , $id);
        $result = $query->execute()->fetch();

        return ["status" => $result->status];
    }
    return services_error(t('The Service is not supported'), 404);
}