<?php
/* pre request function
 * input : merchant id and callback
 * return a token for authorization
 *
 * This function generates a token for user that can view the remote login page with it
 */
function remote_login_resource_pre_request($merchant , $parameter){
    /*
     * check agent and merchant ID validation
     * */
    $query = db_select("remote_login_subscription" , "subscription");
    $query->fields("subscription" , array("merchant"));
    $query->condition("subscription.merchant" , $merchant);
    $result = $query->execute()->fetchCol();
    if(empty($result)) return array("status" => 403 , "error" => "You have not subscribed before.");
    if(!isset($parameter["callback"]) || empty($parameter["callback"])) return array("status" => 406 , "error" => "You did not send callback.");

    /*generate random token for user*/
    $flag = true;
    while($flag){
        /*
         * Token must not be repetitive
         * If it's repetitive, it's generated again
         * */
        $token = rand(pow(10,6) , pow(10,7));
        $query = db_select("remote_login_log")
            ->fields("remote_login_log" , array("token"))
            ->condition("token" , $token)->execute()->fetch();
        if(empty($query)) $flag = false;
    }

    /*insert toke with agent information in db*/
    $insert = db_insert("remote_login_log")->fields(array(
        "token" => $token,
        "merchant" => $merchant,
        "callback" => $parameter["callback"],
        "uid" => 0,
        "created" => REQUEST_TIME,
        "status" => "pending"
    ))->execute();
    if(!$insert) return array("status" => 500 , "error" => "Undefined Error!");

    return array("status" => 200 , "token" => $token);
}

/*
 * After user login successfully the destination site should send request to get the user information
 * Merchant ID and user Token as a parameter is necessary
 *
 * Destination site can get the information of user that has chosen before
 * */
function remote_login_resource_post_request($merchant , $parameter){
    /*
     * check merchant ID and toke validation
     * */
    $query = db_select("remote_login_log" , "log");
    $query->fields("log" , array("uid"));
    $query->condition("log.merchant" , $merchant)->condition("log.token" , $parameter["token"])->condition("log.status" , "successful");
    $uid = $query->execute()->fetch();
    if(empty($uid)) return array("status" => 401 , "error" => "Authorization Failed!");
    $uid = $uid->uid;

    /*
     * fetch setting of information that should send to user
     * */
    $setting = db_select("remote_login_subscription" , "subscription")
        ->fields("subscription" , array("setting"))
        ->condition("merchant" , $merchant)->execute()->fetch();
    $setting = unserialize($setting->setting);

    /*
     * send user information to customer
     * */
    $query = db_select("users" , "user");
    $query->join("profile" , "profile" , "user.uid = profile.uid and profile.type = 'main' ");
    $query->leftJoin("field_data_field_full_name" , "full_name" , "profile.pid = full_name.entity_id");
    $query->fields("user" , array("uid" , "name" , "mail"));
    $query->addField("full_name" , "field_full_name_value" , "full_name");
    $query->condition("user.uid" , $uid);
    $user = $query->execute()->fetch();
    $info = new stdClass();
    foreach($setting as $value){
        $info->$value = $user->$value;
    }

    return array("status" => 200 , "user" => $info);
}
