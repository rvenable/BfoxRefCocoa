<?php

/*
Note: For this script to work you have to modify parser.php:
	Make regex() public
	Make regex() return the book_regex as soon as it has been calculated
*/

require_once '../biblefox-ref.php';

for ($level = 0; $level < 3; $level++) {
	$p = new BfoxRefParser();
	$p->max_level = $level;
	$p->forward = true;
	echo '"BfoxBookRegexForwardLevel' . ($level + 1) . '" = "' . addslashes($p->regex()) . '";';
	echo "\n\n";
}

for ($level = 0; $level < 3; $level++) {
	$p = new BfoxRefParser();
	$p->max_level = $level;
	$p->forward = false;
	echo '"BfoxBookRegexReverseLevel' . ($level + 1) . '" = "' . addslashes($p->regex()) . '";';
	echo "\n\n";
}

?>