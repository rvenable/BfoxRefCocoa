//
//  BfoxRef.m
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxRef.h"
#import "BfoxVerseList.h"
#import "BfoxRefParser.h"

@implementation BfoxRef

@synthesize verseList;

- (id)init {
	self = [super init];
	if (self) {
		self.verseList = [[[BfoxVerseList alloc] init] autorelease];
	}
	return self;
}

- (void)dealloc {
	[verseList release];
	[super dealloc];
}

+ (BfoxRef *)ref {
	return [[[BfoxRef alloc] init] autorelease];
}

+ (BfoxRef *)refWithString:(NSString *)refString {
	BfoxRef *newRef = [BfoxRef ref];
	[newRef addString:refString];
	return newRef;
}

+ (BfoxRef *)refWithRef:(BfoxRef *)ref {
	BfoxRef *newRef = [BfoxRef ref];
	[newRef addRef:ref];
	return newRef;
}

+ (BfoxRef *)refWithVerseList:(BfoxVerseList *)newVerseList {
	BfoxRef *newRef = [BfoxRef ref];
	newRef.verseList = newVerseList;
	return newRef;
}

- (void)addString:(NSString *)refString {
	BfoxRefParser *parser = [[[BfoxRefParser alloc] init] autorelease];
	[parser setParseForward:YES];
	[parser setAllowWholeBooks:YES];
	[parser setMaxSynonymLevel:BfoxBookSynonymLevelLoosest];
	parser.cumulativeRef = self;
	[parser parseString:refString];
}

- (void)addRef:(BfoxRef *)ref {
	[verseList addVerseList:ref.verseList];
}

- (void)addEntireBible {
	[verseList addVersesFromBook:BfoxBookGenesis toBook:BfoxBookRevelation];
}

- (void)addOldTestament {
	[verseList addVersesFromBook:BfoxBookGenesis toBook:BfoxBookMalachi];
}

- (void)addNewTestament {
	[verseList addVersesFromBook:BfoxBookMatthew toBook:BfoxBookRevelation];
}

- (Boolean)hasVerses {
	return [verseList hasVerses];
}

- (NSString *)description {
	return [self refString];
}

- (NSString *)refString {
	return [self stringForBookNameStyle:BfoxBookNameStyleDefault];
}

- (NSString *)shortRefString {
	return [self stringForBookNameStyle:BfoxBookNameStyleShort];
}

- (NSString *)stringForBookNameStyle:(BfoxBookNameStyle)bookNameStyle {
	static NSString *bookNameKeys[BfoxBookNameStyleCount] = {@"BfoxBookNameDefaultForBook", @"BfoxBookNameShortForBook"};
	static NSString *bookNameTables[BfoxBookNameStyleCount] = {@"BfoxBookNamesDefault", @"BfoxBookNamesShort"};
	NSString *bookNameKeyBase = bookNameKeys[bookNameStyle];
	NSString *bookNameTable = bookNameTables[bookNameStyle];

	NSArray *refsByBooks = [self arrayOfRefsByBooks];
	NSMutableString *refString = [NSMutableString string];
	NSUInteger index = 0;
	for (BfoxRef *ref in refsByBooks) {
		if (index) [refString appendString:@"; "];
		NSString *bookName = [BfoxVerseList nameOfBook:[ref.verseList firstBook] forBookNameKeyBase:bookNameKeyBase inTable:bookNameTable];
		NSString *numberString = [ref.verseList numberStringForFirstBook];
		
		if (numberString && [numberString length]) [refString appendFormat:@"%@ %@", bookName, numberString];
		else [refString appendString:bookName];
		
		index++;
	}
	
	return refString;
}

- (NSMutableArray *)arrayOfRefsByBooks {
	return [verseList arrayOfRefsCutAtRangeBorder:BfoxVerseIndexForBCV(BfoxFirstBookInBible, BfoxChapterNotSet, BfoxVerseNotSet) withOffset:0];
}

- (NSMutableArray *)arrayOfRefsByChapter {
	return [verseList arrayOfRefsCutAtRangeBorder:BfoxVerseIndexForBCV(BfoxBookNotSet, BfoxFirstChapterInBook, BfoxVerseNotSet) withOffset:0];
}

- (NSMutableArray *)arrayOfRefsWithChapterSize:(NSUInteger)chapterSize {
	NSArray *refsByChapter = [self arrayOfRefsByChapter];
	NSMutableArray *array = [NSMutableArray arrayWithCapacity:ceil([refsByChapter count] / (double) chapterSize)];
	BfoxRef *currentRef = [BfoxRef ref];
	NSUInteger counter = 0;
	for (BfoxRef *ref in refsByChapter) {
		[currentRef addRef:ref];
		counter++;
		if (counter == chapterSize) {
			counter = 0;
			[array addObject:currentRef];
			currentRef = [BfoxRef ref];
		}
	}
	if (counter) {
		[array addObject:currentRef];
	}
	
	return [NSArray arrayWithArray:array];
}

@end
