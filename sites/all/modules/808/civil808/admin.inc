<?php
function civil808_page_admin_money_nodebuyess($id = 0) {
	global $user;
	if(isset($_GET['sort']) && isset($_GET['order'])) {
		if($_GET['sort'] == 'asc')
			$sort = 'ASC';
		else
			$sort = 'DESC';
	
		switch($_GET['order']) {
			case 'Date':
				$order = 'date';
				break;
			default:
				$order = 'date';
		}
	}
	else {
		$sort = 'DESC';
		$order = 'date';
	}

	$q = db_select('m_buyed_nodes','n')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$q->join('node', 'nn', 'n.nid = nn.nid');
	$q->orderBy($order, $sort);
	$q->fields('n', array())->fields('nn', array('nid', 'title'));

	if($id) $q->condition('n.nid' , intval($id));
	$bijan = $user->uid;
	$rows = $q->condition('n.uid', $bijan)->condition('n.type', 'event')->execute()->fetchAll();

	$tabale_header = array(
		t('User'),
		t('Content'),
		t('Price'),
		array( 'data' => t('Date'), 'field' => 'date')
	);
	$table_rows = array();
	foreach ($rows as $r) {
		$node = node_load($r->nid);
		$user = user_load($r->uid);
		$price=$node->field_point_needed['und'][0]['value'];
		
		if($r->type =='event') {
			$tic = unserialize($r->value);
			$price =0;
			foreach($tic as $t ) {
				$price += intval($t['price']);
			}
		}
		$table_rows[] = array(
			l($user->name, 'user/'.$r->uid),
			l($r->title, 'admin/money/nodebuyes/'.$r->nid),
			formatMoney($price),
			format_date($r->date)
		);
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');
}

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
	$a = variable_get('shop_reseler_percent', array());
	$txt = '';
	foreach($a as $key => $value) {
		$txt .= $key.'|'.$value.'|'.base64_encode($key)."\n";
	}
	$form['shop']['shop_reseler_percent'] = array(
		'#type' => 'textarea',
		'#title' => t('Shop reseler percent'),
		'#required' => TRUE,
		'#default_value' => $txt,
		'#attributes' => array(
		'style' => 'direction:ltr')
	);
	$form['contact'] = array(
		'#type' => 'fieldset',
		'#title' => t('Contact info'),
	);
	$form['contact']['contact_reciever'] = array(
		'#type' => 'textarea',
		'#title' => t('Contact recievers name'),
		'#required' => TRUE,
		'#default_value' => variable_get('civil808_contact_emails', 'info@civil808.com|پشتیبانی')
	);
	$form['event808'] = array(
		'#type' => 'fieldset',
		'#title' => t('Off code'),
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
	$txt = explode("\n", $form_state['values']['shop_reseler_percent']);
	$arr = array();
	foreach($txt as $tt) {
		$a = explode('|', $tt);
		if(count($a) >= 2)
			$arr[$a[0]] = $a[1];
	}
	variable_set('shop_reseler_percent', $arr);
	variable_set('civil808_contact_emails', $form_state['values']['contact_reciever']);
}

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

function civil808_page_admin_people_export($form, $form_state) {
	$form = array();
	$calendar = calendar_systems_get_calendar_instance('iranian');

	$form['type'] = array(
		'#type' => 'radios',
		'#title' => t('Type'),
		'#options' => array(
			'email' => t('Email'),
			'phone' => t('Phone'),
			),
	);
	$form['date'] = array(
		'#type' => 'textfield',
		'#title' => t('From'),
		'#required' => true,
		'#default_value' => $calendar->date('Y-m-d',time() - 24 * 60 * 60),
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Export')
	);
	return $form;
}

function civil808_page_admin_people_export_submit($from, &$form_state) {
	header("Content-Type: text/plain");
	header("Content-Disposition: attachment; filename=\"export.txt\"");
	$calendar = calendar_systems_get_calendar_instance('iranian');
	$val = $calendar->strToTimestamp($form_state['values']['date']);
	switch ($form_state['values']['type']) {
		case 'email':
			$rows = db_select('users','u')->fields('u', array('mail'))->condition('created', $val , '>')->execute()->fetchAll();
			foreach ($rows as $key => $value) {
				echo $value->mail."\n";	
			}
			break;
		default:
			$q = db_select('users','u');
			$q->join('profile', 'p', 'p.uid = u.uid');
			$q->join('field_data_field_mobile', 'm', 'p.pid = m.entity_id');
			$rows = $q->fields('m',array('field_mobile_value'))->condition('u.created', $val , '>')->execute()->fetchAll();
			foreach ($rows as $key => $value) {
				echo $value->field_mobile_value."\n";	
			}
			break;
	}
	die;
}

function administer_messages(){
	if(isset($_GET['sort']) && isset($_GET['order'])) {
		if($_GET['sort'] == 'asc')
			$sort = ' ASC';
		else
			$sort = ' DESC';
	
		switch($_GET['order']) {
			case 'Date':
				$order = 'm.timestamp';
				break;
			default:
				$order = 'm.timestamp';
		}
	}
	else {
		$sort = ' DESC';
		$order = 'm.timestamp';
	}
	
	$user = user_load(60);
	$query = _privatemsg_assemble_query('list', $user, 'inbox');
	foreach ($query->execute() as $thread) {
		// $thread->thread_id;
	}

	// $q = db_select('pm_message','m')->extend('PagerDefault')->extend('TableSort')->limit(50);
	// $q->join('pm_index', 'thread', 'thread.mid = m.mid');
	// $q->fields('thread', array('thread_id', 'recipient'));
	// $q->fields('m', array('author', 'subject', 'body', 'timestamp'));
	// $rows = $q->orderBy($order, $sort)->execute();
	$rows = db_query("SELECT author, subject, body, timestamp FROM {pm_message} m WHERE m.mid IN (SELECT mid FROM {pm_index} th WHERE NOT th.thread_id IN (SELECT thread_id FROM {pm_index} th WHERE th.recipient IN (:uid))) ORDER BY ". $order . $sort, array(':uid' => array(60, 7072)))->fetchAll();
	
	$tabale_header = array(
		t('User'),
		t('Subject'),
		t('Message'),
		array('data' => t('Date'), 'field' => 'timestamp', 'sql_field' => '{pm_message}.timestamp')
	);
	$table_rows = array();
	foreach ($rows as $r) {
		$user = user_load($r->author);
		
		$table_rows[] = array(
			l($user->name, 'user/'.$user->uid),
			// l($r->subject, 'messages/view/'.$r->thread_id),
			$r->subject,
			nl2br($r->body),
			format_date($r->timestamp)
		);
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');	
}
