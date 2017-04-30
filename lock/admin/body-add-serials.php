<?php
 if(check_req('add-serials') == false) die();  


if (isset($_GET['prompt'])){ 

?>
 <div class="agreement-message" style="display: block;">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
	<?php 
	if($_GET['prompt'] == 'ok'){
		echo '<p>با موفقیت افزوده شد</p>';
	} else {
        echo '<p>خطا در افزودن سریال!</p>';
	}
	?>
		
        <input type="button" id="agreement-submit" onclick="$('.agreement-message').hide()" value="باشه">
    </form>
    <br>
</div>

<?php } ?>

 <div class="agreement-message2" style="display: none;">
    <p class="pointer" id="close-agreement2" onclick="$('.agreement-message2').hide()">&nbsp;&nbsp;X</p>
    <form id="agree-form2">
		<p id="msgp"></p>
        <input type="button" id="agreement-submit2" onclick="$('.agreement-message2').hide()" value="باشه">
    </form>
    <br>
</div>
 
<div class="container">

<div class="column text-col flow-opposite">





    <div class="post-row">

		<h2 class="title-h2">افزودن جمعی سریال:</h2>
		<div class="search-blocks">
		
			<h4>مرحله اول:</h4>
			<div class="search-blocks">
				<form id="auto-lvl-1">
					<label>پکیج:</label><input type="text" id="bulk-package"></input>
					<label>تعداد سریال ها:</label><input type="number" id="auto-count" min="1"></input>
					<label>ظرفیت سریال ها:</label><input type="number" id="auto-capacity" min="1"></input>
					<label>فرمت:</label><input type="text" id="bulk-serial-format"></input>
					<label>نمونه فرمت:</label> 
					<p>****-**6*-****-N56<br>*********-Serial</p>
					<input type="button" onclick="makeBulkSerialsJson()" value="پیش نمایش">
				</form>
			</div>
			
			<h4>مرحله دوم:</h4>
			<div class="search-blocks">
				<form id="auto-lvl-2" target="_blank" action="index.php" method="POST">
					<label>کد تولید شده:</label><textarea id="auto-json" name="json" disabled></textarea>
					<input type="submit" id="btn-get-excel" onclick="" value="دریافت فایل Excel" disabled>
					<input type="button" id="btn-insert-json" onclick="insertBulkSerialsJson()" value="افزودن به دیتابیس" disabled>
					<input type="hidden" name="doback" value="getExcel">
				</form disabled>
			</div>
		</div>
		
		<h2 class="title-h2">افزودن تکی سریال:</h2>
		<div class="search-blocks">
			<form action="index.php" method="POST">
				<div class="add-block-right">
				<div class="add-block-right"><label>سریال:</label><input type="text" class="ltr" id="serial1"></div> <div class="add-block-left"><label>پکیج:</label><input type="text" class="ltr" id="package1"></div></div> <div class="add-block-left"><label>تعداد کاربر:</label><input type="number" min="0" id="capacity1"></div><hr>

				<input type="button" value="ثبت کن" onclick="insertSingleSerials()">
			</form>
		</div>
		
		

    </div>




</div>
</div>


