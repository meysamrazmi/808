<?php

function question_resource_index($hash , $domain , $page , $version){
    if(!(hash_true($hash , "question"))) return services_error(t('Failed to access'), 10);
    if($version == 0){
        return list_of_questions_version_one($domain , $page);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "question"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return retrieve_a_question_version_one($nid);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_resource_create($hash , $question , $version){
    if(!(hash_true($hash , "question"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return create_a_question_version_one($question);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_resource_edit($hash , $nid , $question , $version){
    if(!(hash_true($hash , "question"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return edit_a_question_version_one($nid , $question);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_resource_follow($hash , $nid , $data , $version){
    if(!(hash_true($hash , "question"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return follow_a_question_version_one($nid , $data);
    }
    return services_error(t('This version is not supported'), 11);
}
function question_resource_vote($hash , $nid , $data , $version){
    if(!(hash_true($hash , "question"))) services_error(t('Failed to access'), 10);
    if($version == 0){
        return vote_a_question_version_one($nid , $data);
    }
    return services_error(t('This version is not supported'), 11);
}

/*------------------------index-----------------------------------*/
function list_of_questions_version_one($domain , $page){
    switch ($domain){
        case "all_questions" :
            $query = all_questions();
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
        $query->range($page*10, 10);
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
function all_questions(){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body' , 'body' , 'node.nid = body.entity_id');
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.type', 'questions');
    $query->condition('node.status', 1);
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

/*---------------------------retrieve--------------------------------*/
function retrieve_a_question_version_one($nid){
    $query = db_select('node' , 'node');
    $query->leftJoin('field_data_body' , 'body' , 'node.nid = body.entity_id');
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'type' , 'created' , 'changed' , 'status'));
    $query->addField('body' , 'body_value' , 'body');
    $query->condition('node.nid', $nid);
    $node = $query->execute()->fetch();
    if(strcmp($node->type , "questions") != 0 || empty($node))  return services_error(t('Wrong ID'), 16);

    $node->url = "http://civil808.com/node/".$nid;

    global $user;

    /*add tids of a question*/
    $query = db_select('field_data_field_experts' , 'expert');
    $query->addField('expert' , 'field_experts_tid' , 'tid');
    $query->condition('expert.entity_id' , $nid);
    $tids = $query->execute()->fetchAll();
    $node->field_experts = $tids;

    /*add files of a question*/
    $query = db_select('field_data_field_files' , 'feild_file');
    $query->join('file_managed' , 'file' , 'file.fid = feild_file.field_files_fid');
    $query->fields('file', array('fid' , 'filename', 'uri' ,  'filemime' , 'filesize' , 'type' , 'timestamp'));
    $query->condition('feild_file.entity_id' , $nid);
    $query->condition('feild_file.entity_type' , 'node');
    $query->condition('feild_file.bundle' , 'questions');
    $results = $query->execute()->fetchAll();
    if(!empty($results)) $node->field_files = $results;

    /*check if user follow a question or not*/
    $query = db_select('flagging' , 'f')
        ->condition('fid' , 3)
        ->condition('entity_id' , $nid)
        ->condition('uid' , $user->uid);
    $count = $query->countQuery()->execute()->fetchField();
    if($count > 0) $node->follow_status = 1;
    else $node->follow_status = 0;

    /*return the picture of the author*/
    $query = db_select('users' , 'u');
    $query->leftJoin('file_managed' , 'f' , 'u.picture = f.fid');
    $query->fields('u' , array('uid' , 'name' , 'mail' , 'created'));
    $query->addField('f' , 'uri' , 'picture');
    $query->condition('u.uid', $node->uid);
    $author = $query->execute()->fetch();

    /*get the question total vote points*/
    $criteria = array();
    $criteria['entity_id'] = $node->nid;
    $criteria['entity_type'] = "node";
    $criteria['function'] = "sum";
    $vote_points = votingapi_select_results($criteria);
    $vote_points = $vote_points[0]['value'];

    /*check if user vote to the question and his/her point*/
    $query = db_select('votingapi_vote', 'vote');
    $query->fields('vote' , array('value'));
    $query->condition('vote.entity_type' , 'node');
    $query->condition('vote.entity_id' , $node->nid);
    $query->condition('vote.uid' , $user->uid);
    $user_vote = $query->execute()->fetchObject();

    /*check if the question has comment that proved by advisor or not*/
    $query = db_select("field_data_field_prove_advisor" , "prove_advisor");
    $query->join("comment" , "comment" , "prove_advisor.entity_id = comment.cid and comment.nid = " . $nid);
    $query->fields('prove_advisor' , array('entity_id'));
    $query->condition('prove_advisor.field_prove_advisor_value', 1);
    $result = $query->execute()->fetchAll();
    if(!empty($result) && count($result)>0)  $node->prove_advisor = 1;

    /*check if the question has comment that proved by asker or not*/
    $query = db_select("field_data_field_prove_asker" , "prove_asker");
    $query->join("comment" , "comment" , "prove_asker.entity_id = comment.cid and comment.nid = " . $nid);
    $query->fields('prove_asker' , array('entity_id'));
    $query->condition('prove_asker.field_prove_asker_value', 1);
    $result = $query->execute()->fetchAll();
    if(!empty($result) && count($result)>0)  $node->prove_asker = 1;

    return ["question" => $node, "author" => $author, "vote_points" => $vote_points , "user_vote" => $user_vote->value];
}

/*----------------------------create-------------------------------*/
function create_a_question_version_one($question){
    global $user;
    $newQuestion= new stdClass();
    $newQuestion->type  = "questions";
    $newQuestion->title  = $question['title'];
    $newQuestion->body['und'][0]['value'] = $question['body'];
    $newQuestion->body['und'][0]['summary'] = '';
    $newQuestion->body['und'][0]['format'] = 'full_html';
    $newQuestion->field_experts  = $question['field_experts'];
    if(isset($question['field_files']) && !empty($question['field_files'])) $newQuestion->field_files  = $question['field_files'];
    $newQuestion->uid  = $user->uid;
    $newQuestion->language = 'fa';
    $newQuestion->status = 0;
    $newQuestion->comment = 2;
    $newQuestion = node_submit($newQuestion);
    node_save($newQuestion);
    return $newQuestion;
}

/*----------------------------update-------------------------------*/
function edit_a_questions_version_one($nid , $question){
    $newQuestion = node_load($nid);
    $newQuestion->title = $question['title'];
    $newQuestion->body['und'][0]['value'] = $question['body'];
    $newQuestion->field_experts = $question['field_experts'];
    if(isset($question['field_files']) && !empty($question['field_files'])) $newQuestion->field_files = $question['field_files'];
    else $newQuestion->field_files = [];
    node_save($newQuestion);
    return $newQuestion;
}

/*----------------------------follow-------------------------------*/
function follow_a_question_version_one($nid , $data){
    global $user;
    if(!isset($data['action']) && empty($data['action'])) return services_error(t('Action is required!'), 15);

    if(($data['action'] == "follow" || $data['action'] == 1) && follow_status($nid , $user->uid) == 0){
        $fid = db_insert('flagging')
            ->fields(array(
                'fid' => 3,
                'entity_type' => 'node',
                'entity_id' => $nid,
                'uid' => $user->uid,
                'sid' => 0,
                'timestamp' => strtotime(date("Y-m-d H:i:s", time()))
            ))
            ->execute();

        return $fid;
    }
    elseif(($data['action'] == "unfollow" || $data['action'] == 0) && follow_status($nid , $user->uid) == 1){
        $num_deleted = db_delete('flagging')
            ->condition('uid', $user->uid)
            ->condition('entity_id', $nid)
            ->execute();

        return $num_deleted;
    }
    return "error";
}
/*return if the user has followed a question or not*/
function follow_status($nid , $uid){
    $query = db_select('flagging' , 'f')
        ->condition('fid' , 3)
        ->condition('entity_id' , $nid)
        ->condition('uid' , $uid);
    $count = $query->countQuery()->execute()->fetchField();

    if($count > 0) return 1;
    else return 0;
}

/*-----------------------------vote------------------------------*/
function vote_a_question_version_one($nid , $data){
    global $user;
    if(!isset($data['action']) && empty($data['action'])) return services_error(t('Action is required!'), 15);

    if($data['action'] == "up") $value = 1;
    elseif($data['action'] == "down") $value = -1;
    else return services_error(t('Wrong action!'), 16);;

    $votes = array();
    $votes['entity_type'] = "node";
    $votes['entity_id'] = $nid;
    $votes['value_type'] = "points";
    $votes['value'] = $value;
    $votes['tag'] = "vote";
    $votes['uid'] = $user->uid;
    votingapi_set_votes($votes);
    return $votes;
}

/*------------------------------End-----------------------------*/