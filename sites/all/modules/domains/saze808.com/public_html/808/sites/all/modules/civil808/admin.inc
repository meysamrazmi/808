<?php

function civil808_page_admin_money() {
	$q = db_select('m_reward_request', 'r')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$rows = $q->fields('r', array())->condition('r.state', 0)->execute()->fetchAll();
	$tabale_header = array(
		t('User'),
		t('Price'),
		t('Date'),
		t('Bank info')
		);
	$table_rows = array();

	foreach ($rows as $r) {
		$user = user_load($r->uid);
		$p = profile2_load_by_user($user);
		$table_rows[] = array(
			l($user->name, 'user/'.$r->uid),
			$r->price,
			format_date($r->date),
			$p['bank']->field_bank_name['und'][0]['value'].'<br>'.$p['bank']->field_bank_cart_num['und'][0]['value']
			);
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');
}
function civil808_page_admin_money_nodebuyes() {
	$q = db_select('m_buyed_nodes','n')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$q->join('node', 'nn', 'n.nid = nn.nid');
	$rows = $q->fields('n', array())->fields('nn', array())->condition('n.value', '-1')->execute()->fetchAll();

	$tabale_header = array(
		t('User'),
		t('Content'),
		t('Price'),
		t('Date'),
		);
	$table_rows = array();

	foreach ($rows as $r) {
		$node = node_load($r->nid);
		$table_rows[] = array(
			l($user->name, 'user/'.$r->uid),
			l($r->title, 'node/'.$r->nid),
			$node->field_point_needed['und'][0]['value'],
			format_date($r->date)
			);
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');
}

function civil808_page_admin_money_event_buys($eid = -1) {
	echo $eid;
	if($eid == -1) {
	$q = db_select('node','n')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$rows = $q->fields('n', array())->condition('n.type', 'event')->orderBy('created', 'DESC')->execute()->fetchAll();

	$tabale_header = array(
		t('Title'),
		t('Date'),
		t('Operations')
		);
	$table_rows = array();

	foreach ($rows as $r) {
		$table_rows[] = array(
			l($r->title, 'node/'.$r->nid),
			format_date($r->created),
			l(t('View Buys'), 'admin/money/event/'.$r->nid)
			);
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');
		return "s";
	}
	$node = node_load($eid);
	$q = db_select('m_buyed_nodes','n')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$rows = $q->fields('n', array())->condition('n.nid', intval($eid))->execute()->fetchAll();

	$tabale_header = array(
		t('User'),
		t('Ticket'),
		t('Price'),
		t('Date'),
		t('Bank info')
		);
	$table_rows = array();

	foreach ($rows as $r) {
		$user = user_load($r->uid);
		$p = profile2_load_by_user($user);
		$table_rows[] = array(
			l($user->name, 'user/'.$r->uid),
			$r->value,
			$node->field_ticket_price['und'][$r->value]['value'],
			format_date($r->date),
			$p['bank']->field_bank_name['und'][0]['value'].'<br>'.$p['bank']->field_bank_cart_num['und'][0]['value']
			);
	}
	return t("Event").": ".l($node->title, 'node/'.$eid)."<br>".theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');
}


/**
 * 
 */
function civil808_options_808_form($form, &$form_state) {
	if (!is_array($form)) {
		$form = array();
	}
	
	$form['saze808'] = array(
		'#type' => 'fieldset',
		'#title' => t('Saze808'),
		);	
	$form['saze808']['comment_price'] = array(
		'#type' => 'textfield',
		'#title' => t('Saze808 comment price'),
		'#required' => TRUE,
		'#default_value' => variable_get('saze808_comment', 10000)
		);
	$form['saze808']['node_price'] = array(
		'#type' => 'textfield',
		'#title' => t('Saze808 node price'),
		'#required' => TRUE,
		'#default_value' => variable_get('saze808_node', 10000)
		);

	$form['shop'] = array(
		'#type' => 'fieldset',
		'#title' => t('Shop'),
		);	
	$form['shop']['shop_order_percent'] = array(
		'#type' => 'textfield',
		'#title' => t('Shop order percent'),
		'#required' => TRUE,
		'#default_value' => variable_get('shop_order_percent', 0.2)
		);



	// events
	$form['event808'] = array(
		'#type' => 'fieldset',
		'#title' => t('Evet808'),
		);

	$tabale_header = array(
		t('Date'),
		t('Code'),
		t('Percent'),
		t('Active'),
		t('Operations')
		);

	$rows = db_select('m_off_code', 'o')->extend('PagerDefault')->extend('TableSort')->limit(20)->fields('o', array())->execute()->fetchAll();
	foreach ($rows as $row) {
		$table_rows[] = array(
			format_date($row->date),
			$row->code,
			$row->price.'%',
			$row->active ? t('Active') : t('Deactive'),
			$row->active ? l(t('Deactive'), 'admin/content/options/deactive/'.$row->id) : "",
			);
	}
	$form['event808']['codes'] = array(
		'#markup' => l(t('Add off code'), 'admin/content/options/addoff').theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager'),
		);

	// events
	




	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		);
	return $form;
}

/**
 * Summit handler for event808_options_808_form
 */
function civil808_options_808_form_submit($form, &$form_state) {
	variable_set('saze808_node', $form_state['values']['node_price']);
	variable_set('saze808_comment', $form_state['values']['comment_price']);
	variable_set('shop_order_percent', $form_state['values']['shop_order_percent']);

}

/**
 * 
 */
function civil808_options_addoff_808_form($form, &$form_state) {
	if (!is_array($form)) {
		$form = array();
	}

	$form['title'] = array(
		'#markup' => '<h2>'.t('Add off code').'</h2>',
		);

	$form['code'] = array(
		'#type' => 'textfield',
		'#title' => t('Code'),
		'#required' => TRUE,
		);
	$form['percent'] = array(
		'#type' => 'textfield',
		'#title' => t('Percent'),
		'#required' => TRUE,
		);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save')
		);
	

	return $form;
}

/**
 * Summit handler for civil808_options_addoff_808_form
 */
function civil808_options_addoff_808_form_submit($form, &$form_state) {
	db_insert('m_off_code')
	->fields(array(
		'code' => $form_state['values']['code'],
		'price' => $form_state['values']['percent'],
		'date' => time(),
		'active' => 1
		))
	->execute();
	$form_state['redirect'] = 'admin/content/options';
}


/**
 * 
 */
function civil808_options_deactive_808_form($form, &$form_state, $id) {
	$form['id'] = array('#type' => 'value', '#value' => $id);
  return confirm_form($form,
    t('Are you sure you want to deactive %title?', array('%title' => t('Off code'))),
    'admin/content/options',
    t('This action cannot be undone.'),
    t('Deactive'),
    t('Cancel')
  );
}

/**
 * Summit handler for civil808_options_deactive_808_form
 */
function civil808_options_deactive_808_form_submit($form, &$form_state) {
if ($form_state['values']['confirm']) {
    $id = $form_state['values']['id'];
    db_query('UPDATE {m_off_code} SET active = 0 WHERE id = :id', array(':id' => $id));
  }

  $form_state['redirect'] = 'admin/content/options';
}