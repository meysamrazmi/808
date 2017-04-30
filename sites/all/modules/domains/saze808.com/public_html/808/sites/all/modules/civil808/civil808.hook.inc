<?php
define('CIVIL_SHOP_BASE', 'http://saze808.com/fmage/');
/**
 * Implements hook_form_alter().
 */
function civil808_form_alter(&$form, &$form_state, $form_id) {
	switch ($form_id) {
		case 'user_register_form':
			$form['#submit'] = array('civil808_user_form_alter_submit','user_register_submit');
			//print_r($form['#submit']);
			break;
		
		default:
			# code...
			break;
	}
}
/**
 * Implements hook_user_form_alter_submit().
 */
function civil808_user_form_alter_submit($form, &$form_state) {
	variable_set('civil808_is_register', true);

	$arr = array(
		'email' => $form_state['values']['mail'],
		'p' => md5($form_state['values']['pass']),
		'name' => $form_state['values']['profile_main']['field_full_name']['und'][0]['value'],
		);
	user_register_submit($form, $form_state);
	profile2_form_submit_handler($form, $form_state);
	// die;
	variable_set('civil808_is_register', false);
	drupal_goto(CIVIL_SHOP_BASE."civil/mega/re?data="._encode_data($arr));
	// $form_state['redirect'] = CIVIL_SHOP_BASE."civil/mega/re?data="._encode_data($arr);
}


/**
 * Implements hook_user_logout().
 */
function civil808_user_logout($account) {
	if (!isset($_GET['xx'])) {
		$data = "ssid=".base64_encode($account->mail);
		drupal_goto(CIVIL_SHOP_BASE."civil/mega/lo?".$data);
	}
}

/**
 * Implements hook_user_login().
 */
function civil808_user_login(&$edit, $account) {
	$data = "ssid=".base64_encode($account->mail);
	if(!variable_get('civil808_is_register', false))drupal_goto(CIVIL_SHOP_BASE."civil/mega/li?".$data);
}






/*** function internal ****/

function _decode_data($data) {
	$serial = base64_decode($data);
	$arr = unserialize($serial);
	return $arr;
}
function _encode_data($data) {
	return base64_encode(serialize($data));
}