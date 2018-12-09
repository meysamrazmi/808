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
			$form['experts'. $i]['destination_tid'. $i] = array(
				'#type' => 'textfield',
				'#title' => t('destination tid'),
				'#description' => t('insert destination tid. if tid is equal to 0 the taxonomy will be deleted.')
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
				if (strlen($form_state['values']['destination_tid'. $i]) == 0) {
					form_set_error('destination_tid'. $i, t('fill the blank field'));
				}
				else if($form_state['values']['source_tid'. $i] == $form_state['values']['destination_tid'. $i]){
					form_set_error('source_tid'. $i, 'تخصص مبدا و مقصد با هم برابراند.');
				}
				else if(empty(taxonomy_term_load($form_state['values']['source_tid'. $i]))){
					form_set_error('source_tid'. $i, 'تخصص مبدا وجود ندارد');
				}
				else if(($form_state['values']['destination_tid'. $i] != 0) && (empty(taxonomy_term_load($form_state['values']['destination_tid'. $i])))){
					form_set_error('destination_tid'. $i, 'تخصص مقصد وجود ندارد');
				}
			}
			else if(strlen($form_state['values']['destination_tid'. $i]) > 0) {
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
			/*skip if source and destination are null*/
		    if(strlen($form_state['values']['source_tid'. $i]) == 0 && strlen($form_state['values']['destination_tid'. $i]) == 0){
				continue; //skip when both are null
			}			
			$source_term = taxonomy_term_load($form_state['values']['source_tid'. $i]);
			if($form_state['values']['destination_tid'. $i] != 0){
				$destination_term = taxonomy_term_load($form_state['values']['destination_tid'. $i]);
			}

			/*check for duplicate source id for single to multiple action*/
			$j = $i+1;
			if($i < 4 && ($form_state['values']['source_tid'. $i] == $form_state['values']['source_tid'. $j]) ){
				$delete_expert = false; //prevent from deleting source term 
			}else{
				$delete_expert = true; //delete after merging
			}

			/*get the uids that are related to the source term*/
			$query = db_select('field_data_field_experts', 'experts');
			$query->fields('experts', array('entity_id'));
            $query->condition('experts.entity_type', 'profile2');
            $query->condition('experts.bundle', 'main');
            $query->condition('experts.field_experts_tid', $source_term->tid);
            $pids = $query->execute()->fetchCol();

			if($form_state['values']['destination_tid'. $i] == 0){
                $message_title = 'تخصص شما حذف شد';
                $message_body = ' تخصص ' . $source_term->name . ' شما حذف شد <br>' . 'در صورت نادرست بودن آن ، تخصص خود را ویراش کنید و از همین طریق  به ما اطلاع دهید';
                taxonomy_term_delete($source_term->tid);
                drupal_set_message('تخصص ' . $source_term->name . ' حذف شد. ');
                foreach ($pids as $pid){
                    $profile = profile2_load($pid);
                    foreach($profile->field_experts['und'] as $key=>$field_expert){
                        if($field_expert['tid'] == $source_term->tid)
                            unset($profile->field_experts['und'][$key]);
                    }
                    profile2_save($profile);
                    if($form_state['values']['message'. $i] == 1) {
                        privatemsg_new_thread(
                            array(user_load($profile->uid)),
                            $message_title,
                            $message_body,
                            array('author' => user_load(2), 'format' => 'full_html')
                        );
                        drupal_set_message('پیام خصوصی برای کاربران ارسال شد.');
                    }
                }
            }
			else{
                $message_title = 'تخصص شما تغییر کرد';
                $message_body = ' تخصص '. $source_term->name .' شما به '. $destination_term->name .' تغییر کرد <br>'.
                    'در صورت نادرست بودن آن ، تخصص خود را ویراش کنید و از همین طریق  به ما اطلاع دهید';
			    foreach ($pids as $pid){
                    $profile = profile2_load($pid);
                    foreach($profile->field_experts['und'] as $key=>$field_expert){
                        if($field_expert['tid'] == $source_term->tid)
                            unset($profile->field_experts['und'][$key]);
                    }
                    if(!in_array_r($destination_term->tid, $profile->field_experts['und'])){
                        array_push($profile->field_experts['und'], ['tid' => $destination_term->tid]);
                    }
                    profile2_save($profile);
                    if($form_state['values']['message'. $i] == 1) {
                        privatemsg_new_thread(
                            array(user_load($profile->uid)),
                            $message_title,
                            $message_body,
                            array('author' => user_load(2), 'format' => 'full_html')
                        );
                        drupal_set_message('پیام خصوصی برای کاربران ارسال شد.');
                    }
                }

			    $query = db_select("field_data_field_experts" , "node");
			    $query->fields("node" , array("entity_id"));
                $query->condition('node.entity_type', 'node');
                $query->condition('node.field_experts_tid', $source_term->tid);
                $nids = $query->execute()->fetchCol();
                foreach ($nids as $nid){
                    $node = node_load($nid);
                    if(!in_array_r($destination_term->tid, $node->field_experts['und'])){
                        array_push($node->field_experts['und'], ['tid' => $destination_term->tid]);
                        node_save($node);
                    }
                }

                if($delete_expert){
                    taxonomy_term_delete($source_term->tid);
                    drupal_set_message('تخصص ' . $source_term->name . ' حذف شد. ');
                }
            }
		}
		field_cache_clear();
	} catch (Exception $e) {
		drupal_set_message($e->getMessage() , 'error');
		watchdog('merging experts', $e->getMessage(), WATCHDOG_CRITICAL);
	}
}

