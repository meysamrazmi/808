<?php
	include_once('functions.php');
if (is_admin(false)) redirect('index.php');	

 if(isset($_POST['username']) && !is_null($_POST['username']) && isset($_POST['password']) && !is_null($_POST['password'])){
	if(get_setting("user","new") == "new" && $_POST['username'] == 'reset' && get_setting("pass","new") == "new" ){

		set_setting("user",hashc("new"));
		set_setting("pass",hashc("new"));
		
		log_in("admin");
		redirect("index.php");
	} elseif(get_setting("user") == hashc($_POST['username']) && get_setting("pass") == hashc($_POST['password'])){
		log_in("admin");
		redirect("index.php");
	} else {
		// echo '<pre>';
		// print_r(hashc($_POST['username']));
		// echo '<hr>';
		// print_r(get_setting("user"));
		// echo '<hr>';
		// print_r(get_setting("pass"));
		// echo '<hr>';
		
		// print_r(hashc($_POST['password']));
		// echo '<hr>';
		// die();
		reportAttack();
		redirect('http://www.google.com/search?q=reset+password&ie=utf-8&oe=utf-8');
	}

	$conn->close();
	die();
	
} elseif(isset($_GET['admin']) && $_GET['admin'] == '808'){ ?>
<!DOCTYPE html>
<html lang="fa">


<head>
    <meta charset="UTF-8">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    
<title>Log-in</title>
    <link rel="stylesheet" href="styles/login-style.css">
</head>

<body>
	<div id="passbox">
	<form action="login.php" method="POST">
		<label>نام کاربری:</label>
		<br>
		<input type="text" name="username">
		<br>
		<label>پسورد:</label>
		<br>
		<input type="password" name="password">
				<br>
				<h1 id="brand">808</h1>
				<br>
		<input type="submit" value="ورود">
	</form>
	</div>
</body>


</html>

<?php } elseif(isset($_GET['logout'])) {
	
	if ($_GET['logout'] == 12 ){ ?>
		
		<!DOCTYPE html>
<html lang="fa">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">

    
<title>پنل مدیریت قفل 808</title>


    <link rel="stylesheet" href="styles/style.css">
</head>

<body><h1 style="text-align: center;color: rgb(45, 148, 182);font-size: 3em;position: absolute;width: 8em;height: 2em;margin-left: -4em;margin-top: -1em;top: 30%;left: 50%;text-shadow: 0px 0px 6px rgb(49, 144, 197);">شما خارج شدید!</h1></body>
</html>
		
	<?php }
	
} else {
	echo '<html><b>403 access denied</b></html>';
} ?>