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
    $type = $parameter["type"];
    $page = isset($parameter["page"]) ? (int)$parameter["page"] : 0;
    $limit = isset($parameter["limits"]) ? (int)$parameter["limits"] : 20;

    /*Get query related to the @type*/
    $query = get_nodes_query($type);
    /*add custom features of the content type*/
    if(strcmp($type , "publication") == 0){
        $query = publication($query , $parameter);
    }
    elseif(strcmp($type , "podcast") == 0){
        $query = podcast($query , $parameter);
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

        /* fetch the default option price*
         * If the college has no price we use default option price instead
         */
        $attributest = db_select("uc_product_attributes" , "p_attar");
        $attributest->join("uc_product_options" , "a_options" , "a_options.oid = p_attar.default_option");
        $attributest->fields("p_attar" , array("nid"));
        $attributest->fields("a_options" , array("cost" , "price"));
        $attributest->orderBy("p_attar.aid" , "DESC");
        $query->leftJoin($attributest , "defaults" , "node.nid = defaults.nid");
        $query->addField("defaults" , "price" , "default_option_price");
        $query->addField("defaults" , "cost" , "default_option_cost");

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

        if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
            $query->condition("node.nid" , $parameter["custom_list"] , "IN");
            return $query;
        }
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
        $query = designteam($query , $parameter);
    }
    elseif(strcmp($type , "article") == 0){
        $query = article($query , $parameter);
    }

    /*if it calls from other functions with custom nids*/
    if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
        $query->condition("node.nid" , $parameter["custom_list"] , "IN");
        return $query;
    }

    /*Fetch 20 record per each iteration*/
    $query->range($page*$limit, $limit);
    $contents = $query->execute()->fetchAll();

    /*Post process of data and make them similar*/
    $festival_settings = festivals();
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
            if($content->list_price == 0 && !empty($content->default_option_cost)) $content->list_price = (int) $content->default_option_cost;
            if($content->sell_price == 0 && !empty($content->default_option_price)) $content->sell_price = (int) $content->default_option_price;
            unset($content->default_option_price);
            unset($content->default_option_cost);

            $festival = $festival_settings["college"]["festival"];
            $off = false;
            if(in_array($content->nid , $options_off) || $content->sell_price < $content->list_price) $off = true;
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_settings["college"]["percent"], "message" => $festival_settings["college"]["message"]);
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
                $festival = $festival_settings["college"]["publication"];

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
                    $discount = array("name" => "festival", "color" => 1, "enable" => true, "amount" => $festival_settings["publication"]["percent"], "message" => $festival_settings["publication"]["message"]);
                    $content->price = (1 - ["publication"]["percent"]) * $content->price;
                }
            }
            $content->discount = $discount;
        }
    }

    return array("content" => $contents);
}
function list_of_contents_v_2($parameter){
    if(strcmp($parameter["type"] , "homepage") == 0) return homepage_content_v_2($parameter);

    global $user;
    $type = $parameter["type"];
    $page = isset($parameter["page"]) ? (int)$parameter["page"] : 0;
    $limit = isset($parameter["limits"]) ? (int)$parameter["limits"] : 20;

    $response = array();
    /*Get query related to the @type*/
    $query = get_nodes_query($type);

    /*add custom features of the content type*/
    if(strcmp($type , "publication") == 0){
        $query = publication($query , $parameter);
    }
    elseif(strcmp($type , "podcast") == 0){
        $query = podcast($query , $parameter);
    }
    elseif(strcmp($type , "college") == 0){
        /*fetch the distinct course_types and send them in response*/
        $course_type = db_select("field_data_field_course_type" , "course_type")->distinct();
        $course_type->fields("course_type" , array("field_course_type_value"));
        $response["college_type"] = $course_type->execute()->fetchCol();

        /*filter the colleges based on type*/
        if(isset($parameter["college_type"]) && !empty($parameter["college_type"])) {
            $college_type = explode("," , $parameter["college_type"]);

            $query->join("field_data_field_course_type", "college_type", "node.nid = college_type.entity_id and college_type.delta = '0' ");
            $query->condition("college_type.field_course_type_value" , $college_type , "IN");
        }
        else
            $query->leftJoin("field_data_field_course_type", "college_type", "node.nid = college_type.entity_id and college_type.delta = '0' ");
        $query->addField("college_type" , "field_course_type_value" , "college_type");

        /* fetch the options for each college
         * we gather the nid of the contents that have options
         * we gather sum of the costs and prices for checking the discount
         * */
        $subquery = db_select("uc_product_options" , "product_options");
        $subquery->join("node" , "node" , " node.nid = product_options.nid and node.type = 'college' ");
        $subquery->fields("product_options" , array("nid" , "oid" , "cost" , "price"));
        $options_db = $subquery->execute()->fetchAll();
        $options = array();
        $options_nid = array();
        $options_off = array();
        /*fill $options_nid*/
        foreach ($options_db as $option){
            array_push($options_nid , $option->nid);
            if(!isset($options[$option->nid])) $options[$option->nid] = array();
            array_push($options[$option->nid] , $option);
        }
        /*fill $options_off*/
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

        /* fetch the default option price*
         * If the college has no price we use default option price instead
         */
        $attributest = db_select("uc_product_attributes" , "p_attar");
        $attributest->join("uc_product_options" , "a_options" , "a_options.oid = p_attar.default_option");
        $attributest->fields("p_attar" , array("nid"));
        $attributest->fields("a_options" , array("cost" , "price"));
        $attributest->orderBy("p_attar.aid" , "DESC");
        $query->leftJoin($attributest , "defaults" , "node.nid = defaults.nid");
        $query->addField("defaults" , "price" , "default_option_price");
        $query->addField("defaults" , "cost" , "default_option_cost");


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

        /*return query with custom nid*/
        if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
            $query->condition("node.nid" , $parameter["custom_list"] , "IN");
            return $query;
        }

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
    elseif(strcmp($type , "education") == 0){
        $query->orderBy("node.nid" , "DESC");
    }
    elseif(strcmp($type , "product_kit") == 0){
        $query = product_kit($query , $parameter);
    }
    elseif(strcmp($type , "designteam") == 0){
        $query = designteam($query , $parameter);
    }
    elseif(strcmp($type , "article") == 0){
        $query = article($query , $parameter);
    }
    elseif(strcmp($type , "film") == 0){
        $query = film($query , $parameter);
    }

    /*if it calls from other functions with custom nids*/
    if(isset($parameter["custom_list"]) && !empty($parameter["custom_list"])){
        $query->condition("node.nid" , $parameter["custom_list"] , "IN");
        return $query;
    }

    /*Fetch 20 record per each iteration*/
    $query->range($page*$limit, $limit);
    $contents = $query->execute()->fetchAll();

    /*Post process of data and make them similar*/
    $festival_settings = festivals();
    foreach ($contents as $content) {
        $content->nid = (int)$content->nid;
        $content->uid = (int)$content->uid;
        $content->changed = (int)$content->changed;
        if(isset($content->film_time) && !empty($content->film_time)) $content->film_time = (int)$content->film_time;
        if(strlen($content->webinar) > 0) $content->webinar = (int)$content->webinar;
        if(isset($content->picture) && !empty($content->picture)) $content->picture = image_style_url("300x300", $content->picture);
        if(isset($content->picture_s) && !empty($content->picture_s)) $content->picture_s = image_style_url("350x350", $content->picture_s);
        if(isset($content->audio_size)) $content->audio_size = (int) $content->audio_size;
        if(isset($content->audio) && !empty($content->audio)) $content->audio = generate_file_address($content->audio);
        if(strcmp($content->type , "college") == 0){
            $content->list_price = round($content->list_price , 0);
            $content->sell_price = round($content->sell_price , 0);
            if($content->list_price == 0 && !empty($content->default_option_cost)) $content->list_price = (int) $content->default_option_cost;
            if($content->sell_price == 0 && !empty($content->default_option_price)) $content->sell_price = (int) $content->default_option_price;
            unset($content->default_option_price);
            unset($content->default_option_cost);

            $festival = $festival_settings["college"]["festival"];
            $off = false;
            if(in_array($content->nid , $options_off) || $content->sell_price < $content->list_price) $off = true;

            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_settings["college"]["percent"], "message" => $festival_settings["college"]["message"]);
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
                $festival = $festival_settings["publication"]["festival"];

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
                    $discount = array("name" => "festival", "color" => 1, "enable" => true, "amount" => $festival_settings["publication"]["percent"], "message" => $festival_settings["publication"]["message"]);
                    $content->price = (1 - $festival_settings["publication"]["percent"]) * $content->price;
                }
            }
            $content->discount = $discount;
        }
        if(strcmp($type , "product_kit") == 0){
            $content->list_price = (int) $content->list_price;
            $content->sell_price = (int) $content->sell_price;

            $catalog = empty($content->catalog) ? false : true;
            $vip = false;
            if (in_array("Vip", $user->roles)) $vip = true;
            unset($content->catalog);

            $off = ($content->sell_price < $content->list_price) ? true : false;
            $festival = $festival_settings["product_kit"]["festival"];
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_settings["product_kit"]["percent"], "message" => $festival_settings["product_kit"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            elseif($catalog && $vip){
                $content->sell_price = 0.9 * $content->sell_price;
                $discount = array("name" => "vip", "color" => 2, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            elseif($catalog && !$vip){
                $discount = array("name" => "vip", "color" => 4, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            $content->discount = $discount;
        }
    }

    $response["content"] = $contents;

    return $response;
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
    if(strcmp($type , "product") == 0 || strcmp($type , "product_kit") == 0){
        $query->leftJoin("field_data_uc_product_image" , "uc_product_image" , "uc_product_image.entity_id = node.nid and uc_product_image.delta = '0' and uc_product_image.bundle = '" . $type . "'");
        $query->leftJoin("file_managed" , "file_image" , "file_image.fid = uc_product_image.uc_product_image_fid");
    }
    elseif(strcmp($type , "film") == 0){
        $query->leftJoin("field_data_field_posterfilm", "posterfilm", "node.nid = posterfilm.entity_id and posterfilm.bundle = '" . $type . "'");
        $query->leftJoin("file_managed", "file_image", "posterfilm.field_posterfilm_fid = file_image.fid");
    }
    else{
        $query->leftJoin("field_data_field_image", "field_image", "node.nid = field_image.entity_id and field_image.delta = '0' and  field_image.bundle = '" . $type . "'");
        $query->leftJoin("file_managed", "file_image", "field_image.field_image_fid = file_image.fid");
    }
    if(strcmp($type , "education") == 0 || strcmp($type , "college") == 0 || strcmp($type , "podcast") == 0){
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
function publication($query , $parameter){
    /*add ebooks prices*/
    $query->join("field_data_field_point_needed" , "point_needed" , "node.nid = point_needed.entity_id  and point_needed.bundle = 'publication'");
    $query->addField("point_needed" , "field_point_needed_value" , "price");

    /*add the filed "isvip" */
    $query->leftJoin("field_data_field_isvip" , "vip" , "node.nid = vip.entity_id and vip.bundle = 'publication' and vip.field_isvip_tid = '1760' ");
    $query->addField("vip" , "field_isvip_tid" , "free_for_vip");

    /*filter on free ebooks*/
    if(isset($parameter["free"]) && strcmp($parameter["free"] , "1") == 0) $query->condition("point_needed.field_point_needed_value" , 0);

    /*sort ebooks*/
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

    return $query;
}
function podcast($query , $parameter){
    $query->leftJoin("field_data_field_episode" , "field_episode" , "node.nid = field_episode.entity_id and field_episode.bundle = 'podcast'");
    $query->leftJoin("file_managed" , "file_episode" , "field_episode.field_episode_fid = file_episode.fid");
    $query->leftJoin("field_data_field_episode_remote" , "episode_remote" , "node.nid = episode_remote.entity_id and episode_remote.bundle = 'podcast'");
    $query->addField('file_episode' , 'uri' , 'audio');
    $query->addField('file_episode' , 'filesize' , 'audio_size');
    $query->addField('episode_remote' , 'field_episode_remote_value' , 'audio_remote');
    $query->orderBy("node.nid" , "DESC");

    return $query;
}
function product_kit($query , $parameter){
    $query->join("field_data_field_text" , "field_text" , "node.nid = field_text.entity_id and field_text.bundle = 'product_kit' and field_text.entity_type = 'node' ");
    $query->addField("field_text" , "field_text_value" , "model");

    $query->leftJoin("field_data_taxonomy_catalog" , "catalog" , "node.nid = catalog.entity_id and catalog.bundle = 'product_kit' and catalog.taxonomy_catalog_tid = '3751' ");
    $query->addField("catalog" , "taxonomy_catalog_tid" , "catalog");

    $products = db_select("uc_product_kits");
    $products->join("uc_products" , "uc_products" , "uc_products.nid = uc_product_kits.product_id");
    $products->fields("uc_product_kits" , array("nid"));
    $products->groupBy("uc_product_kits.nid");
    $products->addExpression("sum(list_price)" , "list_price");
    $products->addExpression("sum(sell_price)" , "sell_price");
    $query->join($products , "price" , "price.nid = node.nid");
    $query->fields("price" , array("list_price" , "sell_price"));

    if(isset($parameter["sort"]))
        switch ($parameter["sort"]){
            case "last" :
                $query->orderBy("node.nid" , "DESC");
                break;
            case "first" :
                $query->orderBy("node.nid" , "ASC");
                break;
            case "cheap" :
                $query->orderBy("price.sell_price" , "ASC");
                break;
            case "expensive" :
                $query->orderBy("price.sell_price" , "DESC");
                break;
            default :
                $query->orderBy("node.nid" , "DESC");
                break;
        }
    else $query->orderBy("node.nid" , "DESC");

    return $query;
}
function designteam($query , $parameter){
    $query->orderBy("node.nid" , "DESC");
    return $query;
}
function article($query , $parameter){
    $query->join("field_data_field_eventtime", "eventtime", "eventtime.entity_id = node.nid and eventtime.bundle = 'article' ");
    $query->leftJoin("field_data_field_company" , "company" , "company.entity_id = node.nid and company.bundle = 'article' ");
    $query->leftJoin("field_data_field_ifwebinar" , "webinar" , "webinar.entity_id = node.nid and webinar.bundle = 'article' ");
    $query->addField("eventtime" , "field_eventtime_value" , "event_time");
    $query->addField("company" , "field_company_value" , "company");
    $query->addField("webinar" , "field_ifwebinar_value" , "webinar");
    $query->condition("eventtime.field_eventtime_value", date("Y-m-d", time()) , ">=");
    $query->orderBy("eventtime.field_eventtime_value", "ASC");

    return $query;
}
function film($query , $parameter){
    if(!empty($parameter["tid"])) {
        $query->join("field_data_field__playlist", "playlist", "playlist.entity_id = node.nid and playlist.bundle = 'film' and playlist.field__playlist_tid = ' " . $parameter["tid"] . " ' ");
    }

    $query->join("field_data_field_film_time" , "film_time" , "film_time.entity_id = node.nid and film_time.bundle = 'film' ");
    $query->addField("film_time" , "field_film_time_value" , "film_time");

    $query->orderBy("node.nid" , "DESC");

    return $query;
}

/*
 * return the content 30 content for homepage just for version 2 of android app
 * */
function homepage_content_v_2($parameter){
    $types = array("college" , "education" , "product_kit");
    $response = array();
    foreach ($types as $type){
        $query = get_nodes_query($type);
        $query->orderBy("node.nid" , "DESC");
        $query->range(0 , 10);
        $contents = $query->execute()->fetchAll();
        foreach ($contents as $content){
            $content->nid = (int) $content->nid;
            unset ($content->uid);
            unset ($content->changed);
            unset ($content->author_name);
            unset ($content->picture_s);
            $content->picture = !empty($content->picture) ? image_style_url("300x300" , $content->picture) : null;
        }
        $response[$type] = $contents;
    }
    return $response;
}

/*last contents of site for desktop App*/
function last_content_desktop_v_1($parameter){
    $types = array("product" , "product_kit" , "college");
    $response = array();
    foreach ($types as $type){
        $query = get_nodes_query($type);
        $query->orderBy("node.nid" , "DESC");
        $query->range(0 , 10);
        $contents = $query->execute()->fetchAll();
        foreach ($contents as $content){
            $content->nid = (int) $content->nid;
            unset ($content->uid);
            unset ($content->changed);
            unset ($content->author_name);
            unset ($content->picture_s);
            $content->picture = !empty($content->picture) ? image_style_url("400x225" , $content->picture) : null;
            unset($content->type);
            $content->url = "https://civil808.com/node/" . $content->nid;
        }
        $response[$type] = $contents;
    }
    return $response;
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
    $type = db_select("node" , "node")->fields("node" , array("type"))->condition("nid" , $nid)->condition("status" , 1)->execute()->fetch();
    if(empty($type)) return services_error("Node is not found!" , 404);
    $type = $type->type;

    global $user;
    $festival_setting = festivals();

    /*fetch node data*/
    $query = db_select("node" , "node");
    $query->fields('node' , array('nid' , 'type' , 'title' , 'uid' , 'created' , 'changed'));
    $query->condition('node.status' , 1);
    $query->condition('node.nid' , $nid);

    /*add body*/
    $query->leftJoin("field_data_body" , "body" , "node.nid = body.entity_id");
    $query->addField('body' , 'body_value' , 'body');

    /*add features based on content type*/
    switch ($type){
        case "publication" :
            /*add picture*/
            $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.bundle = 'publication' and field_image.delta = '0' ");
            $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.field_image_fid");
            $query->addField('picture' , 'uri' , 'picture');

            /*add sample file*/
            $query->leftJoin("field_data_field_publish_file" , "field_file_published" , "node.nid = field_file_published.entity_id and field_file_published.entity_type = 'node' and field_file_published.bundle = 'publication' ");
            $query->join("file_managed" , "file_published" , "file_published.fid = field_file_published.field_publish_file_fid");
            $query->addField('file_published' , 'uri' , 'sample_file');

            /*add page number*/
            $query->leftJoin("field_data_field_pagenumber" , "page_number" , "node.nid = page_number.entity_id and page_number.entity_type = 'node' and page_number.bundle = 'publication' ");
            $query->addField('page_number' , 'field_pagenumber_value' , 'page_number');

            /*add price*/
            $query->leftJoin("field_data_field_point_needed" , "price" , "node.nid = price.entity_id and price.entity_type = 'node' and price.bundle = 'publication' ");
            $query->addField('price', 'field_point_needed_value', 'price');

            $node = $query->execute()->fetch();

            if(!empty($node->sample_file)) $node->sample_file = generate_file_address($node->sample_file);
            $node->page_number = empty($node->page_number) ? 0 :(int)$node->page_number;
            $node->price = !empty($node->price) ? (int) $node->price : 0;
            $node->original_price = $node->price;

            /*add discount and check file permission*/
            $file_permission = false;
            $discount = new stdClass();
            if($node->price == 0) $file_permission = true;
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
                $festival = $festival_setting["publication"]["festival"];

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
                    $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["publication"]["percent"], "message" => $festival_setting["publication"]["message"]);
                    $node->price = (1 - $festival_setting["publication"]["percent"]) * $node->price;
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

            /*add files if it has permission*/
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

            break;
        case "college" :
            /*add picture*/
            $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.bundle = 'college' and field_image.delta = '0' ");
            $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.field_image_fid");
            $query->addField('picture' , 'uri' , 'picture');

            /*add square picture*/
            $query->leftJoin("field_data_field_image" , "field_image_s" , "node.nid = field_image_s.entity_id and field_image_s.entity_type = 'node' and field_image_s.bundle = 'college' and field_image_s.delta = '1' ");
            $query->leftJoin("file_managed" , "picture_s" , "picture_s.fid = field_image_s.field_image_fid");
            $query->addField('picture_s' , 'uri' , 'picture_s');

            /*add film*/
            $query->leftJoin("field_data_field_film" , "field_film" , "node.nid = field_film.entity_id and field_film.entity_type = 'node' and field_film.bundle = 'college' and field_film.delta = '0' ");
            $query->leftJoin("file_managed" , "film" , "film.fid = field_film.field_film_fid");
            $query->addField("film" , "uri" , "film_link");

            /*add company*/
            $query->leftJoin("field_data_field_company" , "company" , "node.nid = company.entity_id and company.entity_type = 'node' and company.bundle = 'college'");
            $query->addField("company" , "field_company_value" , "company");

            /*add event time*/
            $query->leftJoin("field_data_field_eventtime" , "eventtime" , "node.nid = eventtime.entity_id and eventtime.entity_type = 'node' and eventtime.bundle = 'college'");
            $query->addField("eventtime" , "field_eventtime_value" , "start_time");

            /*add duration*/
            $query->leftJoin("field_data_field_edu_duration" , "duration" , "node.nid = duration.entity_id and duration.entity_type = 'node' and duration.bundle = 'college'");
            $query->addField("duration" , "field_edu_duration_value" , "duration");

            /*time of the holding of college*/
            $query->leftJoin("field_data_field_edu_time" , "edu_time" , "node.nid = edu_time.entity_id and edu_time.entity_type = 'node' and edu_time.bundle = 'college'");
            $query->addField("edu_time" , "field_edu_time_value" , "event_time");

            /*add the model and prices*/
            $query->leftJoin("uc_products" , "uc_products" , "node.nid = uc_products.nid");
            $query->fields("uc_products" , array("model" , "list_price" , "sell_price"));

            $node = $query->execute()->fetch();

            if(!empty($node->film_link)) $node->film_link =  generate_file_address($node->film_link);
            $node->list_price = !empty($node->list_price) ? round($node->list_price, 0) : 0;
            $node->sell_price = !empty($node->sell_price) ? round($node->sell_price, 0) : 0;

            /*add types of the collage*/
            $query = db_select("field_data_field_course_type", "college_type");
            $query->addField("college_type" , "field_course_type_value" , "college_type");
            $query->condition( "college_type.entity_id" , $node->nid);
            $query->condition( "college_type.bundle" , "college");
            $college_types = $query->execute()->fetchAll();
            $node->college_types = array();
            foreach ($college_types as $college_type) array_push($node->college_types , $college_type->college_type);

            /*add the step of the college*/
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

            /*add how it is held*/
            $query = db_select("field_data_field_how_to_be_held" , "how_to_be_held");
            $query->join("taxonomy_term_data" , "term" , "how_to_be_held.field_how_to_be_held_tid = term.tid");
            $query->fields("term" , array("name"));
            $query->condition("how_to_be_held.entity_id" , $node->nid);
            $query->condition("how_to_be_held.bundle" , "college");
            $how_to_be_held = $query->execute()->fetchCol();
            $node->how_to_be_held = !empty($how_to_be_held) ? $how_to_be_held : array();

            /*add academic field*/
            $query = db_select("field_data_field_academic" , "academic");
            $query->join("taxonomy_term_data" , "term" , "academic.field_academic_tid = term.tid");
            $query->fields("term" , array("name"));
            $query->condition("academic.entity_id" , $node->nid);
            $query->condition("academic.bundle" , "college");
            $field_academic = $query->execute()->fetchCol();
            $node->field_academic = (!empty($field_academic)) ? $field_academic : array();

            /*add options*/
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

            /*check if there is discount or not*/
            $discount = new stdClass();
            $off = false;
            $festival = $festival_setting["college"]["festival"];
            if($node->sell_price < $node->list_price || $price < $cost) $off = true;
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["college"]["price"], "message" => $festival_setting["college"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            $node->discount = $discount;

            break;
        case "education" :
            /*add picture*/
            $query->leftJoin("field_data_field_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.bundle = 'education'  and field_image.delta = '0' ");
            $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.field_image_fid");
            $query->addField('picture' , 'uri' , 'picture');

            /*add square page*/
            $query->leftJoin("field_data_field_image" , "field_image_s" , "node.nid = field_image_s.entity_id and field_image_s.entity_type = 'node' and field_image_s.bundle = 'education' and field_image_s.delta = '1' ");
            $query->leftJoin("file_managed" , "picture_s" , "picture_s.fid = field_image_s.field_image_fid");
            $query->addField('picture_s' , 'uri' , 'picture_s');

            /*add film*/
            $query->leftJoin("field_data_field_videoamozesh" , "videoamozesh" , "node.nid = videoamozesh.entity_id and videoamozesh.bundle = 'education' ");
            $query->leftJoin("file_managed" , "film" , "film.fid = videoamozesh.field_videoamozesh_fid ");
            $query->addField("film" , "uri" , "film_link");

            /*add event time*/
            $query->leftJoin("field_data_field_eventtime" , "eventtime" , "node.nid = eventtime.entity_id and eventtime.bundle = 'education' ");
            $query->addField("eventtime" , "field_eventtime_value" , "start_time");

            /*add company*/
            $query->leftJoin("field_data_field_company" , "company" , "node.nid = company.entity_id and company.bundle = 'education' ");
            $query->addField("company" , "field_company_value" , "company");

            /*add if covered by Webinar*/
            $query->leftJoin("field_data_field_ifwebinar" , "ifwebinar" , "node.nid = ifwebinar.entity_id and ifwebinar.bundle = 'education' ");
            $query->addField("ifwebinar" , "field_ifwebinar_value" , "ifwebinar");

            $node = $query->execute()->fetch();

            $node->ifwebinar = (int) $node->ifwebinar;
            if(!empty($node->film_link)) $node->film_link = generate_file_address($node->film_link);

            break;
        case "product_kit" :
            /*fetch product image*/
            $query->leftJoin("field_data_uc_product_image" , "field_image" , "node.nid = field_image.entity_id and field_image.entity_type = 'node' and field_image.bundle = 'product_kit' and field_image.delta = '0' ");
            $query->leftJoin("file_managed" , "picture" , "picture.fid = field_image.uc_product_image_fid");
            $query->addField('picture' , 'uri' , 'picture');

            /*fetch the description*/
            $query->leftJoin("field_data_field_costum_content" , "custom_content" , "node.nid = custom_content.entity_id and custom_content.entity_type = 'node' and custom_content.bundle = 'product_kit'");
            $query->addField('custom_content' , 'field_costum_content_value' , 'description');

            /*fetch the film*/
            $query->leftJoin("field_data_field_files" , "field_files" , "node.nid = field_files.entity_id and field_files.entity_type = 'node' and field_files.bundle = 'product_kit' ");
            $query->leftJoin("file_managed" , "files" , "files.fid = field_files.field_files_fid");
            $query->addField("files" , "uri" , "film_link");

            /*fetch the model*/
            $query->leftJoin("field_data_field_text" , "field_text" , "node.nid = field_text.entity_id and field_text.entity_type = 'node' and field_text.bundle = 'product_kit'");
            $query->addField("field_text" , "field_text_value" , "model");

            /*check if it is 808package or not*/
            $query->leftJoin("field_data_taxonomy_catalog" , "catalog" , "node.nid = catalog.entity_id and catalog.entity_type = 'node' and catalog.bundle = 'product_kit' and catalog.taxonomy_catalog_tid = '3751'");
            $query->addField("catalog" , "taxonomy_catalog_tid" , "catalog");

            $node = $query->execute()->fetch();

            /*fetch the products of this package*/
            $products = db_select("uc_product_kits");
            $products->join("uc_products" , "uc_products" , "uc_products.nid = uc_product_kits.product_id");
            $products->join("node" , "node" , "node.nid = uc_products.nid");
            $products->leftJoin("field_data_uc_product_image" , "uc_product_image" , "uc_product_image.entity_id = node.nid and uc_product_image.delta = '0' and uc_product_image.bundle = 'product' ");
            $products->leftJoin("file_managed" , "picture" , "picture.fid = uc_product_image.uc_product_image_fid");
            $products->fields("uc_product_kits" , array("product_id"));
            $products->fields("uc_products" , array("list_price" , "sell_price"));
            $products->fields("node" , array("title"));
            $products->addField("picture" , "uri" , "picture");
            $products->condition("uc_product_kits.nid" , $node->nid);
            $products = $products->execute()->fetchAll();

            /*calculate the total price for the package*/
            $list_price = 0;
            $sell_price = 0;
            foreach ($products as $value){
                $value->product_id = (int)$value->product_id;
                $value->list_price = (int)$value->list_price;
                $value->sell_price = (int)$value->sell_price;
                $list_price += $value->list_price;
                $sell_price += $value->sell_price;
                $value->url = "https://civil808.com/node/" . $value->product_id;
                $value->picture = !empty($value->picture) ? image_style_url("200x200" , $value->picture) : null;
            }
            $node->products = $products;
            $node->list_price = $list_price;
            $node->sell_price = $sell_price;

            /*check if the user is VIP or not*/
            $vip = false;
            if (in_array("Vip", $user->roles)) $vip = true;

            /*check if it is 808package or not*/
            $catalog = empty($node->catalog) ? false : true;
            unset($node->catalog);

            /*check if there is discount or not*/
            $festival = $festival_setting["product_kit"]["festival"];
            $off = ($sell_price < $list_price) ? true : false;
            $discount = new stdClass();
            if($festival && $off){
                $discount = array("name" => "festival" , "color" => 1, "enable" => true, "amount" => $festival_setting["product_kit"]["price"], "message" => $festival_setting["product_kit"]["message"]);
            }
            elseif($off){
                $discount = array("name" => "off" , "color" => 2, "enable" => true, "amount" => 0.2, "message" => "فروش ویژه");
            }
            elseif($catalog && $vip){
                $node->sell_price = 0.9 * $node->sell_price;
                $discount = array("name" => "vip", "color" => 2, "enable" => true, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            elseif($catalog && !$vip){
                $discount = array("name" => "vip", "color" => 4, "enable" => false, "amount" => 0.1, "message" => "10% تخفیف VIP");
            }
            $node->discount = $discount;

            break;
        case "film" :
            /*add image*/
            $query->leftJoin("field_data_field_posterfilm" , "posterfilm" , "node.nid = posterfilm.entity_id and posterfilm.entity_type = 'node' and posterfilm.bundle = 'film' and posterfilm.delta = '0' ");
            $query->leftJoin("file_managed" , "picture" , "picture.fid = posterfilm.field_posterfilm_fid");
            $query->addField('picture' , 'uri' , 'picture');

            /*add film time*/
            $query->leftJoin("field_data_field_film_time" , "film_time" , "node.nid = film_time.entity_id and film_time.entity_type = 'node' ");
            $query->addField('film_time' , 'field_film_time_value' , 'film_time');

            /*add film*/
            $query->leftJoin("field_data_field_files" , "field_film" , "node.nid = field_film.entity_id and field_film.entity_type = 'node' and field_film.bundle = 'film' and field_film.delta = '0' ");
            $query->leftJoin("file_managed" , "film" , "film.fid = field_film.field_files_fid");
            $query->addField("film" , "uri" , "film");

            $node = $query->execute()->fetch();

            $node->film_time = empty($node->film_time) ? 0 : (int) $node->film_time;
            if(!empty($node->film)) $node->film = generate_file_address($node->film);

            break;
        default :
            return services_error("Node is not found!" , 404);
            break;
    }

    /*---------post process----------*/
    if(!empty($node->picture)) $node->picture = image_style_url("800x600" , $node->picture);
    if(!empty($node->picture_s)) $node->picture_s = image_style_url("350x350" , $node->picture_s);

    $node->nid = (int) $node->nid;
    $node->uid = (int) $node->uid;
    $node->created = (int) $node->created;
    $node->changed = (int) $node->changed;

    $node->body = preg_replace('/(<[^>]+) style=".*?"/i', '$1', $node->body);
    $node->body = preg_replace('/<iframe.*?\/iframe>/i','', $node->body);
    if(strpos($node->body, "<!--break-->") != false) $node->body = substr($node->body, 0, strpos($node->body, "<!--break-->"));
    $parts = explode('="/sites/default', $node->body);
    $node->body = implode('="https://civil808.com/sites/default', $parts);
    $parts = explode('="/node/', $node->body);
    $node->body = implode('="https://civil808.com/node/', $parts);
    $parts = explode('="/taxonomy/', $node->body);
    $node->body = implode('="https://civil808.com/taxonomy/', $parts);
    /*------------------------------*/


    /*---------add author info----------*/
    $query = db_select("users" , "user");
    $query->condition("user.uid" , $node->uid);
    $query->join("profile" , "profile" , "user.uid = profile.uid and profile.type = 'main' ");

    /*add full name*/
    $query->leftJoin("field_data_field_full_name" , "full_name" , "full_name.entity_id = profile.pid");
    $query->addField("full_name" , "field_full_name_value" , "name");

    /*add bio*/
    $query->leftJoin("field_data_field_about_me" , "about_me" , "about_me.entity_id = profile.pid");
    $query->addField('about_me' , 'field_about_me_value' , 'about');

    /*add user picture*/
    $query->leftJoin("file_managed" , "file_managed" , "file_managed.fid = user.picture");
    $query->addField("file_managed" , "uri" , "picture");

    $author = $query->execute()->fetch();

    if(!empty($author)) {
        if(!empty($author->picture)) $author->picture = image_style_url("200x200" , $author->picture);
        $node->author = $author;
    }
    /*----------------------------------*/


    /*check if user bookmark the content or not*/
    if(bookmark_status($nid , $user->uid) == true) $node->bookmark = 1;
    else $node->bookmark = 0;

    return $node;
}
/*--------------------------------------------------------------------------------*/

/*---------------------------------action part------------------------------------*/
function content_resource_search_previous($hash , $type , $value){
    if(!(hash_true($hash , "content"))) return services_error(t('Failed to access'), 10);
    return list_of_contents_v_0(array("type" => $type , "search_value" => $value));
}
/*
 * Return list of nodes that contain the value
 * It's used for searching in contents on version 0
 * Do not delete it
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
    $parameter["all_types"] = array("publication", "podcast", "college", "designteam", "article");
    $parameter["type_count"] = array("publication" => 0, "podcast" => 0, "college" => 0, "designteam" => 0, "article" => 0);
    return search($parameter);
}
function content_search_list_v_2($parameter){
    /*$types shows that in which contents the value should be searched
     *if it's empty search will be done in all types
     */
    $parameter["all_types"] = array("publication" , "podcast" , "college" , "designteam" , "article" , "education" , "product_kit");
    $parameter["type_count"] = array("publication" => 0, "podcast" => 0, "college" => 0, "designteam" => 0, "article" => 0 , "education" => 0, "product_kit" => 0);
    return search($parameter);
}
function content_search_list_v_3($parameter){
    /*$types shows that in which contents the value should be searched
     *if it's empty search will be done in all types
     */
    $parameter["all_types"] = array("publication" , "podcast" , "college" , "designteam" , "article" , "education" , "product_kit" , "film");
    $parameter["type_count"] = array("publication" => 0, "podcast" => 0, "college" => 0, "designteam" => 0, "article" => 0 , "education" => 0, "product_kit" => 0, "film" => 0);

    return search($parameter);
}
function search($parameter){
    if(isset($parameter["types"])) $types = explode("," , $parameter["types"]);
    /*$types shows that in which contents the value should be searched
     *if it's empty search will be done in all types
     */
    $persian = ['۰', '۱', '۲', '۳', '۴', '۵', '۶', '۷', '۸', '۹'];
    $num = range(0, 9);
    $parameter["value"] = str_replace($num , $persian, $parameter["value"]);

    $page = isset($parameter["page"]) ? (int)$parameter["page"] : 0;
    $limit = isset($parameter["limits"]) ? (int)$parameter["limits"] : 20;

    /*search in titles*/
    $query = db_select("node" , "node");
    $query->fields("node" , array("nid"));
    $query->condition("node.title" , '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $query->condition("node.status" , 1);
    $nids = $query->execute()->fetchCol();
    if(empty($nids)) return array("contents" => []);

    /*get information of nids*/
    $query = db_select("node" , "node");
    $query->fields("node" , array("nid" , "title" , "type"));
    $query->condition("node.nid" , $nids , "IN");
    $type_count_query = clone($query);
    $query->condition("node.type" , (isset($types) && !empty($types)) ? $types : $parameter["all_types"] , "IN"); //use filter or not

    $query->leftJoin("field_data_field_image", "field_image", "node.nid = field_image.entity_id and field_image.delta = '0' ");
    $query->leftJoin("file_managed", "image", "field_image.field_image_fid = image.fid");
    $query->addField("image" , "uri" , "image");

    $query->leftJoin("field_data_uc_product_image" , "uc_product_image" , "uc_product_image.entity_id = node.nid and uc_product_image.delta = '0' and uc_product_image.bundle = 'product_kit' ");
    $query->leftJoin("file_managed" , "product_image" , "product_image.fid = uc_product_image.uc_product_image_fid");
    $query->addField("product_image" , "uri" , "product_image");

    $query->leftJoin("field_data_field_posterfilm", "posterfilm", "node.nid = posterfilm.entity_id and posterfilm.bundle = 'film'  and posterfilm.delta = '0'");
    $query->leftJoin("file_managed", "poster_film", "posterfilm.field_posterfilm_fid = poster_film.fid");
    $query->addField("poster_film" , "uri" , "poster_film");

    $query->orderBy("node.nid" , "DESC");

    $query->range($page*$limit, $limit);

    $contents = $query->execute()->fetchAll();

    /*shows the result's number of each types*/
    $type_count_query->condition("node.type" , $parameter["all_types"] , "IN");
    $type_count_query->groupBy("node.type")->addExpression("count(node.type)" , "count");
    $type_count_query = $type_count_query->execute()->fetchAll();

    $type_count = $parameter["type_count"];
    foreach ($type_count_query as $value) $type_count[$value->type] = (int)$value->count;

    foreach($contents as $content){
        $content->nid = (int) $content->nid;
        $content->image = null;
        if(!empty($content->content_image)) $content->image = image_style_url("350x350" , $content->content_image);
        elseif(!empty($content->product_image)) $content->image = image_style_url("350x350" , $content->product_image);
        elseif(!empty($content->poster_film)) $content->image = image_style_url("350x350" , $content->poster_film);
        unset($content->content_image);
        unset($content->product_image);
        unset($content->poster_film);
    }

    return array("contents" => $contents , "count" => $type_count);
}

/*return the type of each nid*/
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

/*return the list of suggestion contents to user*/
function content_resource_suggestion_content_to_user($list , $parameter){
    if(!(hash_true($parameter["hash"] , "content"))) return services_error('Failed to access', 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);
    $function = get_compatible_function_name("/content/uid/related_purchased" , "GET" , $parameter["source"] , $parameter["version"]);

    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function content_suggestion_desktop_v_1($parameter){
    global $user;
    /*if user is not logged in return the last products*/
    if($user->uid == 0) return last_content_desktop_v_1(array());

    /*get the list of products that user purchased*/
    $param["uid"] = $user->uid;
    module_load_include("inc", "custom_services", "user_resource");
    $purchased_contents = user_purchased_products_list_desktop_v_1($param);

    $purchased_nids = array();
    foreach ($purchased_contents as $purchased_content){
        foreach ($purchased_content as $content){
            array_push($purchased_nids , $content->nid);
        }
    }

    $related_nids = array();
    if(!empty($purchased_nids)) {
        /*fetch products that are related to $purchased_contents*/
        $query = db_select("field_data_field_experts", "main_node");
        $query->join("field_data_field_experts", "related_node", "related_node.field_experts_tid = main_node.field_experts_tid and related_node.entity_type = 'node' ");
        $query->condition("main_node.entity_id", $purchased_nids, "IN");
        $query->condition("main_node.entity_type", "node");
        $query->condition("related_node.entity_id", $purchased_nids, "NOT IN");
        $query->condition("related_node.bundle", array("product", "product_kit", "college"));
        $query->fields("related_node", array("entity_id"));
        $related_nids = array_merge($related_nids , $query->execute()->fetchCol());
    }
    /*fetch the products that are related to the user expert*/
    $query = db_select("field_data_field_experts" , "user_expert");
    $query->join("profile" , "profile" , "user_expert.entity_id = profile.pid and profile.type = 'main' and profile.uid = '" . $parameter["uid"] . "'");
    $query->join("field_data_field_experts" , "related_node" , "related_node.field_experts_tid = user_expert.field_experts_tid and related_node.entity_type = 'node' ");
    $query->fields("related_node" , array("entity_id"));
    $query->condition("related_node.bundle" , array("product" , "product_kit" , "college"));
    $related_nids = array_merge($related_nids , $query->execute()->fetchCol());
    if(empty($related_nids)) return array();

    $related_contents = array("product" => array() , "product_kit" => array() , "college" => array());
    /*make the data for related nids*/
    $query = db_select("node" , "node");

    $query->leftJoin("field_data_uc_product_image" , "p_field_image" , "p_field_image.entity_id = node.nid and p_field_image.entity_type = 'node' and p_field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "p_image" , "p_image.fid = p_field_image.uc_product_image_fid");
    $query->addField("p_image" , "uri" , "p_image");

    $query->leftJoin("field_data_field_image" , "c_field_image" , "c_field_image.entity_id = node.nid and c_field_image.entity_type = 'node' and c_field_image.delta = '0' ");
    $query->leftJoin("file_managed" , "c_image" , "c_image.fid = c_field_image.field_image_fid ");
    $query->addField("c_image" , "uri" , "c_image");

    $query->fields("node" , array("nid" , "type" , "title"));
    $query->condition("node.nid" , $related_nids , "IN");
    $query->condition("node.status" , 1);
    $contents = $query->execute()->fetchAll();
    if(empty($contents)) return array();

    /*categorize the response with the types*/
    foreach ($contents as $content){
        $content->nid = (int) $content->nid;

        if(!empty($content->p_image)) $content->picture = image_style_url("400x225" , $content->p_image);
        elseif(!empty($content->c_image)) $content->picture = image_style_url("400x225" , $content->c_image);
        else $content->picture = null;
        unset($content->p_image);
        unset($content->c_image);

        $type = $content->type;
        unset($content->type);

        $content->url = "https://civil808.com/node/" . $content->nid;
        if(count($related_contents[$type]) < 10) array_push($related_contents[$type] , $content);
    }

    /*if there is not enough content add the last ones*/
    $last_contents = last_content_desktop_v_1(array());
    $types = array_keys($related_contents);
    foreach ($types as $type){
        $i = 0;
        while (count($related_contents[$type]) < 10){
            array_push($related_contents[$type] , $last_contents[$type][$i]);
            $i++;
        }
    }

    return $related_contents;
}

function content_resource_playlist($url , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "content"))) return services_error(t('Failed to access'), 403);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 406);

    $function = get_compatible_function_name("/content/film/playlist" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 404);
}
function gallery_film_playlist_v_1($parameter){
    $tids = array(5260, 4206, 3665, 3375, 2966, 2607, 2602, 2566, 2551, 2550, 2547, 2546, 2525, 2430, 2567, 2569, 2566, 2551);
    $page = isset($parameter["page"]) ? $parameter["page"] : 0;
    $limit = isset($parameter["limits"]) ? $parameter["limits"] : 20;

    $subquery = db_select("node" , "node");
    $subquery->condition("node.type" , "film");
    $subquery->condition("node.status" , 1);

    $subquery->join("field_data_field__playlist" , "playlist" , "node.nid = playlist.entity_id");
    $subquery->fields("playlist" , array("field__playlist_tid"));
    $subquery->condition("playlist.field__playlist_tid" , $tids , "IN");
    $subquery->groupBy("playlist.field__playlist_tid");
    $subquery->addExpression("count(playlist.entity_id)" , "film_counts");

    $subquery->join("field_data_field_posterfilm", "field_image", "node.nid = field_image.entity_id and field_image.delta = '0' and  field_image.bundle = 'film' ");
    $subquery->join("file_managed", "file_image", "field_image.field_posterfilm_fid = file_image.fid");
    $subquery->addField('file_image', 'uri', 'picture');


    $query = db_select("taxonomy_term_data" , "playlist");
    $query->fields("playlist" , array("tid" , "name"));
    $query->condition("playlist.vid" , 25);
    $query->condition("playlist.tid" , $tids , "IN");

    $query->leftJoin($subquery , "meta_data" , "meta_data.field__playlist_tid = playlist.tid");
    $query->fields("meta_data" , array("picture" , "film_counts"));

    $query->orderBy("playlist.tid" , "DESC");
    $query->range($page*$limit , $limit);

    $playlist = $query->execute()->fetchAll();

    foreach ($playlist as $value){
        $value->tid = (int) $value->tid;
        $value->film_counts = (int) $value->film_counts;
        $value->picture = image_style_url("350x350" , $value->picture);
    }

    return $playlist;
}

function content_resource_film($tid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "content"))) return services_error(t('Failed to access'), 403);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 406);

    $function = get_compatible_function_name("/content/tid/film" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["tid"] = $tid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 404);
}
function list_of_films_v_1($parameter){
    $parameter["type"] = "film";
    return list_of_contents_v_2($parameter);
}
/*--------------------------------------------------------------------------------*/