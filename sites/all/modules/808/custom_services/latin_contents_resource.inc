<?php

/*----------------------------------------index----------------------------------------*/
function latin_contents_resource_index($hash , $type_tid , $categories, $page , $version){
    if(!(hash_true($hash , "latin_contents"))) return services_error(t('Failed to access'), 10);
    if(strcmp($version , "pbd_0") == 0){
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

/*----------------------------------------retrieve----------------------------------------*/
function latin_contents_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "latin_contents"))) return services_error(t('Failed to access'), 10);

    if(strcmp($version , "pbd_0") == 0){
        $query = db_select("node" , "node");
        $query->leftJoin("field_data_body" , "body" , "body.entity_id = node.nid and body.entity_type = 'node' and body.bundle = 'latin_contents' ");
        $query->leftJoin("field_data_field_image" , "field_image" , "field_image.entity_id = node.nid and field_image.entity_type = 'node' and field_image.bundle = 'latin_contents' and field_image.delta = '0' ");
        $query->leftJoin("file_managed" , "image" , "image.fid = field_image.field_image_fid");
        $query->leftJoin("field_data_field_link" , "field_link" , "field_link.entity_id = node.nid and field_link.entity_type = 'node' and field_link.bundle = 'latin_contents' ");
        $query->fields("node" , array("nid" , "title" , "created" , "changed"));
        $query->fields("body" , array("body_value" , "body_summary"));
        $query->addField("image" , "uri" , "image");
        $query->addField("field_link" , "field_link_url" , "video_link");
        $query->condition("node.nid" , $nid);
        $query->condition("node.status" , 1);
        $query->condition("node.language" , "en");
        $query->condition("node.type" , "latin_contents");
        $content = $query->execute()->fetch();

        if(empty($content)) return services_error("This content is not found!" , 17);

        $query = db_select("field_data_field_latin_content_references" , "ref");
        $query->addField("ref" , "field_latin_content_references_url" , "references_url");
        $query->condition("ref.entity_id" , $content->nid);
        $query->condition("ref.bundle" , "latin_contents");
        $references = $query->execute()->fetchAll();
        if(!empty($references)){
            $content->references =  array();
            foreach ($references as $ref) array_push($content->references , $ref->references_url);
        }

        $query = db_select("field_data_field_latin_tags" , "tags");
        $query->join("taxonomy_term_data" , "taxonomy" , "tags.field_latin_tags_tid = taxonomy.tid");
        $query->addField("taxonomy" , "name" , "tag");
        $query->condition("tags.entity_id" , $content->nid);
        $query->condition("tags.bundle" , "latin_contents");
        $tags = $query->execute()->fetchAll();
        if(!empty($tags)){
            $content->tags =  array();
            foreach ($tags as $tag) array_push($content->tags , $tag->tag);
        }

        $query = db_select("taxonomy_index" , "taxonomy_index");
        $query->join("taxonomy_term_data" , "term_data" , "taxonomy_index.tid = term_data.tid");
        $query->fields("term_data" , array("tid" , "name"));
        $query->condition("taxonomy_index.nid" , $content->nid);
        $category = $query->execute()->fetch();
        $content->category_tid = $category->tid;
        $content->category_name = $category->name;

        return ["content" => $content];
    }
    return services_error(t('This version is not supported'), 11);
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

/*-------------------------------------------------------------------------------------*/
function author_information($uid){
    $query = db_select("profile" , "profile");
    $query->leftJoin("field_data_field_full_name" , "name" , "profile.pid = name.entity_id and name.bundle = 'main' and name.entity_type = 'profile2' ");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "profile.pid = about_me.entity_id and about_me.bundle = 'main' and about_me.entity_type = 'profile2' ");
    $query->fields("profile" , array("pdi"));
    $query->addField("name" , "field_full_name_value" , "full_name");
    $query->addField("about_me" , "field_about_me_value" , "about_me");
    $query->condition("profile.uid" , $uid , "IN");
}