//
//  BfoxRefTests.m
//  BfoxRefTests
//
//  Created by Richard Venable on 2/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "BfoxRefTests.h"
#import "BfoxRef.h"

@implementation BfoxRefTests

#define BfoxRefStringTest(refString, expected, description, ...) STAssertEqualObjects([[BfoxRef refWithString:refString] string], expected, description, ##__VA_ARGS__)

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)testRefStringParsing
{
	// Test the typical references
	BfoxRefStringTest(@"1 sam", @"1 Samuel", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1", @"1 Samuel 1", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1-2", @"1 Samuel 1-2", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1:1", @"1 Samuel 1:1", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1:1-5", @"1 Samuel 1:1-5", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1:1-2:5", @"1 Samuel 1-2:5", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1:2-2:5", @"1 Samuel 1:2-2:5", @"Simple Test Case");
	BfoxRefStringTest(@"1sam 1-2:5", @"1 Samuel 1-2:5", @"Simple Test Case");
	
	// Test periods
	BfoxRefStringTest(@"1sam. 1", @"1 Samuel 1", @"Parsing periods after book name");
	
	// This test was failing
	BfoxRefStringTest(@"Judges 2:6-3:6", @"Judges 2:6-3:6", @"Specific test that used to fail");
	
	// Test ignore words
	BfoxRefStringTest(@"Book of Judges 2", @"Judges 2", @"Test ignore words");
	BfoxRefStringTest(@"First Book of Judges 2", @"error", @"This one should not work, but I dont remember why not..."); // This one should not work!
	BfoxRefStringTest(@"First Book of Samuel 2", @"1 Samuel 2", @"Test ignore words");
	
	// Test that we can match synonyms with multiple words
	BfoxRefStringTest(@"Song of Solomon 2", @"Song of Solomon 2", @"Test multiple word synonyms");
	
	// This should be Gen 1:1, 1:3 - 2:3
	BfoxRefStringTest(@"gen 1:1,3-2:3", @"Genesis 1:1,3-2:3", @"Complex, single book case");
	
	BfoxRefStringTest(@"gen 1-100", @"Genesis", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 2-100", @"Genesis 2-50", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 49:1-100", @"Genesis 49", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 49:2-100", @"Genesis 49:2-33", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 50:1-100", @"Genesis 50", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 50:2-100", @"Genesis 50:2-26", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 50:1,2-100", @"Genesis 50", @"Test end points that are greater than last chapter/verse");
	BfoxRefStringTest(@"gen 50:1,3-100", @"Genesis 50:1,3-26", @"Test end points that are greater than last chapter/verse");
	
	// Test min/max in Romans 14
	BfoxRefStringTest(@"rom 14:2-100", @"Romans 14:2-26", @"Test min/max in Romans 14");
	BfoxRefStringTest(@"rom 14:1-22", @"Romans 14:1-22", @"Test min/max in Romans 14");
	BfoxRefStringTest(@"rom 14:1-23", @"Romans 14", @"Test min/max in Romans 14");
	BfoxRefStringTest(@"rom 14:2-23", @"Romans 14:2-26", @"Test min/max in Romans 14");
	
	// Test having consecutive books
	BfoxRefStringTest(@"Gen 2-100, Exodus", @"Genesis 2-50; Exodus", @"Test consecutive books");
	BfoxRefStringTest(@"Gen 2-100, Exodus, Lev", @"Genesis 2-50; Exodus; Leviticus", @"Test consecutive books");
	
	// Test long strings with lots of garbage
	BfoxRefStringTest(@"hello dude genesis 1,;,2 gen 5 1 sam 4, song ;of song 3", @"Genesis 1-2; 5; 1 Samuel 4; Song of Solomon", @"Test long strings with lots of garbage"); // TODO3: words like song get detected as the entire book Song of Solomon
	BfoxRefStringTest(@"<xml>\
					<p>I like Gen 1.</p>\
					<p>What do you think? john. 21 Do you prefer<d><d> ex 2 or 1sam 3 - 4 or 1 th 4? gen 3:4-8:2 gen 3ddd:2 fff- 1 1 3 </p>\
					<p>exodus lala yoyo 4:5</p>\
					</xml>\
					", @"Genesis 1; 3-8:2; Exodus; 1 Samuel 3-4; John 21; 1 Thessalonians 4", @"Test long strings with lots of garbage"); // TODO3: "ex" is not detected because it is only 2 letters
	
	// Test non-existent chapter
	BfoxRefStringTest(@"2jhn 2", @"Invalid", @"non-existent chapter");
	BfoxRefStringTest(@"hag 3", @"Invalid", @"non-existent chapter");
	BfoxRefStringTest(@"hag 2-3", @"Haggai 2", @"ends with non-existent chapter");
	BfoxRefStringTest(@"hag 1-3", @"Haggai", @"ends with non-existent chapter");
	BfoxRefStringTest(@"hag 5-7", @"Invalid", @"non-existent chapters");
	BfoxRefStringTest(@"hag 1:100-2:4", @"Haggai 2:1-4", @"begins with non-existent verse");
	
	// This test fails unless parsing in reverse
	BfoxRefStringTest(@"Genesis 3; 1 Samuel 5", @"Genesis 3; 1 Samuel 5", @"Only works in reverse");
}

@end
