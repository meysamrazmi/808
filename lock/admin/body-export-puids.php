<?php
 if(check_req('export-puids') == false) die();  


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
 
<div class="container">

<div class="column text-col flow-opposite">





    <div class="post-row">

		<h2 class="title-h2">دریافت خروجی اکسل تمامی کاربران:</h2>
		<div class="search-blocks">
		
				<form id="auto-lvl-2" target="_blank" action="index.php" method="POST">
					<input type="submit" id="btn-get-excel" onclick="" value="دریافت فایل Excel">
					<input type="hidden" name="doback" value="getExcelAllPuids">
				</form>
		</div>
		
		

    </div>




</div>
</div>


