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

function merge_experts_form($from, &$form_state){
	try {
		for($i = 0; $i < 5; $i++){
			$form['experts'. $i] = array(
				'#type' => 'fieldset',
				'#title' => t('Merging'),
			);	
			$form['experts'. $i]['source_tid'. $i] = array(
				'#type' => 'textfield',
				'#title' => t('source tids'),
				'#description' => t('insert source tid')
			);
			$form['experts'. $i]['destionation_tid'. $i] = array(
				'#type' => 'textfield',
				'#title' => t('destionation tid'),
				'#description' => t('insert destionation tid. if tid is equal to 0 the taxonomy will be deleted.')
			);
			$form['experts'. $i]['message'. $i] = array(
				'#type' => 'checkbox',
				'#title' => t('send message to user'),
				'#description' => t('send message to user')
			);	
		}
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Merg')
		);
		return $form;
	} catch (Exception $e) {
		echo 'Caught exception: ',  $e->getMessage(), "\n";
	}
}

function merge_experts_form_validate($from, &$form_state){
	try{
		for($i = 0; $i < 5; $i++){
			if (strlen($form_state['values']['source_tid'. $i]) > 0) {
				if (strlen($form_state['values']['destionation_tid'. $i]) == 0) {
					form_set_error('destionation_tid'. $i, t('fill the blank field'));
				}
				else if($form_state['values']['source_tid'. $i] == $form_state['values']['destionation_tid'. $i]){
					form_set_error('source_tid'. $i, 'تخصص مبدا و مقصد با هم برابراند.');
				}
				else if(empty(taxonomy_term_load($form_state['values']['source_tid'. $i]))){
					form_set_error('source_tid'. $i, 'تخصص مبدا وجود ندارد');
				}
				else if(($form_state['values']['destionation_tid'. $i] != 0) && (empty(taxonomy_term_load($form_state['values']['destionation_tid'. $i])))){
					form_set_error('destionation_tid'. $i, 'تخصص مقصد وجود ندارد');
				}
			}
			else if(strlen($form_state['values']['destionation_tid'. $i]) > 0) {
				form_set_error('source_tid'. $i, t('fill the blank field'));
			}
		}
	} catch (Exception $e) {
		drupal_set_message($e->getMessage() , 'error');
		watchdog('merging experts', $e->getMessage(), WATCHDOG_CRITICAL);
	}
}

function merge_experts_form_submit($from, &$form_state){
	try{
		for($i = 0; $i < 5; $i++){
			if(strlen($form_state['values']['source_tid'. $i]) == 0 && strlen($form_state['values']['destionation_tid'. $i]) == 0){
				continue; //skip when both are null
			}			
			$source_term = taxonomy_term_load($form_state['values']['source_tid'. $i]);
			if($form_state['values']['destionation_tid'. $i] != 0){
				$destionation_term = taxonomy_term_load($form_state['values']['destionation_tid'. $i]);
			}

			/*check for duplicate source id for single to mltiple action*/
			$j = $i+1;
			if($i < 4 && ($form_state['values']['source_tid'. $i] == $form_state['values']['source_tid'. $j]) ){
				$delete_expert = false; //prevent from deleting source term 
			}else{
				$delete_expert = true; //delete after merging
			}
			/*get the profile ids that are related to the source term*/
			$profile_ids = db_select('field_data_field_experts', 'e')
				->fields('e', array('entity_id'))
				->condition('entity_type', 'profile2')
				->condition('bundle', 'main')
				->condition('field_experts_tid', $source_term->tid)
				->execute()->fetchAll();
			
			if(empty($profile_ids)){
				if($form_state['values']['destionation_tid'. $i] == 0){
					taxonomy_term_delete($source_term->tid);
					drupal_set_message('تخصص ' . $source_term->name . ' حذف شد. ');	
				}
				continue; //there is no user related to source term so there is nothing to do
			}

			foreach($profile_ids as $profile_id){
				$profile = profile2_load($profile_id->entity_id);
				
				if($form_state['values']['destionation_tid'. $i] == 0){
					foreach($profile->field_experts['und'] as $key=>$field_expert){
						if($field_expert['tid'] == $source_term->tid)
							unset($profile->field_experts['und'][$key]);
					}
					taxonomy_term_delete($source_term->tid);
					drupal_set_message('تخصص ' . $source_term->name . ' حذف شد. ');	
					$message_title = 'تخصص شما حذف شد';
					$message_body = ' تخصص '. $source_term->name . ' شما حذف شد <br>'. 
					'در صورت نادرست بودن آن ، تخصص خود را ویراش کنید و از همین طریق  به ما اطلاع دهید';
				}
				else{ /*merging taxonomy*/
					if(!in_array_r($destionation_term->tid, $profile->field_experts['und'])){ /*check that the experts are unique*/
						array_push($profile->field_experts['und'], ['tid' => $destionation_term->tid]);
					}
					if($delete_expert){
						foreach($profile->field_experts['und'] as $key=>$field_expert){
							if($field_expert['tid'] == $source_term->tid)
								unset($profile->field_experts['und'][$key]);
						}
						taxonomy_term_delete($source_term->tid);
						drupal_set_message('تخصص ' . $source_term->name . ' حذف شد. ');	
					}
					
					$message_title = 'تخصص شما تغییر کرد';
					$message_body = ' تخصص '. $source_term->name .' شما به '. $destionation_term->name .' تغییر کرد <br>'. 
					'در صورت نادرست بودن آن ، تخصص خود را ویراش کنید و از همین طریق  به ما اطلاع دهید';
				}
				profile2_save($profile);

				/*send message to user*/
				if($form_state['values']['message'. $i] == 1){
					$user=user_load($profile->uid);
					
					privatemsg_new_thread(
						array($user),
						$message_title,
						$message_body,
						array('author' => user_load(2), 'format' => 'full_html')
					);
					drupal_set_message('پیام خصوصی برای کاربران ارسال شد.');		
				}
			}
		}
		field_cache_clear();
	} catch (Exception $e) {
		drupal_set_message($e->getMessage() , 'error');
		watchdog('merging experts', $e->getMessage(), WATCHDOG_CRITICAL);
	}
}

