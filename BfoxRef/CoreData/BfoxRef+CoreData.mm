//
//  BfoxRef+CoreData.m
//  BiblefoxBrowser
//
//  Created by Richard Venable on 4/13/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxRef+CoreData.h"
#import "BfoxVerseList+CoreData.h"

@implementation BfoxRef (CoreData)

- (NSMutableArray *)insertEntitiesForName:(NSString *)entityName inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext
{
	return [self insertEntitiesForName:entityName inManagedObjectContext:managedObjectContext withFirstVerseField:@"firstVerseIndex" andLastVerseField:@"lastVerseIndex"];
}

- (NSMutableArray *)insertEntitiesForName:(NSString *)entityName
				   inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext
					  withFirstVerseField:(NSString *)firstVerseField
						andLastVerseField:(NSString *)lastVerseField
{
	return [self.verseList insertEntitiesForName:entityName inManagedObjectContext:managedObjectContext withFirstVerseField:firstVerseField andLastVerseField:lastVerseField];
}


@end
