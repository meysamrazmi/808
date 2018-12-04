<?php

/*---------------------------------operations part-------------------------------------*/
/* check the hash and find the compatible function for response
 * return list of a content type in order to parameters
 */
function content_resource_index($hash , $type , $page , $parameter){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    $source_name = (isset($parameter["source"]) && !empty($parameter["source"])) ? $parameter["source"] : "android";
    $version = (isset($parameter["version"]) && !empty($parameter["version"])) ? (int)$parameter["version"] : 0;

    $function = get_compatible_function_name("/content" , "GET" , $source_name , $version);

    if($page > 0) $parameter["page"] = $page;
    elseif (!isset($parameter["page"])) $parameter["page"] = 0;
    if(!empty($function) && strlen($function) > 0) {
        $parameter["type"] = $type;
        return call_user_func($function, $parameter);
    }

    return services_error(t('This version is not supported'), 11);
}
function list_of_contents_v_0($parameter){
    $type = $parameter["type"]; $page = $parameter["page"];
    /*Make query to fetch the contents*/
    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->leftJoin("profile" , "profile" , "profile.uid = node.uid and profile.type = 'main'");
    $query->join("field_data_field_full_name" , "name" , "name.entity_id = profile.pid and name.entity_type = 'profile2' and name.bundle = 'main'");
    $query->addField("name" , "field_full_name_value" , "author_name");
    $query->condition('node.status' , 1);
    $query->condition('node.language' , 'en' , '<>');
    $query->condition('node.type' , $type);

    /*If searching is happened, it gets the list of nodes are matched*/
    if(!empty($parameter["search_value"]) && strlen($parameter["search_value"]) > 0){
        $custom_list = search_content_by_value($parameter["search_value"] , $type);
        if(empty($custom_list)) return ["content" => array()];
    }

    if(strcmp($type , "publication") == 0){
        /*add price, author name to e-book*/
        $query->join("field_data_field_point_needed" , "price" , "node.nid = price.entity_id  and price.bundle = 'publication'");
        $query->addField("price" , "field_point_needed_value" , "price");
        $query->orderBy("node.nid" , "DESC");
        if(isset($custom_list)) $query->condition('node.nid' , $custom_list , 'IN');
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
    elseif(strcmp($type , "podcast") == 0){
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
        if(isset($custom_list)) $query->condition('node.nid' , $custom_list , 'IN');
        else $query->range($page*24 , 24);
        $contents = $query->execute()->fetchAll();
    }
    else {
        $contents =  array();
    }
    return ["content" => $contents];
}
function list_of_contents_v_1($parameter){
    global $user;

    $type = $parameter["type"]; $page = (int)$parameter["page"];
    /*Get query related to the @type*/
    $query = get_nodes_query($type);
    /*add custom features of the content type*/
    if(strcmp($type , "publication") == 0){
        $query->join("field_data_field_point_needed" , "point_needed" , "node.nid = point_needed.entity_id  and point_needed.bundle = 'publication'");
        $query->addField("point_needed" , "field_point_needed_value" , "price");

        $query->leftJoin("field_data_field_isvip" , "vip" , "node.nid = vip.entity_id and vip.bundle = 'publication' and vip.field_isvip_tid = '1760' ");
        $query->addField("vip" , "field_isvip_tid" , "free_for_vip");

        if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
            $query->condition("node.nid" , $parameter["custom_list"] , "IN");
            return $query;
        }
        if(isset($parameter["free"]) && strcmp($parameter["free"] , "1") == 0) $query->condition("point_needed.field_point_needed_value" , 0);

        if(isset($parameter["sort"]))
            switch($parameter["sort"]){
                case "last" :
                    $query->orderBy("node.nid" , "DESC");
                    break;
                case "first" :
                    $query->orderBy("node.nid" , "ASC");
                    break;
                case "cheap":
                    $query->orderBy("point_needed.field_point_needed_value" , "ASC");
                    break;
                case "expensive":
                    $query->orderBy("point_needed.field_point_needed_value" , "DESC");
                    break;
                case "popular":
                    break;
                default:
                    $query->orderBy("node.nid" , "DESC");
                    break;
            }
        else $query->orderBy("node.nid" , "DESC");
    }
    elseif(strcmp($type , "podcast") == 0){
        $query->leftJoin("field_data_field_episode" , "field_episode" , "node.nid = field_episode.entity_id and field_episode.bundle = 'podcast'");
        $query->leftJoin("file_managed" , "file_episode" , "field_episode.field_episode_fid = file_episode.fid");
        $query->leftJoin("field_data_field_episode_remote" , "episode_remote" , "node.nid = episode_remote.entity_id and episode_remote.bundle = 'podcast'");
        $query->addField('file_episode' , 'uri' , 'audio');
        $query->addField('file_episode' , 'filesize' , 'audio_size');
        $query->addField('episode_remote' , 'field_episode_remote_value' , 'audio_remote');
        $query->orderBy("node.nid" , "DESC");
        if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
            $query->condition("node.nid" , $parameter["custom_list"] , "IN");
            return $query;
        }
    }
    elseif(strcmp($type , "college") == 0){
        /*select 10th of each type of courses for showing in homepage*/
        if (isset($parameter["college_type"])  && strcmp($parameter["college_type"], "homepage") == 0) {
            $college_types = db_select("field_data_field_course_type" , "college_type")->distinct();
            $college_types->fields("college_type", array("field_course_type_value"));
            $college_types = $college_types->execute()->fetchCol();
            $contents = array();
            foreach ($college_types as $college_type){
                $newquery = clone($query);
                $newquery->join("field_data_field_course_type" , "college_type" , "node.nid = college_type.entity_id and college_type.field_course_type_value = '" . $college_type . "'");
                $newquery->orderBy("node.nid", "DESC")->range(0, 10);
                $newquery = $newquery->execute()->fetchAll();
                foreach ($newquery as $row){
                    $row->picture = image_style_url("300x300" , $row->picture);
                    if(isset($row->picture_s) && !empty($row->picture_s)) $row->picture_s = image_style_url("350x350" , $row->picture_s);
                    if (!isset($contents[$college_type])) $contents[$college_type] = array();
                    array_push($contents[$college_type] , $row);
                }
            }

            return ["content" => $contents];
        }

        /*select a specious type or all types of the courses*/
        if(isset($parameter["college_type"]) && !empty($parameter["college_type"]))
            $query->join("field_data_field_course_type", "college_type", "node.nid = college_type.entity_id and college_type.field_course_type_value = '" . $parameter["college_type"] . "'");
        else
            $query->leftJoin("field_data_field_course_type", "college_type", "node.nid = college_type.entity_id");
        $query->addField("college_type" , "field_course_type_value" , "college_type");


        $subquery = db_select("uc_product_options" , "product_options");
        $subquery->join("node" , "node" , " node.nid = product_options.nid and node.type = 'college' ");
        $subquery->fields("product_options" , array("nid" , "oid" , "cost" , "price"));
        $options_db = $subquery->execute()->fetchAll();
        $options = array();
        $options_nid = array();
        $options_off = array();
        foreach ($options_db as $option){
            array_push($options_nid , $option->nid);
            if(!isset($options[$option->nid])) $options[$option->nid] = array();
            array_push($options[$option->nid] , $option);
        }
        foreach ($options as $key => $option){
            $cost = 0;
            $price = 0;
            foreach ($option as $value){
                $cost += (int)$value->cost;
                $price += (int)$value->price;
            }
            array_push($option , array("sum_cost" => $cost));
            array_push($option , array("sum_price" => $price));
            $options[$key] = $option;
            if($price < $cost){
                array_push($options_off , $key);
            }
        }

        /*add prices of the courses*/
        $query->join("uc_products" , "product" , "node.nid = product.nid");
        $query->fields("product" , array("sell_price" , "list_price"));
        if(!empty($parameter["off"]) && $parameter["off"] == "true"){
            $query->where("sell_price < list_price");
//            if(!empty($option_off_nid))$query->("node.nid" , $option_off_nid , "IN");
        }


        /*add course step*/
        $query->leftJoin("field_data_field_course_step" , "step" , "node.nid = step.entity_id and step.bundle = 'college' ");
        /*filter courses on steps*/
        if(isset($parameter["college_step"]) && strlen($parameter["college_step"]) > 0){
            $steps = explode( "," , $parameter["college_step"]);
            $query->condition("step.field_course_step_value" , $steps , "IN");
        }
        $query->addField("step" , "field_course_step_value" , "college_step");


        /*sort the courses*/
        if(isset($parameter["sort"]))
            switch ($parameter["sort"]){
            case "last" :
                $query->orderBy("node.nid" , "DESC");
                break;
            case "first" :
                $query->orderBy("node.nid" , "ASC");
                break;
            case "cheap" :
                $query->orderBy("product.sell_price" , "ASC");
                if(!empty($options_nid)) $query->condition("node.nid" , $options_nid , "NOT IN");
                break;
            case "expensive" :
                $query->orderBy("product.sell_price" , "DESC");
                if(!empty($options_nid)) $query->condition("node.nid" , $options_nid , "NOT IN");
                break;
            case "options" :
                $query->orderBy("node.nid" , "DESC");
                if(!empty($options_nid)) $query->condition("node.nid" , $options_nid , "IN");
                break;
            default :
                $query->orderBy("node.nid" , "DESC");
                break;
        }
        else $query->orderBy("node.nid" , "DESC");
    }
    elseif(strcmp($type , "designteam") == 0){
        $query->orderBy("node.nid" , "DESC");
    }
    elseif(strcmp($type , "article") == 0){
        $query->join("field_data_field_eventtime", "eventtime", "eventtime.entity_id = node.nid and eventtime.bundle = 'article' ");
        $query->leftJoin("field_data_field_company" , "company" , "company.entity_id = node.nid and company.bundle = 'article' ");
        $query->leftJoin("field_data_field_ifwebinar" , "webinar" , "webinar.entity_id = node.nid and webinar.bundle = 'article' ");
        $query->addField("eventtime" , "field_eventtime_value" , "event_time");
        $query->addField("company" , "field_company_value" , "company");
        $query->addField("webinar" , "field_ifwebinar_value" , "webinar");
        $query->condition("eventtime.field_eventtime_value", date("Y-m-d", time()) , ">=");
        $query->orderBy("eventtime.field_eventtime_value", "ASC");
    }

    /*Fetch 20 record per each iteration*/
    $query->range($page*20, 20);
    $contents = $query->execute()->fetchAll();

    /*Post process of data and make them similar*/
    foreach ($contents as $content) {
        $content->nid = (int)$content->nid;
        $content->uid = (int)$content->uid;
        if(isset($content->picture) && !empty($content->picture)) $content->picture = image_style_url("300x300", $content->picture);
        if(isset($content->picture_s) && !empty($content->picture_s)) $content->picture_s = image_style_url("350x350", $content->picture_s);
        if(isset($content->audio_size)) $content->audio_size = (int) $content->audio_size;
        if(isset($content->audio) && !empty($content->audio)) $content->audio = generate_file_address($content->audio);
        if(strcmp($content->type , "college") == 0){
            $content->list_price = round($content->list_price , 0);
            $content->sell_price = round($content->sell_price , 0);
            $content->off = false;

            $off = false;
            $festival = false;
            if(in_array($content->nid , $options_off) || $content->sell_price < $content->list_price) $off = true;
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => 0.2, "message" => "20% تخفیف جشنواره");
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            $content->discount = $discount;

            switch ($content->college_step){
                case "0" :
                    $content->college_step = array("id" => 0 , "state" => "در حال ثبت نام");
                    break;
                case "1" :
                    $content->college_step = array("id" => 1 , "state" => "در حال برگزاری");
                    break;
                case "2" :
                    $content->college_step = array("id" => 2 , "state" => "برگزار شده");
                    break;
            }
        }
        if(strcmp($type , "publication") == 0){
            $content->price = (int) $content->price;

            if (empty($content->free_for_vip)) $free_for_vip = false;
            else $free_for_vip = true;
            unset($content->free_for_vip);

            $discount = new stdClass();
            if($content->price != 0){
                /*this is used for discount on festival*/
                $festival = false;

                $vip = false;
                if (in_array("Vip", $user->roles)) $vip = true;

                if ($vip && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "enable" => true, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                    $content->price = 0;
                }
                elseif ($vip && !$free_for_vip && !$festival) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
                    $content->price = 0.9 * $content->price;
                }
                elseif (!$vip && !$festival && $free_for_vip) {
                    $discount = array("name" => "free", "color" => 2, "enable" => false, "amount" => 1, "message" => "رایگان برای کاربران VIP");
                }
                elseif (!$vip && !$festival && !$free_for_vip) {
                    $discount = array("name" => "vip", "color" => 3, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
                }
                elseif ($festival) {
                    $discount = array("name" => "festival", "color" => 1, "enable" => true, "amount" => 0.2, "message" => "20% تخفیف جشنواره");
                    $content->price = 0.8 * $content->price;
                }
            }
            $content->discount = $discount;
        }
    }

    return array("content" => $contents);
}
/*
 * Make query for fetching the contents of a content type
 * Return a query
 */
