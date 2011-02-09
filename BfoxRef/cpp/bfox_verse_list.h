/*
 *  bfox_verse_list.h
 *  BfoxRef
 *
 *  Created by Richard Venable on 2/1/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#ifndef BFOX_VERSE_LIST_H_
#define BFOX_VERSE_LIST_H_

#include "bfox_range_list.h"
#include "bfox_bible_meta.h"
#include <string>

namespace Bfox {
	class VerseList : public RangeList {
	public:
		virtual RangeList *new_list() { return new VerseList(); };
		BfoxVerseIndex create_first_verse_index(BfoxBook book1, BfoxChapter chapter1, BfoxVerse verse1);
		BfoxVerseIndex create_last_verse_index(BfoxBook book2, BfoxChapter chapter2, BfoxVerse verse2);
		std::string number_string_for_first_book(const char *separate_chapters_str,
												 const char *connect_chapters_str,
												 const char *connect_chapter_to_verse_str,
												 const char *separate_verses_str,
												 const char *connect_verses_str);
	};
}

#endif // BFOX_VERSE_LIST_H_
