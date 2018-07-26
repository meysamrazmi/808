<?php

/**
 * @file
 * Comment behavior.
 *
 * Updates the node type in the field_data_comment_body and field_revision_comment_body tables.
 */

/**
 * Implementation of node_convert_change().
 */
function comment_node_convert_change($data, $op) {
  if ($op == 'insert') {
    $node = $data['node'];
    
	$prefix = $GLOBALS['databases']['default']['default']['prefix']; //TODO: Perhaphs make get current DB instead of default DB ?
      $prefix = 'megapil_808_';
    $tables = array(
        $prefix . 'field_data_comment_body',
        $prefix . 'field_revision_comment_body'
      );

    foreach ($tables as $table) {
     $query = "
       UPDATE $table AS cb
	   LEFT JOIN {$prefix}comment AS c ON cb.entity_id = c.cid AND cb.entity_type = :entity_type
        SET cb.bundle = :new_bundle
        WHERE c.nid = :nid
        ";
      $args = array(':entity_type' => 'comment', ':nid' => $node->nid, ':new_bundle' => 'comment_node_' . $data['dest_node_type']);
      db_query($query, $args);
    }
  }
}
