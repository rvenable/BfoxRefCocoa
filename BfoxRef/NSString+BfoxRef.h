//
//  NSString+BfoxRef.h
//  BfoxRef
//
//  Created by Richard Venable on 2/3/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface NSString (BfoxRef)

- (NSString *)reversedString;
- (NSString *)stringWithoutWhitespace;
- (NSString *)stringWithWhitespaceReplacedByString:(NSString *)replacement;
- (NSString *)stringWithCharactersInSet:(NSCharacterSet *)characterSet replacedByString:(NSString *)replacement;

@end
