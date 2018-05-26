<?php

function version_data_resource_index($hash , $type){
    if(!(hash_true($hash , "versions"))) return services_error(t('Failed to access'), 10);

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
function version_service_resource_create($hash , $data){
    if(!(hash_true($hash , "versions"))) return "failed to access";

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

    if($version == 1) return true;
    else return services_error(t('Insert version data was not successful!'), 14);
}
function version_service_resource_edit($hash , $vid , $type , $data){
    if(!(hash_true($hash , "versions"))) return "failed to access";

    $query = db_select('api_app_version' , 'version');
    $query->fields('version' , array('id' , 'description' , 'update_link' , 'ebook_key'));
    $query->condition('version.vid' , $vid);
    $query->condition('version.app_type' , $type);
    $result = $query->execute()->fetch();

    if(empty($result)) return services_error(t('This version and type is not found'), 17);

    $id = $result->id;
    if(!isset($data['vid'])) $data['vid'] = $vid;
    if(!isset($data['type'])) $data['type'] = $type;
    if(!isset($data['description'])) $data['description'] = $result->description;
    if(!isset($data['force_update'])) $data['force_update'] = $result->force_update;
    if(!isset($data['update_link'])) $data['update_link'] = $result->update_link;
    if(!isset($data['ebook_key'])) $data['ebook_key'] = $result->ebook_key;

    $version_update = db_update('api_app_version')
        ->fields(array(
            'vid' => $data['vid'],
            'app_type' => $data['type'],
            'description' => $data['description'],
            'force_update' => $data['force_update'],
            'update_link' => $data['update_link'],
            'ebook_key' => $data['ebook_key'],
        ))
        ->condition('id',$id)
        ->execute();

    if($version_update == 1) return true;
    else return services_error(t('Update version data was not successful!'), 14);
}