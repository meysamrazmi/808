<?php 

include_once("functions.php");
if(!is_admin()) redirect('login.php');


if(isset($_GET['action'])){
	switch($_GET['action']){
		case 'logout':
			log_out();
			break;
		case 'puids':
			set_req('puids');
			include_once("header.php");
			include_once("body-puids.php");
			include_once("footer.php");
			break;
		case 'serials':
			set_req('serials');
			include_once("header.php");
			include_once("body-serials.php");
			include_once("footer.php");
			break;
		case 'add-serials':
			set_req('add-serials');
			include_once("header.php");
			include_once("body-add-serials.php");
			include_once("footer.php");
			break;
		case 'settings':
			set_req('settings');
			include_once("header.php");
			include_once("body-settings.php");
			include_once("footer.php");
			break;
		case 'offline-activate':
			set_req('offline-activate');
			include_once("header.php");
			include_once("body-offline-activate.php");
			include_once("footer.php");
			break;
		case 'export-puids':
			set_req('export-puids');
			include_once("header.php");
			include_once("body-export-puids.php");
			include_once("footer.php");
			break;
		case 'packages':
			set_req('packages');
			include_once("header.php");
			include_once("body-packages.php");
			include_once("footer.php");
			break;
		default:
			set_req('puids');
			include_once("header.php");
			include_once("body-puids.php");
			include_once("footer.php");
			break;
	}

} elseif(isset($_POST['doback'])) {
	if (isset($_POST['udata']) && isset($_POST['tdata'])){
		if(!check_ajax_admin($_POST['tdata'],$_POST['udata'])) die();
	} else {
		if(!is_admin()){
			redirect('login.php');
			die();
		} 
	}

	global $conn,$nowTime;		
	switch ($_POST['doback']){
		case 'deleteu':
			if(isset($_POST['id']) && is_numeric($_POST['id'])){
				$id = string_safer($_POST['id']);
				$sql = "DELETE FROM tblusers WHERE id=" . $id;
				if ($conn->query($sql) === TRUE) {
					echo 1;
				}
			}
		break;
		case 'deletes':
			if(isset($_POST['id']) && is_numeric($_POST['id'])){
				$id = string_safer($_POST['id']);
				$sql = "DELETE FROM tblserials WHERE id=" . $id;
				if ($conn->query($sql) === TRUE) {
					echo 1;
				}
			}
		break;
		case 'deletep':
			if(isset($_POST['id']) && is_numeric($_POST['id'])){
				$id = string_safer($_POST['id']);
				
				$sql = "SELECT package FROM tblpackages WHERE id=" . $id;
				$result = $conn->query($sql);
				$row = $result->fetch_assoc();
				$package = $row['package'];
				
				$sql2 = "DELETE FROM tblpackages WHERE id=" . $id;
				if ($conn->query($sql2) === TRUE) {
					$sql3 = "DELETE FROM tblserials WHERE package LIKE '" . $package . "'";
					$conn->query($sql3);
					echo 1;
				}
			}
		break;
		case 'editu':
			if(isset($_POST['id']) && is_numeric($_POST['id'])){
				if(!isset($_POST['name'])) die();
				if(!isset($_POST['phone'])) die();
				if(!isset($_POST['email'])) die();
				if(!isset($_POST['puid'])) die();
				if(!isset($_POST['serial'])) die();
				$name = string_safer($_POST['name']);
				$phone = string_safer($_POST['phone']);
				$email = string_safer($_POST['email']);
				$puid = string_safer($_POST['puid']);
				$serial = string_safer($_POST['serial']);
				$id = string_safer($_POST['id']);
				
				$sql = "UPDATE tblusers SET uname='" . $name . "' , uemail='" . $email . "' , uphone='" . $phone . "' , puid='" . trim(strtolower($puid)) . "' , serial='" . trim(strtolower($serial)) . "' , date_edited='" . $nowTime . "' WHERE id=" . $id;
				if ($conn->query($sql) === TRUE) {
					echo 1;
				}
			}
		break;
		case 'editp':
			if(isset($_POST['id']) && is_numeric($_POST['id']) && isset($_POST['packageDesc']) && isset($_POST['packageCode']) && strlen($_POST['packageCode']) > 0){
			$PackageDesc = string_safer(strtolower(trim($_POST['packageDesc'])));
				$PackageCode = string_safer(strtolower(trim($_POST['packageCode'])));
				$id = string_safer(strtolower(trim($_POST['id'])));
		
				$sql = "UPDATE tblpackages SET package='" . $PackageCode . "' , description='" . $PackageDesc . "' WHERE id=" . $id;
				if ($conn->query($sql) === TRUE) {
					echo 1;
				}
			}
		break;
		case 'edits':
			if(isset($_POST['id']) && is_numeric($_POST['id'])){
				if(!isset($_POST['serial'])) die();
				if(!isset($_POST['max-user-count'])) die();

				$max_user_count = string_safer($_POST['max-user-count']);
				$serial = string_safer($_POST['serial']);
				$description = string_safer($_POST['description']);
				$user_counter = string_safer($_POST['user_counter']);
				$id = string_safer($_POST['id']);
				
				$sql = "SELECT max_use_count FROM tblserials WHERE id='" . $id . "'";
				$result = $conn->query($sql);
				$row = $result->fetch_assoc();
				
				if ($row['max_use_count'] > $max_user_count){
					echo 0;
					break;
				}

				$sql = "UPDATE tblserials SET max_use_count='" . $max_user_count . "', serial='" . trim(strtolower($serial)) . "', description='" . trim($description) . "', use_counter='" . trim($user_counter) . "' WHERE id=" . $id;
				if ($conn->query($sql) === TRUE) {
					echo 1;
				}
			}
		break;
		case 'addserial':
			if(!isset($_POST['serial1']) && !isset($_POST['capacity1']) && strlen($_POST['serial1']) <= 0 && !is_numeric($_POST['capacity1']) && (int)$_POST['capacity1'] <= 0 && !isset($_POST['package1']) && strlen($_POST['package1']) <= 0) die();
			$added = false;
			$serial = string_safer(strtolower(trim($_POST['serial1'])));
			$package = string_safer(strtolower(trim($_POST['package1'])));
			$capacity = string_safer($_POST['capacity1']);
			
				if (substr($serial,0,strlen($package)) == $package) {
					$sql = "SELECT id FROM tblserials WHERE trim(LOWER(serial))  LIKE '" . $serial . "'";
					$result = $conn->query($sql);
					$row = $result->fetch_assoc();
					if (is_null($row['id']) || !is_numeric($row['id'])){
						$sql = "INSERT INTO tblserials (package, serial, max_use_count, use_counter) VALUES ('" . $package . "', '" . $serial . "', '" . $capacity . "', '0')";
						if ($conn->query($sql) === TRUE){
							echo 1;
							die();
						}
					} else {
						//serial exist
						echo 2;
						die();
					}
				}
				echo 0;
		break;
		case 'getActivator':
			if (isset($_POST['puid'])){
				echo makeOfflineCode($_POST['puid']);
			}
		break;
		case 'addOfflineUser':
			if(!isset($_POST['puid']) || !isset($_POST['serial']) || !isset($_POST['package'])) die();
			$puid = string_safer(strtolower(trim($_POST['puid'])));
			$serial = string_safer(strtolower(trim($_POST['serial'])));
			$package = string_safer(strtolower(trim($_POST['package'])));
			
			if (substr($serial,0,strlen($package)) != $package) {
				echo 0;
				die();
			}
		
			$sql = "SELECT max_use_count,use_counter,id FROM tblserials WHERE trim(LOWER(serial))  LIKE '" . $serial . "'";
			$result = $conn->query($sql);
			$row = $result->fetch_assoc();
			
			$use_counter = -1;
			$capacity = -1;

			if (!is_null($row['use_counter']) && is_numeric($row['id'])){
				$use_counter = $row['use_counter'];
				$capacity = $row['max_use_count'];
			} else {
				echo 0;
				break;
			}
			if ($use_counter == -1 || $capacity == -1) {
				echo 0;
				break;
			}
			
			
			$use_counter++;
			if ($capacity < $use_counter){
				echo 0;
				break;
			}
			$sql2 = "UPDATE tblserials SET use_counter='" . $use_counter . "' WHERE id=" . $row['id'];

			$sql = "INSERT INTO tblusers (puid,serial,package,date_joined) VALUES
			('" . $puid . "',
			'" . $serial . "',
			'" . $package . "',
			'" . $nowTime . "')";
			
			
			if ($conn->query($sql2) === TRUE && $conn->query($sql) === TRUE) {
				echo 1;
			}
		break;
		case 'makeBulkSerials':
			if(!isset($_POST['count']) || !is_numeric($_POST['count']) || !isset($_POST['capacity']) || !is_numeric($_POST['capacity']) || !isset($_POST['format']) || !isset($_POST['package']) || strlen($_POST['package']) <= 0) die();

			$count = (int)string_safer(strtolower(trim($_POST['count'])));
			$capacity = (int)string_safer(strtolower(trim($_POST['capacity'])));
			$format = string_safer(strtolower(trim($_POST['format'])));
			$package = string_safer(strtolower(trim($_POST['package'])));
			
			if (substr($format,0,strlen($package)) != $package) {
				echo 1;
				die();
			}
			
			$sql = "SELECT id FROM tblpackages WHERE trim(LOWER(package))  LIKE '" . $package . "'";
			$result = $conn->query($sql);
			if ($result->num_rows > 0) {
				include_once("../libs/serialMaker.php");
				$bulkStr = array();
				for($i = 1;$i<=$count;$i++){
					$temparr = array('serial' => Serial::customFormat($format),'capacity' => $capacity, 'package' => $package);
					array_push($bulkStr, $temparr);
				}
				echo json_encode($bulkStr);
			} else {
				echo 0;
			}
		break;
		
		case 'getExcel':
			if(!isset($_POST['json']))die();

			$json = json_decode($_POST['json'],true);
			
			header("Content-Type: application/vnd.ms-excel");
			
			echo 'Serial' . "\t" . 'users capacity' . "\n";
			for($i= 0; $i < sizeof($json);$i++){
				echo $json[$i]['serial'] . "\t" . $json[$i]['capacity'] . "\n" ;
			}
			header("Content-disposition: attachment; filename=spreadsheet.xls");
			die();
			
		break;
		case 'getExcelAllPuids':
			$sql = "SELECT * FROM tblusers";
			$result = $conn->query($sql);
			
			header("Content-Type: application/vnd.ms-excel");
			echo 'ID' . "\t" . 'Package' . "\t" .'Serial' . "\t" . 'PUID' . "\t" .  'Name' . "\t" .'Email' . "\t" .'Phone' . "\t" . 'Date joined' . "\n";

			if ($result->num_rows > 0) {
				while ($row = $result->fetch_assoc()){
					echo $row["id"] . "\t" . $row["package"] . "\t" . $row["serial"] . "\t" . $row["puid"] . "\t" . $row["uname"] . "\t" . $row["uemail"] . "\t" . $row["uphone"] . "\t" . $row["date_joined"] . "\n" ;
				}
			}

			header("Content-disposition: attachment; filename=spreadsheet.xls");
		break;
		case 'bulkInsert':
			if(!isset($_POST['json']))die();
			$json = json_decode($_POST['json'],true);
			for($i= 0; $i < sizeof($json);$i++){
				$sql = "INSERT INTO tblserials (package, serial, max_use_count, use_counter) VALUES ('" . string_safer(strtolower(trim($json[$i]['package']))) . "', '" . string_safer(strtolower(trim($json[$i]['serial']))) . "', '" . string_safer($json[$i]['capacity']) . "', '0')";
				if ($conn->query($sql) === False){
					echo 0;
					die();
				} 
			}
			echo 1;
		break;
		case 'makePackage':
			if(!isset($_POST['PackageCode']) || !isset($_POST['PackageDesc'])) die();
			$PackageDesc = string_safer(strtolower(trim($_POST['PackageDesc'])));
			$PackageCode = string_safer(strtolower(trim($_POST['PackageCode'])));
		
			$sql = "SELECT id FROM tblpackages WHERE trim(LOWER(package))  LIKE '" . $PackageCode . "'";
			$result = $conn->query($sql);
			if ($result->num_rows > 0) {
				echo 2;
				die();
			} else {
				
			}
			$sql = "INSERT INTO tblpackages (package, description) VALUES ('" . $PackageCode . "', '" . $PackageDesc . "')";
			if ($conn->query($sql) === False){
				echo 0;
				die();
			} 
			echo 1;
		break;
		
		case 'addserialbase64':

		break;
	}
	
	
	$conn->close();
	
} else {
			set_req('puids');
			include_once("header.php");
			include_once("body-puids.php");
			include_once("footer.php");
			break;
}

