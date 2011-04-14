//
//  BfoxVerseList+CoreData.h
//  BiblefoxBrowser
//
//  Created by Richard Venable on 4/13/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>
#import "BfoxVerseList.h"

@interface BfoxVerseList (CoreData)

- (NSMutableArray *)insertEntitiesForName:(NSString *)entityName
				   inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext
					  withFirstVerseField:(NSString *)firstVerseField
						andLastVerseField:(NSString *)lastVerseField;

@end
