/*
 *  bfox_bible_meta.h
 *  BfoxRef
 *
 *  Created by Richard Venable on 2/3/11.
 *  Copyright 2011 Epicfox. All rights reserved.
 *
 */

#ifndef BFOX_BIBLE_META_H_
#define BFOX_BIBLE_META_H_

typedef unsigned int BfoxVerseIndex;
const BfoxVerseIndex BfoxVerseIndexNotSet = 0;
typedef unsigned char BfoxBCV;
const BfoxBCV BfoxBCVInvalid = 0xFF;

typedef enum {
	BfoxBookNotSet = 0,
	BfoxBookGenesis,
	BfoxBookExodus,
	BfoxBookLeviticus,
	BfoxBookNumbers,
	BfoxBookDeuteronomy,
	BfoxBookJoshua,
	BfoxBookJudges,
	BfoxBookRuth,
	BfoxBook1Samuel,
	BfoxBook2Samuel,
	BfoxBook1Kings,
	BfoxBook2Kings,
	BfoxBook1Chronicles,
	BfoxBook2Chronicles,
	BfoxBookEzra,
	BfoxBookNehemiah,
	BfoxBookEsther,
	BfoxBookJob,
	BfoxBookPsalm,
	BfoxBookProverbs,
	BfoxBookEcclesiastes,
	BfoxBookSongofSolomon,
	BfoxBookIsaiah,
	BfoxBookJeremiah,
	BfoxBookLamentations,
	BfoxBookEzekiel,
	BfoxBookDaniel,
	BfoxBookHosea,
	BfoxBookJoel,
	BfoxBookAmos,
	BfoxBookObadiah,
	BfoxBookJonah,
	BfoxBookMicah,
	BfoxBookNahum,
	BfoxBookHabakkuk,
	BfoxBookZephaniah,
	BfoxBookHaggai,
	BfoxBookZechariah,
	BfoxBookMalachi,
	BfoxBookMatthew,
	BfoxBookMark,
	BfoxBookLuke,
	BfoxBookJohn,
	BfoxBookActs,
	BfoxBookRomans,
	BfoxBook1Corinthians,
	BfoxBook2Corinthians,
	BfoxBookGalatians,
	BfoxBookEphesians,
	BfoxBookPhilippians,
	BfoxBookColossians,
	BfoxBook1Thessalonians,
	BfoxBook2Thessalonians,
	BfoxBook1Timothy,
	BfoxBook2Timothy,
	BfoxBookTitus,
	BfoxBookPhilemon,
	BfoxBookHebrews,
	BfoxBookJames,
	BfoxBook1Peter,
	BfoxBook2Peter,
	BfoxBook1John,
	BfoxBook2John,
	BfoxBook3John,
	BfoxBookJude,
	BfoxBookRevelation,
	BfoxBookCount = BfoxBookRevelation,
	
	BfoxFirstBookInBible = BfoxBookGenesis,
	BfoxLastBookInBible = BfoxBookRevelation,
	
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

static inline BfoxVerseIndex BfoxVerseIndexForBCV(BfoxBook book, BfoxChapter chapter, BfoxVerse verse) {
	return (book << 16) + (chapter << 8) + verse;
}

static inline BfoxBook BfoxBookForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxBook) ((verseIndex >> 16) % 0x100);
}

static inline BfoxChapter BfoxChapterForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxChapter) ((verseIndex >> 8) % 0x100);
}

static inline BfoxVerse BfoxVerseForVerseIndex(BfoxVerseIndex verseIndex) {
	return (BfoxVerse) (verseIndex % 0x100);
}

#endif // BFOX_BIBLE_META_H_
