<?php

function user_resource_purchased_products_list($hash , $uid , $version){
    if(!(hash_true($hash , "user"))) return "failed to access";
    if($version == 0){
        return list_of__user_purchased_products_version_one($uid);
    }
    return "This version not supported";
}

function list_of__user_purchased_products_version_one($uid){
    global $user;
    if($user->uid != $uid) return ["ebook" => array()];
    $query = db_select('m_buyed_nodes', 'buyed');
    $query->join('node', 'node', 'buyed.nid = node.nid');
    $query->join('field_data_field_files', 'field_file', 'node.nid = field_file.entity_id');
    $query->join('file_managed', 'file', 'field_file.field_files_fid = file.fid');
    $query->join('users', 'user', 'node.uid = user.uid');
    $query->leftJoin('field_data_field_point_needed', 'price', 'buyed.nid = price.entity_id');
    $query->fields('buyed', array('nid', 'date', 'price'));
    $query->fields('node', array('title'));
    $query->fields('file', array('uri' , 'filesize'));
    $query->fields('user', array('uid', 'name'));
    $query->fields('price', array('field_point_needed_value'));
    $query->condition('buyed.uid', $uid);
    $query->condition('buyed.type', 'article');
    $query->condition('node.type', 'publication');
    $query->condition('field_file.entity_type', 'node');
    $query->condition('field_file.bundle', 'publication');
    $buyed_nodes = $query->execute()->fetchAll();
    foreach ($buyed_nodes as $node) {
        if(empty($node->price) && !empty($node->field_point_needed_value)){
            $node->price =  $node->field_point_needed_value;
        }
        unset($node->field_point_needed_value);
    }
    return ["ebook" => $buyed_nodes];
}