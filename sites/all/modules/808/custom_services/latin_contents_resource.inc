<?php

/*----------------------------------------index----------------------------------------*/
function latin_contents_resource_index($parameters){
    if(!isset($parameters["hash"]) || !(hash_true($parameters["hash"] , "latin_contents"))) return services_error(t('Failed to access'), 10);

    if(!isset($parameters["source"]) || !isset($parameters["version"])) services_error();

    $function = get_compatible_function_name("/latin_contents" , "GET" , $parameters["source"] , $parameters["version"]);

    if (!isset($parameters["page"])) $parameters["page"] = 0;

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameters);
    }

    return services_error(t('This version is not supported'), 11);
}

function list_of_latin_contents_v_0($parameters){
    $query = db_select("node" , "node");
    $query->leftJoin("field_data_field_image" , "field_image" , "field_image.entity_id = node.nid and field_image.bundle = 'latin_contents'");
    $query->leftJoin("file_managed" , "file_managed" , "file_managed.fid = field_image.field_image_fid");
    $query->fields("node" , array("nid" , "title" , "created"));
    $query->addField("file_managed" , "uri" , "picture");
    $query->condition("node.type" , "latin_contents")->condition("node.language" , "en");
    $query->orderBy("node.nid" , "DESC");
    $query->range($parameters["page"] * 30 , 30);
    $contents = $query->execute()->fetchAll();

    $nids = array();
    $new_contents = array();
    foreach ($contents as $content){
        $content->picture = image_style_url("300x300" , $content->picture);
        $content->tags = array();
        $content->types = array();
        $content->categories = array();
        $content->topics = array();
        array_push($nids , $content->nid);
        $new_contents[$content->nid] = $content;
    }

    $query = db_select("field_data_field_latin_tags" , "tags");
    $query->leftJoin("taxonomy_term_data" , "tag_name" , "tag_name.tid = tags.field_latin_tags_tid");
    $query->fields("tags" , array("entity_id"));
    $query->fields("tag_name" , array("tid" , "name"));
    $query->condition("tags.entity_id" , $nids , "IN")->condition("tags.bundle" ,  "latin_contents");
    $tags = $query->execute()->fetchAll();
    foreach ($tags as $tag) array_push($new_contents[$tag->entity_id]->tags , array("tid" => $tag->tid , "name" => $tag->name));

    $query = db_select("field_data_field_latin_contents_types" , "types");
    $query->leftJoin("taxonomy_term_data" , "type_name" , "type_name.tid = types.field_latin_contents_types_tid");
    $query->fields("types" , array("entity_id"));
    $query->fields("type_name" , array("tid" , "name"));
    $query->condition("types.entity_id" , $nids , "IN")->condition("types.bundle" ,  "latin_contents");
    $types = $query->execute()->fetchAll();
    foreach ($types as $type) array_push($new_contents[$type->entity_id]->types , array("tid" => $type->tid , "name" => $type->name));

    $query = db_select("field_data_field_latin_contents_categories" , "categories");
    $query->leftJoin("taxonomy_term_data" , "category_name" , "category_name.tid = categories.field_latin_contents_categories_tid");
    $query->fields("categories" , array("entity_id"));
    $query->fields("category_name" , array("tid" , "name"));
    $query->condition("categories.entity_id" , $nids , "IN")->condition("categories.bundle" ,  "latin_contents");
    $categories = $query->execute()->fetchAll();
    foreach ($categories as $category) array_push($new_contents[$category->entity_id]->categories , array("tid" => $category->tid , "name" => $category->name));

    $query = db_select("field_data_field_latin_contents_topics" , "topics");
    $query->leftJoin("taxonomy_term_data" , "topic_name" , "topic_name.tid = topics.field_latin_contents_topics_tid");
    $query->fields("topics" , array("entity_id"));
    $query->fields("topic_name" , array("tid" , "name"));
    $query->condition("topics.entity_id" , $nids , "IN")->condition("topics.bundle" ,  "latin_contents");
    $topics = $query->execute()->fetchAll();
    foreach ($topics as $topic) array_push($new_contents[$topic->entity_id]->topics , array("tid" => $topic->tid , "name" => $topic->name));

    $contents = array_values($new_contents);

    return $contents;
}

/*----------------------------------------retrieve----------------------------------------*/
function latin_contents_resource_retrieve($nid , $parameters){
    if(!isset($parameters["hash"]) || !(hash_true($parameters["hash"] , "latin_contents"))) return services_error(t('Failed to access'), 10);

    if(!isset($parameters["source"]) || !isset($parameters["version"])) services_error();

    $function = get_compatible_function_name("/latin_contents/nid" , "GET" , $parameters["source"] , $parameters["version"]);

    $parameters["nid"] = $nid;
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameters);
    }

    return services_error(t('This version is not supported'), 11);
}

