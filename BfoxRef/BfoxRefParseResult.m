//
//  BfoxRefParseResult.m
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxRefParseResult.h"


@implementation BfoxRefParseResult

@synthesize baseString, textCheckingResult;

- (NSString *)stringAtIndex:(NSUInteger)idx {
	if (baseString && textCheckingResult) return [baseString substringWithRange:[textCheckingResult rangeAtIndex:idx]];
	return @"";
}

@end
