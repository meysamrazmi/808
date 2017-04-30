<?php

if (!isset($_POST['hash'])){
    die();
}

require_once('config.php');
require_once('functions.php');
global $conn,$nowTime;
	


//$decoded = json_decode('{"action":1,"puid":"9676-f71e-c917-1c6b-32d0-3121-ed60-0231","serial":"si1-shayan","name":"ییییییییی","email":"rturt@wey.com","phone":"55555555555","package":"si1","ranber":54651}',true);

$decoded = json_decode(decryptAES(rawurldecode($_POST['hash'])),true);

checkInput($decoded);
$check_result = check_puid($decoded['puid'],$decoded['package']);

switch((int)$decoded['action']){
	case 1:
		//Add new user with details
		if ($check_result == 2){
			//sync offline user
			$is_ok = edit_detail($decoded['puid'],$decoded['name'],$decoded['email'],$decoded['phone']);
			if ($is_ok == 1) {
				print_output($decoded,1);
				break;
			}
			print_output($decoded,3);
			break;
		}
		if ($check_result == 1){
			//new os or installing
			print_output($decoded,1);
			break;
		}


		//new user
		if ($check_result == 3){
			$is_ok = add_user($decoded['puid'],$decoded['serial'],$decoded['package']);
			if ($is_ok == 1){
				$is_ok = edit_detail($decoded['puid'],$decoded['name'],$decoded['email'],$decoded['phone']);
				if ($is_ok == 1) {
					print_output($decoded,1);
					break;
				}
			} elseif ($is_ok == 2){
				print_output($decoded,2);
				break;
			} elseif ($is_ok == 4){
				print_output($decoded,4);
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