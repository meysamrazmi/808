<?php

/*---------------------------operation part------------------------------*/
function pedia_resource_index($parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "pedia"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/pedia" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function list_of_pedias_v_1($parameter){
    $query = db_select("taxonomy_term_data" , "pedia");
    $query->join("field_data_field_bool" , "field_bool" , "pedia.tid = field_bool.entity_id and field_bool.entity_type = 'taxonomy_term' and field_bool.bundle = 'expert' and field_bool.field_bool_value = '1' ");
    $query->leftJoin("field_data_field_image" , "field_image" , "pedia.tid = field_image.entity_id and field_image.entity_type = 'taxonomy_term' and field_image.bundle = 'expert' and field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "image" , "image.fid = field_image.field_image_fid");
    $query->fields("pedia" , array("tid" , "name"));
    $query->fields("image" , array("uri" , "filesize"));
    $query->condition("pedia.vid" , 28);
    if(isset($parameter["custom_pedia"]) && !empty($parameter["custom_pedia"])) $query->condition("pedia.tid" , $parameter["custom_pedia"] , "IN");
    $query->orderBy("pedia.tid" , "DESC");
    $query->range(isset($parameter["page"])? $parameter["page"]*24 : 0 , 24);
    $pedias = $query->execute()->fetchAll();

    foreach ($pedias as $pedia){
        $pedia->tid = (int) $pedia->tid;
        $pedia->image = empty($pedia->uri) ? null : image_style_url("800x600" , $pedia->uri);
        unset($pedia->uri);
        $pedia->filesize = (int) $pedia->filesize;
    }

    return $pedias;
}

function pedia_resource_retrieve($tid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "pedia"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/pedia/tid" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["tid"] = $tid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function retrieve_pedia_v_1($parameter){
    $query = db_select("taxonomy_term_data" , "pedia");
    $query->join("field_data_field_bool" , "field_bool" , "pedia.tid = field_bool.entity_id and field_bool.entity_type = 'taxonomy_term' and field_bool.bundle = 'expert' and field_bool.field_bool_value = '1' ");
    $query->leftJoin("field_data_field_image" , "field_image" , "pedia.tid = field_image.entity_id and field_image.entity_type = 'taxonomy_term' and field_image.bundle = 'expert'");
    $query->leftJoin("file_managed" , "image" , "image.fid = field_image.field_image_fid");
    $query->fields("pedia" , array("tid" , "name" , "description"));
    $query->fields("image" , array("uri" , "filesize"));
    $query->condition("pedia.tid" , $parameter["tid"]);
    $query->condition("pedia.vid" , 28);
    $pedia = $query->execute()->fetch();

    $pedia->description = preg_replace('/<iframe.*?\/iframe>/i','', $pedia->description);
    $parts = explode('="/sites/default', $pedia->description);
    $pedia->description = implode('="https://civil808.com/sites/default', $parts);
    $parts = explode('href="/', $pedia->description);
    $pedia->description = implode('href="https://civil808.com/', $parts);
    $parts = explode('="/node/', $pedia->description);
    $pedia->description = implode('="https://civil808.com/node/', $parts);


    $pedia->tid = (int) $pedia->tid;
    $pedia->image = empty($pedia->uri) ? null : image_style_url("large" , $pedia->uri);
    unset($pedia->uri);

    $query = db_select("field_data_field_experts" , "advisors");
    $query->join("profile" , "profile" , "advisors.entity_id = profile.pid and advisors.entity_type = 'profile2' and advisors.bundle = 'main' ");
    $query->join("users" , "user" , "user.uid = profile.uid");
    $query->join("users_roles" , "roles" , "user.uid = roles.uid and roles.rid = '10' ");
    $query->leftJoin("file_managed" , "image" , "image.fid = user.picture");
    $query->leftJoin("field_data_field_full_name" , "full_name" , "profile.pid = full_name.entity_id and full_name.entity_type='profile2' and full_name.bundle='main' ");
    $query->condition("advisors.field_experts_tid" , $parameter["tid"]);
    $query->fields("user" , array("uid" , "name"));
    $query->addField("full_name" , "field_full_name_value" , "full_name");
    $query->addField("image" , "uri" , "image");
    $advisors = $query->execute()->fetchAll();
    foreach ($advisors as $advisor){
        $advisor->uid = (int) $advisor->uid;
        if(!empty($advisor->image)) $advisor->image = image_style_url("200x200" , $advisor->image);
    }

    return array("pedia" => $pedia , "advisors" => $advisors);
}
/*---------------------------------------------------------------------- */
/*------------------------relationships part-----------------------------*/
function pedia_resource_search($list , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "pedia"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/pedia/list/search" , "GET" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function pedia_search_list_v_1($parameter){
//    $persian = ['۰', '۱', '۲', '۳', '۴', '۵', '۶', '۷', '۸', '۹'];
//    $num = range(0, 9);
//    $parameter["value"] = str_replace($persian, $num, $parameter["value"]);

    $query = db_select("taxonomy_term_data" , "pedia");
    $query->fields("pedia" , array("tid"));
    $query->condition("pedia.name" , '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $tids = $query->execute()->fetchCol();
    if(empty($tids)) return array();
    $parameter["custom_pedia"] = $tids;
    return list_of_pedias_v_1($parameter);
}
/*---------------------------------------------------------------------- */