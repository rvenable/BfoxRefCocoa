//
//  BfoxRefParser.m
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxRefParser.h"
#import "BfoxRef.h"
#import "BfoxVerseList.h"
#import "BfoxRefParseResult.h"
#import "NSString+BfoxRef.h"

NSString *const BfoxBookRegexForwardLevel1 = @"BfoxBookRegexForwardLevel1";
NSString *const BfoxBookRegexForwardLevel2 = @"BfoxBookRegexForwardLevel2";
NSString *const BfoxBookRegexForwardLevel3 = @"BfoxBookRegexForwardLevel3";
NSString *const BfoxBookRegexReverseLevel1 = @"BfoxBookRegexReverseLevel1";
NSString *const BfoxBookRegexReverseLevel2 = @"BfoxBookRegexReverseLevel2";
NSString *const BfoxBookRegexReverseLevel3 = @"BfoxBookRegexReverseLevel3";

@implementation BfoxRefParser

@synthesize cumulativeRef, arrayOfRefs;
@synthesize maxSynonymLevel, parseForward, allowWholeBooks, requireSpaceBeforeChapterVerse;

- (id)init {
	self = [super init];
	if (self) {
		maxSynonymLevel = BfoxBookSynonymLevelStrictest;
		parseForward = NO;
		allowWholeBooks = YES;
		requireSpaceBeforeChapterVerse = NO;
	}
	return self;
}

- (void)dealloc {
	[super dealloc];
}

- (BfoxBook)bookForLowercaseSynonym:(NSString *)lowercaseSynonym {
	NSString *numberString = NSLocalizedStringFromTable(lowercaseSynonym, @"BfoxBookSynonymLookup", @"bookForLowercaseSynonym");
	BfoxBook book = BfoxBookNotSet;
	if (numberString) {
		book = (BfoxBook) [numberString intValue];
		if (book > BfoxLastBookInBible) book = BfoxBookNotSet;
	}
	return book;
}

- (void)parseString:(NSString *)stringToParse {
	NSError *error;
	
	NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:[self regexPattern] options:NSRegularExpressionCaseInsensitive error:&error];
	NSArray *matches = [regex matchesInString:stringToParse options:0 range:NSMakeRange(0, [stringToParse length])];

	for (NSTextCheckingResult *textCheckingResult in matches) {
		BfoxRefParseResult *match = [[[BfoxRefParseResult alloc] init] autorelease];
		match.baseString = stringToParse;
		match.textCheckingResult = textCheckingResult;
		
		// NSString *text = [match stringAtIndex:0];
		// if (!parseForward) text = [text reversedString];
		
		NSString *synonym;
		if (parseForward) {
			if ([[match stringAtIndex:2] length]) synonym = [match stringAtIndex:2];
			else if ([[match stringAtIndex:7] length]) synonym = [@"1" stringByAppendingString:[match stringAtIndex:7]];
			else if ([[match stringAtIndex:12] length]) synonym = [@"2" stringByAppendingString:[match stringAtIndex:12]];
			else if ([[match stringAtIndex:17] length]) synonym = [@"3" stringByAppendingString:[match stringAtIndex:17]];
		}
		else {
			if ([[match stringAtIndex:19] length]) synonym = [match stringAtIndex:19];
			else if ([[match stringAtIndex:15] length]) synonym = [[match stringAtIndex:15] stringByAppendingString:@"1"];
			else if ([[match stringAtIndex:10] length]) synonym = [[match stringAtIndex:10] stringByAppendingString:@"2"];
			else if ([[match stringAtIndex:5] length]) synonym = [[match stringAtIndex:5] stringByAppendingString:@"3"];
		}
		
		if (!parseForward) synonym = [synonym reversedString];
		synonym = [[synonym stringWithWhitespaceReplacedByString:@" "] lowercaseString];
		
		BfoxBook book = [self bookForLowercaseSynonym:synonym];
		if (BfoxBookNotSet != book) {
			BfoxRef *ref = [BfoxRef ref];
			
			NSString *chapterVerseString;
			if (parseForward) chapterVerseString = [match stringAtIndex:18];
			else chapterVerseString = [[match stringAtIndex:1] reversedString];

			// Trim whitespace and periods
			NSMutableCharacterSet *whitespaceAndPeriods = [NSMutableCharacterSet whitespaceAndNewlineCharacterSet];
			[whitespaceAndPeriods addCharactersInString:@"."];
			chapterVerseString = [chapterVerseString stringByTrimmingCharactersInSet:whitespaceAndPeriods];
			if ([chapterVerseString length]) [self parseChapterVerseString:chapterVerseString forBook:book andAddVersesToRef:ref];
			else [ref.verseList addVersesForFullBook:book];
			
			if ([ref hasVerses]) {
				if (arrayOfRefs) [arrayOfRefs addObject:ref];
				if (cumulativeRef) [cumulativeRef addRef:ref];
				// if (isset($this->replace_func)) $text = call_user_func_array($this->replace_func, array($text, $ref));
				// if (isset($this->leftovers)) $text = '';
			}
		}
	}
}

