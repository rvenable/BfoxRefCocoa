//
//  BfoxRefParser.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "bfox_bible_meta.h"

extern NSString *const BfoxBookRegexForwardLevel1;
extern NSString *const BfoxBookRegexForwardLevel2;
extern NSString *const BfoxBookRegexForwardLevel3;
extern NSString *const BfoxBookRegexReverseLevel1;
extern NSString *const BfoxBookRegexReverseLevel2;
extern NSString *const BfoxBookRegexReverseLevel3;

typedef enum {
	BfoxBookIndexForSingleBook,
	BfoxBookIndexForFirstInSeries,
	BfoxBookIndexForSecondInSeries,
	BfoxBookIndexForThirdInSeries,
	BfoxBookIndexBySeriesCount
} BfoxBookIndexBySeries;

typedef enum {
	BfoxBookSynonymLevel1,
	BfoxBookSynonymLevel2,
	BfoxBookSynonymLevel3,
	BfoxBookSynonymLevelCount,
	
	BfoxBookSynonymLevelStrictest = BfoxBookSynonymLevel1,
	BfoxBookSynonymLevelLoosest = BfoxBookSynonymLevel3,
} BfoxBookSynonymLevel;

@class BfoxRef;

@interface BfoxRefParser : NSObject {
	BfoxRef *cumulativeRef;
	NSMutableArray *arrayOfRefs;

	BfoxBookSynonymLevel maxSynonymLevel;
	Boolean parseForward;
	Boolean allowWholeBooks;
	Boolean requireSpaceBeforeChapterVerse;
}

@property (nonatomic, assign) BfoxRef *cumulativeRef;
@property (nonatomic, assign) NSMutableArray *arrayOfRefs;

@property (nonatomic) BfoxBookSynonymLevel maxSynonymLevel;
@property (nonatomic) Boolean parseForward;
@property (nonatomic) Boolean allowWholeBooks;
@property (nonatomic) Boolean requireSpaceBeforeChapterVerse;

- (void)setMaxSynonymLevel:(BfoxBookSynonymLevel)newMaxSynonymLevel;
- (void)setParseForward:(Boolean)newParseForward;
- (void)setAllowWholeBooks:(Boolean)newAllowWholeBooks;
- (void)setRequireSpaceBeforeChapterVerse:(Boolean)newRequireSpaceBeforeChapterVerse;

- (BfoxBook)bookForLowercaseSynonym:(NSString *)lowercaseSynonym;

- (void)parseString:(NSString *)stringToParse;
- (void)parseChapterVerseString:(NSString *)chapterVerseString forBook:(BfoxBook)book andAddVersesToRef:(BfoxRef *)ref;
- (NSString *)regexPattern;

@end
