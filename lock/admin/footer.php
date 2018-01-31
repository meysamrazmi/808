<?php
 if(check_req() == false) die(); ?>

<script src="js/jquery-2.1.1.js"></script>
<script src="js/jq.js"></script>

</body>


</html>

<?php 
global $conn;
$conn->close();
die(); ?>