//
//  BfoxVerseList+CoreData.m
//  BiblefoxBrowser
//
//  Created by Richard Venable on 4/13/11.
//  Copyright 2011 Epicfox. All rights reserved.
//

#import "BfoxVerseList+CoreData.h"

@implementation BfoxVerseList (CoreData)

- (NSMutableArray *)insertEntitiesForName:(NSString *)entityName
				   inManagedObjectContext:(NSManagedObjectContext *)managedObjectContext
					  withFirstVerseField:(NSString *)firstVerseField
						andLastVerseField:(NSString *)lastVerseField
{
	NSMutableArray *entities = [NSMutableArray arrayWithCapacity:verse_list->ranges.size()];
	for (std::list<Bfox::Range>::iterator it = verse_list->ranges.begin(); it != verse_list->ranges.end(); it++) {
		Bfox::Range range = *it;

		id entity = [NSEntityDescription insertNewObjectForEntityForName:entityName inManagedObjectContext:managedObjectContext];
		[entity setValue:[NSNumber numberWithInt:range.first] forKey:firstVerseField];
		[entity setValue:[NSNumber numberWithInt:range.last] forKey:lastVerseField];
		[entities addObject:entity];
	}
	
	return entities;
}

@end
