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
	$q = db_select('pm_message','pm')->extend('PagerDefault')->extend('TableSort')->limit(50);
	$q->join('pm_index', 'thread', 'thread.mid = pm.mid AND pm.author != thread.recipient');
	$q->fields('thread', array('thread_id', 'recipient'));
	$q->fields('pm', array('author', 'subject', 'body', 'timestamp', 'mid'));
	$rows = $q->orderBy('pm.timestamp', 'DESC')->execute();
	$count = $rows->rowCount();
	$tabale_header = array(
		'#',
		t('message id'),
		t('Sender'),
		'reciver',
		t('Receiver'),
		t('Subject'),
		t('Message'),
		t('Date'),
		'threar-id',
		t('Operations')
	);
	$table_rows = array();
	$i = 0;
	foreach ($rows as $r) {
		$user = user_load($r->author);
		$recipient = user_load($r->recipient);
		if($i != 0 && $table_rows[$i-1][8] == $r->thread_id && $table_rows[$i-1][1] == $r->mid){
			$table_rows[$i-1][3] .= '<br>'. $r->recipient;
			$table_rows[$i-1][4] .= '<br>'. l($recipient->name, 'user/'.$recipient->uid);
			continue;
		}
		$table_rows[] = array(
			$count--,
			$r->mid,
			l($user->name, 'user/'.$user->uid),
			$r->recipient,
			l($recipient->name, 'user/'.$recipient->uid),
			l($r->subject,'/messages/view/'. $r->thread_id),
			nl2br($r->body),
			format_date($r->timestamp),
			$r->thread_id,
			l(t('Edit'), '/messages/edit/'. $r->thread_id .'/'. $r->mid .'?destination=admin/content/messages') .'<br>'. l(t('Delete'), '/messages/delete/'. $r->thread_id .'/'. $r->mid .'?destination=admin/content/messages'),
		);
		$i++;
	}
	return theme('table', array('header' => $tabale_header, 'rows' => $table_rows)).theme('pager');	
}

function privatemsg_edit($form, $form_state, $thread, $message) {
	$form['pmid'] = array(
		'#type' => 'value',
		'#value' => $message->mid,
	);
	if (isset($thread['participants'])) {
		$recipients_plain = $thread['participants'];
	}
	mdump($message,true);
	$form['body'] = array(
		'#type' => 'text_format',
		'#title' => t('Message'),
		'#rows' => 6,
		'#weight' => -3,
		'#default_value' => $message->body,
		'#resizable' => TRUE,
	);
	$form['subject'] = array(
		'#type' => 'textfield',
		'#title' => t('Subject'),
		'#size' => 50,
		'#maxlength' => 255,
		'#default_value' => $message->subject,
		'#weight' => -5,
	);
	$url = isset($_REQUEST['destination'])? $_REQUEST['destination'] : 'messages/view/' . $message->thread_id;
	$form['edit_destination'] = array(
		'#type' => 'value',
		'#value' => $url,
	);
	$form['actions'] = array('#type' => 'actions');	
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Send message'),
		'#weight' => 49,
	);
	$form['actions']['cancel'] = array(
		'#markup' => l(t('Cancel'), $url , array('attributes' => array('id' => 'edit-cancel'))),
	);
	field_attach_form('privatemsg_message', $message, $form, $form_state);
	return $form;
}

function privatemsg_edit_submit($form, &$form_state) {
	$message = $form_state['build_info']['args'][1];
	$thread = $form_state['build_info']['args'][0];
	$flag = false;
	
	$changes = array();
	if(strcmp($form_state['values']['body']['value'], $message->body) != 0){
		$changes['body'] = $form_state['values']['body']['value'];
		$flag = true;
	}
	if(strcmp($form_state['values']['subject'], $message->subject) != 0){
		$changes['subject'] = $form_state['values']['subject'];
		$flag = true;
		//to do: change hole thread subject for every message
	}
	
	//handle other fields of messages
	$message->field_files = $form_state['values']['field_files'];
	field_attach_presave('privatemsg_message', $message);
	field_attach_update('privatemsg_message', $message);

	if($flag){
		db_update('pm_message')
		->fields($changes)
		->condition('mid', $message->mid)
		->execute();
	}
	$form_state['redirect'] = $form_state['values']['edit_destination'];
}

function civil808_privatemsg_message_view(){
  $vars['message_body'] =  drupal_render($message->content);
  if (isset($vars['mid']) && isset($vars['thread_id']) && privatemsg_user_access('delete privatemsg')) {
    $vars['message_actions'][] = array('title' => t('Delete'), 'href' => 'messages/delete/' . $vars['thread_id'] . '/' . $vars['mid']);
  }
  $vars['message_anchors'][] = 'privatemsg-mid-' . $vars['mid'];
  if (!empty($message->is_new)) {
    $vars['message_anchors'][] = 'new';
    $vars['new'] = drupal_ucfirst(t('new'));
  }

  // call hook_privatemsg_message_view_alter
  drupal_alter('privatemsg_message_view', $vars);

  $vars['message_actions'] = !empty($vars['message_actions']) ? theme('links', array('links' => $vars['message_actions'], 'attributes' => array('class' => array('privatemsg-message-actions', 'links', 'inline')))) : '';
	
}

  
  