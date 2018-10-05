<?php
class c_MySQL {
	//=======================================================
	public $MySQL = false;
	//=======================================================
	public __construct($dbhost, $dblogin, $dbpassword, $dbbase) {
		if(!extension_loaded('mysqli')) {
			$prefix = (PHP_SHLIB_SUFFIX === 'dll') ? 'php_' : '';
			if(!dl($prefix."mysqli.".PHP_SHLIB_SUFFIX)) {
				die("Error in connect to database (001)");				
			}
		}
		
		$this -> MySQL = new mysqli($dbhost, $dblogin, $dbpassword, $dbbase);
		if($this -> MySQL -> connect_errno) {
			$this -> MySQL = false;
			die("Error in connect to database (002)");
		}
		$this -> MySQL -> set_charset("utf8");			
	}	
	//=======================================================
}