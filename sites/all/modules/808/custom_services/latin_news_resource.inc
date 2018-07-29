<?php

function latin_news_resource_index($hash , $page , $version){
    if(!(hash_true($hash , "latin_news"))) return "failed to access";
    if($version == 0){
        return list_of_latin_news_version_one($page);
    }
    return "This version not supported";
}
function latin_news_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "latin_news"))) return "failed to access";
    if($version == 0){
        return retrieve_a_latin_news_version_one($nid);
    }
    return "This version not supported";
}

function list_of_latin_news_version_one($page){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_field_eventtime', 'eventtime', 'eventtime.entity_id = node.nid');
    $query->leftJoin('field_data_field_company', 'company', 'company.entity_id = node.nid');
    $query->leftJoin('field_data_field_ifwebinar', 'ifwebinar', 'ifwebinar.entity_id = node.nid');
    $query->leftJoin('field_data_field_latin_contents_categories', 'category', "category.entity_id = node.nid");
    $query->fields('node' , array('nid' , 'title'));
    $query->fields('eventtime' , array('field_eventtime_value'));
    $query->fields('company' , array('field_company_value'));
    $query->fields('ifwebinar' , array('field_ifwebinar_value'));
    $query->condition('node.type', 'latin_contents');
    $query->condition('node.language', 'en');
    $query->condition('node.status', 1);
    $query->condition('category.field_latin_contents_categories_tid', 3929);
    $query->condition('category.entity_type', 'node');
    $query->condition('eventtime.field_eventtime_value', date("Y-m-d", time()) , '>=');
    $query->orderBy('eventtime.field_eventtime_value', 'ASC');
    $latin_news = $query->execute()->fetchAll();
    return $latin_news;
}

function retrieve_a_latin_news_version_one($nid){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body', 'body', 'body.entity_id = node.nid');
    $query->leftJoin('field_data_field_eventtime', 'eventtime', 'eventtime.entity_id = node.nid');
    $query->leftJoin('field_data_field_company', 'company', 'company.entity_id = node.nid');
    $query->leftJoin('field_data_field_ifwebinar', 'ifwebinar', 'ifwebinar.entity_id = node.nid');
    $query->fields('node' , array('title'));
    $query->fields('body' , array('body_value'));
    $query->fields('eventtime' , array('field_eventtime_value'));
    $query->fields('company' , array('field_company_value'));
    $query->fields('ifwebinar' , array('field_ifwebinar_value'));
    $query->condition('node.nid' , $nid);
    $latin_news = $query->execute()->fetch();

    $query = db_select('field_data_field_image' , 'field_image');
    $query->join('file_managed', 'file', 'file.fid = field_image.field_image_fid');
    $query->fields('file' , array('filename' , 'uri'));
    $query->condition('field_image.entity_id' , $nid);
    $query->condition('field_image.entity_type' , 'node');
    $query->condition('field_image.bundle' , 'latin_contents');
    $news_image = $query->execute()->fetch();

    if(!empty($news_image)){ $latin_news->filename = $news_image->filename; $latin_news->uri = $news_image->uri; }

    return ["latin_news" => $latin_news];
}