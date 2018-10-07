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
    $query->fields("term_data" , array("tid" , "name"));
    if(isset($parameter["vocab_id"]) && !empty($parameter["vocab_id"])) $query->condition("term_data.vid" , $parameter["vocab_id"]);
    $taxonomy = $query->execute()->fetchAll();
    return $taxonomy;
}