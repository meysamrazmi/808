<?php

//DB
$servername = "localhost";
$username = "civilcom_lock";
$password = "TEnjc5Ek";
$dbname = "civilcom_lock";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    echo 3;
}

//constants
$GLOBALS['skey'] = "34Syf@fd#l%43WS4972T658ytkr3dEgV"; //session encrypt key
$GLOBALS['ssalt'] = "9shK3%960FD3fv3*&^@-Z0poK3960327f#v3&fXm6"; //session salt
$GLOBALS['stime'] = 3600; //session time validity
$GLOBALS['page_req'] = null; //requested page header
$GLOBALS['multialgoKEY'] = 'lX5wf897+2dSfE^ks!14z5qq=498JHm5'; // 32 * 8 = 256 bit key for (vb.net|PHP) algo
$GLOBALS['multialgoIV'] = '7Oh952hhe%)y67#cs!9hjv48n9xx7(y)'; // 32 * 8 = 256 bit iv key for (vb.net|PHP) algo


//IMPORTS
require_once('libs/security.php');
require_once('libs/jdf.php');


function string_safer($var) {
	$var = strip_tags($var);
	$var = htmlentities($var);
	$var = stripslashes($var);
	return $var;
}

function get_setting($name,$default=''){
    global $conn;

	$name = string_safer($name);
	$default = string_safer($default);
    $sql = "SELECT vvalue FROM tblconfigs WHERE vname LIKE '" . $name . "'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        // output data of each row
        $row = $result->fetch_assoc();
            return $row["vvalue"];

    } else {
        return $default;
    }
}

function set_setting($name,$value){
    global $conn;

	$name = string_safer($name);
	$value = string_safer($value);
    $sql = "SELECT id FROM tblconfigs WHERE vname LIKE '$name'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        global $conn;
        // output data of each row
        $row = $result->fetch_assoc();

        $sql = "UPDATE tblconfigs SET vvalue='$value' WHERE id=" . $row["id"];
        $conn->query($sql);
        return;
    }

    $sql = "INSERT INTO tblconfigs (vname,vvalue) VALUES ('$name', '$value')";
    $conn->query($sql);

}

function hashc($text){
	return hash("SHA512",$text);
}

$nowTime =  jdate("Y-m-d H:i:s","now",true,'','en');

$conn->query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");