function discount_configuration_form($from, &$form_state){
    try {
        $kinds = array("extra_charge" , "article_software" , "article_store" , "publication" , "education" , "vip");
        foreach($kinds as $kind){
            $default = variable_get($kind . "_discount" , array());
            $form[$kind] = array(
                '#type' => 'fieldset',
                '#title' => t($kind),
            );
            $form[$kind]['active_' . $kind] = array(
                '#type' => 'checkbox',
                '#title' => t('فعال'),
                '#default_value' => (!empty($default["active"]))? $default["active"] : '',
            );
            $form[$kind]['amount_' . $kind] = array(
                '#type' => 'textfield',
                '#title' => t('میزان تخفیف'),
                '#description' => t('میزان تخفیف بر اساس درصد. فقط عدد وارد کنید.'),
                '#default_value' => (!empty($default["amount"]))? $default["amount"] : '',
            );
            $form[$kind]['place_' . $kind] = array(
                '#type' => 'checkboxes',
                '#options' => drupal_map_assoc(array(t('site'), t('app'))),
                '#title' => t('این تخفیف در کجا استفاده شود.'),
                '#default_value' => (!empty($default['place']))? array_keys($default['place']) : array(),
            );
            $form[$kind]['message_' . $kind] = array(
                '#type' => 'textfield',
                '#title' => t('دلیل اعمال تخفیف'),
                '#description' => t('این پیام به کاربر نمایش داده میشود.'),
                '#default_value' => (!empty($default["message"]))? $default["message"] : '',
            );
            if($kind == "vip"){
                $form[$kind]['contents_' . $kind] = array(
                    '#type' => 'checkboxes',
                    '#options' => drupal_map_assoc(array(t('article_software'), t('article_store'), t('publication'), t('education') , t('collage') , t('package808'))),
                    '#title' => t('این تخفیف در کدام محتوا اعمال شود.'),
                    '#default_value' => (!empty($default['contents']))? array_keys($default['contents']) : array(),
                );
            }
        }

        $form['submit'] = array(
            '#type' => 'submit',
            '#value' => t('Save')
        );
        return $form;
    } catch (Exception $e) {
        echo 'Caught exception: ',  $e->getMessage(), "\n";
    }
}

