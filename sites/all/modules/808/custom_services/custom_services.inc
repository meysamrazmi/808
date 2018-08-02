<?php
/**
 * 
 *
 * @param string $use
 * @param string $pass
 * @return object
 *
function checklogin_retrieve($use = null, $pass = null){
	$result = user_authenticate($use, $pass);
	if($result){
		return $result;
		//echo "true";
	}else{
		return '0';
		//echo "false";
	}
	return false;
	//die("null :S");
}*/

/*return advisor list*/
function advisor_list(){
	$query = db_select('users_roles' , 'r')
				->fields('r' , array('uid'))
				->condition('rid' , 10)
				->execute()->fetchAll();
	return $query;
}
function advisors_info($page){
    $query = db_select('users' , 'user');
    $query->join('profile', 'profile', 'user.uid = profile.uid');
    $query->join('users_roles', 'roles', 'profile.uid = roles.uid');
    $query->leftJoin('field_data_field_full_name', 'name', 'name.entity_id = profile.pid');
    $query->leftJoin('file_managed', 'file', 'user.picture = file.fid');
    $query->fields('user', array('uid', 'name', 'mail', 'created'));
    $query->addField('name', 'field_full_name_value', 'complete_name');
    $query->addField('file', 'uri', 'picture');
    $query->condition('roles.rid', 10);
    $query->condition('name.bundle', 'main');
    $query->condition('name.entity_type', 'profile2');
    $query->condition('profile.type', 'main');
    $query->range($page*10, 10);
    $results = $query->execute()->fetchAll();
    $return_info = array();
    if(!empty($results)){
        $info = array();
        $uids = array();
        foreach($results as $result){
            $result->send_message = "http://civil808.com/messages/new/" . $result->uid;
            $result->view_profile = "http://civil808.com/user/" . $result->uid . "/advisor";
            array_push($uids, $result->uid);
            $info[$result->uid] = $result;
        }

        $query = db_select('profile' , 'profile');
        $query->leftJoin('field_data_field_darbareye', 'darbareye', 'darbareye.entity_id = profile.pid');
        $query->fields('profile', array('uid'));
        $query->addField('darbareye', 'field_darbareye_value', 'darbareye');
        $query->condition('darbareye.bundle', 'advisor');
        $query->condition('darbareye.entity_type', 'profile2');
        $query->condition('profile.type', 'advisor');
        $query->condition('profile.uid' , $uids , 'IN');
        $results = $query->execute()->fetchAll();
        foreach ($results as $result){
            $info[$result->uid]->darbareye = $result->darbareye;
        }
        foreach($info as $row){
            array_push($return_info, $row);
        }
    }
    return $return_info;
}

