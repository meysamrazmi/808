<?php
$file = "log.txt";

if (!isset($_POST['hash'])){
	file_put_contents($file, "nocontent\n", FILE_APPEND | LOCK_EX);
    die();
}

require_once('config.php');
require_once('functions.php');
global $conn,$nowTime;
	
//$decoded = json_decode('{"action":1,"puid":"9676-f71e-c917-1c6b-32d0-3121-ed60-0231","serial":"si1-shayan","name":"ییییییییی","email":"rturt@wey.com","phone":"55555555555","package":"si1","ranber":54651}',true);

$decoded = json_decode(decryptAES(rawurldecode($_POST['hash'])),true);

$file_content = "---------------------------------------------\n ورودی \n". $nowTime ."\n". print_r($decoded, true) . "\n";
file_put_contents($file, $file_content, FILE_APPEND | LOCK_EX);

checkInput($decoded);
$check_result = check_puid($decoded['puid'],$decoded['package']);

switch((int)$decoded['action']){
	case 1:
		if ($check_result == 1){//everything is ok
			print_output($decoded,1);
			break;
		}
		if ($check_result == 2){//sync offline user
			$is_ok = edit_detail($decoded['puid'],$decoded['name'],$decoded['email'],$decoded['phone']);
			if ($is_ok == 1) {
				print_output($decoded,1);
				break;
			}
			print_output($decoded,3);
			break;
		}
		if ($check_result == 3){//new user
			$is_ok = add_user($decoded['puid'],$decoded['serial'],$decoded['package']);
			if ($is_ok == 1){
				$is_ok = edit_detail($decoded['puid'],$decoded['name'],$decoded['email'],$decoded['phone']);
				if ($is_ok == 1) {
					print_output($decoded,1);
					break;
				}
			}else{
				print_output($decoded,$is_ok);
				break;
			}
		}
		print_output($decoded,3);
		break;
		
	case 2:
		//Add new user without details
		$is_ok = add_user($decoded['puid'],$decoded['serial'],$decoded['package']);
		if ($is_ok == 1) {
			print_output($decoded,1);
		} else {
			print_output($decoded,2);
		}
		break;	
		
	case 3:
		//Add detail of new online user  *OR*   Edit user
		if ($check_result == 1){
			$is_ok = edit_detail($decoded['puid'],$decoded['name'],$decoded['email'],$decoded['phone']);
			if ($is_ok == 1) {
				print_output($decoded,1);
				break;
			}
		}
		print_output($decoded,3);
		break;
}


$conn->close();
die();
?>