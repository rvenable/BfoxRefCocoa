/*
 *  bfox_verse_list.cpp
 *  BfoxRef
 *
 *  Created by Richard Venable on 2/1/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#include "bfox_verse_list.h"
#include "bfox_book_meta.h"
#include <sstream>

bool Bfox::VerseList::add_range(Bfox::Range range, bool test_only = false) {
	return this->add_verse_range(BfoxBookForVerseIndex(range.first), BfoxChapterForVerseIndex(range.first), BfoxVerseForVerseIndex(range.first),
								 BfoxBookForVerseIndex(range.last), BfoxChapterForVerseIndex(range.last), BfoxVerseForVerseIndex(range.last),
								 test_only);
}

bool Bfox::VerseList::add_verse_range(BfoxBook book1, BfoxChapter chapter1, BfoxVerse verse1,
									  BfoxBook book2, BfoxChapter chapter2, BfoxVerse verse2,
									  bool test_only = false) {
	Bfox::Range range;
	range.first = this->create_first_verse_index(book1, chapter1, verse1);
	range.last = this->create_last_verse_index(book2, chapter2, verse2);

	if (range.first == BfoxVerseIndexNotSet || range.last == BfoxVerseIndexNotSet) return false;
	
	return Bfox::RangeList::add_range(range, test_only);
}

BfoxVerseIndex Bfox::VerseList::create_first_verse_index(BfoxBook book1, BfoxChapter chapter1, BfoxVerse verse1) {
	/*
	 * Maximize bible reference before we actually add them to the sequence list
	 */
	
	// Adjust verse1 to be zero if it is one
	if (BfoxFirstVerseInChapter == verse1)
		verse1 = BfoxFirstVerseForFullChapter;
	
	// Adjust chapter1 to zero if this is the first verse of the first chapter
	if ((BfoxFirstChapterInBook == chapter1) && (BfoxFirstVerseForFullChapter == verse1))
		chapter1 = BfoxFirstChapterForFullBook;
	
	// If the start verse is greater than the last verse of the chapter, try to start with the next chapter
	// So, 'Haggai 1:100-2:4' should become 'Haggai 2:1-4'
	if (verse1 > BfoxLastVerseInChapter(book1, chapter1)) {
		verse1 = BfoxFirstVerseForFullChapter;
		if (BfoxChapterMax > chapter1) chapter1 = (BfoxChapter) (chapter1 + 1);
	}
	
	// If the start chapter is greater than the last chapter of the book, this isn't a valid sequence
	if (BfoxLastBookInBible < book1 || BfoxLastChapterInBook(book1) < chapter1 || BfoxLastVerseInChapter(book1, chapter1) < verse1) {
		return BfoxVerseIndexNotSet;
	}
	
	return BfoxVerseIndexForBCV(book1, chapter1, verse1);
}

BfoxVerseIndex Bfox::VerseList::create_last_verse_index(BfoxBook book2, BfoxChapter chapter2, BfoxVerse verse2) {
	/*
	 * Maximize bible reference before we actually add them to the sequence list
	 */
	
	// Adjust verse2 to be max_verse_id if it is greater than equal to the earliest possible end verse for chapter2,
	// or if chapter2 is greater than the end chapter for this verse
	if ((verse2 >= BfoxEarliestLastVerseInChapter(book2, chapter2)) || (chapter2 > BfoxLastChapterInBook(book2)))
		verse2 = BfoxLastVerseForFullChapter;
	
	// Adjust chapter2 to be max_chapter_id if it is greater than or equal to the last chapter of this book
	if ((BfoxLastVerseForFullChapter == verse2) && (chapter2 >= BfoxLastChapterInBook(book2)))
		chapter2 = BfoxLastChapterForFullBook;
	
	// If the start chapter is greater than the last chapter of the book, this isn't a valid sequence
	if (BfoxFirstBookInBible > book2 || BfoxFirstChapterInBook > chapter2 || BfoxFirstVerseInChapter > verse2) {
		return BfoxVerseIndexNotSet;
	}
	
	return BfoxVerseIndexForBCV(book2, chapter2, verse2);
}

std::string Bfox::VerseList::number_string_for_first_book(const char *separate_chapters_str = "; ",
												   const char *connect_chapters_str = "-",
												   const char *connect_chapter_to_verse_str = ":",
												   const char *separate_verses_str = ",",
												   const char *connect_verses_str = "-") {
	BfoxBook book = BfoxBookNotSet;
	BfoxChapter prev_ch = BfoxChapterNotSet;
	std::stringstream str;
	for (std::list<Bfox::Range>::iterator it = this->ranges.begin(); it != this->ranges.end(); it++) {
		Bfox::Range range = *it;

		// Keep track of the book, so that if we reach a range that is in a different book, we can break
		if (BfoxBookNotSet == book) {
			book = BfoxBookForVerseIndex(range.first);
		}
		else if (BfoxBookForVerseIndex(range.first) != book) break;
		
		BfoxChapter ch1 = BfoxChapterForVerseIndex(range.first);
		BfoxVerse vs1 = BfoxVerseForVerseIndex(range.first);
		BfoxChapter ch2 = BfoxChapterForVerseIndex(range.last);
		BfoxVerse vs2 = BfoxVerseForVerseIndex(range.last);
		
		// If this range goes into the next book, just stop it at the end of this book
		if (BfoxBookForVerseIndex(range.last) != book) {
			ch2 = BfoxLastChapterForFullBook;
			vs2 = BfoxLastVerseForFullChapter;
		}
		
		// If chapter1 is 0, then this is either a whole book, or needs to begin at chapter 1
		if (BfoxFirstChapterForFullBook == ch1) {
			if (BfoxLastChapterForFullBook == ch2) return (std::string)"";
			else ch1 = BfoxFirstChapterInBook;
		}
		
		bool is_whole_chapters = false;
		
		// If verse1 is 0, then this is either a whole chapter(s), or needs to begin at verse 1
		if (BfoxFirstVerseForFullChapter == vs1) {
			if (BfoxLastVerseForFullChapter == vs2) is_whole_chapters = true;
			else vs1 = BfoxFirstVerseInChapter;
		}
		
		// Adjust the end chapter and verse to be the actual maximum chapter/verse we can display
		ch2 = std::min(ch2, BfoxLastChapterInBook(book));
		vs2 = std::min(vs2, BfoxLastVerseInChapter(book, ch2));
		
		if (ch1 != prev_ch) {
			if (!str.str().empty()) str << separate_chapters_str;
			
			// Whole Chapters
			if (is_whole_chapters) {
				str << ch1;
				if (ch1 != ch2) str << connect_chapters_str << ch2;
			}
			// Inner Chapters
			else if (ch1 == ch2) {
				str << ch1 << connect_chapter_to_verse_str << vs1;
				if (vs1 != vs2) str << connect_verses_str << vs2;
			}
			// Mixed Chapters
			else {
				str << ch1;
				if (BfoxFirstVerseInChapter != vs1) str << connect_chapter_to_verse_str << vs1;
				str << connect_chapters_str << ch2 << connect_chapter_to_verse_str << vs2;
			}
		}
		else {
			str << separate_verses_str << vs1;
			// Inner Chapters
			if (ch1 == ch2) {
				if (vs1 != vs2) str << connect_verses_str << vs2;
			}
			// Mixed Chapters
			else {
				str << connect_chapters_str << ch2 << connect_chapter_to_verse_str << vs2;
			}
		}
		
		prev_ch = ch2;
	}
	
	return str.str();
}

