<?php

function content_resource_index($hash , $type , $language , $page , $version){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of_contents_version_one($type , $language , $page);
    }
    return services_error(t('This version is not supported'), 11);
}
function content_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return retrieve_a_content_version_one($nid);
    }
    return services_error(t('This version is not supported'), 11);
}
function content_resource_search($hash , $type , $value , $version){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);

    if($version == 0) {
        $query = db_select("node", "node");
        $query->fields('node', array('nid'));
        $query->condition('node.title', '%' . $value . '%', 'LIKE');
        $query->condition('node.type' , $type);
        $nid1 = $query->execute()->fetchAll();

        $query = db_select("field_data_body", "body");
        $query->addField('body', 'entity_id', 'nid');
        $query->condition('body.body_value', '%' . $value . '%', 'LIKE');
        $query->condition('body.entity_type' , 'node');
        $query->condition('body.bundle' , $type);
        $nid2 = $query->execute()->fetchAll();

        $nids = array_merge($nid1, $nid2);
        $custom_list = array();
        foreach ($nids as $row) array_push($custom_list, $row->nid);
        if(!empty($custom_list))
            return list_of_contents_version_one($type, 'fa', 0, $custom_list);
        else
            return ["content" => array()];
    }
    return services_error(t('This version is not supported'), 11);
}

function list_of_contents_version_one($type , $language ,  $page , $custom_list = array()){

    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->leftJoin("profile" , "profile" , "profile.uid = node.uid and profile.type = 'main'");
    $query->join("field_data_field_full_name" , "name" , "name.entity_id = profile.pid and name.entity_type = 'profile2' and name.bundle = 'main'");
    $query->addField("name" , "field_full_name_value" , "author_name");
    $query->condition('node.status' , 1);
    $query->condition('node.language' , $language);
    $query->condition('node.type' , $type);

    if($type == "publication"){
        /*add price, author name to e-book*/
        $query->join("field_data_field_point_needed" , "price" , "node.nid = price.entity_id  and price.bundle = 'publication'");
        $query->addField("price" , "field_point_needed_value" , "price");
        $query->orderBy("node.nid" , "DESC");
        if(!empty($custom_list)) $query->condition('node.nid' , $custom_list , 'IN');
        else $query->range($page*24 , 24);
        $db_contents = $query->execute()->fetchAll();

        if(count($db_contents) > 0) {
            $nids = array();
            $temp_contents = array();
            foreach ($db_contents as $row) {
                array_push($nids, $row->nid);
                $temp_contents[$row->nid] = $row;
            }

            /*add e-book image*/
            $query = db_select("file_managed", "image");
            $query->join("field_data_field_image", "field_image", "image.fid = field_image.field_image_fid and field_image.bundle = 'publication'");
            $query->addField('image', 'uri', 'picture');
            $query->addField('field_image', 'entity_id', 'nid');
            $query->condition('field_image.entity_id', $nids, 'IN');
            $results = $query->execute()->fetchAll();
            foreach ($results as $row) {
                $temp_contents[$row->nid]->picture = $row->picture;
            }

            /*add e-book page number*/
            $query = db_select('field_data_field_pagenumber' , 'page_number');
            $query->addField('page_number' , 'field_pagenumber_value' , 'page_number');
            $query->addField('page_number' , 'entity_id' , 'nid');
            $query->condition('page_number.entity_id' , $nids , 'IN');
            $query->condition('page_number.bundle' , 'publication');
            $results = $query->execute()->fetchAll();
            foreach ($results as $row) {
                $temp_contents[$row->nid]->page_number = $row->page_number;
            }

            $contents = array_values($temp_contents);
        }
        else $contents = array();
    }
    elseif($type == "podcast"){
        $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.delta = 1 and field_image.bundle = 'podcast'");
        $query->leftJoin("file_managed" , "file_image" , "field_image.field_image_fid = file_image.fid");
        $query->leftJoin("field_data_field_episode" , "field_episode" , "node.nid = field_episode.entity_id and field_episode.bundle = 'podcast'");
        $query->leftJoin("file_managed" , "file_episode" , "field_episode.field_episode_fid = file_episode.fid");
        $query->leftJoin("field_data_field_episode_remote" , "episode_remote" , "node.nid = episode_remote.entity_id and episode_remote.bundle = 'podcast'");
        $query->addField('file_image' , 'uri' , 'picture');
        $query->addField('file_episode' , 'uri' , 'audio');
        $query->addField('file_episode' , 'filesize' , 'audio_size');
        $query->addField('episode_remote' , 'field_episode_remote_value' , 'audio_remote');
        $query->orderBy("node.nid" , "DESC");
        $query->range($page*24, 24);
        $contents = $query->execute()->fetchAll();
    }
    else {
        /*
     * @todo
     * return other node type
     * */
        $contents =  array();
    }


    return ["content" => $contents];
}

