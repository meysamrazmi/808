<?php
 if(check_req('puids') == false) die();  ?>

 <div class="overlay-message">
    <p class="pointer" id="close-overlay">&nbsp;&nbsp;X</p>
    <form id="edit-popup">
        <label>سریال:</label><br>
        <input type="text" class="ltr" id="pop-up-serial" name="serial" required>
        <label>کد PUID:</label><br>
        <input type="text" class="ltr" id="pop-up-puid" name="puid" required>
        <label>نام و نام خانوادگی:</label><br>
		<input type="text" id="pop-up-name" name="name" required>
        <label>ایمیل:</label><br>
		<input type="email" class="ltr" id="pop-up-email" name="email" required>
		<label>شماره:</label><br>
		<input type="text" class="ltr" id="pop-up-phone" name="phone" required>
		<p id="confirmed-save">test</p>
        <input type="button" id="edit-submit" onclick="submit_edits('puid')" value="ذخیره">
    </form>
    <br>


</div>

 <div class="agreement-message">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
        <p>از حذف کاربر مطمعن هستید؟</p>
		
        <input type="button" id="agreement-submit" onclick="delete_item('puid')" value="حذف کن!">
    </form>
    <br>
</div>
 
 
<div class="container">

<div class="column text-col flow-opposite">





    <div class="post-row">
		<h2 class="title-h2">آمار:</h2>
		<div class="search-blocks">

			<?php 
			global $conn;
			$sql = "SELECT COUNT(id) FROM tblusers";
			$result = $conn->query($sql);
			$row = $result->fetch_assoc();
			echo '<div>تعداد کل کاربران: <b>' . $row['COUNT(id)'] . '</b></div>' ;
			?>
		</div>
		
		
	<h2 class="title-h2">جستجو:</h2>
		<div class="search-blocks">
			<form action="index.php?action=puids" method="POST">
				<label>کد PUID</label><br><input type="text" class="ltr" name="puid">
				<label>Serial</label><br><input type="text" class="ltr" name="serial">
				<label>نام و نام خانوادگی</label><br><input type="text" name="name">
				<label>شماره تماس</label><br><input type="text" class="ltr" name="phone">
				<label>ایمیل</label><br><input type="text" class="ltr" name="email">
				<label>پکیج</label><br><input type="text" class="ltr" name="package">
				<br>
				<input type="hidden" name="do" value="puid">
				<input type="submit"  value="جستجو">
			</form>
		</div>
		
		<?php 
		if (isset($_POST['do'])){
		
		?> 
		
		<h2 class="title-h2">نتایج:</h2><table id="posts-tbl">
		<tr>
			<th>پکیج</th>
			<th>Serial</th>
			<th>PUID</th>
			<th>نام کاربر</th>
			<th>ایمیل</th>
			<th>شماره</th>
			<th>تاریخ عضویت</th>
			<th>مدیریت کاربر</th>
		</tr>
		
		<?php
			global $conn;
			
			$puid = string_safer(strtolower(trim($_POST['puid'])));
			$serial = string_safer(strtolower(trim($_POST['serial'])));
			$name = string_safer(strtolower(trim($_POST['name'])));
			$phone = string_safer(strtolower(trim($_POST['phone'])));
			$email = string_safer(strtolower(trim($_POST['email'])));
			$package = string_safer(strtolower(trim($_POST['package'])));
			
			$alt_html = false;
			$res_counter = 0;
			if(strlen($puid) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(puid)) LIKE '%" . $puid . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if(strlen($serial) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(serial)) LIKE '%" . $serial . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if(strlen($name) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(uname)) LIKE '%" . $name . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if(strlen($email) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(uemail)) LIKE '%" . $email . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if(strlen($phone) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(uphone)) LIKE '%" . $phone . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if(strlen($package) > 0){
			$sql = "SELECT * FROM tblusers WHERE trim(LOWER(package)) LIKE '%" . $package . "%'";
			$result = $conn->query($sql);
			
			if ($result->num_rows > 0) {
				// output data of each row
				while ($row = $result->fetch_assoc()) {
					$res_counter++;
					if($alt_html) {
						echo '<tr class="alt" id="item-' . $row["id"] . '">';
					} else {
						echo '<tr id="item-' . $row["id"] . '">';
					}
					$alt_html = !$alt_html;
					
					echo
					'<td lass="ltr"  id="package-' . $row["id"] . '">' . $row["package"] . '</td> .
					<td lass="ltr"  id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> .
					<td class="ltr" id="puid-' . $row["id"] . '">' . $row["puid"] . '</td> .
					<td id="uname-' . $row["id"] . '">' . $row["uname"] . '</td> .
					<td class="ltr" id="uemail-' . $row["id"] . '">' . $row["uemail"] . '</td> . 
					<td class="ltr" id="uphone-' . $row["id"] . '">' . $row["uphone"] . '</td> .
					<td>' . $row["date_joined"] . '</td>' .
					'<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_user(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
					</tr>';
				}
			}
		}
		
		if($res_counter == 0){
			echo "<h3>نتیجه ای یافت نشد!</h3>";
		}
		?>
	


	</table>
	
		<?php } ?>
    </div>




</div>
</div>


