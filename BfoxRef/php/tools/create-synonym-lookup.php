<?php

/*
Note: For this script to work you have to modify parser.php:
	Make BfoxRefParser::$book_id_lookup public
*/

require_once '../biblefox-ref.php';

$lookup = BfoxRefParser::$book_id_lookup;

foreach ($lookup as $key => $value) {
	if ($value > 66) continue;
	echo "\"$key\" = \"$value\";\n\n";
}

?>