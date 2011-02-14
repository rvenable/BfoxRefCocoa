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
	self = [super init];
	if (self) {
		verse_list = new Bfox::VerseList();
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

#pragma mark -
#pragma mark Add verses manually (mainly used by BfoxRefParser)

- (void)addVersesFromBook:(BfoxBook)book1 toBook:(BfoxBook)book2 {
	verse_list->add_verse_range(book1, BfoxFirstChapterForFullBook, BfoxFirstVerseForFullChapter,
								book2, BfoxLastChapterForFullBook, BfoxLastVerseForFullChapter,
								false);
}

- (void)addVersesForFullBook:(BfoxBook)book {
	[self addVersesFromChapter:BfoxFirstChapterForFullBook
						 verse:BfoxFirstVerseForFullChapter
					 toChapter:BfoxLastChapterForFullBook
						 verse:BfoxLastVerseForFullChapter
					withinBook:book];
}

- (void)addVersesFromVerse:(BfoxVerse)verse1 toVerse:(BfoxVerse)verse2 withinChapter:(BfoxChapter)chapter ofBook:(BfoxBook)book {
	if (BfoxVerseNotSet == verse2) verse2 = verse1;
	[self addVersesFromChapter:chapter
						 verse:verse1
					 toChapter:chapter
						 verse:verse2
					withinBook:book];
}

- (void)addVersesFromChapter:(BfoxChapter)chapter1 verse:(BfoxVerse)verse1 toChapter:(BfoxChapter)chapter2 verse:(BfoxVerse)verse2 withinBook:(BfoxBook)book {
	[self addVerseRangeForBook:book
				   fromChapter:chapter1
						 verse:verse1
					 toChapter:chapter2
						 verse:verse2];
}

- (void)addVerseRangeForBook:(BfoxBook)book fromChapter:(BfoxChapter)chapter1 verse:(BfoxVerse)verse1 toChapter:(BfoxChapter)chapter2 verse:(BfoxVerse)verse2 {
	verse_list->add_verse_range(book, chapter1, verse1,
								book, chapter2, verse2,
								false);
}

- (Boolean)hasVerses {
	return !verse_list->empty();
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

+ (NSString *)nameOfBook:(BfoxBook)book forBookNameKeyBase:(NSString *)bookNameKeyBase inTable:(NSString *)bookNameTable {
	NSString *bookNameKey = [bookNameKeyBase stringByAppendingFormat:@"%d", book];
	NSString *bookName = NSLocalizedStringFromTable(bookNameKey, bookNameTable, @"nameOfBookWithStyle");
	return bookName;
}

- (BfoxVerseIndex)firstVerseIndex {
	Bfox::Range front_range = verse_list->ranges.front();
	return (BfoxVerseIndex)front_range.first;
}

- (BfoxVerseIndex)lastVerseIndex {
	Bfox::Range front_range = verse_list->ranges.front();
	return (BfoxVerseIndex)front_range.last;
}

- (NSString *)numberStringForFirstBook {
	std::string number_str = verse_list->number_string_for_first_book("; ", "-", ":", ",", "-");
	const char *c_str = number_str.c_str();
	NSString *numString = [NSString stringWithCString:c_str encoding:NSASCIIStringEncoding];
	return numString;
}

@end