function retrieve_a_content_version_one($nid){
    $query = db_select("node" , "node");
    $query->leftJoin("field_data_body" , "body" , "node.nid = body.entity_id and body.bundle = 'publication'");
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.status' , 1);
    $query->condition('node.nid' , $nid);
    $node = $query->execute()->fetch();

    if(empty($node) || count($node) == 0) return ["ebook" => $node];

    $node->body = preg_replace('/(<[^>]+) style=".*?"/i', '$1', $node->body);
    if(strpos($node->body, "<!--break-->") != false) $node->body = substr($node->body, 0, strpos($node->body, "<!--break-->"));

    if($node->type == "publication"){
        /*add publish_file to e-book*/
        $query = db_select("field_data_field_publish_file" , "field_file_published");
        $query->join("file_managed" , "file_published" , "field_file_published.field_publish_file_fid = file_published.fid and field_file_published.bundle = 'publication' and field_file_published.entity_id = " . $nid);
        $query->addField('field_file_published' , 'entity_id' , 'nid');
        $query->addField('file_published' , 'uri' , 'sample_file');
        $sample_file = $query->execute()->fetch();
        $node->sample_file = $sample_file->sample_file;

        /*add field about author to e-book*/
        $query = db_select("field_data_field_about_me" , "about_me");
        $query->join("profile" , "profile" , "profile.pid = about_me.entity_id and profile.type = 'main' and profile.uid = " . $node->uid);
        $query->addField('about_me' , 'field_about_me_value' , 'about_author');
        $query->condition('about_me.entity_type' , 'profile2');
        $query->condition('about_me.bundle' , 'main');
        $about_author = $query->execute()->fetch();
        $node->about_author = $about_author->about_author;

        /*add the file of e-book if user bought it or it is free*/
        global $user;

        /*check if user has been bought E-book or not*/
        if($user->uid > 0) {
            $query = db_select('m_buyed_nodes', 'buyed');
            $query->fields('buyed', array('id', 'uid', 'nid'));
            $query->condition('buyed.uid', $user->uid);
            $query->condition('buyed.nid', $nid);
            $user_buyed = $query->execute()->fetch();
        }

        /*get price for check that is Free or not*/
        if(!isset($user_buyed) || empty($user_buyed)) {
            $query = db_select('field_data_field_point_needed', 'price');
            $query->addField('price', 'field_point_needed_value', 'price');
            $query->condition('price.entity_id', $nid);
            $query->condition('price.entity_type', 'node');
            $query->condition('price.bundle', 'publication');
            $price = $query->execute()->fetch();
        }

        /*check if it is Free for VIP*/
        if(!isset($user_buyed) || empty($user_buyed)) {
            $query = db_select('field_data_field_isvip', 'vip');
            $query->fields('vip', array('field_isvip_tid'));
            $query->condition('vip.entity_id', $nid);
            $query->condition('vip.bundle', 'publication');
            $query->condition('vip.field_isvip_tid', 1760);
            $vip = $query->execute()->fetch();
        }
        if((isset($user_buyed) && !empty($user_buyed)) ||
            (isset($price) && (empty($price) || ($price->price == 0))) ||
            (isset($vip) && !empty($vip) && in_array('Vip' , $user->roles))
            ){
            $query = db_select("field_data_field_files" , "field_file");
            $query->join("file_managed" , "file" , "field_file.field_files_fid = file.fid and file.filemime = 'application/pdf' ");
            $query->fields('file', array('uri' , 'filesize'));
            $query->condition('field_file.entity_id', $nid);
            $query->condition('field_file.entity_type', 'node');
            $query->condition('field_file.bundle', 'publication');
            $files = $query->execute()->fetchAll();

            if(!empty($files)){
                $node->files = array();
                foreach ($files as $file){
                    array_push($node->files , $file);
                }
            }
        }

        return ["ebook" => $node];
    }

    /*
     * @todo
     * return another type of contents
     * */
    return ["node" => array()];
}
