<?php

/*---------------------operations part---------------------------------*/
function user_resource_update($uid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "user"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    global $user;
    if($user->uid != $uid && !in_array("administrator" , $user->roles)) return services_error("You do not have authorization for this action!" , 18);

    $function = get_compatible_function_name("/user/uid" , "PUT" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["uid"] = $uid;
        $data["updater_id"] = $user->uid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_update_v_1($data){
    $user = user_load($data["uid"]);
    $profile = profile2_load_by_user($user , "main");
    $user_update = false;
    $profile_update = false;

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
        $user->picture = (object)$data["picture"];
        $user_update = true;
    }
    if(isset($data["background_image"]) && !empty($data["background_image"]) && strcmp($data["background_image"]["type"] , "image") == 0){
        $user->field_image['und']['0'] = $data["background_image"];
        $user_update = true;
    }
    if($user_update){
        user_save($user);
        add_log($data["updater_id"], "/user/uid" , "update" , "user" , $user->uid , $data["source"] , $data["version"] , "successful" , "update user data");
    }

    if(isset($data["full_name"]) && !empty($data["full_name"])){
        $profile->field_full_name['und'][0]['value'] = $data['full_name'];
        $profile_update = true;
    }
    if(isset($data["about_me"]) && !empty($data["about_me"])){
        $profile->field_about_me['und'][0]['value'] = $data['about_me'];
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
        add_log($data["updater_id"], "/user/uid" , "update" , "profile2" , $profile->pid , $data["source"] , $data["version"] , "successful" , "update profile data");
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

        $login_data->log = add_log($uid , "/user/login2" , "login" , "" , 0 , $data["source"] , $data["version"] , "successful" , "user logged in successfully");

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
    $query->fields("user" , array("name" , "mail"));
    $db_or = db_or();
    $db_or->condition('user.name', $new_user['name'] , 'LIKE');
    $db_or->condition('user.mail', $new_user['mail'] , 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchObject();
    if(!empty($result)) return services_error(t("A user with this username Email is already exist!") , 18);

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
    $newUser->log = add_log($user->uid , "/user/register2" , "register" , "profile2" , $profile->pid, $data["source"] ,$data["version"] , "successful" , "New user register successfully");

    return $newUser;
}
/*---------------------relationships part------------------------------*/
function user_resource_purchased_products_list($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of__user_purchased_products_version_one($uid);
    }
    return services_error(t('This version is not supported'), 11);
}
function list_of__user_purchased_products_version_one($uid){
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
    $profile = $query->execute()->fetch();

    $profile->user_point = userpoints_get_current_points($uid, 'all');

    $query = db_select("field_data_field_image" , "image");
    $query->join("file_managed" , "file" , "file.fid = image.field_image_fid");
    $query->fields("file" , array("uri"));
    $query->condition("image.entity_id" , $profile->pid);
    $query->condition("image.entity_type" , "profile2");
    $result = $query->execute()->fetch();
    if(!empty($result)) $profile->background_image = image_style_url("1360x500_blur", $result->uri);

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

    $query = db_select('users_roles' , 'user_role');
    $query->join('role' , 'role' , 'user_role.rid = role.rid');
    $query->fields('role', array('rid' , 'name'));
    $query->condition('user_role.uid' , $uid);
    $results = $query->execute()->fetchAll();
    $roles = array();
    foreach ($results as $result) {
        $roles[$result->rid] = $result->name;
    }
    $user->roles = $roles;

    return $user;
}