function get_nodes_query($type){
    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'changed'));
    $query->leftJoin("profile" , "profile" , "profile.uid = node.uid and profile.type = 'main'");
    $query->leftJoin("field_data_field_full_name" , "name" , "name.entity_id = profile.pid and name.entity_type = 'profile2' and name.bundle = 'main'");
    $query->leftJoin("field_data_field_image", "field_image", "node.nid = field_image.entity_id and field_image.delta = '0' and  field_image.bundle = '" . $type . "'");
    $query->leftJoin("file_managed", "file_image", "field_image.field_image_fid = file_image.fid");
    if(strcmp($type , "college") == 0 || strcmp($type , "podcast") == 0){
        $query->leftJoin("field_data_field_image", "image_s", "node.nid = image_s.entity_id and image_s.delta = '1' and  field_image.bundle = '" . $type . "'");
        $query->leftJoin("file_managed", "file_image_s", "image_s.field_image_fid = file_image_s.fid");
        $query->addField('file_image_s', 'uri', 'picture_s');
    }
    $query->addField('file_image', 'uri', 'picture');
    $query->addField("name" , "field_full_name_value" , "author_name");
    $query->condition('node.status' , 1);
    $query->condition('node.type' , $type);

    return $query;
}
/*
 * Return list of nodes that contain the value
 * It's used for searching in contents
 */
