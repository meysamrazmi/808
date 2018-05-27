<?php

/*---------------------actions part------------------------------------*/
function user_resource_login($hash , $username_email, $password , $version){
    if(!(hash_true($hash , "user"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return login_version_one($username_email, $password);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_resource_register($hash , $data, $version){
    if(!(hash_true($hash , "user"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return register_version_one($data);
    }
    return services_error(t('This version is not supported'), 11);
}


/*---------------------relationships part------------------------------*/
function user_resource_purchased_products_list($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of__user_purchased_products_version_one($uid);
    }
    return services_error(t('This version is not supported'), 11);
}


/*---------------------functions part----------------------------------*/
function login_version_one($username_email, $password){

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
        return  services_error(t("User is blocked!") , 18);
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

        if ($user->uid) {
            user_login_finalize();

            $result = new stdClass();
            $result->sessid = session_id();
            $result->session_name = session_name();
            $result->token = drupal_get_token('services');

            $user->userpoint = userpoints_get_current_points($user->uid, 'all');
            $result->user = $user;

            $profile = profile2_load_by_user($user);

            $result->profile = $profile;

            return $result;
        }
    }
    return 'Wrong username or password.';
}

/**
 * @param $data
 * @return Profile|stdClass|void
 */
function register_version_one($data){
    /*check input correctness*/
    if(!isset($data['username']) || empty($data['username'])) return services_error(t("Username is required!") , 15);
    if(!isset($data['password']) || empty($data['password'])) return services_error(t("Password is required!") , 15);
    if(!isset($data['email']) || empty($data['email'])) return services_error(t("Email is required!") , 15);
    if(!isset($data['full_name']) || empty($data['full_name'])) return services_error("Full name is required!" , 15);
    if(!isset($data['mobile']) || empty($data['mobile'])) return services_error(t("Mobile is required!") , 15);

    /*check if user is logged in!*/
    global $user;
    if($user->uid > 0) return services_error(t("User is already logged in!") , 18);

    /*check if this username or email is duplicate*/
    $query = db_select("users", "user");
    $query->fields("user" , array("name" , "mail"));
    $db_or = db_or();
    $db_or->condition('user.name', $data['username'] , 'LIKE');
    $db_or->condition('user.mail', $data['email'] , 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchObject();
    if(!empty($result)) return services_error(t("User with username: @username or E-mail: @email is exist!" , array("@username" => $data["username"] , "@email" => $data["email"])) , 18);

    /*create new user*/
    $new_user = array(
        'name' => $data['username'],
        'pass' => $data['password'],
        'mail' => $data['email'],
        'status' => 1,
        'init' => $data['email'],
        'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
        ),
        'field_some_custom_field' => array('und' => array(0 => array('value' => 1))),
    );
    $user = user_save('', $new_user);

    /*create profile for new user*/
    $profile = profile2_create(array('type' => 'main', 'uid' => $user->uid));
    $profile->field_full_name['und'][0]['value'] = $data['full_name'];
    $profile->field_mobile['und'][0]['value'] = $data['mobile'];
    profile2_save($profile);
    $profile = profile2_load_by_user($user);

    /*login user*/
    user_login_finalize();
    $login = new stdClass();
    $login->sessid = session_id();
    $login->session_name = session_name();
    $login->token = drupal_get_token('services');

    $user->userpoint = 0; /*new user has no point*/

    return ["login_data" => $login ,  "user" => $user , "profile" => $profile];
}

function list_of__user_purchased_products_version_one($uid){
    global $user;

    if($user->uid != $uid && !in_array('administrator' , $user->roles)) return ["ebook" => array()];

    $query = db_select('m_buyed_nodes', 'buyed');
    $query->join('node', 'node', 'buyed.nid = node.nid');
    $query->join('field_data_field_point_needed' , 'price' , 'node.nid = price.entity_id');
    $query->leftJoin('profile' , 'profile' , 'profile.uid = node.uid');
    $query->join('field_data_field_full_name' , 'name' , 'name.entity_id = profile.pid');
    $query->fields('buyed', array('nid', 'date', 'price'));
    $query->fields('node', array('title' , 'type' , 'uid' , 'changed'));
    $query->addField('price' , 'field_point_needed_value' , 'field_point_needed_value');
    $query->addField('name' , 'field_full_name_value' , 'author_name');
    $query->condition('buyed.uid', $uid);
    $query->condition('buyed.type', 'article');
    $query->condition('node.type', 'publication');
    $query->condition('price.bundle', 'publication');
    $query->condition('profile.type', 'main');
    $query->condition('name.entity_type' , 'profile2');
    $query->condition('name.bundle' , 'main');
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

		$query = db_select('field_data_field_files' , 'field_file');
		$query->join('file_managed' , 'file' , 'field_file.field_files_fid = file.fid');
		$query->fields('field_file', array('entity_id'));
		$query->fields('file', array('uri' , 'filesize'));
		$query->condition('field_file.entity_id', $nids , 'IN');
		$query->condition('field_file.entity_type', 'node');
		$query->condition('field_file.bundle', 'publication');
		$query->condition('file.filemime', 'application/pdf');
		$files = $query->execute()->fetchAll();
		foreach($files as $file){
			$id = $file->entity_id;
			unset($file->entity_id);
			array_push($buyed_nodes[$id]->files , $file);
		}

		$query = db_select('file_managed' , 'image');
		$query->join('field_data_field_image' , 'field_image' , 'image.fid = field_image.field_image_fid');
		$query->addField('image' , 'uri' , 'picture');
		$query->addField('field_image' , 'entity_id' , 'nid');
		$query->condition('field_image.bundle', 'publication');
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

function user_data($uid){
    $query = db_select('users' , 'user');
    $query->leftJoin('file_managed' , 'image' , 'user.picture = image.fid');
    $query->fields('user' , array('uid' , 'name' , 'mail' , 'created' , 'login'));
    $query->addField('image' , 'uri' , 'picture');
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