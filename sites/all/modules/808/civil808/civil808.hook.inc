<?php

define('CIVIL_SHOP_BASE', 'http://shop.civil808.com/');


/*** function internal ****/

function _decode_data($data) {
	$serial = base64_decode($data);
	$arr = unserialize($serial);
	return $arr;
}
function _encode_data($data) {
	return base64_encode(serialize($data));
}