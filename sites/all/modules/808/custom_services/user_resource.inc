<?php

function user_resource_login($hash , $username_email, $password , $version){
    if(!(hash_true($hash , "user"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return login_version_one($username_email, $password);
    }
    return services_error(t('This version is not supported'), 11);
}
function user_resource_purchased_products_list($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of__user_purchased_products_version_one($uid);
    }
    return services_error(t('This version is not supported'), 11);
}

function login_version_one($username_email, $password){
    global $user;

    if ($user->uid) {
        return 'Already logged in';
    }

    $query =  db_select('users' , 'user');
    $query->fields('user', array('name' , 'status'));
    $db_or = db_or();
    $db_or->condition('user.name', $username_email , 'LIKE');
    $db_or->condition('user.mail', $username_email , 'LIKE');
    $query->condition($db_or);
    $result = $query->execute()->fetchObject();

    if(empty($result)){
        return "This user is not exist!";
    }
    elseif($result->status == 0){
        return  "This user is blocked";
    }
    else{
        $username = $result->name;
    }

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