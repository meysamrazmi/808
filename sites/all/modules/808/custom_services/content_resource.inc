<?php

function content_resource_index($hash , $type , $language , $page , $version){
    if(!(hash_true($hash , "content"))) return "failed to access";
    if($version == 0){
        return list_of_contents_version_one($type , $language , $page);
    }
    return "This version not supported";
}
function content_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "content"))) return "failed to access";
    if($version == 0){
        return retrieve_a_content_version_one($nid);
    }
    return "This version not supported";
}

function list_of_contents_version_one($type , $language ,  $page){
    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->condition('node.status' , 1);
    $query->condition('node.language' , $language);
    $query->condition('node.type' , $type);

    if($type == "publication"){
        $query->join('field_data_field_point_needed' , 'price' , 'node.nid = price.entity_id');
        $query->leftJoin('field_data_field_image' , 'field_image' , 'node.nid = field_image.entity_id');
        $query->join('file_managed' , 'image' , 'field_image.field_image_fid = image.fid');
        $query->addField('price' , 'field_point_needed_value' , 'price');
        $query->addField('image' , 'uri' , 'picture');
        $query->condition('field_image.bundle', 'publication');
    }
    else {
        /*
     * @todo
     * return other node type
     * */
        return ["content" => array()];
    }

    $query->range($page*20 , 20);
    $contents = $query->execute()->fetchAll();
    return ["content" => $contents];
}

function retrieve_a_content_version_one($nid){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body' , 'body' , 'node.nid = body.entity_id');
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.status' , 1);
    $query->condition('node.nid' , $nid);
    $query->condition('body.bundle', 'publication');
    $node = $query->execute()->fetch();;

    if($node->type == "publication"){
        /*add field_point to e-book*/
        $query = db_select('field_data_field_point_needed' , 'price');
        $query->addField('price' , 'field_point_needed_value' , 'price');
        $query->condition('price.bundle', 'publication');
        $query->condition('price.entity_id' , $nid);
        $price = $query->execute()->fetch();

        /*add field_image to e-book*/
        $query = db_select('field_data_field_image' , 'field_image');
        $query->join('file_managed' , 'image' , 'field_image.field_image_fid = image.fid');
        $query->addField('field_image' , 'entity_id' , 'nid');
        $query->addField('image' , 'uri' , 'picture');
        $query->condition('field_image.entity_id' , $nid);
        $query->condition('field_image.bundle', 'publication');
        $picture = $query->execute()->fetch();

        /*add publish_file to e-book*/
        $query = db_select('field_data_field_publish_file' , 'field_file_published');
        $query->join('file_managed' , 'file_published' , 'field_file_published.field_publish_file_fid = file_published.fid');
        $query->addField('field_file_published' , 'entity_id' , 'nid');
        $query->addField('file_published' , 'uri' , 'sample_file');
        $query->condition('field_file_published.entity_id' , $nid);
        $query->condition('field_file_published.bundle', 'publication');
        $sample_file = $query->execute()->fetchAll();

        /*add field full name of author to e-book*/
        $query = db_select('field_data_field_full_name' , 'name');
        $query->join('profile' , 'profile' , 'profile.pid = name.entity_id');
        $query->addField('name' , 'field_full_name_value' , 'full_name');
        $query->condition('profile.uid' , $node->uid);
        $query->condition('profile.type' , 'main');
        $query->condition('name.entity_type' , 'profile2');
        $query->condition('name.bundle' , 'main');
        $author_name = $query->execute()->fetch();

        /*add field about author to e-book*/
        $query = db_select('field_data_field_about_me' , 'about_me');
        $query->join('profile' , 'profile' , 'profile.pid = about_me.entity_id');
        $query->addField('about_me' , 'field_about_me_value' , 'about_author');
        $query->condition('profile.uid' , $node->uid);
        $query->condition('profile.type' , 'main');
        $query->condition('about_me.entity_type' , 'profile2');
        $query->condition('about_me.bundle' , 'main');
        $about_author = $query->execute()->fetch();

        $node->price = $price->price;
        $node->picture = $picture->picture;
        $node->sample_file = $sample_file->sample_file;
        $node->author_name = $author_name->full_name;
        $node->about_author = $about_author->about_author;

        return ["ebook" => $node];
    }

    /*
     * @todo
     * return another type of contents
     * */
    return ["node" => array()];
}







/*
   $nids = array();
   $ebooks_index = array();
   foreach ($ebooks as $row){
       array_push($nids , $row->nid);
       $ebooks_index[$row->nid] = $row;
   }
   $query = db_select('field_data_field_image' , 'field_image');
   $query->join('file_managed' , 'image' , 'field_image.field_image_fid = image.fid');
   $query->addField('field_image' , 'entity_id' , 'nid');
   $query->addField('image' , 'uri' , 'picture');
   $query->condition('field_image.entity_id' , $nids , 'IN');
   $query->condition('field_image.bundle', 'publication');
   $results = $query->execute()->fetchAll();
   foreach ($results as $result){
       $ebooks_index[$result->nid]->picture = $result->picture;
   }
   $query = db_select('field_data_field_publish_file' , 'field_file_published');
   $query->join('file_managed' , 'file_published' , 'field_file_published.field_publish_file_fid = file_published.fid');
   $query->addField('field_file_published' , 'entity_id' , 'nid');
   $query->addField('file_published' , 'uri' , 'sample_file');
   $query->condition('field_file_published.entity_id' , $nids , 'IN');
   $query->condition('field_file_published.bundle', 'publication');
   $results = $query->execute()->fetchAll();
   foreach ($results as $result){
       $ebooks_index[$result->nid]->sample_file = $result->sample_file;
   }
   $ebooks = array();
   foreach ($ebooks_index as $row){
       array_push($ebooks , $row);
   }
   */