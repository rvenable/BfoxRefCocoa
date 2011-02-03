//
//  BfoxVerseList.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "bfox_verse_list.h"
#include "bfox_book_meta.h"

@interface BfoxVerseList : NSObject {
	Bfox::VerseList *verse_list;
}

+ (BfoxVerseList *)verseListForString:(NSString *)verseListString;
- (Bfox::VerseList *)verse_list;
- (void)set_verse_list:(Bfox::VerseList *)new_verse_list;
- (void)addVerseList:(BfoxVerseList *)verseList;
- (NSMutableArray *)arrayOfRefsCutAtRangeBorder:(BfoxVerseIndex)rangeBorder withOffset:(NSUInteger)offset;
- (BfoxBook)firstBook;
- (NSString *)numberStringForFirstBook;

@end
