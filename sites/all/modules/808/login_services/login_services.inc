<?php
    /**
     * 
     *
     * @param string $use
     * @param string $pass
     * @return object
     */
	function checklogin_retrieve($use = null, $pass = null){
		
		$result = user_authenticate($use, $pass);
		
		if($result){
			return $result;
			//echo "true";
		}else{
			return '0';
			//echo "false";
		}
		return false;
		//die("null :S");
		
	}