function search_content_by_value($value , $type){
    /*search the value in titles*/
    $query = db_select("node", "node");
    $query->fields('node', array('nid'));
    $query->condition('node.title', '%' . db_like($value) . '%', 'LIKE');
    $query->condition('node.type' , $type);
    $nid1 = $query->execute()->fetchCol();

    /*search the value in bodies*/
    $query = db_select("field_data_body", "body");
    $query->fields('body', array('entity_id'));
    $query->condition('body.body_value', '%' . db_like($value) . '%', 'LIKE');
    $query->condition('body.entity_type' , 'node');
    $query->condition('body.bundle' , $type);
    $nid2 = $query->execute()->fetchCol();

    $custom_list = array_merge($nid1, $nid2);
    $custom_list = array_unique($custom_list);

    return $custom_list;
}

function content_resource_retrieve($hash , $nid , $parameter){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    $source_name = (isset($parameter["source"]) && !empty($parameter["source"])) ? $parameter["source"] : "android";
    $version = (isset($parameter["version"]) && !empty($parameter["version"])) ? (int)$parameter["version"] : 0;

    $function = get_compatible_function_name("/content/nid" , "GET" , $source_name , $version);

    if(!empty($function) && strlen($function) > 0) {
        $parameter["nid"] = $nid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function retrieve_a_content_v_0($parameter){
    $nid = $parameter["nid"];
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
    return ["node" => array()];
}
function retrieve_a_content_v_1($parameter){
    $nid = $parameter["nid"];
    global $user;

    $query = db_select("node" , "node");
    $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.field_image_fid");
    $query->leftJoin("field_data_body" , "body" , "node.nid = body.entity_id");
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'created' , 'changed'));
    $query->addField('picture' , 'uri' , 'picture');
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.status' , 1);
    $query->condition('node.nid' , $nid);
    $node = $query->execute()->fetch();
    if(empty($node)) return services_error("Content not found!" , 17);

    $node->picture = image_style_url("800x600" , $node->picture);
    $node->body = preg_replace('/(<[^>]+) style=".*?"/i', '$1', $node->body);
    if(strpos($node->body, "<!--break-->") != false) $node->body = substr($node->body, 0, strpos($node->body, "<!--break-->"));

    if(strcmp($node->type , "publication") == 0){
        $query = db_select("field_data_field_publish_file" , "field_file_published");
        $query->join("file_managed" , "file_published" , "field_file_published.field_publish_file_fid = file_published.fid and field_file_published.bundle = 'publication' and field_file_published.entity_id = " . $nid);
        $query->addField('field_file_published' , 'entity_id' , 'nid');
        $query->addField('file_published' , 'uri' , 'sample_file');
        $sample_file = $query->execute()->fetch();
        $node->sample_file = generate_file_address($sample_file->sample_file);

        $query = db_select('field_data_field_pagenumber' , 'page_number');
        $query->addField('page_number' , 'field_pagenumber_value' , 'page_number');
        $query->condition('page_number.entity_id' , $node->nid);
        $query->condition('page_number.bundle' , 'publication');
        $page_number = $query->execute()->fetch();
        if(!empty($page_number)) $node->page_number = (int)$page_number->page_number;

        $file_permission = false;
        $query = db_select('field_data_field_point_needed', 'price');
        $query->addField('price', 'field_point_needed_value', 'price');
        $query->condition('price.entity_id', $nid);
        $query->condition('price.entity_type', 'node');
        $query->condition('price.bundle', 'publication');
        $price = $query->execute()->fetch();
        $node->price = (!empty($price)) ? (int) $price->price : 0;
        $node->original_price = $node->price;

        $discount = new stdClass();
        if($price->price == 0) $file_permission = true;
        else {
            $query = db_select('field_data_field_isvip', 'vip');
            $query->fields('vip', array('field_isvip_tid'));
            $query->condition('vip.entity_id', $nid);
            $query->condition('vip.bundle', 'publication');
            $query->condition('vip.field_isvip_tid', 1760);
            $free_for_vip = $query->execute()->fetch();
            $free_for_vip = empty($free_for_vip) ? false : true;

            $vip = false;
            if (in_array('Vip', $user->roles)) $vip = true;
            $festival = false;

            if ($vip && $free_for_vip) {
                $file_permission = true;
                $node->price = 0;
                $discount = array("name" => "free" , "color" => 2, "enable" => true, "amount" => 1, "message" => "رایگان برای کاربران VIP");
            }
            elseif ($vip && !$free_for_vip && !$festival) {
                $discount = array("name" => "vip" , "color" => 3, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
                $node->price = 0.9 * $node->price;
            }
            elseif(!$vip && !$festival && $free_for_vip){
                $discount = array("name" => "free" , "color" => 2, "enable" => false, "amount" => 1, "message" => "رایگان برای کاربران VIP");
            }
            elseif(!$vip && !$festival && !$free_for_vip){
                $discount = array("name" => "vip" , "color" => 3, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            elseif($festival){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => 0.2, "message" => "20% تخفیف جشنواره");
                $node->price = 0.8 * $node->price;
            }

            if (!$file_permission && $user->uid > 0){
                $query = db_select('m_buyed_nodes', 'buyed');
                $query->fields('buyed', array('id', 'uid', 'nid'));
                $query->condition('buyed.uid', $user->uid);
                $query->condition('buyed.nid', $nid);
                $user_buyed = $query->execute()->fetch();
                if(!empty($user_buyed)) {
                    $file_permission = true;
                }
            }
        }
        $node->discount = $discount;

        if($file_permission){
            $node->bought = true;
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
                    $file->uri = generate_file_address($file->uri);
                    $file->filesize = (int) $file->filesize;
                    array_push($node->files , $file);
                }
            }
        }
        else $node->bought = false;
    }
    elseif(strcmp($node->type , "college") == 0){
        $query = db_select("field_data_field_image" , "field_image");
        $query->join("file_managed" , "picture_s" , "picture_s.fid = field_image.field_image_fid");
        $query->addField('picture_s' , 'uri' , 'picture_s');
        $query->condition("field_image.entity_id" , $node->nid);
        $query->condition("field_image.entity_type" , "node");
        $query->condition("field_image.delta" , "1");
        $picture_s = $query->execute()->fetch();
        $node->picture_s = (!empty($picture_s)) ? image_style_url("350x350" , $picture_s->picture_s) : null;

        $query = db_select("field_data_field_course_type", "college_type");
        $query->addField("college_type" , "field_course_type_value" , "college_type");
        $query->condition( "college_type.entity_id" , $node->nid);
        $query->condition( "college_type.bundle" , "college");
        $college_types = $query->execute()->fetchAll();
        $node->college_types = array();
        foreach ($college_types as $college_type) array_push($node->college_types , $college_type->college_type);


        $query = db_select("uc_products" , "uc_products");
        $query->fields("uc_products" , array("model" , "list_price" , "sell_price"));
        $query->condition("uc_products.nid" , $nid);
        $product = $query->execute()->fetch();
        $node->model = (!empty($product->model)) ? $product->model : "";
        $node->list_price = (!empty($product->list_price)) ? round($product->list_price, 0) : null;
        $node->sell_price = (!empty($product->sell_price)) ? round($product->sell_price, 0) : null;
        $query = db_select("uc_product_options" , "product_options");
        $query->join("node" , "node" , "node.nid = product_options.nid and node.nid = '" . $node->nid . "'");
        $query->join("uc_attribute_options" , "options" , "product_options.oid = options.oid");
        $query->fields("product_options" , array("cost" , "price"));
        $query->fields("options" , array("name"));
        $options = $query->execute()->fetchAll();
        $price = 0; $cost = 0;
        foreach ($options as $option){
            $option->cost = (int) $option->cost;
            $option->price = (int) $option->price;
            $price += $option->price;
            $cost += $option->cost;
        }
        $node->options = $options;
        $discount = new stdClass();
        $off = false;
        $festival = false;
        if($node->sell_price < $node->list_price || $price < $cost) $off = true;
        if($festival && $off){
            $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => 0.2, "message" => "20% تخفیف جشنواره");
        }
        elseif($off){
            $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
        }
        $node->discount = $discount;


        $query = db_select("field_data_field_film" , "field_film");
        $query->join("file_managed" , "film" , "film.fid = field_film.field_film_fid and field_film.bundle = 'college' ");
        $query->addField("film" , "uri" , "film");
        $query->condition("field_film.entity_id" , $nid);
        $film = $query->execute()->fetch();
        $node->film_link = (!empty($film)) ? generate_file_address($film->film) : null;


        $query = db_select("field_data_field_course_step" , "step");
        $query->fields("step" , array("field_course_step_value"));
        $query->condition("step.entity_id" , $node->nid)->condition("step.bundle" , "college");
        $step = $query->execute()->fetch();
        if(!empty($step)) {
            switch ($step->field_course_step_value){
                case "0" :
                    $node->step = array("id" => 0 , "state" => "در حال ثبت نام");
                    break;
                case "1" :
                    $node->step = array("id" => 1 , "state" => "در حال برگزاری");
                    break;
                case "2" :
                    $node->step = array("id" => 2 , "state" => "برگزار شده");
                    break;
            }
        }else{
            $node->step = array();
        }

        $query = db_select("field_data_field_how_to_be_held" , "how_to_be_held");
        $query->join("taxonomy_term_data" , "term" , "how_to_be_held.field_how_to_be_held_tid = term.tid");
        $query->fields("term" , array("name"));
        $query->condition("how_to_be_held.entity_id" , $node->nid);
        $query->condition("how_to_be_held.bundle" , "college");
        $how_to_be_held = $query->execute()->fetchCol();
        $node->how_to_be_held = (!empty($how_to_be_held)) ? $how_to_be_held : array();

        $query = db_select("field_data_field_academic" , "academic");
        $query->join("taxonomy_term_data" , "term" , "academic.field_academic_tid = term.tid");
        $query->fields("term" , array("name"));
        $query->condition("academic.entity_id" , $node->nid);
        $query->condition("academic.bundle" , "college");
        $field_academic = $query->execute()->fetchCol();
        $node->field_academic = (!empty($field_academic)) ? $field_academic : array();

        $query = db_select("field_data_field_eventtime" , "eventtime");
        $query->fields("eventtime" , array("field_eventtime_value"));
        $query->condition("eventtime.entity_id" , $node->nid);
        $query->condition("eventtime.bundle" , "college");
        $start_time = $query->execute()->fetch();
        $node->start_time = (!empty($start_time)) ? $start_time->field_eventtime_value : null;

        $query = db_select("field_data_field_edu_time" , "edu_time");
        $query->fields("edu_time" , array("field_edu_time_value"));
        $query->condition("edu_time.entity_id" , $node->nid);
        $query->condition("edu_time.bundle" , "college");
        $event_time = $query->execute()->fetch();
        $node->event_time = (!empty($event_time)) ? $event_time->field_edu_time_value : null;

        $query = db_select("field_data_field_edu_duration" , "duration");
        $query->fields("duration" , array("field_edu_duration_value"));
        $query->condition("duration.entity_id" , $node->nid);
        $query->condition("duration.bundle" , "college");
        $duration = $query->execute()->fetch();
        $node->duration = (!empty($duration)) ? $duration->field_edu_duration_value : null;

        $query = db_select("field_data_field_company" , "company");
        $query->fields("company" , array("field_company_value"));
        $query->condition("company.entity_id" , $node->nid);
        $query->condition("company.bundle" , "college");
        $company = $query->execute()->fetch();
        $node->company = (!empty($company)) ? $company->field_company_value : null;

    }
    else return services_error("This content type is not supported!" , 17);

    $query = db_select("users" , "user");
    $query->join("profile" , "profile" , "user.uid = profile.uid and profile.type = 'main' ");
    $query->leftJoin("field_data_field_full_name" , "full_name" , "full_name.entity_id = profile.pid");
    $query->leftJoin("field_data_field_about_me" , "about_me" , "about_me.entity_id = profile.pid");
    $query->leftJoin("file_managed" , "file_managed" , "file_managed.fid = user.picture");
    $query->addField("full_name" , "field_full_name_value" , "name");
    $query->addField('about_me' , 'field_about_me_value' , 'about');
    $query->addField("file_managed" , "uri" , "picture");
    $query->condition("user.uid" , $node->uid);
    $author = $query->execute()->fetch();
    if(!empty($author)) {
        $author->picture = image_style_url("200x200" , $author->picture);
        $node->author = $author;
    }

    if(bookmark_status($nid , $user->uid) == true) $node->bookmark = 1;
    else $node->bookmark = 0;


    $node->nid = (int) $node->nid;
    $node->uid = (int) $node->uid;
    $node->created = (int) $node->created;
    $node->changed = (int) $node->changed;

    return $node;
}
/*--------------------------------------------------------------------------------*/

