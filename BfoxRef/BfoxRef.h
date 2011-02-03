//
//  BfoxRef.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "bfox_book_meta.h"

typedef enum {
	BfoxBookNameStyleDefault,
	BfoxBookNameStyleShort,
} BfoxBookNameStyle;

@class BfoxVerseList;

@interface BfoxRef : NSObject {
	BfoxVerseList *verseList;
}

@property (nonatomic, retain) BfoxVerseList *verseList;

+ (BfoxRef *)ref;
+ (BfoxRef *)refWithRef:(BfoxRef *)ref;
+ (BfoxRef *)refWithVerseList:(BfoxVerseList *)newVerseList;
- (void)addRef:(BfoxRef *)ref;
- (NSMutableArray *)arrayOfRefsByBooks;
- (NSMutableArray *)arrayOfRefsByChapter;
- (NSMutableArray *)arrayOfRefsWithChapterSize:(NSUInteger)chapterSize;
+ (NSString *)nameOfBook:(BfoxBook)book withStyle:(BfoxBookNameStyle)style;
- (NSString *)stringForBookNameStyle:(BfoxBookNameStyle)bookNameStyle;


@end
