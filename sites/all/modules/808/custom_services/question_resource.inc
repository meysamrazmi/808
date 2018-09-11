<?php

/*
 * @todo
 * log for vote and follow
 * */

/*--------------------------------operations part--------------------------------------------*/
function question_resource_index($parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function list_of_questions_v_1($parameter){
    if(!isset($parameter["domain"]) || empty($parameter["domain"])) $parameter["domain"] = "all";
    if(!in_array($parameter["domain"] , array("all" , "my_question" , "following" , "related"))) return services_error("Domain is not exist!" , 16);
    global $user;
    $parameter["user"] = $user;

    if(isset($parameter["experts_filter"]) && !empty($parameter["experts_filter"])){
        $tids = explode( "," , $parameter["experts_filter"]);
        $query = db_select("field_data_field_experts" , "experts");
        $query->fields("experts" , array("entity_id"));
        $query->condition("experts.field_experts_tid" , $tids , "IN");
        $query->condition("experts.bundle" , "questions");
        $parameter["custom_question"] = $query->execute()->fetchCol();
    }
    if(strcmp($parameter["domain"] , "following") == 0){
        $query = db_select("flagging" , "flag");
        $query->fields("flag" , array("entity_id"));
        $query->condition("flag.uid" , $user->uid);
        $query->condition("flag.fid" , 3);
        $query->condition("flag.entity_type" , "node");
        $parameter["custom_question"] = $query->execute()->fetchCol();
        return get_questions($parameter);
    }
    if(strcmp($parameter["domain"] , "related") == 0){
        $pid = db_select("profile")->fields("profile" , array("pid"))->condition("uid" , $user->uid)->execute()->fetch()->pid;
        $query = db_select("field_data_field_experts" , "user_expert");
        $query->join("field_data_field_experts" , "qa_expert" , "user_expert.field_experts_tid = qa_expert.field_experts_tid and qa_expert.entity_type = 'node' and qa_expert.bundle = 'questions' ");
        $query->condition("user_expert.entity_id" , $pid);
        $query->condition("user_expert.entity_type" , "profile2");
        $query->condition("user_expert.bundle" , "main");
        $query->fields("qa_expert" , array("entity_id"));
        $parameter["custom_question"] = $query->execute()->fetchCol();
        return get_questions($parameter);
    }

    return get_questions($parameter);
}
function get_questions($parameter){
    $query = db_select("node" , "node");
    $query->leftJoin("users" , "user" , "node.uid = user.uid");
    $query->leftJoin("file_managed" , "author_pic" , "author_pic.fid = user.picture");
    $query->leftJoin("profile" , "profile" , "node.uid = profile.uid");
    $query->leftJoin("field_data_field_full_name" , "author_name" , "author_name.entity_id = profile.pid and author_name.entity_type = 'profile2' and author_name.bundle = 'main' ");
    $query->fields("node" , array("nid" , "uid" , "title" , "created" , "changed" , "status"));
    $query->addField("author_pic" , "uri" , "author_pic");
    $query->addField("author_name" , "field_full_name_value" , "author_name");
    $query->condition("node.type" , "questions");
    if(strcmp($parameter["domain"] , "my_question") == 0) $query->condition("node.uid" , $parameter["user"]->uid);
    else $query->condition("node.status" , 1);
    if(isset($parameter["custom_question"])){
        if(!empty($parameter["custom_question"]))
            $query->condition("node.nid" , $parameter["custom_question"] , "IN");
        else
            return array();
    }
    $query->orderBy("node.created" , "DESC");
    $query->range(isset($parameter["page"])? $parameter["page"]*20 : 0 , 20);
    $results = $query->execute()->fetchAll();
    if(empty($results)) return array();
    $nids = array();
    $questions = array();
    foreach ($results as $result) {
        if(!empty($result->author_pic)) $result->author_pic = image_style_url("200x200" , $result->author_pic);
        array_push($nids , $result->nid);
        $result->experts = array();
        $result->answers_count = 0;
        $result->answer_by_expert_count = 0;
        $result->prove_answer_by_asker_count = 0;
        $result->prove_answer_by_advisor_count = 0;
        $result->vote_points = 0;
        $result->user_follow = false;
        $questions[$result->nid] = $result;
    }

    $query = db_select("field_data_field_experts" , "experts_tid");
    $query->join("taxonomy_term_data" , "expert_data" , "expert_data.tid = experts_tid.field_experts_tid");
    $query->fields("experts_tid" , array("entity_id"));
    $query->fields("expert_data" , array("tid" , "name"));
    $query->condition("experts_tid.entity_id" , $nids , "IN");
    $query->condition("experts_tid.entity_type" , "node");
    $query->condition("experts_tid.bundle" , "questions");
    $experts = $query->execute()->fetchAll();
    foreach ($experts as $expert) array_push($questions[$expert->entity_id]->experts , array("tid" => $expert->tid , "name" => $expert->name));

    $query = db_select('comment' , 'comment');
    $query->fields('comment' , array('nid'));
    $query->condition('comment.nid', $nids, 'IN');
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'count_of_answers');
    $answers_count = $query->execute()->fetchAll();
    foreach ($answers_count as $row) $questions[$row->nid]->answers_count = (int) $row->count_of_answers;

    $query = db_select('comment' , 'comment');
    $query->join('users_roles' , 'role' , 'comment.uid = role.uid');
    $query->fields('comment' , array('nid'));
    $query->condition('comment.nid', $nids, 'IN');
    $query->condition('role.rid', 10);
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'expert_answers');
    $expert_count = $query->execute()->fetchAll();
    foreach ($expert_count as $row) $questions[$row->nid]->answer_by_expert_count = (int) $row->expert_answers;

    $query = db_select('comment' , 'comment');
    $query->join('field_data_field_prove_asker', 'prove_asker' , 'comment.cid = prove_asker.entity_id');
    $query->fields('comment', array('nid'));
    $query->condition('comment.nid', $nids, "IN");
    $query->condition('prove_asker.field_prove_asker_value', 1);
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'count_of_prove_by_asker');
    $prove_asker_count = $query->execute()->fetchAll();
    foreach ($prove_asker_count as $row) $questions[$row->nid]->prove_answer_by_asker_count = (int) $row->count_of_prove_by_asker;

    $query = db_select('comment' , 'comment');
    $query->join('field_data_field_prove_advisor', 'prove_advisor' , 'comment.cid = prove_advisor.entity_id');
    $query->fields('comment', array('nid'));
    $query->condition('comment.nid', $nids, "IN");
    $query->condition('prove_advisor.field_prove_advisor_value', 1);
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'count_of_prove_by_advisor');
    $prove_advisor_count = $query->execute()->fetchAll();
    foreach ($prove_advisor_count as $row) $questions[$row->nid]->prove_answer_by_advisor_count = (int) $row->count_of_prove_by_advisor;

    $query = db_select("votingapi_vote" , "vote");
    $query->fields("vote" , array("entity_id"));
    $query->condition("vote.entity_id" , $nids , "IN");
    $query->condition("vote.entity_type" , "node");
    $query->groupBy('vote.entity_id');
    $query->addExpression('sum(vote.value)', 'vote_point');
    $votes = $query->execute()->fetchAll();
    foreach ($votes as $vote) $questions[$vote->entity_id]->vote_points = (int) $vote->vote_point;

    $query = db_select("flagging" , "flag");
    $query->fields("flag" , array("entity_id"));
    $query->condition("flag.uid" , $parameter["user"]->uid);
    $query->condition("flag.entity_id" , $nids , "IN");
    $query->condition("flag.entity_type" , "node");
    $flags = $query->execute()->fetchAll();
    foreach ($flags as $flag) $questions[$flag->entity_id]->user_follow = true;

    $questions = array_values($questions);

    return $questions;
}