/*---------------------------------action part------------------------------------*/
function content_resource_search_previous($hash , $type , $value){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    return list_of_contents_v_0(array("type" => $type , "search_value" => $value));
}
/*--------------------------------------------------------------------------------*/

/*------------------------------target action part-------------------------------**/
function bookmark_content($nid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "content"))) return services_error(t('Failed to access'), 10);

    $source_name = isset($data["source"]) ? $data["source"] : "android";
    $version = isset($data["version"]) ? $data["version"] : 1;

    $function = get_compatible_function_name("/content/nid/bookmark" , "POST" , $source_name , $version);

    if(!empty($function) && strlen($function) > 0) {
        $data["nid"] = $nid;

        return call_user_func($function, $data);
    }

    return services_error(t('This version is not supported'), 11);
}
function bookmark_a_content_v1($data){
    global $user;
    if(!$user->uid > 0) return services_error("User is not logged in!" , 18);

    if((strcmp($data['action'], "bookmark") == 0 || $data['action'] == 1) && bookmark_status($data["nid"] , $user->uid) == false){
        $fid = db_insert('flagging')
            ->fields(array(
                'fid' => 1,
                'entity_type' => 'node',
                'entity_id' => (int)$data["nid"],
                'uid' => $user->uid,
                'sid' => 0,
                'timestamp' => REQUEST_TIME
            ))
            ->execute();

        if($fid > 1) return true;
        else return false;
    }
    elseif((strcmp($data['action'], "unbookmark") == 0 || $data['action'] == 0) && bookmark_status($data["nid"] , $user->uid) == true){
        $num_deleted = db_delete('flagging')
            ->condition('uid', $user->uid)
            ->condition('entity_id', $data["nid"])
            ->condition('fid', 1)
            ->execute();

        if($num_deleted == 1) return true;
        else return false;
    }
    else return services_error("The action is not valid!", 18);
}
function bookmark_status($nid , $uid){
    $query = db_select('flagging' , 'flagging')
        ->condition('fid' , 1)
        ->condition('entity_id' , $nid)
        ->condition('uid' , $uid);
    $count = $query->countQuery()->execute()->fetchField();

    if($count > 0) return true;
    else return false;
}
/*--------------------------------------------------------------------------------*/

