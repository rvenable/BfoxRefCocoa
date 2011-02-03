//
//  BfoxRef.m
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxRef.h"
#import "BfoxVerseList.h"

@implementation BfoxRef

@synthesize verseList;

- (id)init {
	if (self = [super init]) {
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

- (void)addRef:(BfoxRef *)ref {
	[verseList addVerseList:ref.verseList];
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

+ (NSString *)nameOfBook:(BfoxBook)book withStyle:(BfoxBookNameStyle)style {
	return @"Genesis";
}

- (NSString *)stringForBookNameStyle:(BfoxBookNameStyle)bookNameStyle {
	NSArray *refsByBooks = [self arrayOfRefsByBooks];
	NSMutableString *string;
	NSUInteger index = 0;
	for (BfoxRef *ref in refsByBooks) {
		if (index) [string appendString:@"; "];
		[string appendString:[NSString stringWithFormat:
							  @"%@ %@",
							  [BfoxRef nameOfBook:[ref.verseList firstBook] withStyle:bookNameStyle],
							  [ref.verseList numberStringForFirstBook]]];
		index++;
	}
	
	return string;
}

@end
