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

std::string Bfox::VerseList::number_string_for_first_book(const char *separate_chapters_str = "; ",
												   const char *connect_chapters_str = "-",
												   const char *connect_chapter_to_verse_str = ":",
												   const char *separate_verses_str = ",",
												   const char *connect_verses_str = "-") {
	BfoxBook book = BfoxBookNotSet;
	BfoxChapter prev_ch = BfoxChapterNotSet;
	std::stringstream str;
	for (std::list<Bfox::Range>::iterator it = this->begin(); it != this->end(); it++) {
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