function discount_configuration_form_validate($from, &$form_state){
    try{
        $kinds = array("extra_charge" , "article_software" , "article_store" , "publication" , "education" , "vip");
        foreach($kinds as $kind){
            if($form_state['values']['active_'. $kind] == 1) {
                if(empty($form_state['values']['amount_'. $kind]) || strlen($form_state['values']['amount_'. $kind]) == 0)
                    form_set_error('amount_'. $kind, t('مقدار تخفیف اجباری است.'));

                elseif(!preg_match("/^[0-9]+$/", $form_state['values']['amount_'. $kind]))
                    form_set_error('amount_'. $kind, t('برای میزان تخفیف فقط از عدد استفاده شود.'));

                $places = false;
                foreach ($form_state['values']['place_'. $kind] as $place)
                {
                    if(strcmp($place , 0) != 0) $places = true;
                }
                if(!$places)
                    form_set_error('place_'. $kind, t('حداقل یک مکان باید انتخاب شود.'));

                if(empty($form_state['values']['message_'. $kind]) || strlen($form_state['values']['message_'. $kind]) == 0)
                    form_set_error('message_'. $kind, t('پیام تخفیف اجباری است.'));

                if(strcmp($kind , "vip") == 0){
                    $places = false;
                    foreach ($form_state['values']['contents_'. $kind] as $place)
                    {
                        if(strcmp($place , 0) != 0) $places = true;
                    }
                    if(!$places)
                        form_set_error('contents_'. $kind, t('حداقل یک محتوا برای تخفیف vip باید انتخاب شود.'));
                }
            }
        }
    } catch (Exception $e) {
        drupal_set_message($e->getMessage() , 'error');
        watchdog('Submit configuration failed', $e->getMessage(), WATCHDOG_CRITICAL);
    }

}

function discount_configuration_form_submit($from, &$form_state){
    try{
        $kinds = array("extra_charge" , "article_software" , "article_store" , "publication" , "education" , "vip");
        foreach($kinds as $kind){
            $var = array();
            $var["active"] = $form_state['values']['active_' . $kind];
            $var["amount"] = $form_state['values']['amount_' . $kind];
            foreach($form_state['values']['place_' . $kind] as $place)
                if(strcmp($place , 0) != 0) $var["place"][$place] = 1;

            $var["message"] = $form_state['values']['message_' . $kind];
            if($kind == "vip")
                foreach($form_state['values']['contents_' . $kind] as $place)
                    if(strcmp($place , 0) != 0) $var["contents"][$place] = 1;
            variable_set($kind . '_discount', $var);
        }
        drupal_set_message('تغییرات با موفقیت ذخیره شد.');
    } catch (Exception $e) {
        drupal_set_message($e->getMessage() , 'error');
        watchdog('Submit configuration failed', $e->getMessage(), WATCHDOG_CRITICAL);
    }
}

