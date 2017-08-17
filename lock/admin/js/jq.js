$(document).ready(function(){

	$("#confirmed-save").hide();
  $("#close-overlay").click(function() {
    $(".overlay-message").hide();
  });
  
   $("#close-agreement").click(function() {
    $(".agreement-message").hide();
  });
  
  

 });
  
function edit_user(userid){
	$('#pop-up-serial').val($('#serial-' + userid).text());
	$('#pop-up-puid').val($('#puid-' + userid).text());
	$('#pop-up-email').val($('#uemail-' + userid).text());
	$('#pop-up-name').val($('#uname-' + userid).text());
	$('#pop-up-phone').val($('#uphone-' + userid).text());
	
  $(".overlay-message").show();
    $(".confirmed-save").hide();

    var newInput = document.createElement("input");
    newInput.type = "hidden";
	newInput.id = "pop-up-userid";
    newInput.name = "id";
    newInput.value = userid;
    document.getElementById("edit-popup").appendChild(newInput);
  
}

function edit_serial(serialid){
	$('#pop-up-serial').val($('#serial-' + serialid).text());
	$('#pop-up-capacity').val($('#max-use-count-' + serialid).text());
	$('#pop-up-description').val($('#description-' + serialid).text());
	$('#pop-up-used').val($('#use-counter-' + serialid).text());

	
    $(".overlay-message").show();
    $(".confirmed-save").hide();

    var newInput = document.createElement("input");
    newInput.type = "hidden";
	newInput.id = "pop-up-serialid";
    newInput.name = "id";
    newInput.value = serialid;
    document.getElementById("edit-popup").appendChild(newInput);

  
}

function msgbox(text){
	$("#msgp").text(text);
	$(".agreement-message2").show();
}



function submit_edits(page){
	  var xmlhttp = new XMLHttpRequest();
	  xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			  if (xmlhttp.responseText == 1){
					$("#confirmed-save").text('ذخیره شد');
					$("#confirmed-save").css({"color": "#459B45"});
				    $("#confirmed-save").show();
					if (page == 'serial'){
						var id = $("#pop-up-serialid").val();
						$('#serial-' + id).text($('#pop-up-serial').val());
						$('#max-use-count-' + id).text($('#pop-up-capacity').val());
						$('#description-' + id).text($('#pop-up-description').val());
						$('#use-counter-' + id).text($('#pop-up-used').val());
					} else if(page == 'package') {
						var id = $("#pop-up-packageid").val();
						$('#package-name-' + id).text($('#pop-up-packagecode').val());
						$('#package-desc-' + id).text($('#pop-up-packagedesc').val())
					} else {
						var id = $("#pop-up-userid").val();
						$('#serial-' + id).text($('#pop-up-serial').val());
						$('#puid-' + id).text($('#pop-up-puid').val());
						$('#uemail-' + id).text($('#pop-up-email').val());
						$('#uname-' + id).text($('#pop-up-name').val());
						$('#uphone-' + id).text($('#pop-up-phone').val());
					}
			  } else {
				  	$("#confirmed-save").text('فیلدها را به درستی پر کنید');
					$("#confirmed-save").css({"color": "#B13333"});
				    $("#confirmed-save").show();
			  }

			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	
	var query;
	if (page == 'serial'){
		query = "doback=edits&id=" + $('#pop-up-serialid').val() + "&max-user-count=" + $('#pop-up-capacity').val() + "&serial=" + $('#pop-up-serial').val() + "&description=" + $('#pop-up-description').val() + "&user_counter=" + $('#pop-up-used').val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
	} else if(page == 'package') {
		query = "doback=editp&id=" + $('#pop-up-packageid').val() + "&packageCode=" + $('#pop-up-packagecode').val() + "&packageDesc=" + $('#pop-up-packagedesc').val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
	} else {
		query = "doback=editu&id=" + $('#pop-up-userid').val() + "&name=" + $('#pop-up-name').val() + "&puid=" + $('#pop-up-puid').val() + "&email=" + $('#pop-up-email').val() + "&phone=" + $('#pop-up-phone').val() + "&serial=" + $('#pop-up-serial').val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
    }
	xmlhttp.send(query);
}

function delete_item(type){
	var id = $("#popup-delete-id").val();
	if (id < 1){
		return;
	}
		
	var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			  if (xmlhttp.responseText == 1){
					$("#item-" + id).remove()
					$(".agreement-message").hide();
			  }
			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	var query;
	if (type == 'puid'){
		query = "doback=deleteu&id=" + id + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
	} else if(type == 'package') {
		query = "doback=deletep&id=" + id + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
	} else if(type == 'serial'){
		query = "doback=deletes&id=" + id + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
	}
	xmlhttp.send(query);
}