function question_resource_retrieve($nid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/nid" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["nid"] = $nid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function retrieve_question_v_1($parameter){
    global $user;
    $body = db_select("field_data_body" , "body")
            ->fields("body" , array("body_value"))
            ->condition("entity_id" , $parameter["nid"])
            ->condition("bundle" , "questions")
            ->execute()->fetch();
    if(!empty($body)) $body = $body->body_value;
    else $body = null;

    $query = db_select("field_data_field_files" , "field_files");
    $query->join("file_managed" , "file" , "file.fid = field_files.field_files_fid");
    $query->fields("file" , array("uri" , "filesize" , "filemime"));
    $query->condition("field_files.entity_id" , $parameter["nid"]);
    $query->condition("field_files.bundle" , "questions");
    $files = $query->execute()->fetchAll();

    $voting = db_select("votingapi_vote" , "vote")
            ->fields("vote" , array("value"))
            ->condition("entity_type" , "node")
            ->condition("entity_id" , $parameter["nid"])
            ->condition("uid" , $user->uid)
            ->execute()->fetch();
    $user_vote_value = (!empty($voting)) ? $voting->value : 0;

    return array("nid" => $parameter["nid"] , "body" => $body , "files" => $files , "current_user_vote_value" => $user_vote_value);
}

function question_resource_create($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function create_question_v_1($data){
    global $user;
    if($user->uid == 0) return services_error("You should login first!" , 18);

    $node= new stdClass();
    $node->title  = $data['title'];
    $node->type  = "questions";
    node_object_prepare($node);
    $node->language = 'fa';
    $node->uid  = $user->uid;
    $node->status = 0;
    $node->comment = 2;
    $node->created = REQUEST_TIME;

    node_save($node);
    return $node;

    $node->body['und'][0]['value'] = $data['body'];
    $node->body['und'][0]['summary'] = '';
    $node->body['und'][0]['format'] = 'full_html';
    $node->field_experts  = $data['field_experts'];
    if(isset($data['field_files']) && !empty($data['field_files'])) $node->field_files  = $data['field_files'];
    node_save($node);

    add_log($user->uid, "/question" , "create" , "questions" , $node->nid , $data["source"] , $data["version"] , "successful" , "create a question.");
    return $node;
}

function question_resource_update($nid, $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/nid" , "PUT" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["nid"] = $nid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function update_question_v_1($data){
    $node = node_load($data["nid"]);
    global $user;
    if($user->uid != $node->uid && !in_array("administrator" , $user->roles)) return services_error("You do not have permission to this action!" , 18);

    $update = false;
    if(isset($data["title"]) && !empty($data["title"])){
        $node->title = $data["title"];
        $update = true;
    }
    if(isset($data["body"]) && !empty($data["body"])){
        $node->body["und"][0]["value"] = $data["body"];
        $update = true;
    }
    if(isset($data["field_experts"]) && !empty($data["field_experts"])){
        $node->field_experts = $data["field_experts"];
        $update = true;
    }
    if(isset($data["field_files"]) && !empty($data["field_files"])){
        $node->field_files = $data["field_files"];
        $update = true;
    }
    if($update){
        node_save($node);
        add_log($user->uid, "/question" , "update" , "questions" , $node->nid , $data["source"] , $data["version"] , "successful" , "update a question.");
    }

    return $node;
}
/*--------------------------------------------------------------------------------------*/

/*-------------------------------------actions part-------------------------------------*/
function question_resource_search($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/search" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_search_v_1($data){
    $query = db_select("node", "node");
    $query->fields('node', array('nid'));
    $query->condition('node.title', '%' . $data["value"] . '%', 'LIKE');
    $query->condition('node.type' , 'questions');
    $nid1 = $query->execute()->fetchCol();

    $query = db_select("field_data_body", "body");
    $query->addField('body', 'entity_id', 'nid');
    $query->condition('body.body_value', '%' . $data["value"] . '%', 'LIKE');
    $query->condition('body.entity_type' , 'node');
    $query->condition('body.bundle' , 'questions');
    $nid2 = $query->execute()->fetchCol();

    $parameter = array();
    $parameter["custom_question"] = array_merge($nid1, $nid2);
    $parameter["domain"] = isset($data["domain"]) ? $data["domain"] : "all";
    $parameter["page"] = isset($data["page"]) ? $data["page"] : 0;

    if(!empty($parameter["custom_question"]))
        return get_questions($parameter);
    else
        return ["questions" => array()];
}
/*--------------------------------------------------------------------------------------*/
/*-------------------------------target action part-------------------------------------*/
function question_resource_follow($nid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/nid/follow" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["nid"] = $nid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function follow_question_v_1($data){
    global $user;
    if(!isset($data['action']) && empty($data['action'])) return services_error(t('Action is required!'), 15);

    if(($data['action'] == "follow" || $data['action'] == 1) && follow_status($data["nid"] , $user->uid) == 0){
        $fid = db_insert('flagging')
            ->fields(array(
                'fid' => 3,
                'entity_type' => 'node',
                'entity_id' => $data["nid"],
                'uid' => $user->uid,
                'sid' => 0,
                'timestamp' => strtotime(date("Y-m-d H:i:s", time()))
            ))
            ->execute();

        return $fid;
    }
    elseif(($data['action'] == "unfollow" || $data['action'] == 0) && follow_status($data["nid"] , $user->uid) == 1){
        $num_deleted = db_delete('flagging')
            ->condition('uid', $user->uid)
            ->condition('entity_id', $data["nid"])
            ->execute();

        return $num_deleted;
    }
    return services_error(t('Wrong data!'), 16);
}
function follow_status($nid , $uid){
    $query = db_select('flagging' , 'f')
        ->condition('fid' , 3)
        ->condition('entity_id' , $nid)
        ->condition('uid' , $uid);
    $count = $query->countQuery()->execute()->fetchField();

    if($count > 0) return 1;
    else return 0;
}

function question_resource_vote($nid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/nid/vote" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["nid"] = $nid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function vote_question_v_1($data){
    global $user;
    if(!isset($data['action']) && empty($data['action'])) return services_error(t('Action is required!'), 15);

    if(strcmp($data['action'] , "up") == 0) $value = 1;
    elseif(strcmp($data['action'] , "down") == 0) $value = -1;
    else return services_error(t('Wrong action!'), 16);;

    $votes = array();
    $votes['entity_type'] = "node";
    $votes['entity_id'] = $data["nid"];
    $votes['value_type'] = "points";
    $votes['value'] = $value;
    $votes['tag'] = "vote";
    $votes['uid'] = $user->uid;
    votingapi_set_votes($votes);
    return $votes;
}
/*--------------------------------------------------------------------------------------*/
/*--------------------------------relationship part-------------------------------------*/
function question_resource_experts_list($list , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/list/expert" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function total_experts_of_questions_list_v_1($parameter){
    $query = db_select("field_data_field_experts" , "experts_tid");
    $query->join("taxonomy_term_data" , "expert_data" , "expert_data.tid = experts_tid.field_experts_tid");
    $query->fields("expert_data" , array("tid" , "name"));
    $query->condition("experts_tid.entity_type" , "node");
    $query->condition("experts_tid.bundle" , "questions");
    $query->groupBy("experts_tid.field_experts_tid");
    $query->having('count(experts_tid.field_experts_tid) > :cnt', [':cnt' => 2]);
    $experts = $query->execute()->fetchAll();
    return $experts;
}
/*--------------------------------------------------------------------------------------*/






function question_resource_delete($hash , $nid , $version){
    if(!(hash_true($hash , "question"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        global $user;
        $node = db_select("node")
            ->fields("node" , array("nid" , "uid"))
            ->condition("nid" , $nid)
            ->condition("type" , "questions")
            ->execute()->fetch();
        if(!empty($node)){
            if($user->uid == $node->uid || in_array('administrator' , $user->roles))
                node_delete($nid);
            else
                return services_error(t('You have not permission to this action!'), 18);
        }
        else return services_error(t('Wrong Nid!'), 16);
        return true;
    }
    return services_error(t('This version is not supported'), 11);
}
/*------------------------index-----------------------------------*/
function list_of_questions_version_one($domain , $page , $custom_list = array()){
    switch ($domain){
        case "all_questions" :
            $query = all_questions($custom_list);
            break;
        case "my_questions" :
            $query = my_questions();
            break;
        case "following_questions" :
            $query = following_questions();
            break;
        case "my_experts_questions" :
            $query = my_experts_questions();
            break;
        case "my_answered_questions" :
            return my_answered_questions($page);
            break;
        default:
            return services_error(t('Domain is not exist'), 12);
            break;
    }
    if($query != null){
        $query->orderBy('changed', 'DESC');
        if(empty($custom_list))$query->range($page*10, 10);
        $results = $query->execute()->fetchAll();
    }
    else return ["questions" => array()];
    if(empty($results)) return ["questions" => array()];

    $nids = array();
    $uids = array();
    $questions = array();
    foreach($results as $row){
        if($domain == "all_questions"){
            array_push($uids, $row->uid);
        }
        array_push($nids, $row->nid);
        $row->feild_experts = array();
        $row->field_files = array();
        $questions[$row->nid] = $row;
    }

    /*add each question's experts*/
    $results = question_experts($nids);
    foreach($results as $result){
        $tid = new stdClass();
        $tid->tid = $result->field_experts_tid;
        array_push($questions[$result->entity_id]->feild_experts, $tid);
    }

    /*add each question that how many experts answered it*/
    $results = number_of_experts_answered($nids);
    foreach($results as $result){
        $questions[$result->nid]->expert_answers = $result->expert_answers;
    }

    /*add each question if it has answer that is proved by advisor*/
    $results = answer_with_prove_by_advisor($nids);
    foreach($results as $result){
        $questions[$result->nid]->prove_advisor = 1;
    }

    /*add each question if it has answer that is proved by asker*/
    $results = answer_with_prove_by_asker($nids);
    foreach($results as $result){
        $questions[$result->nid]->prove_asker = 1;
    }

    /*add each question the count of answers*/
    $results = count_of_answers($nids);
    foreach($results as $result){
        $questions[$result->nid]->comment_count = $result->comment_count;
    }

    /*add each question it's file*/
    $results = files_of_question($nids);
    foreach($results as $result){
        array_push($questions[$result->entity_id]->field_files, $result);
    }

    $questions = array_values($questions);
    if($domain == "all_questions"){
        $users = user_information($uids); /*get information about users that ask the questions*/
        return ["questions" => $questions, "users" => $users];
    }
    return ["questions" => $questions];
}
function all_questions($custom_list){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body' , 'body' , 'node.nid = body.entity_id');
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.type', 'questions');
    $query->condition('node.status', 1);
    if(!empty($custom_list))$query->condition('node.nid' , $custom_list, 'IN');
    return $query;
}
function my_questions(){
    global $user;
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body' , 'body' , 'node.nid = body.entity_id');
    $query->fields('node' , array('nid' , 'title' , 'created' , 'changed' , 'status'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.type', 'questions');
    $query->condition('node.uid', $user->uid);
    return $query;
}
function following_questions(){
    global $user;
    $query = db_select("node" , "node");
    $query->join("flagging" , "flag" , "node.nid = flag.entity_id and flag.fid = '3' and flag.uid = " . $user->uid);
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
    $query->condition('node.type', 'questions');
    $query->condition('node.status', 1);
    return $query;
}
function my_experts_questions(){
    global $user;
    $profile = profile2_load_by_user($user);
    $field_experts = $profile["main"]->field_experts['und'];
    $experts = array();
    foreach($field_experts as $e){
        array_push($experts, $e["tid"]);
    }
    if(!empty($experts)){
        $query = db_select('node' , 'node');
        $query->join('field_data_field_experts' , 'expert' , 'node.nid = expert.entity_id');
        $query->fields('node' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
        $query->condition('node.type' , 'questions');
        $query->condition('node.status' , 1);
        $query->condition('expert.field_experts_tid' , $experts, 'IN');
        $query->condition('expert.entity_type' , 'node');
        return $query;
    }
    else return null;
}
function my_answered_questions($page){
    global $user;
    $query = db_select("comment" , "comment");
    $query->join("node" , "node", "comment.nid = node.nid");
    $query->join("field_data_comment_body" , "body", "comment.cid = body.entity_id and body.entity_type = 'comment' and body.bundle = 'comment_node_questions' ");
    $query->join("field_data_field_prove_advisor" , "advisor", "comment.cid = advisor.entity_id");
    $query->join("field_data_field_prove_asker" , "asker", "comment.cid = asker.entity_id");
    $query->fields('comment' , array('cid' , 'pid' , 'nid' , 'subject'));
    $query->addField('node' , 'title' , 'node_title');
    $query->addField('body' , 'comment_body_value' , 'body');
    $query->addField('advisor' , 'field_prove_advisor_value' , 'prove_by_advisor');
    $query->addField('asker' , 'field_prove_asker_value' , 'prove_by_asker');
    $query->condition('comment.uid' , $user->uid);
    $query->range($page*10 , 10);
    $comments = $query->execute()->fetchAll();
    return ["questions" => $comments];
}
/*Experts of questions*/
function question_experts($nids){
    $query = db_select('field_data_field_experts' , 'expert');
    $query->fields('expert' , array('entity_id' , 'field_experts_tid'));
    $query->condition('expert.entity_id', $nids, "IN");
    $results = $query->execute()->fetchAll();
    return $results;
}
/*number of comments that an expert left for a question*/
function number_of_experts_answered($nids){
    $query = db_select("comment" , "comment");
    $query->join("users_roles" , "role" , "comment.uid = role.uid and role.rid = '10' ");
    $query->fields('comment' , array('nid'));
    $query->condition('comment.nid', $nids, 'IN');
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'expert_answers');
    $results = $query->execute()->fetchAll();
    return $results;
}
/*return the comments that proved by advisor*/
function answer_with_prove_by_advisor($nids){
    $query = db_select("comment" , "comment");
    $query->join("field_data_field_prove_advisor", "prove_advisor" , "comment.cid = prove_advisor.entity_id and prove_advisor.field_prove_advisor_value = '1' ");
    $query->fields('comment', array('nid'));
    $query->condition('comment.nid', $nids, "IN");
    $query->groupBy('comment.nid');
    $results = $query->execute()->fetchAll();
    return $results;
}
/*return the comments that proved by asker*/
function answer_with_prove_by_asker($nids){
    $query = db_select("comment" , "comment");
    $query->join("field_data_field_prove_asker", "prove_asker" , "comment.cid = prove_asker.entity_id and prove_asker.field_prove_asker_value = '1' ");
    $query->fields('comment', array('nid'));
    $query->condition('comment.nid', $nids, "IN");
    $query->groupBy('comment.nid');
    $results = $query->execute()->fetchAll();
    return $results;
}
/*return the count of comments on each question*/
function count_of_answers($nids){
    $query = db_select('comment' , 'comment');
    $query->fields('comment', array('nid'));
    $query->condition('comment.nid', $nids, 'IN');
    $query->groupBy('comment.nid');
    $query->addExpression('count(comment.cid)', 'comment_count');
    $results = $query->execute()->fetchAll();
    return $results;
}
/*return the files of each question*/
function files_of_question($nids){
    $query = db_select('field_data_field_files' , 'feild_file');
    $query->join('file_managed' , 'file' , 'file.fid = feild_file.field_files_fid');
    $query->fields('feild_file', array('entity_id'));
    $query->fields('file', array('fid' , 'filename', 'uri' ,  'filemime' , 'filesize' , 'type' , 'timestamp'));
    $query->condition('feild_file.entity_id' , $nids , 'IN');
    $query->condition('feild_file.entity_type' , 'node');
    $query->condition('feild_file.bundle' , 'questions');
    $results = $query->execute()->fetchAll();
    return $results;
}
