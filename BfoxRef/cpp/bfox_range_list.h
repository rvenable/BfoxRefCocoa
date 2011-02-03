/*
 *  bfox_range_list.h
 *  BfoxRef
 *
 *  Created by Richard Venable on 1/31/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#ifndef BFOX_RANGE_LIST_H_
#define BFOX_RANGE_LIST_H_

#include <list>

namespace Bfox {
	struct Range {
		unsigned int first;
		unsigned int last;
	};
	
	struct RangeList : public std::list<Range> {	
	public:
		virtual RangeList *new_list() { return new RangeList(); };
		bool add_range(Range range, bool test_only);
		bool add_range_list(RangeList *new_range_list, bool test_only);
		std::list<RangeList *> cut_at_range_borders(unsigned int range_size, unsigned int range_offset);
	};
}

#endif // BFOX_RANGE_LIST_H_
