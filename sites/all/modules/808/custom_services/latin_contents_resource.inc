<?php

/*-------------------------------------index-----------------------------------*/
function latin_contents_resource_index($hash , $type_tid , $categories, $page , $version){
    if(!(hash_true($hash , "latin_contents"))) return services_error(t('Failed to access'), 10);
    if($version == "pbd_0"){
        return list_of_latin_contents($type_tid, $categories, $page);
    }
    return services_error(t('This version is not supported'), 11);
}

function list_of_latin_contents($type_tid, $categories, $page){
    $query = db_select("node" , "node");
    $query->join("field_data_field_latin_contents_types" , "contents_types" , "node.nid = contents_types.entity_id");
    $query->join("field_data_body" , "body" , "node.nid = body.entity_id and body.entity_type = 'node' and body.bundle = 'latin_contents' ");
    $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.bundle = 'latin_contents' ");
    $query->leftJoin("file_managed" , "file" , "file.fid = field_image.field_image_fid");
    $query->fields("node" , array("nid" , "title" , "uid" , "created" , "changed"));
    $query->addField("body" , "body_value" , "body");
    $query->addField("file" , "uri" , "picture");
    $query->condition("node.status" , 1);
    $query->condition("node.type" , "latin_contents");
    $query->condition("node.language" , "en");
    $query->condition("contents_types.field_latin_contents_types_tid" , $type_tid);

    if(!empty($categories)){
        $tids = array_map('intval', explode(',', $categories));
        $vid = db_select("taxonomy_term_data" , "taxonomy");
        $vid->join("taxonomy_vocabulary" , "vocab" , "taxonomy.vid = vocab.vid");
        $vid->fields("vocab", array("vid"));
        $vid->condition("taxonomy.tid" , $tids , "IN");
        $category = $vid->execute()->fetch();

        switch ($category->vid){
            case 29:
                $query->join("data_field_latin_news_category" , "news" , "node.nid = news.entity_id");
                $query->condition("news.field_latin_resources_news_tid" , $tids , "IN");
                break;
            case 31:
                $query->join("field_data_field_latin_resources_category" , "resources" , "node.nid = resources.entity_id");
                $query->condition("resources.field_latin_resources_category_tid" , $tids , "IN");
                break;
            case 32:
                $query->join("field_data_field_latin_casestudies_category" , "casestudies" , "node.nid = casestudies.entity_id");
                $query->condition("casestudies.field_latin_casestudies_category_tid" , $tids , "IN");
                break;
        }
    }
    $query->orderBy("node.nid" , "DESC");
    $query->range(30*$page, 30);
    $contents = $query->execute()->fetchAll();

    foreach($contents as $key => $value){
        $contents[$key]->created = format_date($value->created);
        $contents[$key]->changed = format_date($value->changed);

        $contents[$key]->picture = image_style_url("300x300", $contents[$key]->picture);
    }

    return ["contents" => $contents];
}

/*-------------------------------------relationships-----------------------------------*/
function latin_contents_resource_filters($hash  , $type , $version){
    if(!(hash_true($hash , "latin_contents"))) return services_error(t('Failed to access'), 10);
    if(strcmp($version , "pbd_0") == 0){
        switch ($type){
            case "news":
                $vid = 29;
                break;
            case "resources":
                $vid = 31;
                break;
            case "case_studies":
                $vid = 32;
                break;
            default:
                return services_error(t('The type is wrong!'), 16);
        }
        $query = db_select("taxonomy_term_data" , "taxonomy");
        $query->fields("taxonomy" , array("tid" , "name"));
        $query->condition("taxonomy.vid" , $vid);
        $filters = $query->execute()->fetchAll();

        return ["type" => $type, "filters" => $filters];
    }
    return services_error(t('This version is not supported'), 11);
}

/*------------------------------*/
function author_information($uid){
    $query = db_select("profile" , "profile");
    $query->leftJoin("field_data_field_full_name" , "name" , "profile.pid = name.entity_id and name.bundle = 'main' and name.entity_type = 'profile2' ");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "profile.pid = about_me.entity_id and about_me.bundle = 'main' and about_me.entity_type = 'profile2' ");
    $query->fields("profile" , array("pdi"));
    $query->addField("name" , "field_full_name_value" , "full_name");
    $query->addField("about_me" , "field_about_me_value" , "about_me");
    $query->condition("profile.uid" , $uid , "IN");
}

