<?php

function pedia_resource_index($hash , $page , $version){
    if(!(hash_true($hash , "pedia"))) return "failed to access";
    if($version == 0){
        return list_of_pedia_version_one($page);
    }
    return "This version not supported";
}
function pedia_resource_retrieve($hash , $nid , $version){
    if(!(hash_true($hash , "pedia"))) return "failed to access";
    if($version == 0){
        return retrieve_a_pedia_version_one($nid);
    }
    return "This version not supported";
}
function pedia_resource_advisors_list($hash , $nid , $version){
    if(!(hash_true($hash , "pedia"))) return "failed to access";
    if($version == 0){
        return list_of_advisors_of_a_pedia_version_one($nid);
    }
    return "This version not supported";
}
function pedia_resource_search($hash , $value , $version){
    if(!(hash_true($hash , "pedia"))) return "failed to access";

    if($version == 0) {
        $query = db_select("node", "node");
        $query->fields('node', array('nid'));
        $query->condition('node.title', '%' . $value . '%', 'LIKE');
        $query->condition('node.type' , 'architect');
        $query->condition('node.status' , 1);
        $nid1 = $query->execute()->fetchAll();

        /*
         * @todo
         * Subtract the body that is not published
         * */
        $query = db_select("field_data_field_architecttext", "body");
        $query->addField('body', 'entity_id', 'nid');
        $query->condition('body.body_value', '%' . $value . '%', 'LIKE');
        $query->condition('body.entity_type' , 'node');
        $query->condition('body.bundle' , 'architect');
        $nid2 = $query->execute()->fetchAll();

        $nids = array_merge($nid1, $nid2);
        $custom_list = array();
        foreach ($nids as $row) array_push($custom_list, $row->nid);
        if(!empty($custom_list))
            return list_of_pedia_version_one( 0, $custom_list);
        else
            return ["pedia" => array()];
    }
    return "This version not supported";
}

function list_of_pedia_version_one($page , $custom_list = array()){
    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'created' , 'changed' , 'status'));
    $query->condition('node.type', 'architect');
    $query->condition('node.status', 1);
    $query->orderBy('node.changed', 'DESC');
    if(!empty($custom_list)) $query->condition('node.nid' , $custom_list , 'IN');
    else $query->range($page*24, 24);
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
        $query = db_select('field_data_field_arch_picture' , 'field_picture');
        $query->join('file_managed' , 'file_picture' , 'field_picture.field_arch_picture_fid = file_picture.fid');
        $query->fields('field_picture' , array('entity_id'));
        $query->fields('file_picture' , array('uri'));
        $query->condition('field_picture.entity_id', $nids, "IN");
        $results = $query->execute()->fetchAll();
        foreach($results as $result){
            $pedias[$result->entity_id]->picture = $result->uri;
        }

        /*add each pedia's taxonomy*/
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

        $pedias = array_values($pedias);

        return ["pedia" => $pedias];
    }
    return ["pedia" => array()];
}

function retrieve_a_pedia_version_one($nid){
    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' , 'uid' , 'title' , 'type' , 'created' , 'changed' , 'status'));
    $query->condition('node.nid', $nid);
    $pedia = $query->execute()->fetch();
    if(empty($pedia) || count($pedia) == 0) return "The peida is not exist";
    $pedia->url = "http://civil808.com/node/".$nid;

    $query = db_select('field_data_field_experts' , 'expert');
    $query->addField('expert' , 'field_experts_tid' , 'tid');
    $query->condition('expert.entity_id' , $nid);
    $tids = $query->execute()->fetchAll();
    $pedia->field_experts = $tids;

    $query = $query = db_select('field_data_field_architecttext' , 'body');
    $query->fields('body' , array('field_architecttext_value'));
    $query->condition('body.entity_id', $nid);
    $pedia->body = $query->execute()->fetch()->field_architecttext_value;

    $query = db_select('field_data_field_arch_picture' , 'field_picture');
    $query->join('file_managed' , 'file_picture' , 'field_picture.field_arch_picture_fid = file_picture.fid');
    $query->fields('file_picture' , array('uri'));
    $query->condition('field_picture.entity_id', $nid);
    $results = $query->execute()->fetchAll();
    $pedia->picture = $results;

    $query = db_select('field_data_field_dastebandimemar' , 'node_kind');
    $query->join('taxonomy_term_data' , 'taxonomy' , 'node_kind.field_dastebandimemar_tid = taxonomy.tid');
    $query->fields('taxonomy' , array('name'));
    $query->condition('node_kind.entity_id', $nid);
    $query->condition('node_kind.field_dastebandimemar_tid', array(2519, 2522), "NOT IN");
    $results = $query->execute()->fetchAll();
    $pedia->kind = $results;

    return ["pedia" => $pedia];
}

function list_of_advisors_of_a_pedia_version_one($nid){
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
    if (!empty($results)) {
        $uids = array();
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
    else{
        return ["advisors" => array()];
    }

    $advisors = array_values($advisors);

    return ["advisors" => $advisors];
}