<?php
/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 */
?>
<!DOCTYPE html>
<html xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <!-- Global site tag (gtag.js) - Google Analytics -->
  <script async src="https://www.googletagmanager.com/gtag/js?id=UA-107721597-1"></script>
  <script>
    window.dataLayer = window.dataLayer || [];
    function gtag(){dataLayer.push(arguments);}
    gtag('js', new Date());
    gtag('config', 'UA-107721597-1');
  </script>
  <?php print $head; ?>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

  <title><?php print $head_title; ?></title>

  <script type="text/javascript">
    window.heap=window.heap||[],heap.load=function(e,t){window.heap.appid=e,window.heap.config=t=t||{};var r=t.forceSSL||"https:"===document.location.protocol,a=document.createElement("script");a.type="text/javascript",a.async=!0,a.src=(r?"https:":"http:")+"//cdn.heapanalytics.com/js/heap-"+e+".js";var n=document.getElementsByTagName("script")[0];n.parentNode.insertBefore(a,n);for(var o=function(e){return function(){heap.push([e].concat(Array.prototype.slice.call(arguments,0)))}},p=["addEventProperties","addUserProperties","clearEventProperties","identify","removeEventProperty","setEventProperties","track","unsetEventProperty"],c=0;c<p.length;c++)heap[p[c]]=o(p[c])};
      heap.load("3610844765");
  </script>  

</head>
<body>
	<div class="aa"></div>
	<?php print $page; ?>
