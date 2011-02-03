/*
 *  bfox_book_meta.h
 *  BfoxRef
 *
 *  Created by Richard Venable on 1/31/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#ifndef BFOX_BOOK_META_H_
#define BFOX_BOOK_META_H_

typedef unsigned int BfoxVerseIndex;
typedef unsigned char BfoxBCV;
const BfoxBCV BfoxBCVInvalid = 0xFF;

typedef enum {
	BfoxBookNotSet = 0,
	BfoxBookGenesis,
	BfoxBookCount,
	
	BfoxFirstBookInBible = BfoxBookGenesis,
	BfoxLastBookInBible = BfoxBookCount - 1,
	
	BfoxBookMax = 0xFF,
	
	BfoxFirstBookForFullBible = BfoxBookNotSet,
	BfoxLastBookForFullBible = BfoxBookMax
} BfoxBook;

typedef enum {
	BfoxChapterNotSet = 0,
	BfoxFirstChapterInBook,
	
	BfoxChapterMax = 0xFF,
	
	BfoxFirstChapterForFullBook = BfoxChapterNotSet,
	BfoxLastChapterForFullBook = BfoxChapterMax
} BfoxChapter;

typedef enum {
	BfoxVerseNotSet = 0,
	BfoxFirstVerseInChapter,
	
	BfoxVerseMax = 0xFF,
	
	BfoxFirstVerseForFullChapter = BfoxVerseNotSet,
	BfoxLastVerseForFullChapter = BfoxVerseMax
} BfoxVerse;

typedef struct {
	unsigned int min_verse_count;
	unsigned int max_verse_count;
} BfoxChapterMeta;

typedef struct {
	unsigned int chapter_count;
	BfoxChapterMeta chapter_metas[];
} BfoxBookMeta;

const BfoxBookMeta BfoxBookMetaArray[BfoxBookCount] = {
	{ 0, {} },
	{ 50, {} }
};

static inline BfoxVerseIndex BfoxVerseIndexForBCV(BfoxBook book, BfoxChapter chapter, BfoxVerse verse) {
	return book << 16 + chapter << 8 + verse;
}

static inline BfoxBook BfoxBookForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxBook) ((verseIndex >> 16) % BfoxBookMax);
}

static inline BfoxChapter BfoxChapterForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxChapter) ((verseIndex >> 8) % BfoxChapterMax);
}

static inline BfoxVerse BfoxVerseForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxVerse) (verseIndex % BfoxVerseMax);
}

static inline BfoxBCV BfoxPassageEnd(BfoxBook book, BfoxChapter chapter, bool is_earliest) {
	if (BfoxBookNotSet == book) return BfoxBookCount;
	if (book < BfoxBookCount) {
		const BfoxBookMeta *book_meta = &(BfoxBookMetaArray[book]);
		if (BfoxChapterNotSet == chapter) return book_meta->chapter_count;
		if (chapter < book_meta->chapter_count) {
			const BfoxChapterMeta *chapter_meta = &(book_meta->chapter_metas[chapter]);
			if (!is_earliest && chapter_meta->max_verse_count) return chapter_meta->max_verse_count;
			return chapter_meta->min_verse_count;
		}
	}
	return BfoxChapterNotSet;
}

static inline BfoxChapter BfoxLastChapterInBook(BfoxBook book) {
	return (BfoxChapter) (BfoxPassageEnd(book, BfoxChapterNotSet, false));
}

static inline BfoxVerse BfoxLastVerseInChapter(BfoxBook book, BfoxChapter chapter) {
	return (BfoxVerse) (BfoxPassageEnd(book, chapter, false));
}

static inline BfoxVerseIndex PreviousVerseIndex(BfoxVerseIndex verseIndex) {
	return 0;
}

#endif // BFOX_BOOK_META_H_