/*question part*/
/*return the if user follow a question or not*/
function follow_status($nid , $uid){
	$query = db_select('flagging' , 'f')
	->condition('fid' , 3)
	->condition('entity_id' , $nid)
	->condition('uid' , $uid);
	$count = $query->countQuery()->execute()->fetchField();
	
	if($count > 0) return 1;
	else return 0;
}
/*follow or unfollow a question*/
function follow_unfollow($nid, $data){
	global $user;
	if(!isset($data['action']) && empty($data['action'])) return "error! action is empty";
	
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
/*vote a question*/
function question_vote_up_down($nid, $data){
	global $user;
	if(!isset($data['action']) && empty($data['action'])) return "error! action is empty";
		
	if($data['action'] == "up") $value = 1;
	elseif($data['action'] == "down") $value = -1;
	else return "error";
	
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
/*return the questions*/
function get_questions($url, $page){
    /*get appropriate questions*/
	if($url == "all_questions"){
		$query = db_select('node' , 'n');
		$query->leftJoin('field_data_body' , 'b' , 'n.nid = b.entity_id');
		$query->fields('n' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
		$query->addField('b' , 'body_value' , 'body');
		$query->condition('n.type', 'questions');
		$query->condition('n.status', 1);
		$query->orderBy('changed', 'DESC');
		$query->range($page*10, 10);
		$nodes = $query->execute()->fetchAll();
	}
	elseif($url == "my_questions"){
		global $user;
		$query = db_select('node' , 'n');
        $query->leftJoin('field_data_body' , 'b' , 'n.nid = b.entity_id');
		$query->fields('n' , array('nid' , 'title' , 'created' , 'changed' , 'status'));
        $query->addField('b' , 'body_value' , 'body');
		$query->condition('n.type', 'questions');
		$query->condition('n.uid', $user->uid);
		$query->orderBy('changed', 'DESC');
		$query->range($page*10, 10);
		$nodes = $query->execute()->fetchAll();
	}
	elseif($url == "following_questions"){
		global $user;
		$query = db_select('node' , 'n');
		$query->join('flagging' , 'f' , 'n.nid = f.entity_id');
		$query->fields('n' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
		$query->condition('n.type', 'questions');
		$query->condition('n.status', 1);
		$query->condition("f.fid" , 3);
		$query->condition("f.uid" , $user->uid);
		$query->orderBy('changed', 'DESC');
		$query->range($page*10, 10);
		$nodes = $query->execute()->fetchAll();
	}
	elseif($url == "my_experts_questions"){
		global $user;
		$profile = profile2_load_by_user($user);
		$field_experts = $profile["main"]->field_experts['und'];
		$experts = array();
		foreach($field_experts as $e){
			array_push($experts, $e["tid"]);
		}
		if(!empty($experts)){
			$query = db_select('node' , 'n');
			$query->join('field_data_field_experts' , 'e' , 'n.nid = e.entity_id');
			$query->fields('n' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
			$query->condition('n.type' , 'questions');
			$query->condition('n.status' , 1);
			$query->condition('e.field_experts_tid' , $experts, 'IN');
			$query->condition('e.entity_type' , 'node');
			$query->orderBy('changed', 'DESC');
			$query->range($page*10, 10);
			$nodes = $query->execute()->fetchAll();
		}
		else $nodes = array();
	}
	if(!empty($nodes)){
		$nids = array();
		$uids = array();
		$questions = array();
		foreach($nodes as $row){
			if($url == "all_questions"){
				array_push($uids, $row->uid);
			}
			array_push($nids, $row->nid);
			$row->feild_experts = array();
			$row->field_files = array();
			$questions[$row->nid] = $row;
		}

		/*add each question's experts*/
		$query = db_select('field_data_field_experts' , 'e');
		$query->fields('e' , array('entity_id' , 'field_experts_tid'));
		$query->condition('e.entity_id', $nids, "IN");
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			$tid = new stdClass();
			$tid->tid = $result->field_experts_tid;
			array_push($questions[$result->entity_id]->feild_experts, $tid);
		}

		/*add each question that how many experts answered it*/
		$query = db_select('comment' , 'c');
		$query->join('users_roles' , 'r' , 'c.uid = r.uid');
		$query->fields('c' , array('nid'));
		$query->condition('c.nid', $nids, 'IN');
		$query->condition('r.rid', 10);
		$query->groupBy('c.nid');
		$query->addExpression('count(c.cid)', 'expert_answers');
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			$questions[$result->nid]->expert_answers = $result->expert_answers;
		}

		/*add each question if it has answer that is proved by advisor*/
		$query = db_select('comment' , 'c');
		$query->join('field_data_field_prove_advisor', 'f' , 'c.cid = f.entity_id');
		$query->fields('c', array('nid'));
		$query->condition('c.nid', $nids, "IN");
		$query->condition('f.field_prove_advisor_value', 1);
		$query->groupBy('c.nid');
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			$questions[$result->nid]->prove_advisor = 1;
		}

        /*add each question if it has answer that is proved by asker*/
		$query = db_select('comment' , 'c');
		$query->join('field_data_field_prove_asker', 'f' , 'c.cid = f.entity_id');
		$query->fields('c', array('nid'));
		$query->condition('c.nid', $nids, "IN");
		$query->condition('f.field_prove_asker_value', 1);
		$query->groupBy('c.nid');
        $results = $query->execute()->fetchAll();
		foreach($results as $result){
			$questions[$result->nid]->prove_asker = 1;
		}

        /*add each question the count of answers*/
		$query = db_select('comment' , 'c');
		$query->fields('c', array('nid'));
		$query->condition('c.nid', $nids, 'IN');
		$query->groupBy('c.nid');
		$query->addExpression('count(c.cid)', 'comment_count');
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			$questions[$result->nid]->comment_count = $result->comment_count;
		}

        /*add each question it's file*/
        $query = db_select('field_data_field_files' , 'feild_file');
        $query->join('file_managed' , 'file' , 'file.fid = feild_file.field_files_fid');
        $query->fields('feild_file', array('entity_id'));
        $query->fields('file', array('fid' , 'filename', 'uri' ,  'filemime' , 'filesize' , 'type' , 'timestamp'));
        $query->condition('feild_file.entity_id' , $nids , 'IN');
        $query->condition('feild_file.entity_type' , 'node');
        $query->condition('feild_file.bundle' , 'questions');
        $results = $query->execute()->fetchAll();
        foreach($results as $result){
            array_push($questions[$result->entity_id]->field_files, $result);
        }

		$return_questions = array();
		foreach($questions as $q){
			array_push($return_questions, $q);
		}
		if($url == "all_questions"){
			$users = user_information($uids);
			return ["questions" => $return_questions, "users" => $users];
		}
		return ["questions" => $return_questions];
	}
	return ["questions" => array()];
}
/*return questions that user answered*/
function my_answered_questions($page){
    global $user;
    $query = db_select('comment' , 'comment');
    $query->join('node' , 'node', 'comment.nid = node.nid');
    $query->join('field_data_comment_body' , 'body', 'comment.cid = body.entity_id');
    $query->join('field_data_field_prove_advisor' , 'advisor', 'comment.cid = advisor.entity_id');
    $query->join('field_data_field_prove_asker' , 'asker', 'comment.cid = asker.entity_id');
    $query->fields('comment' , array('cid' , 'pid' , 'nid' , 'subject'));
    $query->addField('node' , 'title' , 'node_title');
    $query->addField('body' , 'comment_body_value' , 'body');
    $query->addField('advisor' , 'field_prove_advisor_value' , 'prove_by_advisor');
    $query->addField('asker' , 'field_prove_asker_value' , 'prove_by_asker');
    $query->condition('body.entity_type' , 'comment');
    $query->condition('body.bundle' , 'comment_node_questions');
    $query->condition('comment.uid' , $user->uid);
    $query->range($page*10 , 10);
    $comments = $query->execute()->fetchAll();
    return ["questions" => $comments];
}
/*edit a question*/
function node_edit($nid, $data){
	$node = node_load($nid);
	$node->title = $data['title'];
	$node->body['und'][0]['value'] = $data['body'];
	$node->field_experts = $data['field_experts'];
    if(isset($data['field_files']) && !empty($data['field_files'])) $node->field_files = $data['field_files'];
    else $node->field_files = [];
	node_save($node);
	return $node;
}
/*end of question part*/

/*
 * comment part
 */
/*edit comment*/
function comment_edit($cid, $data){
	$comment = comment_load($cid);
	$comment->comment_body[$comment->language][0]['value'] = $data['body'];
	$comment->comment_body[$comment->language][0]['safe_value'] = $data['body'];
    if(isset($data['field_files']) && !empty($data['field_files'])) $comment->field_files = $data['field_files'];
    else $comment->field_files = [];
	comment_save($comment);
	return $comment;
}
/*vote a comment up or down*/
function comment_vote_up_down($cid, $data){
	global $user;
	if(!isset($data['action']) && empty($data['action'])) return "error! action is empty";
		
	if($data['action'] == "up") $value = 1;
	elseif($data['action'] == "down") $value = -1;
	else return "error";
	
	$votes = array();
	$votes['entity_type'] = "comment";
	$votes['entity_id'] = $cid;
	$votes['value_type'] = "points";
	$votes['value'] = $value;
	$votes['tag'] = "vote";
	$votes['uid'] = $user->uid;
	votingapi_set_votes($votes);
	return $votes;
}
/* prove a comment by advisor*/
function comment_prove_by_advisor($cid, $data=1){

    global $user;
	if(!isset($user->roles['10']) || strcmp($user->roles['10'], 'مشاور') != 0){
	    return false;
    }

    $comment = comment_load($cid);

	$query = db_select('comment' , 'c');
	$query->join('field_data_field_prove_advisor' , 'advisor' , 'c.cid = advisor.entity_id');
	$query->fields('c' , array('cid'));
	$query->condition('c.nid' , $comment->nid);
	$query->condition('advisor.field_prove_advisor_value' , 1);
	$result = $query->execute()->fetchAll();
	if(!empty($result) && count($result) > 0) return false;

	if($comment->field_prove_advisor['und']['0']['value'] == 0){
		$comment->field_prove_advisor['und']['0']['value'] = 1;
		comment_save($comment);
		return true;
	}
	else return false;
}
/* prove a comment by asker of question*/
function comment_prove_by_asker($cid, $data=1){
    $comment = comment_load($cid);

    $query = db_select('comment' , 'c');
    $query->join('field_data_field_prove_asker' , 'asker' , 'c.cid = asker.entity_id');
    $query->fields('c' , array('cid'));
    $query->condition('c.nid' , $comment->nid);
    $query->condition('asker.field_prove_asker_value' , 1);
    $result = $query->execute()->fetchAll();
    if(!empty($result) && count($result) > 0) return false;

    $query = db_select('node' , 'n');
    $query->join('comment' , 'c' , 'c.nid = n.nid');
    $query->fields('n' , array('uid'));
    $query->condition('c.cid' , $cid);
    $result = $query->execute()->fetch();
    global $user;
    if($user->uid != $result->uid) return false;

	if($comment->field_prove_asker['und']['0']['value'] == 0){
		$comment->field_prove_asker['und']['0']['value'] = 1;
		comment_save($comment);
		return true;
	}
	else return false;
}
/*
 * end of comment part
 */

/*
 * implementation of slideshow callback
 */
function slideshow_items(){
	$query = db_select('node' , 'node');
	$query->join('field_data_field_show_slider', 'show_slider' , "node.nid = show_slider.entity_id AND (show_slider.entity_type = 'node' AND show_slider.deleted = 0)");
	$query->join('field_data_field_image', 'image' , "node.nid = image.entity_id AND (image.entity_type = 'node' AND image.deleted = 0)");
	$query->join('file_managed', 'files' , "image.field_image_fid = files.fid");
	$results = $query->fields('node' , array('nid', 'title'))
				->fields('files' , array('fid', 'uri', 'filesize'))
				->condition('node.status' , 1)
				->condition('show_slider.field_show_slider_value' , 1)
				->orderBy('node.created', 'DESC')
				->range(0, 5)
				->execute()->fetchAll();

	return $results;
}

/*
 * implementation of calendar callback
 */
function calendar_items(){
	$results = db_query("SELECT node.title , node.nid , eventtime.field_eventtime_value as eventtime, company.field_company_value as company, webinar.field_ifwebinar_value as webinar

				FROM {node} node
				LEFT JOIN {field_data_field_eventtime} eventtime ON node.nid = eventtime.entity_id AND (eventtime.entity_type = 'node' AND eventtime.deleted = '0')
                join megapil_808_field_data_field_company company ON node.nid = company.entity_id AND (company.entity_type = 'node' AND company.deleted = '0')
                join megapil_808_field_data_field_ifwebinar webinar ON node.nid = webinar.entity_id AND (webinar.entity_type = 'node' AND webinar.deleted = '0')
				WHERE (
					(DATE_FORMAT(eventtime.field_eventtime_value, '%Y-%m-%d') >= '". date("Y-m-d") ."') 
					AND
					( 
						(node.type IN  ('education', 'college')) 
						OR
						( 
							(node.type IN  ('article')) 
							AND 
							(node.nid IN  
								(SELECT tn.nid AS nid
								FROM {taxonomy_index} tn
								LEFT OUTER JOIN {taxonomy_term_hierarchy} th ON th.tid = tn.tid
								LEFT OUTER JOIN {taxonomy_term_hierarchy} th1 ON th.parent = th1.tid
								WHERE ( (tn.tid = '1900') OR (th1.tid = '1900') ))
							) 
						)
					)
				)
				ORDER BY eventtime ASC")
				->fetchAll();

	return $results;
}

/*
 * implementation of front_news callback
 */
function front_news_items(){
	$results = db_select('node' , 'node')
				->fields('node' , array('nid', 'title', 'created'))
				->condition('node.status' , 1)
				->condition('type' , array('education', 'article', 'publication', 'blog', 'designteam', 'poll', 'podcast', 'projectnew', 'project'), 'IN')
				->condition('language' , 'en' , '<>')
				->orderBy('node.created', 'DESC')
				->range(0, 20)
				->execute()->fetchAll();

	return $results;
}

/*return pedia*/
function get_pedia($page){
    /*list of pedia items*/
	$query = db_select('node' , 'n');
	$query->fields('n' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
	$query->condition('n.type', 'architect');
	$query->condition('n.status', 1);
	$query->orderBy('changed', 'DESC');
	$query->range($page*24, 24);
	$nodes = $query->execute()->fetchAll();
	
	if(!empty($nodes)){
		$nids = array();
		$pedias = array();
		foreach($nodes as $row){
			array_push($nids, $row->nid);
			$row->kind = array();
			$pedias[$row->nid] = $row;
		}

		/*add each pedia picture*/
		$query = db_select('field_data_field_image' , 'p');
		$query->join('file_managed' , 'f' , 'p.field_image_fid = f.fid');
		$query->fields('p' , array('entity_id'));
		$query->fields('f' , array('uri'));
		$query->condition('p.entity_id', $nids, "IN");
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			$pedias[$result->entity_id]->picture = $result->uri;
		}

		/*add each pedia's picture*/
		$query = db_select('field_data_field_dastebandimemar' , 'node_kind');
		$query->join('taxonomy_term_data' , 'taxonomy' , 'node_kind.field_dastebandimemar_tid = taxonomy.tid');
		$query->fields('node_kind' , array('entity_id'));
		$query->fields('taxonomy' , array('name'));
		$query->condition('node_kind.entity_id', $nids, "IN");
		$query->condition('node_kind.field_dastebandimemar_tid', array(2519, 2522), "NOT IN");
		$results = $query->execute()->fetchAll();
		foreach($results as $result){
			array_push($pedias[$result->entity_id]->kind, $result->name);
		}
			
		$return_pedias = array();
		foreach($pedias as $p){
			array_push($return_pedias, $p);
		}
		return ["pedia" => $return_pedias];
	}
	return ["pedia" => array()];
}

/*return the advisors related to a pedia*/
function pedia_advisor($nid)
{
    $query = db_select('field_data_field_experts', 'node_expert');
    $query->join('field_data_field_experts', 'profile_expert', 'profile_expert.field_experts_tid = node_expert.field_experts_tid');
    $query->join('profile', 'profile', 'profile_expert.entity_id = profile.pid');
    $query->leftJoin('field_data_field_full_name', 'name', 'name.entity_id = profile.pid');
    $query->join('users', 'user', 'profile.uid = user.uid');
    $query->leftJoin('file_managed', 'file', 'user.picture = file.fid');
    $query->join('users_roles', 'roles', 'profile.uid = roles.uid');
    $query->fields('profile', array('pid'));
    $query->fields('user', array('uid', 'name', 'mail', 'created'));
    $query->addField('file', 'uri', 'picture');
    $query->addField('name', 'field_full_name_value', 'complete_name');
    $query->condition('node_expert.entity_id', $nid);
    $query->condition('node_expert.entity_type', 'node');
    $query->condition('profile_expert.entity_type', 'profile2');
    $query->condition('name.bundle', 'main');
    $query->condition('name.entity_type', 'profile2');
    $query->condition('profile.type', 'main');
    $query->condition('roles.rid', 10);
    $results = $query->execute()->fetchAll();

    $advisors = array();
    $uids = array();
    if (!empty($results)) {
        foreach ($results as $result) {
            array_push($uids, $result->uid);
            $result->roles = array();
            $advisors[$result->uid] = $result;
        }
        $query = db_select('users_roles', 'users_roles');
        $query->join('role', 'role', 'users_roles.rid = role.rid');
        $query->fields('role', array('name'));
        $query->fields('users_roles', array('uid'));
        $query->condition('users_roles.uid', $uids, 'IN');
        $results = $query->execute()->fetchAll();
        foreach ($results as $row) {
            array_push($advisors[$row->uid]->roles, $row->name);
        }
    }
    $return_advisors = array();
    foreach($advisors as $advisor){
        array_push($return_advisors , $advisor);
    }
    return $return_advisors;
    /*
    if(!empty($node->field_experts)){
        $node->advisor = array();
        $tids = array();
        foreach($node->field_experts as $row){
            array_push($tids, $row->tid);
        }

        if(!empty($tids)){
            $query = db_select('field_data_field_experts' , 'profile_expert');
            $query->join('profile' , 'profile' , 'profile_expert.entity_id = profile.pid');
            $query->join('users_roles' , 'roles' , 'profile.uid = roles.uid');
            $query->addField('profile_expert' , 'entity_id' , 'pid');
            $query->condition('profile_expert.field_experts_tid', $tids, "IN");
            $query->condition('profile.type', 'main');
            $query->condition('profile_expert.entity_type', 'profile2');
            $query->condition('roles.rid', 10);
            $results = $query->execute()->fetchAll();
            foreach($results as $result){
                if(count($node->advisor) < 5){
                    $profile = profile2_load($result->pid);

                    $query = db_select('users' , 'u');
                    $query->leftJoin('file_managed' , 'f' , 'u.picture = f.fid');
                    $query->fields('u' , array('uid' , 'name' , 'mail'));
                    $query->addField('f' , 'uri' , 'picture');
                    $query->condition('u.uid', $profile->uid);
                    $result = $query->execute()->fetch();

                    $p = new stdClass();
                    $p->uid = $profile->uid;
                    $p->user_name = $result->name;
                    $p->mail = $result->mail;
                    $p->picture = $result->picture;
                    $p->name = $profile->field_full_name['und'][0]['value'];
                    $p->education = $profile->field_education_field['und'][0]['value'];
                    $p->university = $profile->field_university['und'][0]['value'];
                    $p->skills = $profile->field_skills['und'][0]['value'];
                    $p->experts = $profile->field_experts['und'];
                    array_push($node->advisor, $p);
                }elseif(count($node->advisor) == 5){
                    array_push($node->advisor, "etc");
                }
            }
        }
    }
    */
}

/*return information about taxonomy*/
function taxonomy_information($tid){
    /*count of questions that have this tid*/
    $query = db_select('field_data_field_experts', 'e')
        ->fields('e' , array('entity_id'))
        ->condition('field_experts_tid', $tid)
        ->condition('entity_type', 'node')
        ->condition('bundle', 'questions')
        ->execute();
    $question_count = $query->rowCount();

    /*count of users that have this tid*/
    $query = db_select('field_data_field_experts', 'e')
        ->fields('e' , array('entity_id'))
        ->condition('field_experts_tid', $tid)
        ->condition('entity_type', 'profile2')
        ->execute();
    $user_count = $query->rowCount();

    /*nid of pedia that related to this tid*/
    $query = db_select('field_data_field_experts', 'e');
    $query->fields('e' , array('entity_id'));
    $query->condition('field_experts_tid', $tid);
    $query->condition('entity_type', 'node');
    $query->condition('bundle', 'architect');
    $nid = $query->execute()->fetch();
    $nid = $nid->entity_id;

    /*picture of pedia that related to this tid*/
    $query = db_select('field_data_field_image' , 'p');
    $query->join('file_managed' , 'f' , 'p.field_image_fid = f.fid');
    $query->fields('f' , array('uri'));
    $query->condition('p.entity_id', $nid);
    $picture = $query->execute()->fetch();

    return ['question_count' => $question_count, 'user_count' => $user_count, 'pic' => $picture , 'tid' => $tid, 'nid' => $nid];
}

/*upload file on site*/
function create_file(){
    $files =  $_FILES;
    foreach ($files as $file_name => $file_info){
        $_FILES["files"]["name"][$file_name] = $file_info['name'];
        $_FILES["files"]["tmp_name"][$file_name] = $file_info['tmp_name'];
        $_FILES["files"]["size"][$file_name] = $file_info['size'];
        $_FILES["files"]["error"][$file_name] = $file_info['error'];
    }
    /*function address : services module /resources /file_resource.inc*/
    return _file_resource_create_raw();
}

/*retrieve uids information function*
function user_information($uids = array()){
    $query = db_select('users' , 'u');
    $query->leftJoin('file_managed' , 'f' , 'u.picture = f.fid');
    $query->fields('u' , array('uid' , 'name' , 'mail'));
    $query->addField('f' , 'uri' , 'picture');
    if(!empty($uids)) $query->condition('u.uid', $uids, 'IN');
    $result = $query->execute()->fetchAll();

    return $result;
}
/*end function*/


/*latin site web services*/
/*
 * insert email
*/
function latin_insert_email($email){
    $email = json_decode($email, true);
    $path = "sites/all/modules/808/custom_services/pbd.json";
    $string = file_get_contents($path);
    $data = json_decode($string, true);
    if($data == '') $data = array();
    else{
        if(in_array($email, $data)) return $email;
    }
    array_push($data, $email);
    $json = json_encode($data);

    if (file_put_contents($path, $json))
        return 200;
    else
        return 401;
}
