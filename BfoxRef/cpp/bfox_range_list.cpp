/*
 *  bfox_range_list.cpp
 *  BfoxRef
 *
 *  Created by Richard Venable on 1/31/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#include "bfox_range_list.h"

bool Bfox::RangeList::add_range(Bfox::Range new_range, bool test_only = false) {
	bool is_modified = false;
	bool is_finished = false;
	
	std::list<Bfox::Range> new_ranges;
	
	for (Bfox::RangeList::iterator it = this->begin(); it != this->end(); it++) {
		Bfox::Range range = *it;
		if (!is_finished) {
			
			// If the new range starts before range
			if (new_range.first < range.first) {
				// If the new range also ends before, then we've found the spot to place it
				// Otherwise, it intersects, so modify the new range to include range
				if ((new_range.last + 1) < range.first) {
					new_ranges.insert(new_ranges.end(), new_range);
					new_ranges.insert(new_ranges.end(), range);
					is_finished = true;
					is_modified = true;
				}
				else {
					if (new_range.last < range.last) {
						new_range.last = range.last;
						is_modified = true;
					}
				}
			}
			else {
				// The new range starts with or after range
				// If the new range starts before range ends, we have an intersection
				// Otherwise, we passed range without intersecting it, so add it to the array
				if ((new_range.first - 1) <= range.last) {
					// Create a new range that starts with range.first
					new_range.first = range.first;
					if (new_range.last <= range.last) {
						// The new range is within an existing range, so set the existing one and get rid of the new one
						new_ranges.insert(new_ranges.end(), range);
						is_finished = true;
					}
				}
				else {
					new_ranges.insert(new_ranges.end(), range);
				}
			}
		}
		else {
			new_ranges.insert(new_ranges.end(), range);
		}
	}
	if (!is_finished) {
		new_ranges.insert(new_ranges.end(), new_range);
		is_modified = true;
	}

	if (is_modified && !test_only) this->assign(new_ranges.begin(), new_ranges.end());
	return is_modified;
}

bool Bfox::RangeList::add_range_list(Bfox::RangeList *new_range_list, bool test_only = false) {
	bool is_modified = false;
	for (Bfox::RangeList::iterator it = new_range_list->begin(); it != new_range_list->end(); it++) {
		Bfox::Range range = *it;
		is_modified = this->add_range(range, test_only) || is_modified;
		if (is_modified && test_only) break;
	}
	return is_modified;
}

std::list<Bfox::RangeList *> Bfox::RangeList::cut_at_range_borders(unsigned int range_size, unsigned int range_offset = 0) {
	std::list<Bfox::RangeList *> list_of_lists;
	Bfox::RangeList *current_list;
	unsigned int next_range_first = 0;

	// Iterate through each range and see where it belongs in the new list of lists
	for (Bfox::RangeList::iterator it = this->begin(); it != this->end(); it++) {
		Bfox::Range range = *it;

		// Start with a multiple
		if (range.first >= next_range_first) {
			next_range_first = (1 + range.first / range_size) * range_size + range_offset;

			// Moving to a new Bfox::RangeList, so insert the old one and create a new one
			if (!current_list->empty()) {
				list_of_lists.insert(list_of_lists.end(), current_list);
				current_list = this->new_list();
			}
		}
		
		while (range.last >= next_range_first) {
			Bfox::Range new_range = {range.first, next_range_first - 1};
			current_list->insert(current_list->end(), new_range);
			
			range.first = next_range_first;
			next_range_first += range_size;

			// Moving to a new Bfox::RangeList, so insert the old one and create a new one
			if (!current_list->empty()) {
				list_of_lists.insert(list_of_lists.end(), current_list);
				current_list = this->new_list();
			}
		}
		
		current_list->insert(current_list->end(), range);
	}
	// If we still have a Bfox::RangeList to insert, do it
	if (!current_list->empty()) {
		list_of_lists.insert(list_of_lists.end(), current_list);
	}
	
	return list_of_lists;
}
