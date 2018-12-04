<?php

/*--------------------------operation part------------------------------*/
function comment_resource_create($data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "comments"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/comments" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function create_comment_v_1($data){
    global $user;
    if($user->uid == 0) return services_error("You should log in first!" , 18);
    if(!isset($data["nid"]) || empty($data["nid"])) return services_error("Nid is required!" , 15);

    $comment = new stdClass();
    $comment->nid = $data['nid'];
    $comment->pid = (isset($data['pid']) && !empty($data['pid'])) ? $data['pid'] : 0;
    $comment->uid = $user->uid;
    $comment->name = $user->name;
    $comment->mail = $user->mail;
    $comment->node_type = "comment_node_questions";
    $comment->is_anonymous = 0;
    $comment->status = COMMENT_PUBLISHED;
    $comment->language = 'und';
    if(isset($data['field_files']) && !empty($data['field_files'])) $comment->field_files = $data['field_files'];
    $comment->comment_body[$comment->language][0]['value'] = $data['body'];
    $comment->subject = "from android part";
    comment_submit($comment);
    comment_save($comment);
    add_log($user->uid , "/comment" , "create" , "comment" , $comment->cid , $data["source"] , $data["version"] , "successful" ,"create a comment for a questions");

    $comment->nid = (int) $comment->nid;
    $comment->pid = (int) $comment->pid;
    $comment->uid = (int) $comment->uid;
    $comment->cid = (int) $comment->cid;
    unset($comment->is_anonymous);
    unset($comment->subject);
    unset($comment->date);
    unset($comment->homepage);
    unset($comment->thread);
    unset($comment->hostname);
    unset($comment->field_vote_ud);

    return $comment;
}

function comment_resource_update($cid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "comments"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/comments/cid" , "PUT" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["cid"] = $cid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function update_comment_v_1($data){
    $comment = comment_load($data["cid"]);
    if(!$comment) return services_error("Undefined cid!" , 17);
    global $user;
    if($user->uid != $comment->uid && !in_array("administrator" , $user->roles)) return services_error("You do not have permission to this action!" , 18);

    $update = false;
    if(isset($data["body"]) && !empty($data["body"])){
        $comment->comment_body[$comment->language][0]['value'] = $data['body'];
        $comment->comment_body[$comment->language][0]['safe_value'] = $data['body'];
        $update = true;
    }
    if(isset($data['field_files']) && !empty($data['field_files'])) {
        $comment->field_files = $data['field_files'];
        $update = true;
    }
    if($update){
        comment_save($comment);
        add_log($user->uid, "/comment/cid" , "update" , "comment" , $comment->cid , $data["source"] , $data["version"] , "successful" , "update a comment.");
    }
    return $comment;
}
/*----------------------------------------------------------------------*/

/*----------------------targeted action part----------------------------*/
function comment_resource_vote($cid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "comments"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/comments/cid/vote" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["cid"] = $cid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function vote_comment_v_1($data){
    global $user;
    if(!isset($data['action']) && empty($data['action'])) return services_error(t('Action is required!'), 15);

    if(strcmp($data['action'] , "up") == 0) $value = 1;
    elseif(strcmp($data['action'] , "down") == 0) $value = -1;
    else return services_error(t('Wrong action!'), 16);;

    $votes = array();
    $votes['entity_type'] = "comment";
    $votes['entity_id'] = $data["cid"];
    $votes['value_type'] = "points";
    $votes['value'] = $value;
    $votes['tag'] = "vote";
    $votes['uid'] = $user->uid;
    votingapi_set_votes($votes);
    add_log($user->uid , "/comment/cid/vote" , "vote " . $data["action"] ,"comment" , $data["cid"] , $data["source"] , $data["version"] , "successful" , "vote a comment");

    $query = db_select("votingapi_vote" , "vote");
    $query->fields("vote" , array("entity_id"));
    $query->condition("vote.entity_id" , $data["cid"]);
    $query->condition("vote.entity_type" , "comment");
    $query->groupBy('vote.entity_id');
    $query->addExpression('sum(vote.value)', 'vote_point');
    $vote = $query->execute()->fetch();
    return array("vote_points" => (int) $vote->vote_point);
}

function comment_resource_prove($cid , $data){
    if(!isset($data["hash"]) || !(hash_true($data["hash"] , "comments"))) return services_error(t('Failed to access'), 10);
    if(empty($data["source"]) || empty($data["version"])) return services_error("source or version is empty!" , 11);

    $function = get_compatible_function_name("/comments/cid/prove" , "POST" , $data["source"] , $data["version"]);
    if(!empty($function) && strlen($function) > 0) {
        $data["cid"] = $cid;
        return call_user_func($function, $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function prove_comment_v_1($data){
    global $user;
    $comment = comment_load($data["cid"]);
    if(strcmp($data["prove"] , "advisor") == 0){
        if(!isset($user->roles['10']) || strcmp($user->roles['10'], 'مشاور') != 0) return services_error("You do not have permission for this action!" , 18);

        $query = db_select('comment' , 'comment');
        $query->join('field_data_field_prove_advisor' , 'advisor' , 'comment.cid = advisor.entity_id');
        $query->fields('comment' , array('cid'));
        $query->condition('comment.nid' , $comment->nid);
        $query->condition('advisor.field_prove_advisor_value' , 1);
        $result = $query->execute()->fetchCol();
        if(!empty($result) && count($result) > 0) return false;

        if($comment->field_prove_advisor['und']['0']['value'] == 0){
            $comment->field_prove_advisor['und']['0']['value'] = 1;
            comment_save($comment);
            add_log($user->uid , "/comments/cid/advisor_prove" , "prove by advisor" , "comment" , $comment->cid , $data["source"] , $data["version"] , "successful" , "prove a comment by advisor");
            return true;
        }
        else return false;
    }
    elseif(strcmp($data["prove"] , "asker") == 0){
        $query = db_select('comment' , 'comment');
        $query->join('field_data_field_prove_asker' , 'asker' , 'comment.cid = asker.entity_id');
        $query->fields('comment' , array('cid'));
        $query->condition('comment.nid' , $comment->nid);
        $query->condition('asker.field_prove_asker_value' , 1);
        $result = $query->execute()->fetchCol();
        if(!empty($result) && count($result) > 0) return false;

        $query = db_select('node' , 'node');
        $query->join('comment' , 'comment' , 'comment.nid = node.nid');
        $query->fields('node' , array('uid'));
        $query->condition('comment.cid' , $comment->cid);
        $result = $query->execute()->fetch();
        if($user->uid != $result->uid) return services_error("You do not have permission for this action!" , 18);

        if($comment->field_prove_asker['und']['0']['value'] == 0){
            $comment->field_prove_asker['und']['0']['value'] = 1;
            comment_save($comment);
            return true;
        }
        else return false;
    }
    else return services_error("Wrong Input!" , 16);
}
/*----------------------------------------------------------------------*/