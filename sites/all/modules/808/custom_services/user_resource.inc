<?php

/*---------------------actions part------------------------------------*/
function user_resource_login($hash , $username_email, $password , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);

    $login_user = login($username_email, $password);
    if(strcmp($version , "pbd_0") == 0){
        unset($login_user->user);
        return (array)$login_user;
    }
    if(strcmp($version , "android_0") == 0){
        $profile = profile_data($login_user->user);
        unset($login_user->user);
        $login_user = array_merge((array) $login_user, (array) $profile);
        return $login_user;
    }
    return services_error(t('This version is not supported'), 11);
}
function user_resource_register($hash , $data, $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);

    if(!isset($data['username']) || empty($data['username'])) return services_error(t("Username is required!") , 15);
    if(!isset($data['password']) || empty($data['password'])) return services_error(t("Password is required!") , 15);
    if(!isset($data['email']) || empty($data['email'])) return services_error(t("Email is required!") , 15);
    if(!isset($data['full_name']) || empty($data['full_name'])) return services_error(t("Email is required!") , 15);

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

    if(strcmp($version , "pbd_0") == 0){
        $new_user["language"] = "en";
        $register = register($new_user , $data['full_name']);
        unset($register->user);
        unset($register->profile);
        return (array) $register;
    }
    if(strcmp($version , "android_0") == 0){
        if(!isset($data['mobile']) || empty($data['mobile'])) return services_error(t("Mobile is required!") , 15);

        $register = register($new_user , $data['full_name']);

        update_user_main_profile($register->user->uid , array("mobile" => $data["mobile"]));

        $profile = profile_data($register->user->uid);
        unset($register->user);
        unset($register->profile);
        $register = array_merge((array)$register , (array)$profile);
        return $register;
    }

    return services_error(t('This version is not supported'), 11);
}
function user_resource_exist($hash  , $data , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        $query = db_select("users", "user");
        $query->fields("user" , array("name" , "mail"));
        if(isset($data["username"]) && strlen($data["username"]) > 0) $query->condition('user.name', $data['username'] , 'LIKE');
        elseif(isset($data["email"]) && strlen($data["email"]) > 0) $query->condition('user.mail', $data['email'] , 'LIKE');
        else return services_error(t('The username or email is required!'), 15);
        $result = $query->execute()->fetchObject();
        if(!empty($result)) return true;
        else return false;
    }
    return services_error(t('This version is not supported'), 11);
}

/*---------------------target action part------------------------------------*/
function user_resource_edit_profile($hash , $uid , $data , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);

    global $user;
    if($user->uid != $uid) return services_error(t('You do not have permission for this action!'), 18);

    if($version == 0){
        if(isset($data["type"]) && strcmp($data["type"] , "main") == 0) return update_user_main_profile($uid , $data);
        else return services_error(t('This profile type is not supported'), 12);

    }
    return services_error(t('This version is not supported'), 11);
}
function user_resource_edit_data($hash , $uid , $data , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    global $user;
    if($user->uid != $uid) return services_error(t('You do not have permission for this action!'), 18);
    if($version == 0){
        return update_user_data($uid , $data);
    }
    return services_error(t('This version is not supported'), 11);
}

