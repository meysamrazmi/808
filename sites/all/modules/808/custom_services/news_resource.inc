<?php

function news_resource_index($hash , $domain , $page , $version){
    if(!(hash_true($hash , "news"))) return "failed to access";
    if($version == 0){
        return list_of_news_version_one($domain , $page);
    }
    return "This version not supported";
}
function news_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "news"))) return "failed to access";
    if($version == 0){
        return retrieve_a_news_version_one($nid);
    }
    return "This version not supported";
}

function list_of_news_version_one($domain , $page){
    switch ($domain){
        case "all_news" :
            return all_news($page);
            break;
        case "front_news" :
            return front_news();
            break;
        default:
            return "domain is not exist";
            break;
    }
}

function all_news($page){
    $results = db_select('node' , 'node')
        ->fields('node' , array('nid', 'title', 'created'))
        ->condition('node.status' , 1)
        ->condition('type' , array('education', 'article', 'publication', 'blog', 'designteam' , 'podcast', 'projectnew', 'project'), 'IN')
        ->condition('node.language' , 'en' , '<>')
        ->orderBy('node.created', 'DESC')
        ->range($page*20, 20)
        ->execute()->fetchAll();

    return ["front_news" => $results];
}

function front_news(){
    $results = db_select('node' , 'node')
        ->fields('node' , array('nid', 'title', 'created'))
        ->condition('node.status' , 1)
        ->condition('type' , array('education', 'article', 'publication', 'blog', 'designteam' , 'podcast', 'projectnew', 'project'), 'IN')
        ->condition('node.language' , 'en' , '<>')
        ->orderBy('node.created', 'DESC')
        ->range(0, 20)
        ->execute()->fetchAll();

    return ["front_news" => $results];
}

function retrieve_a_news_version_one($nid){
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
    $news = $query->execute()->fetch();

    $query = db_select('field_data_field_image' , 'field_image');
    $query->join('file_managed', 'file', 'file.fid = field_image.field_image_fid');
    $query->fields('file' , array('filename' , 'uri'));
    $query->condition('field_image.entity_id' , $nid);
    $query->condition('field_image.entity_type' , 'node');
    $query->condition('field_image.bundle' , 'article');
    $news_image = $query->execute()->fetch();

    if(!empty($news_image)){ $news->filename = $news_image->filename; $news->uri = $news_image->uri; }

    return ["news" => $news];
}