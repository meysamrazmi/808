<?php
	include_once('../config.php');
	
    function redirect($URL)
    {
        header('Location: ' . $URL, 302);
    }

	function is_admin($redirect_login=true){
		if(session_id() == '') {
			session_start();
		}
		if(!isset($_SESSION['udata']) || !isset($_SESSION['tdata'])){
			if($redirect_login) redirect("login.php");
			return false;
			die();
		}
		$security = new Security();
		$session_time = security::decrypt($_SESSION['tdata'], $GLOBALS['skey']);
		$session_data = security::decrypt($_SESSION['udata'], $GLOBALS['skey']);
		
		$decoded = json_decode($session_data);
		if ($decoded->{'time'} != $session_time) return false;
		
		if ($decoded->{'username'} == "admin" && $session_time > time() - $GLOBALS['stime'] && $decoded->{'checks'} == hashc($GLOBALS['ssalt'] . get_client_info() . session_id())){
			session_regenerate_id(true);
			$timevar = time();
			$udata = '{"username":"' . "admin" . '","time":' . $timevar . ',"checks":"' . hashc($GLOBALS['ssalt'] . get_client_info() . session_id()) . '"}';
			$_SESSION['tdata'] = security::encrypt(time(), $GLOBALS['skey']);
			$_SESSION['udata'] = security::encrypt($udata , $GLOBALS['skey']);
			return true;
		}
			

		session_unset();
		session_destroy();
		if($redirect_login) redirect("login.php");
		return false;
	}
	
	function log_in($user){
		if(session_id() == '') {
			session_start();
		}
		$security = new Security();
		$timevar = time();
		$udata = '{"username":"' . $user . '","time":' . $timevar . ',"checks":"' . hashc($GLOBALS['ssalt'] . get_client_info() . session_id()) . '"}';
		$_SESSION['tdata'] = security::encrypt(time(), $GLOBALS['skey']);
		$_SESSION['udata'] = security::encrypt($udata , $GLOBALS['skey']);
	}
	
	function log_out($redirect = true){
		if(session_id() == '') {
			session_start();
		}
		session_unset();
		session_destroy();
		if($redirect) redirect("login.php?logout=12");
		die();
	}
	
	function check_ajax_admin($in_tdata,$in_udata){
			if(strlen($in_udata) < 1 || strlen($in_tdata) < 1) return false;
			$security = new Security();
			$session_time = security::decrypt(base64_decode($in_tdata), $GLOBALS['skey']);
			$session_data = security::decrypt(base64_decode($in_udata), $GLOBALS['skey']);
			
			$decoded = json_decode($session_data);
			if ($decoded->{'time'} != $session_time) return false;
			
			if ($decoded->{'username'} == "admin" && $session_time > time() - $GLOBALS['stime']){
				return true;
			}
			
		return false;
	}
	
	function get_client_info(){
		$result = "";

		if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
			$result = $_SERVER['HTTP_CLIENT_IP'];
		}

		if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
			$result = $result . $_SERVER['HTTP_X_FORWARDED_FOR'];
		}


		$result = $result . $_SERVER['REMOTE_ADDR'];
		$result = $result . $_SERVER['HTTP_USER_AGENT'];
		
		return $result;
	}
	
	function check_req($current_page = ""){
		if(!isset($GLOBALS['page_req']) || is_null($GLOBALS['page_req'])) return false;
		if ($current_page == ""){ 
			return true;
		} else {
			if ($GLOBALS['page_req'] == $current_page) return true;
		}
		return false;
	}
	
	function set_req($current_page){
		$GLOBALS['page_req'] = $current_page;
	}
	
	function reportAttack(){
		ini_set("display_errors", 0);
		if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
			$HTTP_CLIENT_IP = $_SERVER['HTTP_CLIENT_IP'];
		}

		if (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
			$HTTP_X_FORWARDED_FOR = $_SERVER['HTTP_X_FORWARDED_FOR'];
		}

			$REMOTE_ADDR = $_SERVER['REMOTE_ADDR'];

		$txt = "HTTP_CLIENT_IP: " . $HTTP_CLIENT_IP . "\nHTTP_X_FORWARDED_FOR: " . $HTTP_X_FORWARDED_FOR . "\nREMOTE_ADDR: " . $REMOTE_ADDR;
		$myfile = file_put_contents('../logs/att.txt', $txt.PHP_EOL , FILE_APPEND);
		ini_set("display_errors", 1);
	}
	
	function makeOfflineCode($PUID){
		mb_internal_encoding('UTF-8');
		$len = strlen($PUID);
		$encoded_signature = base64_encode(MD5($PUID . ($len * 1023) . $PUID . ($len * ord(substr( $PUID, 0, 1 ))),true));

		$strlen = strlen($encoded_signature);
		$x = 2146;
		for( $i = 0; $i < $strlen; $i++ ) {
			$char = substr( $encoded_signature, $i, 1 );
			$x += pow(((((ord($char) * 256) + 2048 ) / 64) + 1073 ),3);
		}
		$x += -261;
		if ($x < 0) $x = $x * -1;
	return substr($x,2);
}
