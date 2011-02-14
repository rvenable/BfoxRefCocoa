//
//  BfoxVerseList.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "bfox_verse_list.h"
#import "bfox_bible_meta.h"

@interface BfoxVerseList : NSObject {
	Bfox::VerseList *verse_list;
}

+ (BfoxVerseList *)verseListForString:(NSString *)verseListString;
- (Bfox::VerseList *)verse_list;
- (void)set_verse_list:(Bfox::VerseList *)new_verse_list;
- (void)addVerseList:(BfoxVerseList *)verseList;
- (void)addVersesFromBook:(BfoxBook)book1 toBook:(BfoxBook)book2;
- (void)addVersesForFullBook:(BfoxBook)book;
- (void)addVersesFromVerse:(BfoxVerse)verse1 toVerse:(BfoxVerse)verse2 withinChapter:(BfoxChapter)chapter ofBook:(BfoxBook)book;
- (void)addVersesFromChapter:(BfoxChapter)chapter1 verse:(BfoxVerse)verse1 toChapter:(BfoxChapter)chapter2 verse:(BfoxVerse)verse2 withinBook:(BfoxBook)book;
- (void)addVerseRangeForBook:(BfoxBook)book fromChapter:(BfoxChapter)chapter1 verse:(BfoxVerse)verse1 toChapter:(BfoxChapter)chapter2 verse:(BfoxVerse)verse2;
- (Boolean)hasVerses;
- (NSMutableArray *)arrayOfRefsCutAtRangeBorder:(BfoxVerseIndex)rangeBorder withOffset:(NSUInteger)offset;
+ (NSString *)nameOfBook:(BfoxBook)book forBookNameKeyBase:(NSString *)bookNameKeyBase inTable:(NSString *)bookNameTable;
- (BfoxVerseIndex)firstVerseIndex;
- (BfoxVerseIndex)lastVerseIndex;
- (NSString *)numberStringForFirstBook;

@end
