<?php

/**
 * Returns the sortable table listing of all sellers orders.
 */
function up_share_history_all() {
  drupal_set_title(t('Share Points History'));
  $header = array(
    array('data' => t('Customer'), 	'field' => 'buyer_uid'),
    array('data' => t('Owner'), 	'field' => 'uid'),
    array('data' => t('Entity type'),'field' => 'entity_type'),
    array('data' => t('Entity id'),'field' => 'entity_id'),
    array('data' => t('Portion'),	'field' => 'portion'),
    array('data' => t('Model'), 	'field' => 'model'),
    array('data' => t('total'), 	'field' => 'total'),
    array('data' => t('User Share'), 	'field' => 'points'),
    array('data' => t('Date'), 	'field' => 'updated'),
  );
  
  if(isset($_GET['sort']) && isset($_GET['order'])) {
  	if($_GET['sort'] == 'asc') $sort = 'ASC';
  	else $sort = 'DESC';
	foreach($header as $key=>$val){
		if(in_array($_GET['order'], $val)){
			$sort_order = $header[$key]['field'];
			break;
		}
	}
  }
  else {
  	$sort = 'DESC';
  	$sort_order = 'updated';
  }
  
  $query = db_select('up_share_log', 'sl')->extend('PagerDefault')->limit(50);
  $query->fields('sl', array('uid', 'buyer_uid', 'entity_id', 'entity_type', 'field_id', 'points', 'portion', 'model', 'total', 'updated'));
  $query->join('users', 'u' , 'sl.uid = u.uid');
  $query->fields('u', array('name'));
  $query->orderBy($sort_order, $sort);
  $results = $query->execute();
  
  $total_sell = $total_share = 0;
  // Build a table based on the customer's sales.
  foreach ($results as $sales) {
	switch($sales->entity_type){
		case 'uc_order':
			$entity_id = l($sales->entity_id, '/admin/store/orders/'. $sales->entity_id);
			$nid = db_query("SELECT nid FROM {uc_products} WHERE model = :sku", array(':sku' => $sales->model))->fetchObject();
			$model = '<a href="/node/'. $nid->nid .'" target="_blank">'. $sales->model .'</a>';
			break;
		default:
			$entity_id = $sales->entity_id;
			$model = '<a href="/node/'. $sales->model .'" target="_blank">'. t('content') .' '. $sales->model .'</a>';
	}
	$buyer = '';
	if($sales->buyer_uid){
		$buyer_uid = user_load($sales->buyer_uid);
		$buyer = '<a href="/user/'. $buyer_uid->uid .'">'. $buyer_uid->name .'</a>' ;
	}
	$total_sell += $sales->total;
	$total_share += $sales->points;
    $rows[] = array(
      array('data' => $buyer),
      array('data' => l($sales->name, 'user/'. $sales->uid .'/sharepoints')),
      array('data' => t($sales->entity_type)),
      array('data' => $entity_id),
      array('data' => $sales->portion .' %'),
      array('data' => $model),
      array('data' => formatMoney($sales->total)),
      array('data' => formatMoney($sales->points)),
      array('data' => format_date($sales->updated, 'date_time')),
    );
  }
  if (!empty($rows)) {
	array_unshift($rows, '', array(count($rows) . t('Order'),
		'','','','','', 
		'<p style="font-weight: 500;font-size: 14px;margin: 0;">' . formatMoney($total_sell) . t('toman') .'</p>',
		'<p style="font-weight: 500;font-size: 14px;margin: 0;">' . formatMoney($total_share)  . t('toman') .'</p>',
		'',
	));
  }
	
  $build['up_share_history'] = array(
    '#theme' => 'table', 
    '#header' => $header, 
    '#rows' => $rows, 
  );
  $build['up_share_history_pager'] = array('#theme' => 'pager');
  return $build;
}
