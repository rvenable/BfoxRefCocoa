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

- (Boolean)hasVerses {
	return [verseList hasVerses];
}

- (NSString *)description {
	return [verseList stringForBookNameStyle:BfoxBookNameStyleDefault];
}

@end
