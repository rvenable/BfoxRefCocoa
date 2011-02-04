//
//  NSString+BfoxRef.m
//  BfoxRef
//
//  Created by Richard Venable on 2/3/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "NSString+BfoxRef.h"


@implementation NSString (BfoxRef)

- (NSString *)reversedString {
	return [self stringByFoldingWithOptions:NSBackwardsSearch locale:nil];
}

- (NSString *)stringWithoutWhitespace {
	return [self stringWithWhitespaceReplacedByString:@""];
}

- (NSString *)stringWithWhitespaceReplacedByString:(NSString *)replacement {
	return [self stringWithCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet] replacedByString:replacement];
}

- (NSString *)stringWithCharactersInSet:(NSCharacterSet *)characterSet replacedByString:(NSString *)replacement {
	return [[self componentsSeparatedByCharactersInSet:characterSet] componentsJoinedByString:replacement];
}


@end
