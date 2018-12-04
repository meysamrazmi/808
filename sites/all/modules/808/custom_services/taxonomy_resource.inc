<?php

/*-------------------------------------operations part---------------------------------------------*/
function taxonomy_resource_index($parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "taxonomy"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/taxonomy" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function list_of_taxonomy_v1($parameter){
    $query = db_select("taxonomy_term_data" , "term_data");
    $query->join("field_data_field_bool" , "bool" , "bool.entity_id = term_data.tid and bool.bundle = 'expert' and bool.entity_type = 'taxonomy_term' and bool.field_bool_value = '1' ");
    $query->fields("term_data" , array("tid" , "name"));
    if(isset($parameter["vocab_id"]) && !empty($parameter["vocab_id"])) $query->condition("term_data.vid" , $parameter["vocab_id"]);
    $taxonomy = $query->execute()->fetchAll();
    return $taxonomy;
}

function taxonomy_resource_retrieve($tid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "taxonomy"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/taxonomy/tid" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["tid"] = $tid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function retrieve_taxonomy_information_v_1($parameter){
    $query = db_select("taxonomy_term_data" , "data");
    $query->join("field_data_field_experts" , "content" , "data.tid = content.field_experts_tid and content.entity_type = 'node' and content.bundle = 'questions' ");
    $query->join("node" , "node" , "content.entity_id = node.nid and node.status = '1' ");
    $query->condition("data.vid" , 28);
    $query->condition("data.tid" , $parameter["tid"]);
    $query->fields("content" , array("entity_id"));
    $question_count = $query->execute()->rowCount();

    $query = db_select("taxonomy_term_data" , "data");
    $query->join("field_data_field_experts" , "content" , "data.tid = content.field_experts_tid and content.entity_type = 'node' and content.bundle != 'questions' ");
    $query->join("node" , "node" , "content.entity_id = node.nid and node.status = '1' ");
    $query->condition("data.vid" , 28);
    $query->condition("data.tid" , $parameter["tid"]);
    $query->fields("content" , array("entity_id"));
    $content_count = $query->execute()->rowCount();

    $query = db_select("taxonomy_term_data" , "data");
    $query->join("field_data_field_experts" , "advisor" , "data.tid = advisor.field_experts_tid and advisor.entity_type = 'profile2' and advisor.bundle = 'main' ");
    $query->condition("data.vid" , 28);
    $query->condition("data.tid" , $parameter["tid"]);
    $query->fields("advisor" , array("entity_id"));
    $user_count = $query->execute()->rowCount();

    $query = db_select("field_data_field_image" , "image");
    $query->join("file_managed" , "file" , "file.fid = image.field_image_fid ");
    $query->condition("image.entity_type" , "taxonomy_term");
    $query->condition("image.entity_id" , $parameter["tid"]);
    $query->condition("image.bundle" , "expert");
    $query->fields("file" , array("uri"));
    $image = $query->execute()->fetch();
    if(!empty($image)) $image = image_style_url("200x200" , $image->uri);

    return array("image" => $image , "question_count" => $question_count , "content_count" => $content_count , "user_count" => $user_count);
}
/*------------------------------------------------------------------------------------------------*/