<?php

/*-------------------------------------index-----------------------------------*/
function latin_front_page_resource_index($hash , $version){
    if(!(hash_true($hash , "latin_front_page"))) return services_error(t('Failed to access'), 10);
    if(strcmp($version , "pbd_0") == 0){
        return list_of_items();
    }
    return services_error(t('This version is not supported'), 11);
}

function list_of_items(){
    /*--------------------------------------------------------------------------------------------------------------------*/
    $query = db_select("taxonomy_term_data" , "taxonomy");
    $query->join("taxonomy_term_hierarchy" , "hierarchy" , "taxonomy.tid = hierarchy.tid and hierarchy.parent = '0' ");
    $query->fields("taxonomy" , array("tid" , "name"));
    $query->condition("taxonomy.vid" , 30);
    $roots = $query->execute()->fetchAll();
    $parent = array();
    foreach ($roots as $row){
        $parent[$row->tid] = $row;
        $parent[$row->tid]->children = array();
    }
    $query = db_select("taxonomy_term_data" , "taxonomy");
    $query->join("taxonomy_term_hierarchy" , "hierarchy" , "taxonomy.tid = hierarchy.tid and hierarchy.parent != '0' ");
    $query->fields("taxonomy" , array("tid" , "name"));
    $query->fields("hierarchy" , array("parent"));
    $query->condition("taxonomy.vid" , 30);
    $leaf = $query->execute()->fetchAll();
    foreach ($leaf as $row){
        $tid = new stdClass();
        $tid->tid = $row->tid;
        $tid->name = $row->name;
        if(isset($parent[$row->parent])) array_push($parent[$row->parent]->children , $tid);
    }
    $content_types = array_values($parent);
    /*--------------------------------------------------------------------------------------------------------------------*/

    
    return ["content_types" => $content_types];
}