function developer()
{
//    $new_hash = hash_hmac("sha256" , "content" , "@Civil808Android@Saze808@" , false);
//    adump($new_hash);
/*
    $node = node_load(887);
    switch ($node->type){
        case 'designteam' :
            $query = db_select("field_data_field_maghalat" , "pedia");
            $query->condition('pedia.field_maghalat_nid' , $node->nid);
            break;
        case 'article' :
            $query = db_select("field_data_field_akhbar" , "pedia");
            $query->condition('pedia.field_akhbar_nid' , $node->nid);
            break;
        case 'publication' :
            $query = db_select("field_data_field_entesharat" , "pedia");
            $query->condition('pedia.field_entesharat_nid' , $node->nid);
            break;
        case 'gallerynew' :
            $query = db_select("field_data_field_porojhe" , "pedia");
            $query->condition('pedia.field_porojhe_nid' , $node->nid);
            break;
        case 'product' :
            $query = db_select("field_data_field_shopproduct" , "pedia");
            $query->condition('pedia.field_shopproduct_nid' , $node->nid);
            break;
        case 'podcast' :
            $query = db_select("field_data_field_podcast808" , "pedia");
            $query->condition('pedia.field_podcast808_nid' , $node->nid);
            break;
        case 'education || college' :
            $query = db_select("field_data_field_edu_college" , "pedia");
            $query->condition('pedia.field_edu_college_nid' , $node->nid);
            break;
        case 'film' :
            $query = db_select("field_data_field_filmmortabet" , "pedia");
            $query->condition('pedia.field_filmmortabet_nid' , $node->nid);
            break;
        default:
            return 0;
    }

    $query->fields('pedia' , array('entity_id'));
    $result = $query->execute()->fetchAll();

    $pedias = array();
    foreach ($result as $row) array_push($pedias , $row->entity_id);

    $query = db_select('field_data_field_experts' , 'pedia_expert');
    $query->join('field_data_field_experts' , 'question_expert' , 'pedia_expert.field_experts_tid = question_expert.field_experts_tid');
    $query->condition('pedia_expert.bundle' , 'architect');
    $query->condition('pedia_expert.entity_id' , $pedias , 'IN');
    $query->condition('question_expert.bundle' , 'questions');
    $query->fields('question_expert' , array('entity_id'));
    $result = $query->execute()->fetchAll();

    $questions_nid= array();
    foreach ($result as $row) array_push($questions_nid , $row->entity_id);

    $query = db_select('node' , 'node');
    $query->fields('node' , array('nid' ,'title'));
    $query->condition('node.nid' , $questions_nid , 'IN');
    $query->orderBy('node.nid' , 'DESC');
    $query->range(0, 3);
    $questions = $query->execute()->fetchAll();

    /*
    foreach($questions as $row) {
        print $row->title;
        print '<br/>';
    }*/


    $value = "دوره هفتم";


    $nodes = array();

    $query = db_select("node" , "node");
    $query->fields("node" , array("nid"));
    $query->condition("node.type" , array("product" , "product_kit") , "IN");
    $query->condition('node.title', '%' . db_like($value) . '%' , 'LIKE');
    $nid1 = $query->execute()->fetchAll();
    foreach ($nid1 as $row) array_push($nodes , $row->nid);

    $query = db_select("field_data_body" , "body");
    $query->fields("body" , array("entity_id"));
    $query->condition("body.bundle" , array("product" , "product_kit") , "IN");
    $query->condition('body.body_value', '%' . db_like($value) . '%' , 'LIKE');
    $nid2 = $query->execute()->fetchAll();
    foreach ($nid2 as $row) array_push($nodes , $row->entity_id);

    $query = db_select("field_data_field_costum_content" , "costum_content");
    $query->fields("costum_content" , array("entity_id"));
    $query->condition("costum_content.bundle" , array("product" , "product_kit") , "IN");
    $query->condition('costum_content.field_costum_content_value', '%' . db_like($value) . '%' , 'LIKE');
    $nid3 = $query->execute()->fetchAll();
    foreach ($nid3 as $row) array_push($nodes , $row->entity_id);


    $query = db_select("field_data_taxonomy_catalog" , "catalog");
    $query->join("taxonomy_term_data" , "taxonomy_term" , "catalog.taxonomy_catalog_tid = taxonomy_term.tid");
    $query->fields("catalog" , array("entity_id"));
    $query->condition("catalog.bundle" , array("product" , "product_kit") , "IN");
    $query->condition('taxonomy_term.name', '%' . db_like($value) . '%' , 'LIKE');
    $nid4 = $query->execute()->fetchAll();
    foreach ($nid4 as $row) array_push($nodes , $row->entity_id);

    $nodes = array_unique($nodes);

    adump(array_values($nodes));
    die();

}