/*---------------------relationships part------------------------------*/
function user_resource_purchased_products_list($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of__user_purchased_products_version_one($uid);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_profile_data($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return profile_data($uid);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_nav_bar_info($hash , $login , $version){
    if(!(hash_true($hash , "user"))) return services_error(t('Failed to access'), 10);
    if($version == "pbd_0"){
        global $user;
        $query = db_select("file_managed" , "picture");
        $query->fields("picture" , array("uri"));
        $query->condition("picture.fid" , $user->picture);
        $picture = $query->execute()->fetch();

        $result = array();
        $result["uid"] = $user->uid;
        $result["username"] = $user->name;
        $result["picture"] = (!empty($picture)) ? image_style_url("200x200", $picture->uri) : "";
        return $result;
    }
    return services_error(t('This version is not supported'), 11);
}

/*---------------------functions part----------------------------------*/
function login($username_email, $password){
    /*check if user is login or not*/
    global $user;
    if ($user->uid > 0) {
        return services_error(t("User is already logged in!") , 18);
    }

    /*check if user is exist and unblocked*/
    $query =  db_select('users' , 'user');
    $query->fields('user', array('name' , 'status'));
    $db_or = db_or();
    $db_or->condition('user.name', $username_email , 'LIKE');
    $db_or->condition('user.mail', $username_email , 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchObject();
    if(empty($result)){
        return services_error(t("User is not exist!") , 17);
    }
    elseif($result->status == 0){
        return  services_error(t("User is inactive!") , 18);
    }
    else{
        $username = $result->name;
    }

    /*check the truth of username and password*/
    $uid = user_authenticate($username, $password);

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
        return $login_data;
    }
    return services_error(t('Wrong username or password!') , 16);
}

/**
 * @param array
 * @param string
 * param $new_user
 * @return object
 * return login data
 */
function register($new_user , $full_name){
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
    $profile->field_full_name['und'][0]['value'] = $full_name;
    profile2_save($profile);

    /*login user*/
    user_login_finalize();
    $newUser = new stdClass();
    $newUser->sessid = session_id();
    $newUser->session_name = session_name();
    $newUser->token = drupal_get_token('services');
    $newUser->user = $user;
    $newUser->profile = $profile;

    return $newUser;
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

function update_user_main_profile($uid , $data){
    $profile = profile2_by_uid_load($uid , "main");
    if(isset($data["full_name"]) && !empty($data["full_name"])){
        $profile->field_full_name['und'][0]['value'] = $data['full_name'];
    }
    if(isset($data["about_me"]) && !empty($data["about_me"])){
        $profile->field_about_me['und'][0]['value'] = $data['about_me'];;
    }
    if(isset($data["skills"]) && !empty($data["skills"])){
        $profile->field_skills['und'][0]['value'] = $data['skills'];
    }
    if(isset($data["university"]) && !empty($data["university"])){
        $profile->field_university['und'][0]['value'] = $data['university'];
    }
    if(isset($data["education"]) && !empty($data["education"])){
        $profile->field_education_field['und'][0]['value'] = $data['education'];
    }
    if(isset($data["education_degree"]) && !empty($data["education_degree"])){
        $profile->field_education_degree['und'][0]['value'] = $data['education_degree'];
    }
    if(isset($data["mobile"]) && !empty($data["mobile"])){
        $profile->field_mobile['und'][0]['value'] = $data['mobile'];
    }
    if(isset($data["job"]) && !empty($data["job"])){
        $profile->field_job['und'][0]['value'] = $data['job'];
    }
    if(isset($data["job_place"]) && !empty($data["job_place"])){
        $profile->field_job_place['und'][0]['value'] = $data['job_place'];
    }
    if(isset($data["job_title"]) && !empty($data["job_title"])){
        $profile->field_job_title['und'][0]['value'] = $data['job_title'];
    }
    if(isset($data["address"]) && !empty($data["address"])){
        $profile->field_address['und'][0]['value'] = $data['address'];
    }
    profile2_save($profile);
    return $profile;
}

function update_user_data($uid , $data){
    $user = user_load($uid);
    if(isset($data["username"]) && !empty($data["username"])){
        $query = db_select("users" , "user");
        $query->fields("user" , array("name"));
        $query->condition("user.name" , $data["username"]);
        $result = $query->execute()->fetch();
        if(empty($result)) $user->name = $data["username"];
        else return services_error(t("This username is already taken!") , 18);
    }
    if(isset($data["email"]) && !empty($data["email"])){
        $query = db_select("users" , "user");
        $query->fields("user" , array("mail"));
        $query->condition("user.mail" , $data["email"]);
        $result = $query->execute()->fetch();
        if(empty($result)) $user->mail = $data["email"];
        else return services_error(t("This Email is already taken!") , 18);
    }
    if(isset($data["password"]) && !empty($data["password"])){
        if(strlen($data["password"]) < 6) return services_error(t("The password should be at least 6 character!") , 16);
        require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
        $user->pass = user_hash_password(trim($data['password']));
    }
    if(isset($data["picture"]) && !empty($data["picture"]) && strcmp($data["picture"]["type"] , "image") == 0){
        $user->picture = (object)$data["picture"];
    }
    if(isset($data["background_image"]) && !empty($data["background_image"]) && strcmp($data["background_image"]["type"] , "image") == 0){
        $user->field_image['und']['0'] = $data["background_image"];
    }
    user_save($user);
    return true;
}

function profile_data($user){
    if(!is_object($user))
        $user = user_data($user);

    $profile = $user;

    $query = db_select("profile" , "profile");
    $query->leftJoin("field_data_field_full_name" , "full_name" , "profile.pid = full_name.entity_id and full_name.entity_type='profile2' and full_name.bundle='main' ");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "profile.pid = about_me.entity_id and about_me.entity_type='profile2' and about_me.bundle='main' ");
    $query->leftJoin("field_data_field_skills" , "skills" , "profile.pid = skills.entity_id and skills.entity_type='profile2' and skills.bundle='main' ");
    $query->leftJoin("field_data_field_university" , "university" , "profile.pid = university.entity_id and university.entity_type='profile2' and university.bundle='main' ");
    $query->leftJoin("field_data_field_education_field" , "education_field" , "profile.pid = education_field.entity_id and education_field.entity_type='profile2' and education_field.bundle='main' ");
    $query->leftJoin("field_data_field_education_degree" , "education_degree" , "profile.pid = education_degree.entity_id and education_degree.entity_type='profile2' and education_degree.bundle='main' ");
    $query->leftJoin("field_data_field_mobile" , "mobile" , "profile.pid = mobile.entity_id and mobile.entity_type='profile2' and mobile.bundle='main' ");
    $query->leftJoin("field_data_field_job" , "job" , "profile.pid = job.entity_id and job.entity_type='profile2' and job.bundle='main' ");
    $query->addField("full_name" , "field_full_name_value" , "full_name");
    $query->addField("about_me" , "field_about_me_value" , "about_me");
    $query->addField("skills" , "field_skills_value" , "skills");
    $query->addField("university" , "field_university_value" , "university");
    $query->addField("education_field" , "field_education_field_value" , "education_field");
    $query->addField("education_degree" , "field_education_degree_value" , "education_degree");
    $query->addField("mobile" , "field_mobile_value" , "mobile");
    $query->addField("job" , "field_job_value" , "job");
    $query->condition("profile.uid" , $user->uid);
    $result = $query->execute()->fetch();

    !empty($result->full_name)? $profile->full_name = $result->full_name : $profile->full_name = "";
    !empty($result->about_me)? $profile->about_me = $result->about_me : $profile->about_me = "";
    !empty($result->skills)? $profile->skills = $result->skills : $profile->skills = "";
    !empty($result->university)? $profile->university = $result->university : $profile->university = "";
    !empty($result->education_field)? $profile->education_field = $result->education_field : $profile->education_field = "";
    !empty($result->education_degree)? $profile->education_degree = $result->education_degree : $profile->education_degree = "";
    !empty($result->mobile)? $profile->mobile = $result->mobile : $profile->mobile = "";
    !empty($result->job)? $profile->job = $result->job : $profile->job = "";

    $query = db_select("file_managed" , "file_managed");
    $query->fields("file_managed", array("uri"));
    $query->condition("file_managed.fid", $user->picture);
    $result = $query->execute()->fetch();
    if(!empty($result)) $profile->picture = image_style_url("200x200", $result->uri);

    $query = db_select("field_data_field_image" , "image");
    $query->join("file_managed" , "file" , "file.fid = image.field_image_fid");
    $query->fields("file" , array("uri"));
    $query->condition("image.entity_id" , $user->uid);
    $query->condition("image.entity_type" , "user");
    $result = $query->execute()->fetch();
    if(!empty($result)) $profile->background_image = image_style_url("1360x500_blur", $result->uri);

    $profile->user_point = userpoints_get_current_points($user->uid, 'all');

    return $profile;
}

function user_data($uid){
    $query = db_select('users' , 'user');
    $query->fields('user' , array('uid' , 'name' , 'mail' , 'created' , 'login' , 'picture'));
    $query->condition('user.uid' , $uid);
    $user = $query->execute()->fetch();

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