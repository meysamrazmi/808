<?php
 if(check_req('packages') == false) die();  


if (isset($_GET['prompt'])){ 

?>
 <div class="agreement-message" style="display: block;">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
	<?php 
	if($_GET['prompt'] == 'ok'){
		echo '<p>با موفقیت افزوده شد</p>';
	} else {
        echo '<p>خطا در افزودن پکیج!</p>';
	}
	?>
		
        <input type="button" id="agreement-submit" onclick="$('.agreement-message').hide()" value="باشه">
    </form>
    <br>
</div>

<?php } ?>

 <div class="overlay-message">
    <p class="pointer" id="close-overlay">&nbsp;&nbsp;X</p>
    <form id="edit-popup">
        <label>پکیج:</label><br>
        <input type="text" class="ltr" id="pop-up-packagecode" name="serial" required>
        <label>توضیح:</label><br>
		<input type="text" class="ltr" id="pop-up-packagedesc" name="max-use-count">

		<p id="confirmed-save"></p>
        <input type="button" id="edit-submit" onclick="submit_edits('package')" value="ذخیره">
    </form>
    <br>

</div>


 <div class="agreement-message">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
        <p>از حذف پکیج اطمینان دارید؟</p>
		
        <input type="button" id="agreement-submit" onclick="delete_item('package')" value="حذف کن!">
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
			$sql = "SELECT COUNT(id) FROM tblpackages";
			$result = $conn->query($sql);
			$row = $result->fetch_assoc();
			$package_count = $row['COUNT(id)'];
			
			echo '<div>تعداد کل پکیج ها: <b>' . $package_count . '</b></div><br>' ;
			?>
		</div>
		

		<h2 class="title-h2">ساخت پکیج:</h2>
		<div class="search-blocks">	
				<form id="auto-lvl-1">
					<label>پکیج:</label><input type="text" class="ltr" id="packageCode" required></input>
					<label>توضیح:</label><input type="text" id="packageDesc" ></input>
					<input type="button" onclick="makePackage()" value="بساز!">
				</form>
		</div>
		

		
		
	<h2 class="title-h2">جستجو:</h2>
		<div class="search-blocks">
			<form action="index.php?action=packages" method="POST">
				<label>پکیج:</label><br><input type="text" class="ltr" name="packageCode">
				<label>توضیح:</label><br><input type="text" name="packageDesc">
				<br>
				<input type="hidden" name="do" value="package">
				<input type="submit"  value="جستجو">
			</form>
		</div>
		
		<?php 
		if (isset($_POST['do'])){
		
		?> 
		
		<h2 class="title-h2">نتایج:</h2><table id="posts-tbl">
		<tr>
			<th>پکیج (پیش کد)</th>
			<th>توضیح</th>
			<th>تعداد سریال ها</th>
			<th>تعداد کاربران</th>
			<th>مدیریت پکیج</th>
		</tr>
		
		<?php
			global $conn;

			$packageCode = string_safer(strtolower(trim($_POST['packageCode'])));
			$packageDesc = string_safer(strtolower(trim($_POST['packageDesc'])));

			
			$alt_html = false;
			$res_counter = 0;
			if(strlen($packageCode) > 0){
			if($packageCode == '*'){
				$sql = "SELECT * FROM tblpackages";
			}else{
				$sql = "SELECT * FROM tblpackages WHERE trim(LOWER(package)) LIKE '%" . $packageCode . "%'";
			}
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
						
						
						$sql2 = "SELECT id FROM tblusers WHERE trim(LOWER(package)) = '" . $row['package'] . "'";
						$result2 = $conn->query($sql2);
						
						$serial_sql = "SELECT count(id) AS num FROM tblserials WHERE trim(LOWER(package)) = '" . $row['package'] . "'";
						$serials = $conn->query($serial_sql)->fetch_assoc();
						
						echo
						'<td class="ltr" id="package-name-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="package-desc-' . $row["id"] . '">' . $row["description"] . '</td>
						<td id="package-seials-' . $row["id"] . '">' . $serials['num'] . '</td> 
						<td id="package-users-' . $row["id"] . '">' . $result2->num_rows . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_package(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
						</tr>';
						
					}
				}
			}	
		
		
			if(strlen($packageDesc) > 0){
			$sql = "SELECT * FROM tblpackages WHERE trim(LOWER(description)) LIKE '%" . $packageDesc . "%'";
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
						
						
						$sql2 = "SELECT id FROM tblusers WHERE trim(LOWER(package)) = '" . $row['package'] . "'";
						$result2 = $conn->query($sql2);
						
						$serial_sql = "SELECT count(id) AS num FROM tblserials WHERE trim(LOWER(package)) = '" . $row['package'] . "'";
						$serials = $conn->query($serial_sql)->fetch_assoc();
						
						echo
						'<td class="ltr" id="package-name-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="package-desc-' . $row["id"] . '">' . $row["description"] . '</td>
						<td id="package-seials-' . $row["id"] . '">' . $serials['num'] . '</td> 
						<td id="package-users-' . $row["id"] . '">' . $result2->num_rows . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_package(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
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


