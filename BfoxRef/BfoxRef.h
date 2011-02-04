//
//  BfoxRef.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BfoxVerseList;

@interface BfoxRef : NSObject {
	BfoxVerseList *verseList;
}

@property (nonatomic, retain) BfoxVerseList *verseList;

+ (BfoxRef *)ref;
+ (BfoxRef *)refWithString:(NSString *)refString;
+ (BfoxRef *)refWithRef:(BfoxRef *)ref;
+ (BfoxRef *)refWithVerseList:(BfoxVerseList *)newVerseList;

- (void)addString:(NSString *)refString;
- (void)addRef:(BfoxRef *)ref;

- (Boolean)hasVerses;

@end
