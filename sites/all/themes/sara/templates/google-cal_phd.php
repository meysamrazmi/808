<?php
$content = file_get_contents('https://calendar.google.com/calendar/embed?src=3aban4q4gcnqmbuocppkopuuog%40group.calendar.google.com&ctz=Asia/Tehran');
$content = str_replace('</title>','</title><base href="https://www.google.com/calendar/" />', $content);
$content = str_replace('</head>','<link rel="stylesheet" href="http://civil808.com/sites/all/themes/sara/css/razmia-calendar.css" type="text/css" /></head>', $content);
echo $content;