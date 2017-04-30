<?php

function checkInput($decoded){
	$wrongInput = false;
	if (!isset($decoded['puid']) OR !isset($decoded['serial']) OR !isset($decoded['name']) OR !isset($decoded['email']) OR !isset($decoded['phone']) OR !isset($decoded['package']) OR !isset($decoded['ranber'])) die();
	if (strlen($decoded['puid']) < 3 OR strlen($decoded['serial']) < 3 OR strlen($decoded['package']) < 1) $wrongInput = true;
	if (substr($decoded['serial'],0,strlen($decoded['package'])) != $decoded['package']) $wrongInput = true;

	if ($wrongInput) {
		print_output($decoded,4);
		global $conn;
		$conn->close();
		die();
	}
	$decoded['puid'] = string_safer(strtolower(trim($decoded['puid'])));
	$decoded['serial'] = string_safer(strtolower(trim($decoded['serial'])));
	$decoded['name'] = string_safer(strtolower(trim($decoded['name'])));
	$decoded['email'] = string_safer(strtolower(trim($decoded['email'])));
	$decoded['phone'] = string_safer(strtolower(trim($decoded['phone'])));
	$decoded['package'] = string_safer(strtolower(trim($decoded['package'])));
}


/*
##Edit_detail##
edits or adds user details(name,email,phone)

Output:
1: edited (OK)
2: error
*/
function edit_detail($puid,$name,$email,$phone){
	    global $conn,$nowTime;
		
		$sql = "SELECT * FROM tblusers WHERE trim(LOWER(puid)) LIKE '" . $puid . "'";
		$result = $conn->query($sql);

		if ($result->num_rows > 0) {
			// output data of each row
			if ($row = $result->fetch_assoc()) {
				$sql = "UPDATE tblusers SET uname='" . $name . "' , uemail='" . $email . "' , uphone='" . $phone . "' , date_edited='" . $nowTime . "' WHERE id=" . $row["id"];
				if ($conn->query($sql) === TRUE) {
					return 1;
				}
			}
		}
		return 2;
}


/*
##check_puid##
checks puid exists on package or not

Output:
1: puid match on package (OK
2: sync offline user
3: puid doesn't exist (Unknown user)
*/
function check_puid($puid,$package){
	    global $conn,$nowTime;
		
		$sql = "SELECT * FROM tblusers WHERE trim(LOWER(puid)) LIKE '" . $puid . "' AND trim(LOWER(package)) LIKE '" . $package . "'";
		$result = $conn->query($sql);
		
		if ($result->num_rows > 0) {
			//puid exists on DB
			$row = $result->fetch_assoc();
			if (strlen($row["uemail"]) > 0){
				return 1;
			} else {
				//sync offline user
				return 2;
			}
		}
		return 3;
}


/*
##Add_user##
adds puids to serials

Output:
1: edited (OK)
2: maximum serial used_count reached
3: db error
4: Serial Not found
*/
function add_user($puid,$serial,$package){
	    global $conn,$nowTime;
		$sql = "SELECT * FROM tblserials WHERE trim(LOWER(serial)) LIKE '" . $serial . "' AND trim(LOWER(package)) LIKE '" . $package . "'";
		$result = $conn->query($sql);

		if ($result->num_rows > 0) {
			// output data of each row
			if ($row = $result->fetch_assoc()) {
				$used_count = (int)$row["use_counter"];
				if ($used_count < (int)$row["max_use_count"]){
					$used_count++;
					$sql = "UPDATE tblserials SET use_counter='" . $used_count . "' WHERE id=" . $row["id"];
						if ($conn->query($sql) === FALSE) {
							//db error
							return 3;
						}
				} else {
					//maximum serial used_count reached
					return 2;
				}
		
		
				//new user record
				$sql = "INSERT INTO tblusers (puid,serial,package,date_joined) VALUES
				('" . $puid . "',
				'" . $serial . "',
				'" . $package . "',
				'" . $nowTime . "')";

				if ($conn->query($sql) === TRUE) {
					//all OK
					return 1;
				}

			}
			
		} else {
				//Serial Not found
				return 4;
		}
		return 3;
}

/*
##OutPut##
1: OK
2: maximum serial used_count reached
3: db error
4: Serial Not found
5: Use old serial OR new one?
*/
function print_output($arr,$response,$extra = ""){
	echo (encryptAES('{"action":' . $arr['action'] . ',"response":' . $response . ',"puid":"' . $arr['puid'] . '","serial":"' . $arr['serial']. '","name":"' . $arr['name']. '","email":"' . $arr['email'] . '","phone":"' . $arr['phone'] . '","package":"' . $arr['package'] . '","ranber":' . (((int)$arr['ranber'] * 73) - 320)  . ',"extra":"' . $extra . '"}'));
	//echo ('{"action":' . $arr['action'] . ',"response":' . $response . ',"puid":' . $arr['puid'] . ',"serial":' . $arr['serial']. ',"name":' . $arr['name']. ',"email":' . $arr['email']. ',"phone":' . $arr['phone'] . '","package":"' . $arr['package'] . '","ranber":' . (((int)$arr['ranber'] * 73) - 320)  . ',"extra":"' . $extra . '"}');
}
 
 
 
 //other
function addpadding($string, $blocksize = 32)
{
    $len = strlen($string);
    $pad = $blocksize - ($len % $blocksize);
    $string .= str_repeat(chr($pad), $pad);
    return $string;
}

function strippadding($string)
{
    $slast = ord(substr($string, -1));
    $slastc = chr($slast);
    $pcheck = substr($string, -$slast);
    if(preg_match("/$slastc{".$slast."}/", $string)){
        $string = substr($string, 0, strlen($string)-$slast);
        return $string;
    } else {
        return false;
    }
}

function encryptAES($string)
{
	return base64_encode(mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $GLOBALS['multialgoKEY'], addpadding($string), MCRYPT_MODE_CBC, $GLOBALS['multialgoIV']));
}

function decryptAES($string)
{
	$string = base64_decode($string);
	return strippadding(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $GLOBALS['multialgoKEY'], $string, MCRYPT_MODE_CBC, $GLOBALS['multialgoIV']));
}


