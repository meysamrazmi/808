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

function list_of_pedia_version_one($page){
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
        $query = db_select('field_data_field_arch_picture' , 'p');
        $query->join('file_managed' , 'f' , 'p.field_arch_picture_fid = f.fid');
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

function retrieve_a_pedia_version_one($nid){
    $query = db_select('node' , 'n');
    $query->fields('n' , array('nid' , 'uid' , 'title' , 'type' , 'created' , 'changed' , 'status'));
    $query->condition('n.nid', $nid);
    $pedia = $query->execute()->fetch();
    if(empty($pedia) || count($pedia) == 0) return "The peida is not exist";
    $pedia->url = "http://civil808.com/node/".$nid;

    $query = db_select('field_data_field_experts' , 'e');
    $query->addField('e' , 'field_experts_tid' , 'tid');
    $query->condition('e.entity_id' , $nid);
    $tids = $query->execute()->fetchAll();
    $pedia->field_experts = $tids;

    $query = $query = db_select('field_data_field_architecttext' , 't');
    $query->fields('t' , array('field_architecttext_value'));
    $query->condition('t.entity_id', $nid);
    $pedia->body = $query->execute()->fetch()->field_architecttext_value;

    $query = db_select('field_data_field_arch_picture' , 'p');
    $query->join('file_managed' , 'f' , 'p.field_arch_picture_fid = f.fid');
    $query->fields('f' , array('uri'));
    $query->condition('p.entity_id', $nid);
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
    $return_advisors = array();
    foreach($advisors as $advisor){
        array_push($return_advisors , $advisor);
    }
    return ["advisors" => $return_advisors];
}