function developer()
{
    /*
    $query = db_select("field_data_field_tag_is_not_expert" , "not_expert");
    $query->fields("not_expert" , array("entity_id"));
    $not_expert = $query->execute()->fetchCol();

    $query = db_select("taxonomy_term_data" , "term");
    $query->fields("term" , array("tid"));
    $query->condition("term.vid" , 28);
    $query->condition("term.tid" , $not_expert , "NOT IN");
    $terms = $query->execute()->fetchCol();
    adump($terms);
    foreach ($terms as $term){
        $query = db_select("field_data_field_tag_is_not_expert" , "not_expert");
        $query->fields("not_expert" , array("entity_id"));
        $query->condition("not_expert.entity_id" , $term);
        $result = $query->execute()->fetchCol();
        if(empty($result)){
            db_insert("field_data_field_tag_is_not_expert")->fields(
                array(
                    "entity_type" => "taxonomy_term",
                    "bundle" => "expert",
                    "deleted" => 0,
                    "entity_id" => $term,
                    "revision_id" => $term,
                    "language" => "und",
                    "delta" => 0,
                    "field_tag_is_not_expert_value" => 0,
                )
            )->execute();

            db_insert("field_revision_field_tag_is_not_expert")->fields(
                array(
                    "entity_type" => "taxonomy_term",
                    "bundle" => "expert",
                    "deleted" => 0,
                    "entity_id" => $term,
                    "revision_id" => $term,
                    "language" => "und",
                    "delta" => 0,
                    "field_tag_is_not_expert_value" => 0,
                )
            )->execute();
        }
    }
    */
    /*
    $query = db_select("field_data_field_experts" , "field_experts")->distinct();
    $query->fields("field_experts" , array("entity_id"))
        ->condition("field_experts.entity_type" , "node")->condition("field_experts.bundle" , "architect");
    $pedias = $query->execute()->fetchCol();
    foreach ($pedias as $pedia){
        $nids = array();
        $query = db_select("field_data_field_maghalat", "pedia");
        $query->fields("pedia" , array("field_maghalat_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_akhbar", "pedia");
        $query->fields("pedia" , array("field_akhbar_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_entesharat", "pedia");
        $query->fields("pedia" , array("field_entesharat_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_porojhe", "pedia");
        $query->fields("pedia" , array("field_porojhe_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_shopproduct", "pedia");
        $query->fields("pedia" , array("field_shopproduct_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_podcast808", "pedia");
        $query->fields("pedia" , array("field_podcast808_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_edu_college", "pedia");
        $query->fields("pedia" , array("field_edu_college_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $query = db_select("field_data_field_filmmortabet", "pedia");
        $query->fields("pedia" , array("field_filmmortabet_nid"));
        $query->condition("pedia.entity_id" , $pedia);
        $nids = array_merge($nids , $query->execute()->fetchCol());

        $nids = array_unique($nids);

        $query = db_select("field_data_field_experts" , "field_experts");
        $query->fields("field_experts" , array("field_experts_tid"))
            ->condition("field_experts.entity_type" , "node")->condition("field_experts.bundle" , "architect")->condition("field_experts.entity_id" , $pedia);
        $tids = $query->execute()->fetchCol();

        foreach ($nids as $nid){
            $node = node_load($nid);
            if(!$node) continue;

            foreach ($tids as $tid){
                $query = db_select("field_data_field_experts" , "experts");
                $query->fields("experts" , array("delta" , "field_experts_tid"));
                $query->condition("experts.entity_type" , "node")
                    ->condition("experts.bundle" , $node->type)
                    ->condition("experts.entity_id" , $node->nid);
                $query = $query->execute()->fetchAll();
                $delta = 0;
                $experts = array();
                foreach ($query as $value){
                    array_push($experts , $value->field_experts_tid);
                    if($value->delta > $delta) $delta = $value->delta;
                }
                if(!empty($experts)) $delta = $delta + 1;

                if(!in_array($tid , $experts)){
                    db_insert("field_data_field_experts")
                        ->fields(array(
                            "entity_type" => "node",
                            "bundle" => $node->type,
                            "deleted" => 0,
                            "entity_id" => $node->nid,
                            "revision_id" => $node->nid,
                            "language" => "und",
                            "delta" => $delta,
                            "field_experts_tid" => $tid
                        ))
                        ->execute();
                    db_insert("field_revision_field_experts")
                        ->fields(array(
                            "entity_type" => "node",
                            "bundle" => $node->type,
                            "deleted" => 0,
                            "entity_id" => $node->nid,
                            "revision_id" => $node->nid,
                            "language" => "und",
                            "delta" => $delta,
                            "field_experts_tid" => $tid
                        ))
                        ->execute();
                }
            }
        }

    }
    adump($pedias);
    */
    /*
    $query = db_select("uc_product_stock" , "stock")->distinct();
    $query->join("node" , "node" , "node.nid = stock.nid and node.status = '1' ");
    $query->fields("stock" , array("nid"));
    $query->condition("node.type" , array("product" , "product_kit") , "IN");
    $stocks = $query->execute()->fetchCol();

    $query = db_select("uc_products" , "product");
    $query->join("node" , "node" , "node.nid = product.nid and node.status = '1' ");
    $query->fields("product" , array("nid" , "model"));
    $query->condition("node.type" , array("product" , "product_kit") , "IN");
    $query->condition("product.nid" , $stocks , "NOT IN");
    $witout_stocks = $query->execute()->fetchAll();
    adump($witout_stocks);
    foreach ($witout_stocks as $row){
        $query = db_insert('uc_product_stock')->fields(
            array(
                "sku" => $row->model,
                "nid" => $row->nid,
                "active" => 0,
                "stock" => 0,
                "threshold" => 0
            )
        )->execute();
    }
    adump("ok");
    */
    die();
}