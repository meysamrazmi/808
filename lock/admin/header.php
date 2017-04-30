<?php
 if(check_req() == false) die(); ?>
 
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



<body>
<nav>

    <div id="haed-nav">
        <div id="nav-right">
            <div class="nav-item nav-right-item" id="nav-right-item-1">

<a href="index.php?action=puids">مدیریت کاربران</a>
            </div>
		    <div class="nav-item nav-right-item" id="nav-right-item-2">

<a href="index.php?action=packages">مدیریت پکیج</a>
            </div>
            <div class="nav-item nav-right-item" id="nav-right-item-3">

<a href="index.php?action=serials">مدیریت سریال</a>
            </div>
            <div class="nav-item nav-right-item" id="nav-right-item-4">

<a href="index.php?action=add-serials">افزودن سریال</a>
            </div>
			<div class="nav-item nav-right-item" id="nav-right-item-5">

<a href="index.php?action=offline-activate">فعالسازی آفلاین</a>
            </div>
			<div class="nav-item nav-right-item" id="nav-right-item-6">
<a href="index.php?action=export-puids">خروجی DB</a>
            </div>
        </div>
        <div id="nav-left">
            <div class="nav-item nav-left-item">
<a href="index.php?action=logout">خروج</a>
            </div>
            <div class="nav-item nav-left-item">
<a href="index.php?action=settings">تنظیمات</a>

            </div>
        </div>

    </div>


</nav>

<form style="display: none;">
<input type="hidden" id="tdata" value="<?php echo base64_encode($_SESSION['tdata']); ?>">
<input type="hidden" id="udata" value="<?php echo base64_encode($_SESSION['udata']); ?>">
</form>





