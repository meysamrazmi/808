<?php
 if(check_req('offline-activate') == false) die();  


?>
 <div class="agreement-message" style="display: none;">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
		<p>با موفقیت افزوده شد</p>

        <input type="button" id="agreement-submit" onclick="$('.agreement-message').hide()" value="باشه">
    </form>
    <br>
</div>
 
<div class="container">

<div class="column text-col flow-opposite">





    <div class="post-row">

		<h2 class="title-h2">فعالسازی آفلاین:</h2>
		<div class="search-blocks">
			<form>
				<label>کد PUID کاربر:</label>
				<p>کد 32 رقمی کامپیوتر کاربر به فرمت: ****-****-****-****-****-****-****-****</p>
				<textarea type="text" class="ltr" id="user-puid"></textarea>
				<label>فعالساز:</label><input type="text" class="ltr" id="activator" disabled></input>
				
				<input type="button" onclick="offlineActivator()" value="دریافت">
			</form>
		</div>
		
		<h2 class="title-h2">افزودن کاربر:</h2>
		<div class="search-blocks">
			<form>
				<label>PUID</label><textarea type="text" class="ltr" id="add-user-puid"></textarea>
				<label>Serial</label><input type="text" class="ltr" id="add-user-serial"></input>
				<label>Package</label><input type="text" class="ltr" id="add-user-package"></input>
				
				<input type="button" onclick="addOfflineUser()" value="اضافه کن!">
			</form>
		</div>
		
		

    </div>




</div>
</div>