function agreebox(id){
	$(".agreement-message").show();

    var newInput = document.createElement("input");
    newInput.type = "hidden";
	newInput.id = "popup-delete-id";
    newInput.name = "id";
    newInput.value = id;
    document.getElementById("agree-form").appendChild(newInput);
}

function offlineActivator(){
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				$("#activator").val(xmlhttp.responseText)
			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("doback=getActivator&puid=" + $("#user-puid").val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val());
}

function addOfflineUser(){

	var serial = String($("#add-user-serial").val());
	var puid = String($("#add-user-puid").val());
	var packagee = String($("#add-user-package").val());
	
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				if (xmlhttp.responseText == 1){
					$(".agreement-message").show();
				}
			}
	  }

	if(serial.length > 0 && puid.length > 0 && packagee.length > 0){
		if (serial.substr(0,packagee.length) == packagee) {
			xmlhttp.open("POST","index.php",true);
			xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
			xmlhttp.send("doback=addOfflineUser&puid=" + puid + "&serial=" + serial + "&package=" + packagee + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val());
		} else {
			msgbox('عدم تناسب پکیج با سریال');
		}
	}

}

function makeBulkSerialsJson(){
	if ($("#bulk-serial-format").val().substr(0,$("#bulk-package").val().length) != $("#bulk-package").val()){
		msgbox('عدم تطابق فرمت سریال با پکیج!');
		return;
	}
	
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				if (xmlhttp.responseText.length > 5){
					$("#auto-json").val(xmlhttp.responseText);
					$("#btn-get-excel").prop('disabled', false);
					$("#btn-insert-json").prop('disabled', false);
					$("#auto-json").prop('disabled', false);
				} else if (xmlhttp.responseText == '0'){
					msgbox('پکیج در دتیابیس موجود نیست!');
				}
			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("doback=makeBulkSerials&count=" + $("#auto-count").val() + "&capacity=" + $("#auto-capacity").val() + "&format=" + $("#bulk-serial-format").val() + "&package=" + $("#bulk-package").val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val());
}

function insertBulkSerialsJson(){
	if ($("#auto-json").length <= 0){
		msgbox('اپتدا مرحله اول را کامل کنید!');
		return;
	}
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {

				if (xmlhttp.responseText == 1){
					window.location = "index.php?action=add-serials&prompt=ok";
				} else {
					window.location = "index.php?action=add-serials&prompt=err";
				}
			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("doback=bulkInsert&json=" + $("#auto-json").val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val());
}


function makePackage(){
	if($("#packageCode").val() == ""){
		return;
	}
	
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {

				if (xmlhttp.responseText == 1){
					//added
					window.location = "index.php?action=packages&prompt=ok";
				} else {
					//error
					window.location = "index.php?action=packages&prompt=err";
				}
			}
	  }
    xmlhttp.open("POST","index.php",true);
    xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("doback=makePackage&PackageCode=" + $("#packageCode").val() + "&PackageDesc=" + $("#packageDesc").val() + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val());
}

function edit_package(packageid){
	$('#pop-up-packagecode').val($('#package-name-' + packageid).text());
	$('#pop-up-packagedesc').val($('#package-desc-' + packageid).text());

	
    $(".overlay-message").show();
    $(".confirmed-save").hide();

    var newInput = document.createElement("input");
    newInput.type = "hidden";
	newInput.id = "pop-up-packageid";
    newInput.name = "id";
    newInput.value = packageid;
    document.getElementById("edit-popup").appendChild(newInput);
}

function insertSingleSerials(){
	var queryt = "";
	var serial = String($("#serial1").val());
	var capacity = String($("#capacity1").val());
	var packagee = String($("#package1").val());
	if(serial.length > 0 && capacity.length > 0 && packagee.length > 0){
		if (serial.substr(0,packagee.length) == packagee) {
			queryt += "doback=addserial&serial1=" + serial + "&capacity1=" + capacity + "&package1=" + packagee + "&udata=" + $("#udata").val() + "&tdata=" + $("#tdata").val();
			notEmpty = true;
		} else {
			msgbox('عدم تناسب پکیج با سریال');
		}
	}
	
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				if (xmlhttp.responseText == 1){
					msgbox('با موفقیت افزوده شد');
				} else if(xmlhttp.responseText == 2){ 
					msgbox('سریال از قبل در دیتابیس موجود است');
				} else {
					msgbox('خطا در افزودن سریال');
				}
			}
	  }
	if (notEmpty == true){
		xmlhttp.open("POST","index.php",true);
		xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
		xmlhttp.send(queryt);
	}
}