- (void)parseChapterVerseString:(NSString *)chapterVerseString forBook:(BfoxBook)book andAddVersesToRef:(BfoxRef *)ref {
	NSError *error;

	// Spaces between numbers count as semicolons
	NSRegularExpression *spacesBetweenNumbers = [NSRegularExpression regularExpressionWithPattern:@"(\\d)\\s+(\\d)" options:0 error:&error];
	chapterVerseString = [spacesBetweenNumbers stringByReplacingMatchesInString:chapterVerseString options:0 range:NSMakeRange(0, chapterVerseString.length) withTemplate:@"$1;$2"];

	NSArray *semis = [chapterVerseString componentsSeparatedByString:@";"];
	for (NSString *semi in semis) {
		NSArray *commas = [semi componentsSeparatedByString:@","];
		
		// Keep track of a chapter that might be associated with some loose verse numbers
		// ie. in "Gen 1:2,4", the "4" gets separated from the "1:2",
		// so we need to remember that it is still in chapter 1
		BfoxChapter chapterForLooseVerses = BfoxChapterNotSet;
		
		for (NSString *comma in commas) {
			NSArray *dash = [comma componentsSeparatedByString:@"-"];

			BfoxChapter ch1 = BfoxChapterNotSet;
			BfoxVerse vs1 = BfoxVerseNotSet;
			BfoxChapter ch2 = BfoxChapterNotSet;
			BfoxVerse vs2 = BfoxVerseNotSet;
			
			if (dash.count) {
				NSArray *left = [(NSString *)[dash objectAtIndex:0] componentsSeparatedByString:@":"];
				if (left.count) {
					ch1 = (BfoxChapter) [(NSString *)[left objectAtIndex:0] intValue];
					if (1 < left.count) {
						vs1 = (BfoxVerse) [(NSString *)[left objectAtIndex:1] intValue];
					}
				}
				
				if (1 < dash.count) {
					NSArray *right = [(NSString *)[dash objectAtIndex:1] componentsSeparatedByString:@":"];
					if (right.count) {
						ch2 = (BfoxChapter) [(NSString *)[right objectAtIndex:0] intValue];
						if (1 < right.count) {
							vs2 = (BfoxVerse) [(NSString *)[right objectAtIndex:1] intValue];
						}
					}
				}
			}
			
			// We must have a chapter1
			if (BfoxChapterNotSet != ch1) {
				// If verse0 is not 0, but verse1 is 0, we should use chapter1 as verse1, and chapter1 should be 0
				// This fixes the following type of case: 1:2-3 (1:2-3:0 becomes 1:2-0:3)
				if ((BfoxVerseNotSet != vs1) && (BfoxVerseNotSet == vs2)) {
					vs2 = (BfoxVerse) ch2;
					ch2 = BfoxChapterNotSet;
				}
				
				// Full Chapters (or just verses)
				if ((BfoxVerseNotSet == vs1) && (BfoxVerseNotSet == vs2)) {
					if (BfoxChapterNotSet == ch2) ch2 = ch1;
					
					if (BfoxChapterNotSet == chapterForLooseVerses) {
						// If there is no chapterForLooseVerses, then these are whole chapters (from ch1 to ch2)
						[ref.verseList addVersesFromChapter:ch1
													  verse:BfoxFirstVerseForFullChapter
												  toChapter:ch2
													  verse:BfoxLastVerseForFullChapter
												 withinBook:book];
					}
					else {
						// Otherwise, what we thought were chapters (ch1 and ch2) are actually verses within chapter chapterForLooseVerses
						[ref.verseList addVersesFromVerse:(BfoxVerse)ch1
												  toVerse:(BfoxVerse)ch2
											withinChapter:chapterForLooseVerses
												   ofBook:book];
					}
				}
				// Inner Chapters (verses within a single chapter)
				else if ((BfoxChapterNotSet == ch2) || (ch1 == ch2)) {
					chapterForLooseVerses = ch1;
					[ref.verseList addVersesFromVerse:vs1
											  toVerse:vs2
										withinChapter:chapterForLooseVerses
											   ofBook:book];
				}
				// Mixed Chapters (verses within multiple chapters, but not full chapters)
				else {
					// Handle verse chapters, in case this is following a verse and comma
					if (BfoxChapterNotSet != chapterForLooseVerses && BfoxVerseNotSet == vs1) {
						// What we though was the first chapter is actually the first verse of chapter chapterForLooseVerses
						vs1 = (BfoxVerse) ch1;
						ch1 = chapterForLooseVerses;
					}
					
					[ref.verseList addVersesFromChapter:ch1
												  verse:vs1
											  toChapter:ch2
												  verse:vs2
											 withinBook:book];
					chapterForLooseVerses = ch2;
				}
			}
		}
	}
}

