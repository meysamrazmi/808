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
//    $query->leftJoin('field_data_field_image', 'image', 'image.entity_id = node.nid');
//    $query->join('file_managed', 'file', 'file.fid = image.field_image_fid');
    $query->fields('node' , array('nid' , 'title' , 'uid' , 'created' , 'changed'));
    $query->fields('body' , array('body_value'));
//    $query->fields('file' , array('filename' , 'uri'));
    $query->condition('node.nid' , $nid);
    $query->condition('body.entity_type', 'node');
    $query->condition('body.bundle', 'article');
//    $query->condition('image.entity_type', 'node');
//    $query->condition('image.bundle', 'article');
    $news = $query->execute()->fetch();
    return ["news" => $news];
}