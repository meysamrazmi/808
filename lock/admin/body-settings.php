<?php
 if(check_req('settings') == false) die(); ?>

<div class="container">

<div class="column text-col flow-opposite">





    <div class="post-row">
		<h2 class="title-h2">تغییر کلمه عبور و نام کاربری:</h2>
			<div class="search-blocks">
				<form action="index.php?action=settings" method="POST">
					<label>نام کاربری جدید</label><br><input type="text" name="newuser">
					<label>تکرار نام کاربری جدید</label><br><input type="text" name="newuser2">
					<label>پسورد جدید</label><br><input type="text" name="newpass">
					<label>تکرار پسورد جدید</label><br><input type="text" name="newpass2">
									<input type="hidden" name="do" value="settings">
					<br>
					<input type="submit" id="settings-btn" value="ذخیره">
				</form>
			</div>
			
				<?php 
	if (isset($_POST['do'])){
		if (isset($_POST['newuser']) && isset($_POST['newuser2']) || isset($_POST['newpass']) && isset($_POST['newpass2'])){
			if ($_POST['newuser'] === $_POST['newuser2']){
				set_setting("user",hashc($_POST['newuser']));
			}
			if ($_POST['newpass'] === $_POST['newpass2']){
				set_setting("pass",hashc($_POST['newpass']));
			}
			echo '<h3 style="color: rgb(30, 176, 155);font-size: 1.5em;">تغییرات ذخیره شد! </h3>';
		}
	} ?>
    </div>





</div>
</div>