- (NSString *)regexPattern {
	NSString *bookRegexKey;
	if (parseForward) {
		NSString *bookRegexKeys[] = {BfoxBookRegexForwardLevel1, BfoxBookRegexForwardLevel2, BfoxBookRegexForwardLevel3};
		bookRegexKey = bookRegexKeys[maxSynonymLevel];
	}
	else {
		NSString *bookRegexKeys[] = {BfoxBookRegexReverseLevel1, BfoxBookRegexReverseLevel2, BfoxBookRegexReverseLevel3};
		bookRegexKey = bookRegexKeys[maxSynonymLevel];
	}
	NSString *bookRegex = NSLocalizedStringFromTable(bookRegexKey, @"BfoxBookRegexes", @"BfoxBookRegexes");
	
	NSString *chapterVerseQuestionMark;
	if (allowWholeBooks) chapterVerseQuestionMark = @"?";
	else chapterVerseQuestionMark = @"";
	
	NSString *spaceBeforeChapterVerseStar;
	if (requireSpaceBeforeChapterVerse) spaceBeforeChapterVerseStar = @"+";
	else spaceBeforeChapterVerseStar = @"*";
	
	// Regex = word boundary, book regex, word boundary, CV regex
	// CV regex = optional period, optional whitespace, number, optional [\s-:,;] ending with number
	if (parseForward) return [NSString stringWithFormat:@"\\b(%@)\\b(\\.?\\s%@\\d([\\s-:,;]*\\d)*)%@", bookRegex, spaceBeforeChapterVerseStar, chapterVerseQuestionMark];
	return [NSString stringWithFormat:@"((\\d[\\s-:,;]*)*\\d\\s%@\\.?)%@\\b(%@)\\b", spaceBeforeChapterVerseStar, chapterVerseQuestionMark, bookRegex];
}

@end
