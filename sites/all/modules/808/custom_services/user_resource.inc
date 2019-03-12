<?php

/*---------------------operations part---------------------------------*/
function user_resource_retrieve($uid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/user/uid" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["uid"] = $uid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function retrieve_user_v_1($parameter){
    $user_data = (array) user_data($parameter["uid"]);
    $pofile_data = (array) profile_data($parameter["uid"]);
    $result = array_merge($user_data , $pofile_data);
    global $user;
    if($user->uid != $parameter["uid"]){
        unset($result["mail"]);
        unset($result["user_point"]);
        unset($result["mobile"]);
    }
    return $result;
}

function user_resource_update($uid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    global $user;
    if($user->uid != $uid) return services_error("You do not have authorization for this action!" , 18);

    $function = get_compatible_function_name("/user/uid" , "PUT" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["uid"] = $uid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_update_v_1($data){
    $user = user_load($data["uid"]);
    $profile = profile2_load_by_user($user , "main");
    $user_update = false; //if there is any changes it will be true
    $profile_update = false; //if there is any changes it will be true

    /*check for each field and update the user if is needed*/
    if(isset($data["username"]) && !empty($data["username"])){
        $query = db_select("users" , "user");
        $query->fields("user" , array("name"));
        $query->condition("user.name" , $data["username"]);
        $result = $query->execute()->fetch();
        if(empty($result)){
            $user->name = $data["username"];
            $user_update = true;
        }
        else return services_error(t("This username is already taken!") , 18);
    }
    if(isset($data["email"]) && !empty($data["email"])){
        $query = db_select("users" , "user");
        $query->fields("user" , array("mail"));
        $query->condition("user.mail" , $data["email"]);
        $result = $query->execute()->fetch();
        if(empty($result)) {
            $user->mail = $data["email"];
            $user_update = true;
        }
        else return services_error(t("This Email is already taken!") , 18);
    }
    if(isset($data["password"]) && !empty($data["password"])){
        if(strlen($data["password"]) < 6) return services_error(t("The password should be at least 6 character!") , 16);
        require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
        $user->pass = user_hash_password(trim($data['password']));
        $user_update = true;
    }
    if(isset($data["picture"]) && !empty($data["picture"]) && strcmp($data["picture"]["type"] , "image") == 0){
        $picture = (object)$data["picture"];
        $file = db_select("file_managed")->fields("file_managed" , array("fid"))->condition("fid" , $picture->fid)->execute()->fetch();
        if(!empty($file) && (empty($user->picture) || $user->picture->fid != $picture->fid)) {
            $user->picture = $picture;
            $user_update = true;
            file_usage_add($picture, 'user', 'user', $user->uid);
        }
    }
    if(isset($data["background_image"]) && !empty($data["background_image"]) && strcmp($data["background_image"]["type"] , "image") == 0){
        $user->field_image['und']['0'] = $data["background_image"];
        $user_update = true;
    }
    if($user_update){
        user_save($user);
        add_log($data["uid"], "/user/uid" , "update" , "user" , $user->uid , $data["source"] , $data["version"] , "successful" , "update user data");
    }
    /*check for each field and update the profile if is needed*/
    if(isset($data["full_name"]) && !empty($data["full_name"])){
        $profile->field_full_name['und'][0]['value'] = $data['full_name'];
        $profile_update = true;
    }
    if(isset($data["about"]) && !empty($data["about"])){
        $profile->field_about_me['und'][0]['value'] = $data['about'];
        $profile_update = true;
    }
    if(isset($data["skills"]) && !empty($data["skills"])){
        $profile->field_skills['und'][0]['value'] = $data['skills'];
        $profile_update = true;
    }
    if(isset($data["university"]) && !empty($data["university"])){
        $profile->field_university['und'][0]['value'] = $data['university'];
        $profile_update = true;
    }
    if(isset($data["education"]) && !empty($data["education"])){
        $profile->field_education_field['und'][0]['value'] = $data['education'];
        $profile_update = true;
    }
    if(isset($data["education_degree"]) && !empty($data["education_degree"])){
        $profile->field_education_degree['und'][0]['value'] = $data['education_degree'];
        $profile_update = true;
    }
    if(isset($data["mobile"]) && !empty($data["mobile"])){
        $profile->field_mobile['und'][0]['value'] = $data['mobile'];
        $profile_update = true;
    }
    if(isset($data["job"]) && !empty($data["job"])){
        $profile->field_job['und'][0]['value'] = $data['job'];
        $profile_update = true;
    }
    if(isset($data["job_place"]) && !empty($data["job_place"])){
        $profile->field_job_place['und'][0]['value'] = $data['job_place'];
        $profile_update = true;
    }
    if(isset($data["job_title"]) && !empty($data["job_title"])){
        $profile->field_job_title['und'][0]['value'] = $data['job_title'];
        $profile_update = true;
    }
    if(isset($data["address"]) && !empty($data["address"])){
        $profile->field_address['und'][0]['value'] = $data['address'];
        $profile_update = true;
    }
    if($profile_update){
        profile2_save($profile);
        add_log($data["uid"], "/user/uid" , "update" , "profile2" , $profile->pid , $data["source"] , $data["version"] , "successful" , "update profile data");
    }

    return true;
}
/*---------------------actions part------------------------------------*/
function user_resource_login($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/user/login2" , "POST" , $data["source"] , $data["version"]);

    if(!empty($function) && strlen($function) > 0)
        return call_user_func($function, $data);

    return services_error(t('This version is not supported'), 11);
}
function login_v_1($data){
    /*check if user is login or not*/
    global $user;
    if ($user->uid > 0) {
        return services_error(t("User is already logged in!") , 18);
    }

    /*check if user is exist and unblocked*/
    $query =  db_select('users' , 'user');
    $query->fields('user', array('uid' , 'name' , 'status'));
    $db_or = db_or();
    $db_or->condition('user.name', $data["username_email"] , 'LIKE');
    $db_or->condition('user.mail', $data["username_email"] , 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchObject();
    if(empty($result)) return services_error(t("User is not exist!") , 17);
    elseif($result->status == 0) return  services_error(t("User is inactive!") , 18);
    else $username = $result->name;

    /*check the truth of username and password*/
    $uid = user_authenticate($username, $data["password"]);

    /*
     * @todo
     * check flood for attempting to login frequently
     * */

    if ($uid) {
        $user = user_data($uid);
        user_login_finalize();
        $login_data = new stdClass();
        $login_data->sessid = session_id();
        $login_data->session_name = session_name();
        $login_data->token = drupal_get_token('services');
        $login_data->user = $user;
        $login_data->profile = profile_data($user->uid);
        add_log($uid , "/user/login2" , "login" , "" , 0 , $data["source"] , $data["version"] , "successful" , "user logged in successfully");

        return $login_data;
    }

    add_log($result->uid , "/user/login2" , "login" , "" , 0 , $data["source"] , $data["version"] , "error" , "username or password is wrong!");
    return services_error(t('Wrong username or password!') , 16);
}
function user_resource_register($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/user/register2" , "POST" , $data["source"] , $data["version"]);

    if(!empty($function) && strlen($function) > 0)
        return call_user_func($function, $data);

    return services_error(t('This version is not supported'), 11);
}
function register_v_1($data){
    if(!isset($data['username']) || empty($data['username'])) return services_error(t("Username is required!") , 15);
    if(!isset($data['password']) || empty($data['password'])) return services_error(t("Password is required!") , 15);
    if(!isset($data['email']) || empty($data['email'])) return services_error(t("Email is required!") , 15);
    if(!isset($data['full_name']) || empty($data['full_name'])) return services_error(t("Full name is required!") , 15);
    if(!isset($data['mobile']) || empty($data['mobile'])) return services_error(t("Mobile is required!") , 15);

    $new_user = array(
        'name' => $data['username'],
        'pass' => $data['password'],
        'mail' => $data['email'],
        'status' => 1,
        'init' => $data['email'],
        'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
        ),
        'field_laws' => array('und' => array(0 => array('value' => 1))),
    );

    /*check if user is logged in!*/
    global $user;
    if($user->uid > 0) return services_error(t("User is already logged in!") , 18);

    /*check if this username or email is duplicate*/
    $query = db_select("users", "user");
    $query->fields("user" , array("name"));
    $query->condition('user.name', $new_user['name'] , 'LIKE');
    $result = $query->execute()->fetchObject();
    if(!empty($result)) return services_error(t("A user with this username is already exist!") , 18);
    $query = db_select("users", "user");
    $query->fields("user" , array("mail"));
    $query->condition('user.mail', $new_user['mail'] , 'LIKE');
    $result = $query->execute()->fetchObject();
    if(!empty($result)) return services_error(t("A user with this e-mail is already exist!") , 18);

    /*create new user*/
    $user = user_save('', $new_user);
    /*create profile for new user*/
    $profile = profile2_create(array('type' => 'main', 'uid' => $user->uid));
    $profile->field_full_name['und'][0]['value'] = $data["full_name"];
    $profile->field_mobile['und'][0]['value'] = $data["mobile"];
    profile2_save($profile);

    /*login user*/
    user_login_finalize();
    $newUser = new stdClass();
    $newUser->sessid = session_id();
    $newUser->session_name = session_name();
    $newUser->token = drupal_get_token('services');
    $newUser->user = user_data($user->uid);
    $newUser->profile = profile_data($user->uid);
    add_log($user->uid , "/user/register2" , "register" , "profile2" , $profile->pid, $data["source"] ,$data["version"] , "successful" , "New user register successfully");

    return $newUser;
}

/* It is used for Android App
 * When any user install Android App and logging a token send automatically and saved in database
 * This token is unique for each device
 * Token is used for sending notification
 * Token is saved in "app_notification_token" table
 * Token and UID should be unique together
 */
function user_resource_phone_token($data){
    $function = get_compatible_function_name("/user/phoneToken" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function insert_user_phone_token_v_1($data){
    global $user;
    if(empty($data["uid"]) || empty($data["token"]) || empty($data["serial"])) return services_error("Incomplete Data!" , 15);
    if($user->uid != $data["uid"]) return services_error("Unauthorized Error!" , 18);

    $token = db_select("app_notification_token" , "app_token")->fields("app_token" , array("token"))->condition("serial" , $data["serial"])->condition("uid" , $user->uid)->execute()->fetch();
    /*if the toked saved before return true*/
    if(!empty($token) && strcmp($data["token"] , $token->token) == 0) return true;
    $insert = db_merge("app_notification_token")
        ->key(array('serial' => $data["serial"]))
        ->fields(array(
            'uid' => $user->uid,
            "token" => $data["token"],
            "time" => REQUEST_TIME
        ))
        ->execute();
    if($insert) return true;
    else return services_error(t('Unknown Error!'), 20);
}
/*---------------------relationships part------------------------------*/
function user_resource_purchased_products_list($hash , $uid , $parameter){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    $function = get_compatible_function_name("/user/uid/purchased_products" , "GET" , (isset($parameter["source"])) ? $parameter["source"] : "android" , (isset($parameter["version"])) ? $parameter["version"] : 0);
    if(!empty($function) && strlen($function) > 0){
        $parameter["uid"] = $uid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_purchased_products_list_v_0($parameter){
    $uid = $parameter["uid"];
    global $user;

    if($user->uid != $uid && !in_array('administrator' , $user->roles)) return ["ebook" => array()];

    $query = db_select("m_buyed_nodes", "buyed");
    $query->join("node", "node", "buyed.nid = node.nid and node.type = 'publication' ");
    $query->join("field_data_field_point_needed" , "price" , "node.nid = price.entity_id and price.bundle = 'publication' ");
    $query->leftJoin("profile" , "profile" , "profile.uid = node.uid and profile.type = 'main'");
    $query->join("field_data_field_full_name" , "name" , "name.entity_id = profile.pid and name.bundle = 'main' and name.entity_type = 'profile2' ");
    $query->fields('buyed', array('nid', 'date', 'price'));
    $query->fields('node', array('title' , 'type' , 'uid' , 'changed'));
    $query->addField('price' , 'field_point_needed_value' , 'field_point_needed_value');
    $query->addField('name' , 'field_full_name_value' , 'author_name');
    $query->condition('buyed.uid', $uid);
    $query->condition('buyed.type', 'article');
    $results= $query->execute()->fetchAll();

    if(!empty($results) && count($results) > 0){
        $buyed_nodes = array();
        $nids = array();
        foreach ($results as $result){
            if(empty($result->price) && !empty($result->field_point_needed_value)){
                $result->price =  $result->field_point_needed_value;
            }
            unset($result->field_point_needed_value);

            $buyed_nodes[$result->nid] = $result;
            $buyed_nodes[$result->nid]->files = array();
            array_push($nids , $result->nid);
        }

        $query = db_select("field_data_field_files" , "field_file");
        $query->join("file_managed" , "file" , "field_file.field_files_fid = file.fid and file.filemime = 'application/pdf' ");
        $query->fields('field_file', array('entity_id'));
        $query->fields('file', array('uri' , 'filesize'));
        $query->condition('field_file.entity_id', $nids , 'IN');
        $query->condition('field_file.entity_type', 'node');
        $query->condition('field_file.bundle', 'publication');
        $files = $query->execute()->fetchAll();
        foreach($files as $file){
            $id = $file->entity_id;
            unset($file->entity_id);
            array_push($buyed_nodes[$id]->files , $file);
        }

        $query = db_select("file_managed" , "image");
        $query->join("field_data_field_image" , "field_image" , "image.fid = field_image.field_image_fid and field_image.bundle = 'publication' ");
        $query->addField('image' , 'uri' , 'picture');
        $query->addField('field_image' , 'entity_id' , 'nid');
        $query->condition('field_image.entity_id', $nids , 'IN');
        $results = $query->execute()->fetchAll();
        foreach ($results as $row){
            $buyed_nodes[$row->nid]->picture = $row->picture;
        }

        $query = db_select('field_data_field_pagenumber' , 'page_number');
        $query->addField('page_number' , 'field_pagenumber_value' , 'page_number');
        $query->addField('page_number' , 'entity_id' , 'nid');
        $query->condition('page_number.entity_id' , $nids , 'IN');
        $query->condition('page_number.bundle' , 'publication');
        $results = $query->execute()->fetchAll();
        foreach ($results as $row){
            $buyed_nodes[$row->nid]->page_number = $row->page_number;
        }

        $buyed_ebook = array_values($buyed_nodes);

        return ["ebook" => $buyed_ebook];
    }
    else{
        return ["ebook" => array()];
    }
}
function user_purchased_products_list_v_1($parameter){
    if(!isset($parameter["type"]) || empty($parameter["type"])) return services_error("Error in request!" , 15);
    if(strcmp($parameter["type"] , "publication") == 0) {
        $query = db_select("m_buyed_nodes" , "buyed");
        $query->fields("buyed" , array("nid" , "date"));
        $query->condition('buyed.uid', $parameter["uid"]);
        $query->condition('buyed.type', 'article');
        $custom_list = $query->execute()->fetchCol();
        $bought = $query->execute()->fetchAll();
        if(empty($custom_list)) return array();

        module_load_include("inc" , "custom_services" , "content_resource");
        $param["type"] = $parameter["type"];
        $param["custom_list"] = $custom_list;
        $query = list_of_contents_v_1($param);
        $list = $query->execute()->fetchAll();

        $bought_list = array();
        foreach($list as $row){
            $row->picture = image_style_url("300x300", $row->picture);
            $row->files = array();
            $row->bought_date = 0;
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            $row->price = (int) $row->price;
            unset($row->free_for_vip);
            $bought_list[$row->nid] = $row;
        }
        foreach ($bought as $row) if(isset($bought_list[$row->nid])) $bought_list[$row->nid]->bought_date = (int) $row->date;

        $query = db_select("field_data_field_files" , "field_file");
        $query->join("file_managed" , "file" , "field_file.field_files_fid = file.fid and file.filemime = 'application/pdf' ");
        $query->fields('field_file', array('entity_id'));
        $query->fields('file', array('uri' , 'filesize'));
        $query->condition('field_file.entity_id', $custom_list , "IN");
        $query->condition('field_file.entity_type', 'node');
        $query->condition('field_file.bundle', 'publication');
        $files = $query->execute()->fetchAll();
        foreach($files as $file){
            if(isset($bought_list[$file->entity_id]))
                array_push($bought_list[$file->entity_id]->files , array("uri" => generate_file_address($file->uri) , "filesize" => (int) $file->filesize));
        }
        $bought_list = array_values($bought_list);
        return $bought_list;
    }
    if(strcmp($parameter["type"] , "product") == 0) {
        $query = db_select("uc_orders", "uc_orders");
        $query->join("uc_order_products", "uc_products", "uc_orders.order_id = uc_products.order_id");
        $query->join("node", "node", "uc_products.nid = node.nid and node.type = 'product' ");
        $query->leftJoin("field_data_uc_product_image", "product_image", "product_image.entity_id = node.nid and product_image.delta = '0' and product_image.bundle = 'product' ");
        $query->leftJoin("file_managed", "image", "image.fid = product_image.uc_product_image_fid");
        $query->leftJoin("profile" , "profile" , "node.uid = profile.uid and profile.type = 'main' ");
        $query->leftJoin("field_data_field_full_name" , "author" , "author.entity_id = profile.pid");
        $query->addField('uc_orders', 'created', 'bought_date');
        $query->fields("node", array("type"));
        $query->addField("image", "uri", "picture");
        $query->fields("uc_products", array("nid", "title"));
        $query->addExpression('SUM(uc_products.qty)', 'qty');
        $query->addExpression('SUM(uc_products.price*uc_products.qty)', 'price');
        $query->condition('uc_orders.uid', $parameter["uid"]);
        $query->condition('uc_orders.order_status', array('payment_received', 'completed', 'sent'), 'IN');
        $query->groupBy('uc_products.nid');
        $query->orderBy('uc_orders.created', 'DESC');
        $products = $query->execute()->fetchAll();
        foreach ($products as $product){
            $product->picture = (!empty($product->picture)) ? image_style_url("200x200" , $product->picture) : "";
        }
        return $products;
    }
    if(strcmp($parameter["type"] , "college") == 0) {
        $query = db_select("uc_orders", "uc_orders");
        $query->join("uc_order_products", "uc_products", "uc_orders.order_id = uc_products.order_id");
        $query->join("node", "node", "uc_products.nid = node.nid and node.type = 'college' ");
        $query->leftJoin("field_data_field_image", "field_image", "field_image.entity_id = node.nid and field_image.bundle = 'college' ");
        $query->leftJoin("file_managed", "image", "image.fid = field_image.field_image_fid");
        $query->leftJoin("profile" , "profile" , "node.uid = profile.uid and profile.type = 'main' ");
        $query->leftJoin("field_data_field_full_name" , "author" , "author.entity_id = profile.pid");
        $query->addField('uc_orders', 'created', 'bought_date');
        $query->fields("node", array("type"));
        $query->addField("image", "uri", "picture");
        $query->fields("uc_products", array("nid", "title"));
        $query->addField("author" , "field_full_name_value" , "author");
        $query->addExpression('SUM(uc_products.qty)', 'qty');
        $query->addExpression('SUM(uc_products.price*uc_products.qty)', 'price');
        $query->condition('uc_orders.uid', $parameter["uid"]);
        $query->condition('uc_orders.order_status', array('payment_received', 'completed', 'sent'), 'IN');
        $query->groupBy('uc_products.nid');
        $query->orderBy('uc_orders.created', 'DESC');
        $colleges = $query->execute()->fetchAll();
        foreach ($colleges as $college){
            if(!empty($college->picture)) $college->picture = image_style_url("200x200" , $college->picture);
            $college->nid = (int) $college->nid;
            $college->bought_date = (int) $college->bought_date;
            $college->qty = (int) $college->qty;
            $college->price = (int) $college->price;
        }
        return $colleges;
    }
    return array();
}
function user_purchased_products_list_desktop_v_1($parameter){
    global $user;
    if($user->uid != $parameter["uid"]) return services_error("Permission denied!" , 401);
    /* find the products that user purchased
     * order status IN ("completed" , "payment_received" , "sent")
     * product type IN ("product" , "college")
     * fields ("nid" , "title" , "type" , "author name" , "author picture" , "order time" , "order total price")
     */
    $query = db_select("uc_orders" , "orders");
    $query->join("uc_order_products" , "order_product" , "orders.order_id = order_product.order_id");
    $query->join("node" , "node" , "order_product.nid = node.nid and node.status = '1' ");
    $query->join("users" , "user" , "user.uid = node.uid");
    $query->join("profile" , "profile" , "profile.uid = user.uid and profile.type = 'main' ");
    $query->join("field_data_field_full_name" , "author" , "author.entity_id = profile.pid and author.entity_type = 'profile2' and author.bundle = 'main' ");
    $query->leftJoin("field_data_uc_product_image" , "product_image" , "product_image.entity_id = node.nid and product_image.bundle = 'product' ");
    $query->leftJoin("file_managed" , "image" , "image.fid = product_image.uc_product_image_fid");
    $query->fields("node" , array("nid" , "title" , "type"));
    $query->fields("orders" , array("modified" , "order_total"));
    $query->addField("author" , "field_full_name_value" , "author");
    $query->addField("image" , "uri" , "picture");
    $query->condition("orders.order_status" , array("completed" , "payment_received" , "sent") , "IN");
    $query->condition("orders.uid" , $user->uid);
    $query->condition("node.type" , array("product" , "college" , "product_kit") , "IN");
    $products = $query->execute()->fetchAll();
    $nids = array();
    $return_products = array();
    foreach ($products as $product){
        array_push($nids , $product->nid);
        $product->nid = (int) $product->nid;
        $product->order_time = (int) $product->modified;
        unset($product->modified);
        $product->price = round($product->order_total);
        unset($product->order_total);
        if(!empty($product->picture)) $product->picture = image_style_url("200x200" , $product->picture);
        $product->files = array();
        $return_products[$product->nid] = $product;
    }
    /* find the locked files for each product and attach them */
    if(!empty($nids)) {
        $query = db_select("field_data_field_locked_files", "locked_files");
        $query->join("file_managed", "files", "files.fid = locked_files.field_locked_files_fid");
        $query->join("desktop_lock_encryption", "info", "files.fid = info.fid and info.active = '1' ");
        $query->fields("files", array("uri", "filesize"));
        $query->fields("locked_files", array("entity_id"));
        $query->fields("info", array("title", "name", "password", "new_name"));
        $query->condition("locked_files.entity_type", "node");
        $query->condition("locked_files.bundle", "product");
        $query->condition("locked_files.entity_id", $nids, "IN");
        $locked_files = $query->execute()->fetchAll();
        foreach ($locked_files as $file) {
            array_push($return_products[$file->entity_id]->files, array(
                    "url" => generate_file_address($file->uri),
                    "filesize" => (int)$file->filesize,
                    "title" => $file->title,
                    "name" => $file->name,
                    "new_name" => $file->new_name,
                    "password" => $file->password,
                )
            );
        }

        $products = array_values($return_products);
    }
    /*
     * prepare the response
     * categorize the products with their type
     */
    $response = array("product" => array(), "college" => array() , "product_kit" => array());
    foreach ($products as $product){
        $type = $product->type;
        unset($product->type);
        array_push($response[$type] , $product);
    }

    return $response;
}

function user_resource_bookmark_contents_list($uid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/user/uid/bookmarks" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["uid"] = $uid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_bookmark_contents_list_v_1($parameter){
    if(!isset($parameter["type"]) || empty($parameter["type"])) return services_error("Error in request!" , 15);
    global $user;

    $query = db_select("flagging", "flagging");
    $query->fields("flagging", array("entity_id"));
    $query->condition('flagging.uid', $parameter["uid"]);
    $query->condition('flagging.fid', 1);
    $custom_list = $query->execute()->fetchCol();
    if (empty($custom_list)) return array();
    module_load_include("inc", "custom_services", "content_resource");
    $param["type"] = $parameter["type"];
    $param["custom_list"] = $custom_list;
    $query = list_of_contents_v_1($param);
    $list = $query->execute()->fetchAll();
    if(empty($list)) return array();
    $festival_setting = festivals();
    if(strcmp($parameter["type"] , "publication") == 0) {
        $permission = array();
        $query = db_select('m_buyed_nodes', 'buyed');
        $query->fields('buyed', array('nid'));
        $query->condition('buyed.uid', $parameter["uid"]);
        $query->condition('buyed.nid', $custom_list , "IN");
        $bought = $query->execute()->fetchCol();
        $permission = array_merge($permission , $bought);

        $vip = false;
        if (in_array('Vip', $user->roles)) $vip = true;

        if($vip) {
            $query = db_select('field_data_field_isvip', 'vip');
            $query->fields('vip', array('entity_id'));
            $query->condition('vip.entity_id', $custom_list, "IN");
            $query->condition('vip.bundle', 'publication');
            $query->condition('vip.field_isvip_tid', 1760);
            $permission = array_merge($permission , $query->execute()->fetchCol());
        }
        $bookmark_list = array();
        foreach ($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);
            $row->files = array();
            if($row->price == 0) array_push($permission, $row->nid);
            if(in_array($row->nid , $permission)) $row->bought = true;
            else $row->bought = false;

            $row->price = (int) $row->price;
            $row->original_price = $row->price;

            if (empty($row->free_for_vip)) $free_for_vip = false;
            else $free_for_vip = true;
            unset($row->free_for_vip);

            $discount = new stdClass();
            if($row->price != 0){
                /*this is used for discount on festival*/
                $festival = $festival_setting["publication"]["festival"];

                if ($vip && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "enable" => true, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                    $row->price = 0;
                }
                elseif ($vip && !$free_for_vip && !$festival) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
                    $row->price = 0.9 * $row->price;
                }
                elseif (!$vip && !$festival && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "name" => "vip", "enable" => false, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                }
                elseif (!$vip && !$festival && !$free_for_vip) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
                }
                elseif ($festival) {
                    $discount = array("name" => "festival", "color" => 1, "enable" => true, "amount" => $festival_setting["publication"]["price"], "message" => $festival_setting["publication"]["message"]);
                    $row->price = (1 - $festival_setting["publication"]["price"]) * $row->price;
                }
            }
            $row->discount = $discount;

            $bookmark_list[$row->nid] = $row;
        }

        if(!empty($permission)) {
            $query = db_select("field_data_field_files", "field_file");
            $query->join("file_managed", "file", "field_file.field_files_fid = file.fid and file.filemime = 'application/pdf' ");
            $query->fields('field_file', array('entity_id'));
            $query->fields('file', array('uri', 'filesize'));
            $query->condition('field_file.entity_id', $permission, "IN");
            $query->condition('field_file.entity_type', 'node');
            $query->condition('field_file.bundle', 'publication');
            $files = $query->execute()->fetchAll();

            foreach ($files as $file) {
                array_push($bookmark_list[$file->entity_id]->files, array("uri" => generate_file_address($file->uri) , "filesize" => (int) $file->filesize));
            }
        }
        $bookmark_list = array_values($bookmark_list);
        return $bookmark_list;
    }
    if(strcmp($parameter["type"] , "podcast") == 0){
        foreach ($list as $row) {
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->audio_size = (int) $row->audio_size;
            $row->changed = (int) $row->changed;
            $row->audio = generate_file_address($row->audio);
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);
        }
        return $list;
    }
    if(strcmp($parameter["type"] , "college") == 0){
        $subquery = db_select("uc_product_options" , "product_options");
        $subquery->join("node" , "node" , " node.nid = product_options.nid and node.type = 'college' ");
        $subquery->fields("product_options" , array("nid" , "oid" , "cost" , "price"));
        $subquery->condition("product_options.nid" , $custom_list , "IN");
        $options = $subquery->execute()->fetchAll();
        $opt_cost = array();
        $opt_price = array();
        foreach ($options as $option){
            if(!empty($price[$option->nid])) $opt_price[$option->nid] += $option->price; else $opt_price[$option->nid] = $option->price;
            if(!empty($cost[$option->nid])) $opt_cost[$option->nid] += $option->cost; else $opt_cost[$option->nid] = $option->cost;
        }

        foreach ($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            $row->list_price = (int) $row->list_price;
            $row->sell_price = (int) $row->sell_price;

            $row->picture = image_style_url("300x300", $row->picture);
            $row->picture_s = image_style_url("350x350", $row->picture_s);

            $festival = $festival_setting["college"]["festival"];
            $off = false;
            if($opt_price[$row->nid] < $opt_cost[$row->nid] || $row->sell_price < $row->list_price) $off = true;
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["college"]["price"], "message" => $festival_setting["college"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            $row->discount = $discount;

            switch ($row->college_step){
                case "0" :
                    $row->college_step = array("id" => 0 , "state" => "در حال ثبت نام");
                    break;
                case "1" :
                    $row->college_step = array("id" => 1 , "state" => "در حال برگزاری");
                    break;
                case "2" :
                    $row->college_step = array("id" => 2 , "state" => "برگزار شده");
                    break;
            }
        }
        return $list;
    }

    return array();
}
function user_bookmark_contents_list_v_2($parameter){
    if(!isset($parameter["type"]) || empty($parameter["type"])) return services_error("Error in request!" , 15);
    global $user;

    $query = db_select("flagging", "flagging");
    $query->fields("flagging", array("entity_id"));
    $query->condition('flagging.uid', $parameter["uid"]);
    $query->condition('flagging.fid', 1);
    $custom_list = $query->execute()->fetchCol();
    if (empty($custom_list)) return array();
    module_load_include("inc", "custom_services", "content_resource");
    $param["type"] = $parameter["type"];
    $param["custom_list"] = $custom_list;
    $query = list_of_contents_v_2($param);
    $list = $query->execute()->fetchAll();
    if(empty($list)) return array();

    $festival_setting = festivals();
    if(strcmp($parameter["type"] , "publication") == 0) {
        $permission = array();
        $query = db_select('m_buyed_nodes', 'buyed');
        $query->fields('buyed', array('nid'));
        $query->condition('buyed.uid', $parameter["uid"]);
        $query->condition('buyed.nid', $custom_list , "IN");
        $bought = $query->execute()->fetchCol();
        $permission = array_merge($permission , $bought);

        $vip = false;
        if (in_array('Vip', $user->roles)) $vip = true;

        if($vip) {
            $query = db_select('field_data_field_isvip', 'vip');
            $query->fields('vip', array('entity_id'));
            $query->condition('vip.entity_id', $custom_list, "IN");
            $query->condition('vip.bundle', 'publication');
            $query->condition('vip.field_isvip_tid', 1760);
            $permission = array_merge($permission , $query->execute()->fetchCol());
        }
        $bookmark_list = array();
        foreach ($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);
            $row->files = array();
            if($row->price == 0) array_push($permission, $row->nid);
            if(in_array($row->nid , $permission)) $row->bought = true;
            else $row->bought = false;

            $row->price = (int) $row->price;
            $row->original_price = $row->price;

            if (empty($row->free_for_vip)) $free_for_vip = false;
            else $free_for_vip = true;
            unset($row->free_for_vip);

            $discount = new stdClass();
            if($row->price != 0){
                /*this is used for discount on festival*/
                $festival = $festival_setting["publication"]["festival"];

                if ($vip && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "enable" => true, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                    $row->price = 0;
                }
                elseif ($vip && !$free_for_vip && !$festival) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
                    $row->price = 0.9 * $row->price;
                }
                elseif (!$vip && !$festival && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "name" => "vip", "enable" => false, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                }
                elseif (!$vip && !$festival && !$free_for_vip) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
                }
                elseif ($festival) {
                    $discount = array("name" => "festival", "color" => 1, "enable" => true, "amount" => $festival_setting["publication"]["price"], "message" => $festival_setting["publication"]["message"]);
                    $row->price = (1 - $festival_setting["publication"]["price"]) * $row->price;
                }
            }
            $row->discount = $discount;

            $bookmark_list[$row->nid] = $row;
        }

        if(!empty($permission)) {
            $query = db_select("field_data_field_files", "field_file");
            $query->join("file_managed", "file", "field_file.field_files_fid = file.fid and file.filemime = 'application/pdf' ");
            $query->fields('field_file', array('entity_id'));
            $query->fields('file', array('uri', 'filesize'));
            $query->condition('field_file.entity_id', $permission, "IN");
            $query->condition('field_file.entity_type', 'node');
            $query->condition('field_file.bundle', 'publication');
            $files = $query->execute()->fetchAll();

            foreach ($files as $file) {
                array_push($bookmark_list[$file->entity_id]->files, array("uri" => generate_file_address($file->uri) , "filesize" => (int) $file->filesize));
            }
        }
        $bookmark_list = array_values($bookmark_list);
        return $bookmark_list;
    }
    if(strcmp($parameter["type"] , "podcast") == 0){
        foreach ($list as $row) {
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->audio_size = (int) $row->audio_size;
            $row->changed = (int) $row->changed;
            $row->audio = generate_file_address($row->audio);
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);
        }
        return $list;
    }
    if(strcmp($parameter["type"] , "college") == 0){
        $subquery = db_select("uc_product_options" , "product_options");
        $subquery->join("node" , "node" , " node.nid = product_options.nid and node.type = 'college' ");
        $subquery->fields("product_options" , array("nid" , "oid" , "cost" , "price"));
        $subquery->condition("product_options.nid" , $custom_list , "IN");
        $options = $subquery->execute()->fetchAll();
        $opt_cost = array();
        $opt_price = array();
        foreach ($options as $option){
            if(!empty($price[$option->nid])) $opt_price[$option->nid] += $option->price; else $opt_price[$option->nid] = $option->price;
            if(!empty($cost[$option->nid])) $opt_cost[$option->nid] += $option->cost; else $opt_cost[$option->nid] = $option->cost;
        }

        foreach ($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            $row->list_price = (int) $row->list_price;
            $row->sell_price = (int) $row->sell_price;

            $row->picture = image_style_url("300x300", $row->picture);
            $row->picture_s = image_style_url("350x350", $row->picture_s);

            $festival = $festival_setting["college"]["festival"];
            $off = false;
            if($opt_price[$row->nid] < $opt_cost[$row->nid] || $row->sell_price < $row->list_price) $off = true;
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["college"]["price"], "message" => $festival_setting["college"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            $row->discount = $discount;

            switch ($row->college_step){
                case "0" :
                    $row->college_step = array("id" => 0 , "state" => "در حال ثبت نام");
                    break;
                case "1" :
                    $row->college_step = array("id" => 1 , "state" => "در حال برگزاری");
                    break;
                case "2" :
                    $row->college_step = array("id" => 2 , "state" => "برگزار شده");
                    break;
            }
        }
        return $list;
    }
    if(strcmp($parameter["type"] , "education") == 0){
        foreach($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);
        }

        return $list;
    }
    if(strcmp($parameter["type"] , "product_kit") == 0){
        foreach ($list as $row){
            $row->nid = (int) $row->nid;
            $row->uid = (int) $row->uid;
            $row->changed = (int) $row->changed;
            if(isset($row->picture) && !empty($row->picture)) $row->picture = image_style_url("300x300", $row->picture);
            if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350", $row->picture_s);


            $row->list_price = (int) $row->list_price;
            $row->sell_price = (int) $row->sell_price;

            $catalog = empty($row->catalog) ? false : true;
            $vip = false;
            if (in_array("Vip", $user->roles)) $vip = true;
            unset($row->catalog);

            $off = ($row->sell_price < $row->list_price) ? true : false;
            $festival = $festival_setting["product_kit"]["festival"];
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["product_kit"]["price"], "message" => $festival_setting["product_kit"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            elseif($catalog && $vip){
                $row->sell_price = 0.9 * $row->sell_price;
                $discount = array("name" => "vip", "color" => 2, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            elseif($catalog && !$vip){
                $discount = array("name" => "vip", "color" => 4, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            $row->discount = $discount;
        }
        return $list;
    }
    return array();
}
function user_bookmark_contents_list_desktop_v_1($parameter){
    global $user;
    if($user->uid != $parameter["uid"]) return services_error("Permission denied!" , 401);
    $response = array(
        "article" => array(),
        "blog" => array(),
        "college" => array(),
        "designteam" => array(),
        "education" => array(),
        "film" => array(),
        "gallerynew" => array(),
        "podcast" => array(),
        "product" => array(),
        "product_kit" => array(),
        "publication" => array(),
        "pedia" => array(),
        );

    /*list of contents that user bookmarked*/
    $query = db_select("flagging", "flagging");
    $query->join("node" , "node" , "node.nid = flagging.entity_id and node.status ='1' ");

    $query->leftJoin("field_data_uc_product_image" , "p_field_image" , "p_field_image.entity_id = node.nid and p_field_image.entity_type = 'node' and p_field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "p_image" , "p_image.fid = p_field_image.uc_product_image_fid");
    $query->addField("p_image" , "uri" , "p_image");

    $query->leftJoin("field_data_field_image" , "c_field_image" , "c_field_image.entity_id = node.nid and c_field_image.entity_type = 'node' and c_field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "c_image" , "c_image.fid = c_field_image.field_image_fid ");
    $query->addField("c_image" , "uri" , "c_image");

    $query->fields("node" , array("nid" , "type" , "title"));
    $query->condition('flagging.uid', $parameter["uid"]);
    $query->condition('flagging.fid', 1);
    $bookmarks = $query->execute()->fetchAll();

    /*categorize nodes with their types*/
    foreach ($bookmarks as $bookmark){
        $bookmark->url = "https://civil808.com/node/" . $bookmark->nid;
        $bookmark->nid = (int) $bookmark->nid;

        if(!empty($bookmark->p_image)) $bookmark->picture = image_style_url("400x225" , $bookmark->p_image);
        elseif(!empty($bookmark->c_image)) $bookmark->picture = image_style_url("400x225" , $bookmark->c_image);
        else $bookmark->picture = null;
        unset($bookmark->p_image);
        unset($bookmark->c_image);
        $type = $bookmark->type;
        unset($bookmark->type);
        array_push($response[$type] , $bookmark);
    }

    /*list of taxonomies that user bookmarked*/
    $query = db_select("flagging", "flagging");
    $query->join("taxonomy_term_data" , "term" , "term.tid = flagging.entity_id and term.vid = '28' ");
    $query->leftJoin("field_data_field_image" , "field_image" , "field_image.entity_id = term.tid and field_image.entity_type = 'taxonomy_term' ");
    $query->leftJoin("file_managed" , "image" , "image.fid = field_image.field_image_fid ");
    $query->condition("flagging.fid" , 4);
    $query->condition('flagging.uid', $parameter["uid"]);
    $query->fields("term" , array("tid" , "name"));
    $query->addField("image" , "uri" , "picture");
    $tbookmarks = $query->execute()->fetchAll();
    if(!empty($tbookmarks)) {
        foreach ($tbookmarks as $tbookmark) {
            $tbookmark->url = "https://civil808.com/taxonomy/term/" . $tbookmark->tid;
            $tbookmark->nid = (int)$tbookmark->tid;
            unset($tbookmark->tid);
            $tbookmark->title = $tbookmark->name;
            unset($tbookmark->name);
            if (!empty($tbookmark->picture)) $tbookmark->picture = image_style_url("400x225", $tbookmark->image);
            array_push($response["pedia"], $tbookmark);
        }
    }

    return $response;
}

function user_resource_login_check($url , $parameter){
    global $user;
    return array("uid" => (int)$user->uid);
}
/*---------------------functions part----------------------------------*/
function profile_data($uid){
    $query = db_select("profile" , "profile");
    $query->leftJoin("field_data_field_full_name" , "full_name" , "profile.pid = full_name.entity_id and full_name.entity_type='profile2' and full_name.bundle='main' ");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "profile.pid = about_me.entity_id and about_me.entity_type='profile2' and about_me.bundle='main' ");
    $query->leftJoin("field_data_field_skills" , "skills" , "profile.pid = skills.entity_id and skills.entity_type='profile2' and skills.bundle='main' ");
    $query->leftJoin("field_data_field_university" , "university" , "profile.pid = university.entity_id and university.entity_type='profile2' and university.bundle='main' ");
    $query->leftJoin("field_data_field_education_field" , "education_field" , "profile.pid = education_field.entity_id and education_field.entity_type='profile2' and education_field.bundle='main' ");
    $query->leftJoin("field_data_field_education_degree" , "education_degree" , "profile.pid = education_degree.entity_id and education_degree.entity_type='profile2' and education_degree.bundle='main' ");
    $query->leftJoin("field_data_field_mobile" , "mobile" , "profile.pid = mobile.entity_id and mobile.entity_type='profile2' and mobile.bundle='main' ");
    $query->leftJoin("field_data_field_job" , "job" , "profile.pid = job.entity_id and job.entity_type='profile2' and job.bundle='main' ");
    $query->fields("profile" , array("pid"));
    $query->addField("full_name" , "field_full_name_value" , "full_name");
    $query->addField("about_me" , "field_about_me_value" , "about_me");
    $query->addField("skills" , "field_skills_value" , "skills");
    $query->addField("university" , "field_university_value" , "university");
    $query->addField("education_field" , "field_education_field_value" , "education_field");
    $query->addField("education_degree" , "field_education_degree_value" , "education_degree");
    $query->addField("mobile" , "field_mobile_value" , "mobile");
    $query->addField("job" , "field_job_value" , "job");
    $query->condition("profile.uid" , $uid);
    $query->condition("profile.type" , "main");
    $profile = $query->execute()->fetch();

    $profile->user_point = userpoints_get_current_points($uid, 'all');

    $query = db_select("field_data_field_image" , "image");
    $query->join("file_managed" , "file" , "file.fid = image.field_image_fid");
    $query->fields("file" , array("uri"));
    $query->condition("image.entity_id" , $profile->pid);
    $query->condition("image.entity_type" , "profile2");
    $result = $query->execute()->fetch();
    if(!empty($result)) $profile->background_image = image_style_url("1360x500_blur", $result->uri);
    else $profile->background_image = null;

    $profile->pid = (int) $profile->pid;

    $query = db_select("field_data_field_experts" , "expert");
    $query->join("taxonomy_term_data" , "term" , "expert.field_experts_tid = term.tid");
    $query->join("field_data_field_bool" , "bool" , "bool.entity_id = term.tid and bool.bundle = 'expert' and bool.entity_type = 'taxonomy_term' and bool.field_bool_value = '1' ");
    $query->condition("expert.entity_id" , $profile->pid);
    $query->condition("expert.entity_type" , "profile2");
    $query->condition("expert.bundle" , "main");
    $query->fields("term" , array("tid" , "name"));
    $experts = $query->execute()->fetchAll();
    $profile->experts = array();
    foreach ($experts as $expert){
        array_push($profile->experts, array($expert->tid => $expert->name));
    }

    unset($profile->pid);
    return $profile;
}
function user_data($uid){
    $query = db_select('users' , 'user');
    $query->fields('user' , array('uid' , 'name' , 'mail' , 'created' , 'login' , 'picture'));
    $query->condition('user.uid' , $uid);
    $user = $query->execute()->fetch();
    if(empty($user)) return services_error("User is not exist!" , 16);

    $query = db_select("file_managed" , "file_managed");
    $query->fields("file_managed", array("uri"));
    $query->condition("file_managed.fid", $user->picture);
    $result = $query->execute()->fetch();
    if(!empty($result)) $user->picture = image_style_url("200x200", $result->uri);
    else $user->picture = null;

    $query = db_select('users_roles' , 'user_role');
    $query->join('role' , 'role' , 'user_role.rid = role.rid');
    $query->fields('role', array('rid' , 'name'));
    $query->condition('user_role.uid' , $uid);
    $results = $query->execute()->fetchAll();

    $roles = array("2" => "کاربر شناخته شده");
    foreach ($results as $result) {
        $roles[$result->rid] = $result->name;
    }
    $user->roles = $roles;

    $user->uid = (int) $user->uid;
    $user->created = (int) $user->created;
    $user->login = (int) $user->login;

    return $user;
}