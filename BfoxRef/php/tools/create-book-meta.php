<?php

/*
Note: For this script to work you have to modify bible-meta.php:
	Make BibleMeta::$min_verse_counts public
	Make BibleMeta::$max_verse_counts public
*/

require_once '../biblefox-ref.php';

$lookup = BfoxRefParser::$book_id_lookup;

foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$ch_count = array_shift($array);
	$book_name = BibleMeta::get_book_name($book);
	$book_name = preg_replace('/\s+/', '', $book_name);
//	echo "/* $book $book_name */ { ";
	echo "unsigned int BfoxBook{$book_name}MinVerseCounts[] = { ";
	foreach ($array as $index => $vs_count) {
		if (isset(BibleMeta::$max_verse_counts[$book][$index + 1])) $max_vs_count = BibleMeta::$max_verse_counts[$book][$index + 1];
		else $max_vs_count = $vs_count;
		if ($index) echo ", ";
		echo "$vs_count";
	}
	echo " };\n";

	echo "unsigned int BfoxBook{$book_name}MaxVerseCounts[] = { ";
	foreach ($array as $index => $vs_count) {
		if (isset(BibleMeta::$max_verse_counts[$book][$index + 1])) $max_vs_count = BibleMeta::$max_verse_counts[$book][$index + 1];
		else $max_vs_count = $vs_count;
		if ($index) echo ", ";
		echo "$max_vs_count";
	}
	echo " };\n";
}

echo "\n\n\n";

echo "const unsigned int BfoxBookChapterCounts[] = { ";
foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$ch_count = array_shift($array);
	if (1 != $book) echo ", ";
	echo "$ch_count";
}
echo " };\n";

echo "\n\n\n";

echo "const unsigned int *BfoxBookChapterMinVerseCounts[] = { ";
foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$book_name = BibleMeta::get_book_name($book);
	$book_name = preg_replace('/\s+/', '', $book_name);
	if (1 != $book) echo ", ";
	echo "BfoxBook{$book_name}MinVerseCounts";
}
echo " };\n";

echo "\n\n\n";

echo "const unsigned int *BfoxBookChapterMaxVerseCounts[] = { ";
foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$book_name = BibleMeta::get_book_name($book);
	$book_name = preg_replace('/\s+/', '', $book_name);
	if (1 != $book) echo ", ";
	echo "BfoxBook{$book_name}MaxVerseCounts";
}
echo " };\n";

echo "\n\n\n";

foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$book_name = BibleMeta::get_book_name($book);
	$book_name = preg_replace('/\s+/', '', $book_name);
	echo "BfoxBook$book_name,\n";
}

echo "\n\n\n";

foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$book_name = BibleMeta::get_book_name($book);
	echo "\"BfoxBookNameDefaultForBook$book\" = \"$book_name\";\n\n";
}

echo "\n\n\n";

foreach (BibleMeta::$min_verse_counts as $book => $array) {
	if ($book > 66) break;
	$book_name = BibleMeta::get_book_name($book, BibleMeta::name_short);
	echo "\"BfoxBookNameShortForBook$book\" = \"$book_name\";\n\n";
}

?>