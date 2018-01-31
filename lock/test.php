<?php

require_once('config.php');
require_once('functions.php');

    global $conn,$nowTime;
	
	$sql = "SELECT * FROM tblusers WHERE trim(LOWER(puid)) LIKE '4878-992c-9459-6931-eefb-ae19-e238-cc4e' AND trim(LOWER(package)) LIKE 'nb' ";
	$result = $conn->query($sql)->fetch_assoc();

echo '<pre>';
print_r($result);
echo '</pre>';
die();