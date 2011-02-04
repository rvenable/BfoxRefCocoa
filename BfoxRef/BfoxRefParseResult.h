//
//  BfoxRefParseResult.h
//  BfoxRef
//
//  Created by Richard Venable on 2/2/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface BfoxRefParseResult : NSObject {
	NSString *baseString;
	NSTextCheckingResult *textCheckingResult;
}

@property (nonatomic, assign) NSString *baseString;
@property (nonatomic, assign) NSTextCheckingResult *textCheckingResult;

- (NSString *)stringAtIndex:(NSUInteger)idx;

@end