/*--------------------------------relationships part------------------------------*/
/*search a value in all contents*/
function content_resource_search($list , $parameter){
    if(!(hash_true($parameter["hash"] , "content"))) return services_error(t('Failed to access'), 10);
    $source_name = (isset($parameter["source"]) && !empty($parameter["source"])) ? $parameter["source"] : "android";
    $version = (isset($parameter["version"]) && !empty($parameter["version"])) ? (int)$parameter["version"] : 0;

    $function = get_compatible_function_name("/content/list/search" , "GET" , $source_name , $version);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function content_search_list_v_1($parameter){
    /*$types shows that in which contents the value should be searched
     *if it's empty search will be done in all types
     */
    if(isset($parameter["types"])) $types = explode("," , $parameter["types"]);
    $all_types = array("publication" , "podcast" , "college" , "video" , "designteam" , "article" , "pedia");

    /*search in titles*/
    $query = db_select("node" , "node");
    $query->fields("node" , array("nid"));
    $query->condition("node.title" , '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $first = $query->execute()->fetchCol();
    /*search in bodies*/
    $query = db_select("field_data_body" , "body");
    $query->fields("body" , array("entity_id"));
    $query->condition("body.body_value" , '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $second = $query->execute()->fetchCol();
    /*merge all nids that are found*/
    $nids = array_merge($first , $second);
    if(empty($nids)) return array("contents" => []);

    /*get information of nids*/
    $query = db_select("node" , "node");
    $query->leftJoin("field_data_field_image", "field_image", "node.nid = field_image.entity_id and field_image.delta = '0' ");
    $query->leftJoin("file_managed", "image", "field_image.field_image_fid = image.fid");
    $query->condition("node.status" , 1);
    $query->condition("node.nid" , $nids , "IN");
    $query->orderBy("node.nid" , "DESC");
    $query->addField("node" , "type" , "type");
    $type_count_query = clone($query);
    $query->condition("node.type" , (isset($types) && !empty($types)) ? $types : $all_types , "IN"); //use filter or not
    $query->fields("node" , array("nid" , "title"));
    $query->addField("image" , "uri" , "image");
    $query->range((isset($parameter["page"])) ? $parameter["page"]*20 : 0, 20);
    $contents = $query->execute()->fetchAll();

    /*shows the result's number of each types*/
    $type_count_query->condition("node.type" , $all_types , "IN");
    $type_count_query->groupBy("node.type")->addExpression("count(node.type)" , "count");
    $type_count_query = $type_count_query->execute()->fetchAll();
    $type_count = array();
    foreach ($type_count_query as $value) $type_count[$value->type] = (int)$value->count;


    foreach($contents as $content){
        $content->nid = (int) $content->nid;
        if(!empty($content->image)) $content->image = image_style_url("350x350" , $content->image);
    }

    return array("contents" => $contents , "count" => $type_count);
}


function content_resource_content_type($nid , $parameter){
    if(!(hash_true($parameter["hash"] , "content"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/content/nid/type" , "GET" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        $parameter["nid"] = $nid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function content_type_v_1($parameter){
    $type = db_select("node")->fields("node" , array("type"))->condition("nid" , $parameter["nid"])->condition("status" , 1)->execute()->fetch();

    if(empty($type)) return services_error("Invalid nid!" , 13);
    return $type->type;
}
/*--------------------------------------------------------------------------------*/