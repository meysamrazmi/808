<?php
$content = file_get_contents('https://www.google.com/calendar/embed?src=eflbktilh60r1ji9gokag0ab10%40group.calendar.google.com&ctz=Asia/Tehran');
$content = str_replace('</title>','</title><base href="https://www.google.com/calendar/" />', $content);
$content = str_replace('</head>','<link rel="stylesheet" href="https://civil808.com/sites/all/themes/sara/css/razmia-calendar.css" type="text/css" /></head>', $content);
echo $content;