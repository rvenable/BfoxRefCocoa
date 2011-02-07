BfoxRef is a class for representing Bible References as sequences of integers. It was originally written in PHP and this is the brand new, just barely working Cocoa Objective C port (currently iOS only).

Usage
-----

    NSString *refString = @"Gen 1";
    BfoxRef *ref = [BfoxRef refWithString:refString];

    NSLog(@"Ref check: '%@' => '%@'", refString, ref); // Output: 'Gen 1' => 'Genesis 1'

Individual bible verses are represented by 3 byte integer values:

* Genesis 2:3 = 0x 01 02 03
* Genesis => book index 1 = 0x01
* Chapter 2 => chapter index 2 = 0x02
* Verse 3 => verse index 3 = 0x03
* So, Genesis 2:3 = (0x01 << 16) + (0x02 << 8) + 0x03 = 0x010203

Genesis 2:3-5 would be represented by two integers: the start verse and the end first

* First verse: Genesis 2:3 = 0x010203
* Last verse: Genesis 2:5 = 0x010205
* So, Genesis 2:3-5 = [0x010203, 0x010205]

But the BfoxRef class can also represent more complex references, like "Genesis 2:3-5,7,9-10; 3"

* [[0x010203, 0x010205], [0x010207, 0x010207], [0x010209, 0x01020A], [0x010300, 0x0103FF]]

BfoxRef also include BfoxRefParser for parsing Bible references out of strings, and includes many different synonyms/abbreviations for Bible book names ('gen', 'exo', '1sam', etc.).