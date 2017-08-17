<?php
 if(check_req('serials') == false) die();  ?>

  <div class="overlay-message">
    <p class="pointer" id="close-overlay">&nbsp;&nbsp;X</p>
    <form id="edit-popup">
        <label>سریال:</label><br>
        <input type="text" class="ltr" id="pop-up-serial" name="serial" required>
        <label>ظرفیت</label><br>
		<input type="number" id="pop-up-capacity" name="max-use-count" required>
        <label>ظرفیت پر شده</label><br>
		<input type="number" id="pop-up-used" name="used-serials" required>
        <label>توضیحات</label><br>
		<textarea type="text" id="pop-up-description" name="description"></textarea>

		<p id="confirmed-save"></p>
        <input type="button" id="edit-submit" onclick="submit_edits('serial')" value="ذخیره">
    </form>
    <br>

</div>


 <div class="agreement-message">
    <p class="pointer" id="close-agreement">&nbsp;&nbsp;X</p>
    <form id="agree-form">
        <p>از حذف سریال اطمینان دارید؟</p>
		
        <input type="button" id="agreement-submit" onclick="delete_item('serial')" value="حذف کن!">
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
			$sql = "SELECT COUNT(id) FROM tblserials";
			$result = $conn->query($sql);
			$row = $result->fetch_assoc();
			$serial_count = $row['COUNT(id)'];
			
			$sql = "SELECT max_use_count,use_counter FROM tblserials";
			$result = $conn->query($sql);
			$empty_serials = 0;
			$fulled_serials = 0;
			$not_fulled_serials = 0;
			if ($result->num_rows > 0) {
				while($row = $result->fetch_assoc()){
					if ($row['use_counter'] == 0) {
						$empty_serials++;
					} elseif($row['use_counter'] < $row['max_use_count']){
						$not_fulled_serials++;
					} elseif ($row['use_counter'] == $row['max_use_count']){
						$fulled_serials++;
					}
				}
			}
			echo '<div>تعداد کل سریال ها: <b>' . $serial_count . '</b></div><br>' ;
			echo '<div>تعداد سریال های خام (استفاده نشده): <b>' . $empty_serials . '</b></div><br>';
			echo '<div>سریال های نیمه استفاده شده: <b>' . $not_fulled_serials . '</b></div><br>' ;
			echo '<div>تعداد سریال های پر شده: <b>' . $fulled_serials . '</b></div>' ;
			?>
		</div>
		
		
	<h2 class="title-h2">جستجو:</h2>
		<div class="search-blocks">
			<form action="index.php?action=serials" method="POST">
				<label>Serial</label><br><input type="text" class="ltr" name="serial">
				<label>پکیج</label><br><input type="text" class="ltr" name="package">
				<label>ظرفیت</label><br><input type="number" name="max-use-count" min="0">
				<label>ظرفیت پر شده</label><br><input type="number" name="use-counter" min="0">
				<br>
				<input type="hidden" name="do" value="serial">
				<input type="submit"  value="جستجو">
			</form>
		</div>
		
		<?php 
		if (isset($_POST['do'])){
		
		?> 
		
		<h2 class="title-h2">نتایج:</h2><table id="posts-tbl">
		<tr>
			<th>سریال</th>
			<th>پکیج</th>
			<th>ظرفیت</th>
			<th>ظرفیت پر شده</th>
			<th>مدیریت سریال</th>
			<th>توضیحات</th>
		</tr>
		
		<?php
			global $conn;

			$serial = string_safer(strtolower(trim($_POST['serial'])));
			$max_use_count = (int)string_safer(strtolower(trim($_POST['max-use-count'])));
			$use_counter = (int)string_safer(strtolower(trim($_POST['use-counter'])));
			$package = string_safer(strtolower(trim($_POST['package'])));

			
			$alt_html = false;
			$res_counter = 0;
			if(strlen($serial) > 0){
				$sql = "SELECT * FROM tblserials WHERE trim(LOWER(serial)) LIKE '%" . $serial . "%'";
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
						'<td class="ltr" id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> 
						<td class="ltr" id="serial-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="max-use-count-' . $row["id"] . '">' . $row["max_use_count"] . '</td>
						<td id="use-counter-' . $row["id"] . '">' . $row["use_counter"] . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_serial(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
						<td id="description-' . $row["id"] . '">' . $row["description"] . '</td> 
						</tr>';
					}
				}
			}	
		
		
			if($max_use_count > 0){
			$sql = "SELECT * FROM tblserials WHERE max_use_count='" . $max_use_count . "'";
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
						'<td class="ltr" id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> 
						<td class="ltr" id="serial-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="max-use-count-' . $row["id"] . '">' . $row["max_use_count"] . '</td>
						<td id="use-counter-' . $row["id"] . '">' . $row["use_counter"] . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_serial(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
						<td id="description-' . $row["id"] . '">' . $row["description"] . '</td> 
						</tr>';
					}
				}
			}	
		
			if($use_counter > 0){
			$sql = "SELECT * FROM tblserials WHERE use_counter='" . $use_counter . "'";
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
						'<td class="ltr" id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> 
						<td class="ltr" id="serial-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="max-use-count-' . $row["id"] . '">' . $row["max_use_count"] . '</td>
						<td id="use-counter-' . $row["id"] . '">' . $row["use_counter"] . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_serial(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
						<td id="description-' . $row["id"] . '">' . $row["description"] . '</td> 
						</tr>';
					}
				}
			}	
			
			
			if(strlen($package) > 0){
			$sql = "SELECT * FROM tblserials WHERE trim(LOWER(package)) LIKE '%" . $package . "%'";
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
						'<td class="ltr" id="serial-' . $row["id"] . '">' . $row["serial"] . '</td> 
						<td class="ltr" id="serial-' . $row["id"] . '">' . $row["package"] . '</td> 
						<td id="max-use-count-' . $row["id"] . '">' . $row["max_use_count"] . '</td>
						<td id="use-counter-' . $row["id"] . '">' . $row["use_counter"] . '</td> 
						<td><a onclick="agreebox(' . $row["id"] . ')"><img class="img-delete" src="img/delete.png"></a>  <a href="javascript:edit_serial(' . $row["id"] . ')"><img class="img-delete" src="img/edit.png"></a></td> 
						<td id="description-' . $row["id"] . '">' . $row["description"] . '</td> 
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