function retrieve_latin_content_v_0($parameters){
    $query = db_select("node" , "node");
    $query->leftJoin("field_data_body" , "body" , "body.entity_id = node.nid");
    $query->leftJoin("field_data_field_image" , "field_image" , "field_image.entity_id = node.nid and field_image.bundle = 'latin_contents'");
    $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.field_image_fid");
    $query->leftJoin("field_data_field_eventtime" , "eventtime" , "eventtime.entity_id = node.nid and eventtime.bundle = 'latin_contents' ");
    $query->leftJoin("field_data_field_company" , "company" , "company.entity_id = node.nid and company.bundle = 'latin_contents' ");
    $query->leftJoin("field_data_field_ifwebinar" , "webinar" , "webinar.entity_id = node.nid and webinar.bundle = 'latin_contents' ");
    $query->leftJoin("field_data_field_event_808_suggestion" , "808_suggestion" , "808_suggestion.entity_id = node.nid and 808_suggestion.bundle = 'latin_contents' ");
    $query->leftJoin("field_data_field_link" , "link" , "link.entity_id = node.nid and link.bundle = 'latin_contents' ");
    $query->fields("node" , array("nid" , "title" , "uid" , "created"));
    $query->addField("body" , "body_value" , "body");
    $query->addField("picture" , "uri" , "picture");
    $query->fields("eventtime" , array("field_eventtime_value"));
    $query->fields("company" , array("field_company_value"));
    $query->fields("webinar" , array("field_ifwebinar_value"));
    $query->fields("808_suggestion" , array("field_event_808_suggestion_value"));
    $query->addField("link" , "field_link_url" , "video");
    $query->condition("node.nid" , $parameters["nid"]);
    $query->condition("node.status" , 1);
    $query->condition("node.type" , "latin_contents");
    $content = $query->execute()->fetch();

    $content->picture = image_style_url("300x300" , $content->picture);

    $query = db_select("field_data_field_latin_tags" , "tags");
    $query->join("taxonomy_term_data" , "tag_name" , "tag_name.tid = tags.field_latin_tags_tid");
    $query->fields("tag_name" , array("tid" , "name"));
    $query->condition("tags.entity_id" , $content->nid);
    $content->tags = $query->execute()->fetchAll();

    $query = db_select("field_data_field_latin_contents_types" , "types");
    $query->join("taxonomy_term_data" , "type_name" , "type_name.tid = types.field_latin_contents_types_tid");
    $query->fields("type_name" , array("tid" , "name"));
    $query->condition("types.entity_id" , $content->nid);
    $content->types = $query->execute()->fetchAll();

    $query = db_select("field_data_field_latin_contents_categories" , "categories");
    $query->join("taxonomy_term_data" , "category_name" , "category_name.tid = categories.field_latin_contents_categories_tid");
    $query->fields("category_name" , array("tid" , "name"));
    $query->condition("categories.entity_id" , $content->nid);
    $content->categories = $query->execute()->fetchAll();

    $query = db_select("field_data_field_latin_contents_topics" , "topics");
    $query->join("taxonomy_term_data" , "topic_name" , "topic_name.tid = topics.field_latin_contents_topics_tid");
    $query->fields("topic_name" , array("tid" , "name"));
    $query->condition("topics.entity_id" , $content->nid);
    $content->topics = $query->execute()->fetchAll();

    $query = db_select("field_data_field_files" , "field_file");
    $query->join("file_managed" , "file_managed" , "file_managed.fid = field_file.field_files_fid");
    $query->addField("file_managed" , "uri" , "file");
    $query->condition("field_file.entity_id" , $content->nid);
    $query->condition("field_file.bundle" , "latin_contents");
    $content->files = $query->execute()->fetchAll();

    $query = db_select("field_data_field_latin_content_references" , "references_url");
    $query->addField("references_url" , "field_latin_content_references_url" , "url");
    $query->condition("references_url.entity_id" , $content->nid);
    $query->condition("references_url.bundle" , "latin_contents");
    $content->references = $query->execute()->fetchAll();

    return $content;
}

/*-------------------------------------------------------------------------------------*/
function author_information($uid){
    $query = db_select("profile" , "profile");
    $query->leftJoin("field_data_field_full_name" , "name" , "profile.pid = name.entity_id and name.bundle = 'main' and name.entity_type = 'profile2' ");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "profile.pid = about_me.entity_id and about_me.bundle = 'main' and about_me.entity_type = 'profile2' ");
    $query->fields("profile" , array("pid"));
    $query->addField("name" , "field_full_name_value" , "full_name");
    $query->addField("about_me" , "field_about_me_value" , "about_me");
    $query->condition("profile.uid" , $uid , "IN");
}