<style>
@font-face {
	font-family: irans;
	font-style: normal;
	font-weight: bold;
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Bold.eot');
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Bold.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
		 url('/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Bold.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Bold.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Bold.ttf') format('truetype');
}
@font-face {
	font-family: irans;
	font-style: normal;
	font-weight: 500;
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Medium.eot');
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Medium.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
		 url('/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Medium.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Medium.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Medium.ttf') format('truetype');
}
@font-face {
	font-family: irans;
	font-style: normal;
	font-weight: normal;
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb.eot');
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
		 url('/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb.ttf') format('truetype');
}
@font-face {
	font-family: irans;
	font-style: normal;
	font-weight: 200;
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Light.eot');
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_Light.eot?#iefix') format('embedded-opentype'),  /* IE6-8 */
		 url('/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_Light.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_Light.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_Light.ttf') format('truetype');
}
@font-face {
	font-family: irans;
	font-style: normal;
	font-weight: 100;
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_UltraLight.eot');
	src: url('/sites/all/themes/sara/fonts/sans/eot/IRANSansWeb_UltraLight.eot?#iefix') format('embedded-opentype'),  /* IE6-8*/
		 url('/sites/all/themes/sara/fonts/sans/woff2/IRANSansWeb_UltraLight.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/woff/IRANSansWeb_UltraLight.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/ttf/IRANSansWeb_UltraLight.ttf') format('truetype');
}
@font-face {
	font-family: fanum;
	font-style: normal;
	font-weight: 100;
	src: url('/sites/all/themes/sara/fonts/sans/fanum/irsfanum.eot');
	src: url('/sites/all/themes/sara/fonts/sans/fanum/irsfanum.eot?#iefix') format('embedded-opentype'),  /* IE6-8*/
		 url('/sites/all/themes/sara/fonts/sans/fanum/irsfanum.woff2') format('woff2'),  /* FF39+,Chrome36+, Opera24+*/
		 url('/sites/all/themes/sara/fonts/sans/fanum/irsfanum.woff') format('woff'),  /* FF3.6+, IE9, Chrome6+, Saf5.1+*/
		 url('/sites/all/themes/sara/fonts/sans/fanum/irsfanum.ttf') format('truetype');
}
@font-face {
	font-family:'mat';
	src:	url('/sites/all/themes/sara/fonts/material/material.eot');
	src:	url('/sites/all/themes/sara/fonts/material/material.eot?#iefix') format('embedded-opentype'),
			url('/sites/all/themes/sara/fonts/material/material.woff') format('woff'),
			url('/sites/all/themes/sara/fonts/material/material.ttf') format('truetype'),
			url('/sites/all/themes/sara/fonts/material/material.svg#materialdesigniconsregular') format('svg');
	font-weight:normal;
	font-style:normal;
}
* {
  -webkit-box-sizing: border-box;
  -moz-box-sizing: border-box;
  box-sizing: border-box;
}
body {
	width: 100vw;
	height: 100vh;
	/*overflow: hidden;*/
	align-items: center;
	margin: 0;
	/*background: url(/sites/all/themes/sara/images/remote-login-bg.jpg);*/
	font-family: irans;
}
body:before {
	content: "";
	position: absolute;
	width: 100%;
	height: 100%;
	background: url(/sites/all/themes/sara/images/remote-login-bg.jpg);
	top: 0;
	background-position: 0 top;
	left: 0;
	opacity: 0;
	transform: rotate(180deg);
}
#main{
	position: relative;
}
div#block-system-main {
	display: flex;
	height: 100vh;
}
#main .content{
	max-width: 900px;
	width: 100%;
	margin: auto;
}
form {
	border-top: 1px solid #9C27B0;
	position: relative;
	overflow: hidden;
	margin: 0 10px;
	box-shadow: rgba(0,0,0,0.117647) 0 1px 6px, rgba(0,0,0,0.117647) 0 1px 4px;
	border-radius: 2px;
	background: #fff;
}
form > div {
	display: flex;
	flex-direction: row-reverse;
	min-height: 300px;
	align-items: center;
	align-items: stretch;
}
fieldset {
	border: none;
	width: 50%;
	margin: 0 0 0 60px;
	width: 400px;
	padding: 20px 35px;
}
.description {
	width: calc(100% - 470px);
	display: flex;
	align-items: center;
	justify-content: center;
	flex-direction: column;
	position: relative;
}
.description:before,
.description:after {
	content: "";
	position: absolute;
	width: 800px;
	height: 800px;
	background: rgba(148, 148, 148, 0.08);
	z-index: 0;
	border-radius: 50%;
	left: -370px;
	top: -350px;
}
.description:before {
	top: -280px;
}
.description > div {
	z-index: 10;
	position: relative;
}
.description .title {
	top: -50px;
	font-size: 15px;
}
#main .company-name label{
	display: inline;
	font-size: 13px;
	padding: 0px 5px;
}
.company-logo {
	width: calc(100% - 20px);
	text-align: center;
	margin-bottom: 20px;
}
img:first-child {
	margin-left: 60px;
}
img {
	max-height: 110px;
	max-width: 110px;
	vertical-align: middle;
}
i:before {
	content: "\f4e1";
	font-family: mat;
	font-size: 44px;
	font-style: initial;
	color: #bbb;
	position: absolute;
	margin: 7px -65px 0 0;
}
.form-type-password {
	margin-bottom: 25px;
}
.form-item{
	display: flex;
	justify-content: space-between;
	font-size: 13px;
	padding: 10px 0 15px;
	line-height: 30px;
	flex-direction: column;
}
.form-item input {
	border-radius: 30px;
	border: none;
	background: #f5f5f5;
	height: 32px;
	line-height: 30px;
	text-align: left;
	padding: 0 15px;
	width: 100%;
	margin-top: 5px;
	margin-right: auto;
}
.form-item input:hover {
	background: #eee;
}
.form-item input:focus, .form-item input:active {
	box-shadow: rgba(0,0,0,0.117647) 0 1px 6px, rgba(0,0,0,0.117647) 0 1px 4px;
	background: #fff;
}
#edit-submit {
	border: 0;
	height: 36px;
	border-radius: 30px;
	line-height: 36px;
	text-align: center;
	padding: 0 16px;
	font-size: 14px;
	min-width: 100px;
	transition: all .2s;
	text-decoration: none;
	box-shadow: rgba(0,0,0,0.117647) 0 1px 6px, rgba(0,0,0,0.117647) 0 1px 4px;
	outline: 0;
	color: #fff !important;
	background-color: #4caf50;
	float: left;
	cursor: pointer;
}
input {
	font-family: irans !important;
}
a.join {
	text-decoration: none;
	color: #1E88E5;
	font-size: 14px;
	border-bottom: 1px dashed;
}

@media (max-width: 840px){
#main .content {
	max-width: 440px;
}
form > div {
	flex-direction: column;
}
.description {
	width: 100%;
	height: 300px;
}
.description:before, .description:after {
	top: -520px;
	left: -300px;
}
.description:before {
	left: -260px;
}
fieldset {
	margin: 0;
	width: 100%;
	padding: 0 20px 30px;
}


}


  </style>
  <script type="text/javascript" src="/sites/all/themes/sara/js/bootstrap.min.js"></script>
  
</body>
</html>
