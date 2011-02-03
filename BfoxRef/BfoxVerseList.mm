//
//  BfoxVerseList.m
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxVerseList.h"
#import "BfoxRef.h"

@implementation BfoxVerseList

- (id)init {
	if (self = [super init]) {
		verse_list = NULL;
	}
	return self;
}

- (void)dealloc {
	[self set_verse_list:NULL];
	
	[super dealloc];
}

+ (BfoxVerseList *)verseListForString:(NSString *)verseListString {
	return [[[BfoxVerseList alloc] init] autorelease];
}

- (Bfox::VerseList *)verse_list {
	return verse_list;
}

- (void)set_verse_list:(Bfox::VerseList *)new_verse_list {
	if (verse_list) delete verse_list;
	verse_list = new_verse_list;
}

- (void)addVerseList:(BfoxVerseList *)verseList {
	Bfox::RangeList *range_list = [verseList verse_list];
	verse_list->add_range_list(range_list, false);
}

- (NSMutableArray *)arrayOfRefsCutAtRangeBorder:(BfoxVerseIndex)rangeBorder withOffset:(NSUInteger)offset {
	std::list<Bfox::RangeList *> list_of_verse_lists = verse_list->cut_at_range_borders(rangeBorder, offset);
	
	NSMutableArray *array = [NSMutableArray arrayWithCapacity:(NSUInteger)list_of_verse_lists.size()];
	for (std::list<Bfox::RangeList *>::iterator it = list_of_verse_lists.begin(); it != list_of_verse_lists.end(); it++) {
		Bfox::RangeList *new_range_list = *it;

		Bfox::VerseList *new_verse_list = dynamic_cast<Bfox::VerseList *> (new_range_list);
		if (new_verse_list) {
			BfoxVerseList *newVerseList = [[[BfoxVerseList alloc] init] autorelease];
			[newVerseList set_verse_list:new_verse_list];
			[array addObject:[BfoxRef refWithVerseList:newVerseList]];
		}
		else {
			delete new_range_list;
		}
	}
	
	return array;
}

- (BfoxBook)firstBook {
	Bfox::Range front_range = verse_list->front();
	return BfoxBookForVerseIndex(front_range.first);
}

- (NSString *)numberStringForFirstBook {
	std::string number_str = verse_list->number_string_for_first_book("; ", "-", ":", ",", "-");
	return [NSString stringWithCString:number_str.c_str() encoding:NSASCIIStringEncoding];
}

@end
