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
	Bfox::Range range;
	range.first = verse_list->create_first_verse_index(book1, BfoxFirstChapterForFullBook, BfoxFirstVerseForFullChapter);
	range.last = verse_list->create_last_verse_index(book2, BfoxLastChapterForFullBook, BfoxLastVerseForFullChapter);
	
	verse_list->add_range(range, false);
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
	Bfox::Range range;
	range.first = verse_list->create_first_verse_index(book, chapter1, verse1);
	range.last = verse_list->create_last_verse_index(book, chapter2, verse2);
	
	verse_list->add_range(range, false);
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

- (NSMutableArray *)arrayOfRefsByBooks {
	return [self arrayOfRefsCutAtRangeBorder:BfoxVerseIndexForBCV(BfoxFirstBookInBible, BfoxChapterNotSet, BfoxVerseNotSet) withOffset:0];
}

- (NSMutableArray *)arrayOfRefsByChapter {
	return [self arrayOfRefsCutAtRangeBorder:BfoxVerseIndexForBCV(BfoxBookNotSet, BfoxFirstChapterInBook, BfoxVerseNotSet) withOffset:0];
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
	static NSString *bookNameKeys[BfoxBookNameStyleCount] = {@"BfoxBookNameDefaultForBook", @"BfoxBookNameShortForBook"};
	static NSString *bookNameTables[BfoxBookNameStyleCount] = {@"BfoxBookNamesDefault", @"BfoxBookNamesShort"};
	NSString *bookNameKeyBase = bookNameKeys[style];
	NSString *bookNameTable = bookNameTables[style];
	NSString *bookNameKey = [bookNameKeyBase stringByAppendingFormat:@"%d", book];
	NSString *bookName = NSLocalizedStringFromTable(bookNameKey, bookNameTable, @"nameOfBookWithStyle");
	return bookName;
}

- (NSString *)stringForBookNameStyle:(BfoxBookNameStyle)bookNameStyle {
	NSArray *refsByBooks = [self arrayOfRefsByBooks];
	NSMutableString *refString = [NSMutableString string];
	NSUInteger index = 0;
	for (BfoxRef *ref in refsByBooks) {
		if (index) [refString appendString:@"; "];
		NSString *bookName = [BfoxVerseList nameOfBook:[ref.verseList firstBook] withStyle:bookNameStyle];
		NSString *numberString = [ref.verseList numberStringForFirstBook];
		[refString appendFormat:@"%@ %@", bookName, numberString];
		index++;
	}
	
	return refString;
}

- (BfoxBook)firstBook {
	Bfox::Range front_range = verse_list->front();
	return BfoxBookForVerseIndex(front_range.first);
}

- (NSString *)numberStringForFirstBook {
	std::string number_str = verse_list->number_string_for_first_book("; ", "-", ":", ",", "-");
	const char *c_str = number_str.c_str();
	NSString *numString = [NSString stringWithCString:c_str encoding:NSASCIIStringEncoding];
	return numString;
}

@end
