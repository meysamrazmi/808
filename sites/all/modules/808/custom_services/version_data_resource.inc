<?php

function version_data_resource_index($hash , $type , $vid){
    if(!(hash_true($hash , "versions"))) return services_error(t('Failed to access'), 10);
    /*
     * Ali Banaei : I had a mistake in writing this web service
     * so I have to change the Desktop version without changing the Android version
     * for retrieve a Desktop data I'm using this function and send the parameter to "get_desktop_version"
     * and fetch the data for the $vid
     * */
    if(strcmp($type , "desktop") == 0 && strlen($vid) > 0) return get_desktop_version($vid);

    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array('vid' , 'app_type' , 'description' , 'force_update' , 'update_link' , 'ebook_key'));
    if($type != '' && strlen($type) > 0) $query->condition('version.app_type' , $type);
    $results = $query->execute()->fetchAll();
    if(empty($results) && $type != '')
        return services_error(t('There is no data about @type type' , array('@type' => $type)), 17);

    return ["versions" => $results];
}
function version_service_resource_retrieve($hash , $vid , $type){
    if(!(hash_true($hash , "versions"))) return services_error(t('Failed to access'), 10);

    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array('vid' , 'description' , 'force_update' , 'update_link' , 'ebook_key'));
    $query->condition('version.vid' , $vid);
    $query->condition('version.app_type' , $type);
    $result = $query->execute()->fetch();
    if(!empty($result))
        return ["version_data" => $result];
    else
        return services_error(t('This version and type is not found'), 17);
}
function version_service_resource_create($data){
    global $user;
    if($user->uid != 20436 && !in_array("administrator" , $user->roles)) return services_error("You are not admin" , 403);

    if(empty($data['version_id'] || $data['force_update'] || $data['type'])){
        return services_error(t('version_id, force_update and type field is required!'), 15);
    }

    $version = db_insert('api_app_version')
        ->fields(array(
            'vid' => $data['version_id'],
            'description' => $data['description'],
            'force_update' => $data['force_update'],
            'update_link' => $data['update_link'],
            'ebook_key' => $data['ebook_key'],
            'app_type' => $data['type'],
            'created' => REQUEST_TIME,
        ))
        ->execute();

    if($version > 0) return true;
    else return services_error(t('Insert version data was not successful!'), 500);
}
function version_service_resource_update($vid , $data){
    global $user;
    if($user->uid != 20436 && !in_array("administrator" , $user->roles)) return services_error("You are not admin" , 403);
    if(empty($data['type'])){
        return services_error(t('type field is required!'), 15);
    }
    /*
     * Ali Banaei : I had a mistake in writing this web service
     * so I have to change the Desktop version without changing the Android version
     * for update a Desktop data I'm using this function and send the parameter to "update_desktop_version"
     * and update the data for the $vid
     * NOTE : In Android I used $vid for updating but This was mistake so in Desktop version $vid is equal to id
     * but I cant change the name
     * */
    if(strcmp($data["type"] , "desktop") == 0) return update_desktop_version($vid , $data);

    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array('id' , 'description' , 'update_link' , 'ebook_key'));
    $query->condition('version.vid' , $vid);
    $query->condition('version.app_type' , $data["type"]);
    $result = $query->execute()->fetch();

    if(empty($result)) return services_error(t('This version and type is not found'), 17);

    $id = $result->id;
    if(!isset($data['vid'])) $data['vid'] = $vid;
    if(!isset($data['new_type'])) $data['new_type'] = $data["type"];
    if(!isset($data['description'])) $data['description'] = $result->description;
    if(!isset($data['force_update'])) $data['force_update'] = $result->force_update;
    if(!isset($data['update_link'])) $data['update_link'] = $result->update_link;
    if(!isset($data['ebook_key'])) $data['ebook_key'] = $result->ebook_key;

    $version_update = db_update('api_app_version')
        ->fields(array(
            'vid' => $data['vid'],
            'app_type' => $data['new_type'],
            'description' => $data['description'],
            'force_update' => $data['force_update'],
            'update_link' => $data['update_link'],
            'ebook_key' => $data['ebook_key'],
        ))
        ->condition('id',$id)
        ->execute();

    if($version_update > 0) return true;
    else return services_error(t('Update version data was not successful!'), 14);
}


/*This two functions are used for Desktop Versions*/
function get_desktop_version($vid){
    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array('id' , 'vid' , 'description' , 'force_update' , 'update_link'));
    $query->condition('version.vid' , $vid);
    $query->condition('version.app_type' , "desktop");
    $result = $query->execute()->fetch();
    if(!empty($result))
        return $result;
    else
        return services_error(t('This version and type is not found'), 404);
}
function update_desktop_version($id , $data){
    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array());
    $query->condition('version.id' , $id);
    $query->condition('version.app_type' , $data["type"]);
    $result = $query->execute()->fetch();
    if(empty($result)) return services_error(t('This version and type is not found'), 404);

    if(!isset($data['vid'])) $data['vid'] = $result->vid;
    if(!isset($data['new_type'])) $data['new_type'] = $data["type"];
    if(!isset($data['description'])) $data['description'] = $result->description;
    if(!isset($data['force_update'])) $data['force_update'] = $result->force_update;
    if(!isset($data['update_link'])) $data['update_link'] = $result->update_link;

    $version_update = db_update('api_app_version')
        ->fields(array(
            'vid' => $data['vid'],
            'app_type' => $data['new_type'],
            'description' => $data['description'],
            'force_update' => $data['force_update'],
            'update_link' => $data['update_link'],
        ))
        ->condition('id', $id)
        ->execute();

    if($version_update > 0) return true;
    else return services_error(t('Update version data was not successful!'), 500);
}