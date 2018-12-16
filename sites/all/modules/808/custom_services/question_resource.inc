<?php

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
    global $user;
    $parameter["user"] = $user;
    if(!isset($parameter["domain"]) || empty($parameter["domain"])) $parameter["domain"] = "all";
    if(!in_array($parameter["domain"] , array("all" , "my_question" , "following" , "related" , "my_response"))) return services_error("Domain is not exist!" , 16);

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
        if(empty($parameter["custom_question"])) $parameter["custom_question"] = $query->execute()->fetchCol();
        else{
            $custom = $query->execute()->fetchCol();
            $parameter["custom_question"] = array_intersect($custom , $parameter["custom_question"]);
        }
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
        if(empty($parameter["custom_question"])) $parameter["custom_question"] = $query->execute()->fetchCol();
        else{
            $custom = $query->execute()->fetchCol();
            $parameter["custom_question"] = array_intersect($custom , $parameter["custom_question"]);
        }
        return get_questions($parameter);
    }
    if(strcmp($parameter["domain"] , "my_response") == 0){
        $query = db_select("comment" , "comment");
        $query->join("node" , "node" , "node.nid = comment.nid and node.type = 'questions' and node.status = '1' ");
        $query->fields("comment" , array("nid"));
        $query->condition("comment.uid" , $user->uid);
        if(empty($parameter["custom_question"])) $parameter["custom_question"] = $query->execute()->fetchCol();
        else{
            $custom = $query->execute()->fetchCol();
            $parameter["custom_question"] = array_intersect($custom , $parameter["custom_question"]);
        }
        return get_questions($parameter);
    }

    return get_questions($parameter);
}
function get_questions($parameter){
    $query = db_select("node" , "node");
    $query->join("users" , "user" , "node.uid = user.uid");
    $query->join("profile" , "profile" , "user.uid = profile.uid and profile.type = 'main' ");
    $query->leftJoin("field_data_field_full_name" , "author_name" , "author_name.entity_id = profile.pid and author_name.entity_type = 'profile2' and author_name.bundle = 'main' ");
    $query->leftJoin("file_managed" , "author_pic" , "author_pic.fid = user.picture");
    $query->fields("node" , array("nid" , "uid" , "title" , "created" , "changed" , "status"));
    $query->addField("author_pic" , "uri" , "author_pic");
    $query->addField("author_name" , "field_full_name_value" , "author_name");
    $query->condition("node.type" , "questions");
    if(strcmp($parameter["domain"] , "my_question") == 0) $query->condition("node.uid" , $parameter["user"]->uid);
    elseif($parameter["user"]->uid != 10628) $query->condition("node.status" , 1);
    if(isset($parameter["custom_question"])){
        if(!empty($parameter["custom_question"]))
            $query->condition("node.nid" , $parameter["custom_question"] , "IN");
        else
            return array();
    }
    $query->orderBy("node.nid" , "DESC");
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

        /*post process*/
        $result->nid = (int)$result->nid;
        $result->uid = (int)$result->uid;
        $result->status = (int)$result->status;
        $result->created = (int)$result->created;
        $result->changed = (int)$result->changed;
    }

    $query = db_select("field_data_field_experts" , "experts_tid");
    $query->join("taxonomy_term_data" , "expert_data" , "expert_data.tid = experts_tid.field_experts_tid");
    $query->join("field_data_field_bool" , "bool" , "bool.entity_id = expert_data.tid and bool.entity_type = 'taxonomy_term' and bool.bundle = 'expert' and bool.field_bool_value = '1' ");
    $query->fields("experts_tid" , array("entity_id"));
    $query->fields("expert_data" , array("tid" , "name"));
    $query->condition("experts_tid.entity_id" , $nids , "IN");
    $query->condition("experts_tid.entity_type" , "node");
    $query->condition("experts_tid.bundle" , "questions");
    $experts = $query->execute()->fetchAll();
    foreach ($experts as $expert) array_push($questions[$expert->entity_id]->experts , array("tid" => (int)$expert->tid , "name" => $expert->name));

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
	$author = db_select("node")->fields("node" , array("uid"))->condition("node.nid" , $parameter["nid"])->execute()->fetch();
	if(!empty($author) && $author->uid == $user->uid) $parameter["domain"] = "my_question";
	else $parameter["domain"] = "all";
    $parameter["custom_question"] = array($parameter["nid"]);
    $parameter["user"] = $user;
    $get_question = get_questions($parameter);
    if(empty($get_question)) return $get_question;
    $question = $get_question[0];

    $body = db_select("field_data_body" , "body")
            ->fields("body" , array("body_value"))
            ->condition("entity_id" , $parameter["nid"])
            ->condition("bundle" , "questions")
            ->execute()->fetch();
    if(!empty($body)) $question->body = $body->body_value;
    else $question->body = null;

    $query = db_select("field_data_field_files" , "field_files");
    $query->join("file_managed" , "file" , "file.fid = field_files.field_files_fid");
    $query->fields("file" , array("fid" , "uri" , "filesize" , "filemime"));
    $query->condition("field_files.entity_id" , $parameter["nid"]);
    $query->condition("field_files.bundle" , "questions");
    $files = $query->execute()->fetchAll();
    foreach ($files as $file) {
        $file->fid = (int) $file->fid;
        $file->uri = generate_file_address($file->uri);
        $file->filesize = (int) $file->filesize;
    }
    $question->files = $files;


    $voting = db_select("votingapi_vote" , "vote")
            ->fields("vote" , array("value"))
            ->condition("entity_type" , "node")
            ->condition("entity_id" , $parameter["nid"])
            ->condition("uid" , $user->uid)
            ->execute()->fetch();
    $question->current_user_vote_value = (!empty($voting)) ? (int) $voting->value : 0;

    return $question;
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
    $node->body['und'][0]['value'] = $data['body'];
    $node->body['und'][0]['summary'] = '';
    $node->body['und'][0]['format'] = 'full_html';
    $node->field_experts  = $data['field_experts'];
    if(isset($data['field_files']) && !empty($data['field_files'])) $node->field_files  = $data['field_files'];
    node_save($node);

    unset($node->menu);
    unset($node->field_social_share);
    unset($node->log);
    unset($node->tnid);
    unset($node->translate);
    unset($node->vid);
    unset($node->ds_switch);
    unset($node->field_vote_ud);
    $node->nid = (int) $node->nid;
    $node->uid = (int) $node->uid;

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
    if(!$node) return services_error("Undefined nid!" , 17);
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
        add_log($user->uid, "/question/nid" , "update" , "questions" , $node->nid , $data["source"] , $data["version"] , "successful" , "update a question.");
    }

    return $node;
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

    if(strcmp($data['action'], "follow") == 0 && follow_status($data["nid"] , $user->uid) == 0){
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

        return (int)$fid;
    }
    elseif(strcmp($data['action'], "unfollow") == 0 && follow_status($data["nid"] , $user->uid) == 1){
        $num_deleted = db_delete('flagging')
            ->condition('uid', $user->uid)
            ->condition('entity_id', $data["nid"])
            ->execute();

        return (int)$num_deleted;
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
    add_log($user->uid , "/question/nid/vote" , "vote " . $data["action"] ,"questions" , $data["nid"] , $data["source"] , $data["version"] , "successful" , "vote a question");

    $query = db_select("votingapi_vote" , "vote");
    $query->fields("vote" , array("entity_id"));
    $query->condition("vote.entity_id" , $data["nid"]);
    $query->condition("vote.entity_type" , "node");
    $query->groupBy('vote.entity_id');
    $query->addExpression('sum(vote.value)', 'vote_point');
    $votes = $query->execute()->fetch();
    return array("vote_points" => (int) $votes->vote_point);
}
/*--------------------------------------------------------------------------------------*/
/*--------------------------------relationship part-------------------------------------*/
function question_resource_question_comments($nid , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/nid/comment" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $parameter["nid"] = $nid;
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function comments_of_question_v_1($parameter){
    /*Get 20th of main comments*/
    $query = db_select("comment" , "comment");
    $query->join("field_data_comment_body" , "body" , "body.entity_id = comment.cid and body.bundle = 'comment_node_questions' ");
    $query->join("users" , "user" , "comment.uid = user.uid");
    $query->leftJoin("file_managed" , "author_pic" , "author_pic.fid = user.picture");
    $query->join("profile" , "profile" , "profile.uid = comment.uid and profile.type = 'main' ");
    $query->leftJoin("field_data_field_full_name" , "author_name" , "author_name.entity_id = profile.pid and author_name.entity_type = 'profile2' and author_name.bundle = 'main' ");
    $query->leftJoin("field_data_field_prove_advisor" , "prove_advisor" , "prove_advisor.entity_id = comment.cid and prove_advisor.entity_type = 'comment' and prove_advisor.bundle = 'comment_node_questions' ");
    $query->leftJoin("field_data_field_prove_asker" , "prove_asker" , "prove_asker.entity_id = comment.cid and prove_asker.entity_type = 'comment' and prove_asker.bundle = 'comment_node_questions' ");
    $query->leftJoin("users_roles" , "roles" , "roles.uid = comment.uid and roles.rid = '10' ");
    $query->fields("comment" , array("cid" , "uid" , "created" , "changed" , "name"));
    $query->addField("body" , "comment_body_value" , "body");
    $query->addField("author_pic" , "uri" , "author_pic");
    $query->addField("author_name" , "field_full_name_value" , "author_name");
    $query->addField("prove_advisor" , "field_prove_advisor_value" , "prove_by_advisor");
    $query->addField("prove_asker" , "field_prove_asker_value" , "prove_by_asker");
    $query->addField("roles" , "rid" , "role");
    $query->condition("comment.nid" , $parameter["nid"]);
    $query->condition("comment.status" , 1);
    $query->condition("comment.pid" , 0);
    $query->orderBy("prove_advisor.field_prove_advisor_value" , "DESC")
            ->orderBy("prove_asker.field_prove_asker_value" , "DESC")->orderBy("comment.cid" , "DESC");
    $query->range((isset($parameter["page"]))? $parameter["page"] : 0 * 20 , 20);
    $comments = $query->execute()->fetchAll();
    if(empty($comments)) return array();

    /* pre process on comments
     * convert data type and initialize
     */
    $cids = array();
    $comments_key = array();
    foreach ($comments as $comment) {
        array_push($cids , $comment->cid);
        if(!empty($comment->author_pic))  $comment->author_pic = image_style_url("200x200" , $comment->author_pic);
        if(!empty($comment->role)) $comment->role = "advisor"; else unset($comment->role);
        $comment->children = array();
        $comment->vote_points = 0;
        $comment->user_vote = 0;
        $comment->files = array();
        $comments_key[$comment->cid] = $comment;

        /*post process*/
        $comment->cid = (int) $comment->cid;
        $comment->uid = (int) $comment->uid;
        $comment->prove_by_advisor = (int) $comment->prove_by_advisor;
        $comment->prove_by_asker = (int) $comment->prove_by_asker;
        $comment->created = (int) $comment->created;
        $comment->changed = (int) $comment->changed;
    }

    /*add votes of each comment*/
    $query = db_select("votingapi_vote" , "vote");
    $query->fields("vote" , array("entity_id"));
    $query->condition("vote.entity_id" , $cids , "IN");
    $query->condition("vote.entity_type" , "comment");
    $query->groupBy('vote.entity_id');
    $query->addExpression('sum(vote.value)', 'vote_point');
    $votes = $query->execute()->fetchAll();
    foreach ($votes as $vote) $comments_key[$vote->entity_id]->vote_points = (int) $vote->vote_point;

    /*add the point that user has voted before*/
    global $user;
    $query = db_select("votingapi_vote" , "vote");
    $query->fields("vote" , array("entity_id" , "value"));
    $query->condition("vote.entity_id" , $cids , "IN");
    $query->condition("vote.entity_type" , "comment");
    $query->condition("vote.uid" , $user->uid);
    $user_votes = $query->execute()->fetchAll();
    foreach ($user_votes as $user_vote) $comments_key[$user_vote->entity_id]->user_vote = (int) $user_vote->value;

    /*find replies of main comments*/
    $query = db_select("comment" , "comment");
    $query->join("field_data_comment_body" , "body" , "body.entity_id = comment.cid and body.bundle = 'comment_node_questions' ");
    $query->join("users" , "user" , "comment.uid = user.uid");
    $query->leftJoin("file_managed" , "author_pic" , "author_pic.fid = user.picture");
    $query->join("profile" , "profile" , "profile.uid = comment.uid and profile.type = 'main' ");
    $query->leftJoin("field_data_field_full_name" , "author_name" , "author_name.entity_id = profile.pid and author_name.entity_type = 'profile2' and author_name.bundle = 'main' ");
    $query->fields("comment" , array("cid" , "pid" , "uid" , "created" , "changed"));
    $query->addField("body" , "comment_body_value" , "body");
    $query->addField("author_pic" , "uri" , "author_pic");
    $query->addField("author_name" , "field_full_name_value" , "author_name");
    $query->condition("comment.status" , 1);
    $query->condition("comment.pid" , $cids , "IN");
    $query->orderBy("comment.cid" , "ASC");
    $replies = $query->execute()->fetchAll();
    $replies_key = array();
    foreach ($replies as $reply) {
        array_push($cids , $reply->cid);
        $reply->files = array();
        $reply->cid = (int) $reply->cid;
        $reply->pid = (int) $reply->pid;
        $reply->uid = (int) $reply->uid;
        if(!empty($reply->author_pic)) $reply->author_pic = image_style_url("200x200" , $reply->author_pic);
        $replies_key[$reply->cid] = $reply;
    }

    $query = db_select("field_data_field_files" , "field_files");
    $query->leftJoin("file_managed" , "files" , "field_files.field_files_fid = files.fid");
    $query->fields("field_files" , array("entity_id"));
    $query->fields("files" , array("fid" , "uri" , "filesize" , "filemime"));
    $query->condition("field_files.entity_id" , $cids , "IN");
    $query->condition("field_files.entity_type" , "comment");
    $query->condition("field_files.bundle" , "comment_node_questions");
    $files = $query->execute()->fetchAll();
    foreach ($files as $file) {
        $file->uri = generate_file_address($file->uri);
        if(isset($comments_key[$file->entity_id])) array_push($comments_key[$file->entity_id]->files , array("fid" => (int) $file->fid , "uri" => $file->uri , "filesize" => (int) $file->filesize , "filemime" => $file->filemime));
        if(isset($replies_key[$file->entity_id])) array_push($replies_key[$file->entity_id]->files , array("fid" => (int) $file->fid , "uri" => $file->uri , "filesize" => (int) $file->filesize , "filemime" => $file->filemime));
    }
    $replies = array_values($replies_key);

    foreach ($replies as $reply)
        if(isset($comments_key[$reply->pid]))
            array_push($comments_key[$reply->pid]->children , $reply);


    $comments = array_values($comments_key);
    return $comments;
}

function question_resource_search($list , $parameter){
    if(!isset($parameter["hash"]) || !(hash_true($parameter["hash"] , "question"))) return services_error(t('Failed to access'), 10);
    if(empty($parameter["source"]) || empty($parameter["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/question/list/search" , "GET" , $parameter["source"] , $parameter["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $parameter);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_search_v_1($parameter){
//    $persian = ['۰', '۱', '۲', '۳', '۴', '۵', '۶', '۷', '۸', '۹'];
//    $num = range(0, 9);
//    $parameter["value"] = str_replace($persian, $num, $parameter["value"]);

    $query = db_select("node", "node");
    $query->fields('node', array('nid'));
    $query->condition('node.title', '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $query->condition('node.type' , 'questions');
    $nid1 = $query->execute()->fetchCol();

    $query = db_select("field_data_body", "body");
    $query->addField('body', 'entity_id', 'nid');
    $query->condition('body.body_value', '%' . db_like($parameter["value"]) . '%', 'LIKE');
    $query->condition('body.entity_type' , 'node');
    $query->condition('body.bundle' , 'questions');
    $nid2 = $query->execute()->fetchCol();
	
    $data = array();
    $data["custom_question"] = array_merge($nid1, $nid2);
    $data["domain"] = isset($parameter["domain"]) ? $parameter["domain"] : "all";
    $data["page"] = isset($parameter["page"]) ? $parameter["page"] : 0;
    if(!empty($data["custom_question"]))
        return list_of_questions_v_1($data);
    else
        return array();
}

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
    foreach($experts as $expert) $expert->tid = (int)$expert->tid;
    return $experts;
}
/*--------------------------------------------------------------------------------------*/
