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

#include "bfox_bible_meta.h"

unsigned int BfoxBookGenesisMinVerseCounts[] = { 31, 25, 24, 26, 32, 22, 24, 22, 29, 32, 32, 20, 18, 24, 21, 16, 27, 33, 38, 18, 34, 24, 20, 67, 34, 35, 46, 22, 35, 43, 55, 32, 20, 31, 29, 43, 36, 30, 23, 23, 57, 38, 34, 34, 28, 34, 31, 22, 33, 26 };
unsigned int BfoxBookGenesisMaxVerseCounts[] = { 31, 25, 24, 26, 32, 22, 24, 22, 29, 32, 32, 20, 18, 24, 21, 16, 27, 33, 38, 18, 34, 24, 20, 67, 34, 35, 46, 22, 35, 43, 55, 32, 20, 31, 29, 43, 36, 30, 23, 23, 57, 38, 34, 34, 28, 34, 31, 22, 33, 26 };
unsigned int BfoxBookExodusMinVerseCounts[] = { 22, 25, 22, 31, 23, 30, 25, 32, 35, 29, 10, 51, 22, 31, 27, 36, 16, 27, 25, 26, 36, 31, 33, 18, 40, 37, 21, 43, 46, 38, 18, 35, 23, 35, 35, 38, 29, 31, 43, 38 };
unsigned int BfoxBookExodusMaxVerseCounts[] = { 22, 25, 22, 31, 23, 30, 25, 32, 35, 29, 10, 51, 22, 31, 27, 36, 16, 27, 25, 26, 36, 31, 33, 18, 40, 37, 21, 43, 46, 38, 18, 35, 23, 35, 35, 38, 29, 31, 43, 38 };
unsigned int BfoxBookLeviticusMinVerseCounts[] = { 17, 16, 17, 35, 19, 30, 38, 36, 24, 20, 47, 8, 59, 57, 33, 34, 16, 30, 37, 27, 24, 33, 44, 23, 55, 46, 34 };
unsigned int BfoxBookLeviticusMaxVerseCounts[] = { 17, 16, 17, 35, 19, 30, 38, 36, 24, 20, 47, 8, 59, 57, 33, 34, 16, 30, 37, 27, 24, 33, 44, 23, 55, 46, 34 };
unsigned int BfoxBookNumbersMinVerseCounts[] = { 54, 34, 51, 49, 31, 27, 89, 26, 23, 36, 35, 16, 33, 45, 41, 50, 13, 32, 22, 29, 35, 41, 30, 25, 18, 65, 23, 31, 40, 16, 54, 42, 56, 29, 34, 13 };
unsigned int BfoxBookNumbersMaxVerseCounts[] = { 54, 34, 51, 49, 31, 27, 89, 26, 23, 36, 35, 16, 33, 45, 41, 50, 13, 32, 22, 29, 35, 41, 30, 25, 18, 65, 23, 31, 40, 16, 54, 42, 56, 29, 34, 13 };
unsigned int BfoxBookDeuteronomyMinVerseCounts[] = { 46, 37, 29, 49, 33, 25, 26, 20, 29, 22, 32, 32, 18, 29, 23, 22, 20, 22, 21, 20, 23, 30, 25, 22, 19, 19, 26, 68, 29, 20, 30, 52, 29, 12 };
unsigned int BfoxBookDeuteronomyMaxVerseCounts[] = { 46, 37, 29, 49, 33, 25, 26, 20, 29, 22, 32, 32, 18, 29, 23, 22, 20, 22, 21, 20, 23, 30, 25, 22, 19, 19, 26, 68, 29, 20, 30, 52, 29, 12 };
unsigned int BfoxBookJoshuaMinVerseCounts[] = { 18, 24, 17, 24, 15, 27, 26, 35, 27, 43, 23, 24, 33, 15, 63, 10, 18, 28, 51, 9, 45, 34, 16, 33 };
unsigned int BfoxBookJoshuaMaxVerseCounts[] = { 18, 24, 17, 24, 15, 27, 26, 35, 27, 43, 23, 24, 33, 15, 63, 10, 18, 28, 51, 9, 45, 34, 16, 33 };
unsigned int BfoxBookJudgesMinVerseCounts[] = { 36, 23, 31, 24, 31, 40, 25, 35, 57, 18, 40, 15, 25, 20, 20, 31, 13, 31, 30, 48, 25 };
unsigned int BfoxBookJudgesMaxVerseCounts[] = { 36, 23, 31, 24, 31, 40, 25, 35, 57, 18, 40, 15, 25, 20, 20, 31, 13, 31, 30, 48, 25 };
unsigned int BfoxBookRuthMinVerseCounts[] = { 22, 23, 18, 22 };
unsigned int BfoxBookRuthMaxVerseCounts[] = { 22, 23, 18, 22 };
unsigned int BfoxBook1SamuelMinVerseCounts[] = { 28, 36, 21, 22, 12, 21, 17, 22, 27, 27, 15, 25, 23, 52, 35, 23, 58, 30, 24, 42, 15, 23, 29, 22, 44, 25, 12, 25, 11, 31, 13 };
unsigned int BfoxBook1SamuelMaxVerseCounts[] = { 28, 36, 21, 22, 12, 21, 17, 22, 27, 27, 15, 25, 23, 52, 35, 23, 58, 30, 24, 42, 15, 23, 29, 22, 44, 25, 12, 25, 11, 31, 13 };
unsigned int BfoxBook2SamuelMinVerseCounts[] = { 27, 32, 39, 12, 25, 23, 29, 18, 13, 19, 27, 31, 39, 33, 37, 23, 29, 33, 43, 26, 22, 51, 39, 25 };
unsigned int BfoxBook2SamuelMaxVerseCounts[] = { 27, 32, 39, 12, 25, 23, 29, 18, 13, 19, 27, 31, 39, 33, 37, 23, 29, 33, 43, 26, 22, 51, 39, 25 };
unsigned int BfoxBook1KingsMinVerseCounts[] = { 53, 46, 28, 34, 18, 38, 51, 66, 28, 29, 43, 33, 34, 31, 34, 34, 24, 46, 21, 43, 29, 53 };
unsigned int BfoxBook1KingsMaxVerseCounts[] = { 53, 46, 28, 34, 18, 38, 51, 66, 28, 29, 43, 33, 34, 31, 34, 34, 24, 46, 21, 43, 29, 53 };
unsigned int BfoxBook2KingsMinVerseCounts[] = { 18, 25, 27, 44, 27, 33, 20, 29, 37, 36, 21, 21, 25, 29, 38, 20, 41, 37, 37, 21, 26, 20, 37, 20, 30 };
unsigned int BfoxBook2KingsMaxVerseCounts[] = { 18, 25, 27, 44, 27, 33, 20, 29, 37, 36, 21, 21, 25, 29, 38, 20, 41, 37, 37, 21, 26, 20, 37, 20, 30 };
unsigned int BfoxBook1ChroniclesMinVerseCounts[] = { 54, 55, 24, 43, 26, 81, 40, 40, 44, 14, 47, 40, 14, 17, 29, 43, 27, 17, 19, 8, 30, 19, 32, 31, 31, 32, 34, 21, 30 };
unsigned int BfoxBook1ChroniclesMaxVerseCounts[] = { 54, 55, 24, 43, 26, 81, 40, 40, 44, 14, 47, 40, 14, 17, 29, 43, 27, 17, 19, 8, 30, 19, 32, 31, 31, 32, 34, 21, 30 };
unsigned int BfoxBook2ChroniclesMinVerseCounts[] = { 17, 18, 17, 22, 14, 42, 22, 18, 31, 19, 23, 16, 22, 15, 19, 14, 19, 34, 11, 37, 20, 12, 21, 27, 28, 23, 9, 27, 36, 27, 21, 33, 25, 33, 27, 23 };
unsigned int BfoxBook2ChroniclesMaxVerseCounts[] = { 17, 18, 17, 22, 14, 42, 22, 18, 31, 19, 23, 16, 22, 15, 19, 14, 19, 34, 11, 37, 20, 12, 21, 27, 28, 23, 9, 27, 36, 27, 21, 33, 25, 33, 27, 23 };
unsigned int BfoxBookEzraMinVerseCounts[] = { 11, 70, 13, 24, 17, 22, 28, 36, 15, 44 };
unsigned int BfoxBookEzraMaxVerseCounts[] = { 11, 70, 13, 24, 17, 22, 28, 36, 15, 44 };
unsigned int BfoxBookNehemiahMinVerseCounts[] = { 11, 20, 32, 23, 19, 19, 73, 18, 38, 39, 36, 47, 31 };
unsigned int BfoxBookNehemiahMaxVerseCounts[] = { 11, 20, 32, 23, 19, 19, 73, 18, 38, 39, 36, 47, 31 };
unsigned int BfoxBookEstherMinVerseCounts[] = { 22, 23, 15, 17, 14, 14, 10, 17, 32, 3 };
unsigned int BfoxBookEstherMaxVerseCounts[] = { 22, 23, 15, 17, 14, 14, 10, 17, 32, 3 };
unsigned int BfoxBookJobMinVerseCounts[] = { 22, 13, 26, 21, 27, 30, 21, 22, 35, 22, 20, 25, 28, 22, 35, 22, 16, 21, 29, 29, 34, 30, 17, 25, 6, 14, 23, 28, 25, 31, 40, 22, 33, 37, 16, 33, 24, 41, 30, 24, 34, 17 };
unsigned int BfoxBookJobMaxVerseCounts[] = { 22, 13, 26, 21, 27, 30, 21, 22, 35, 22, 20, 25, 28, 22, 35, 22, 16, 21, 29, 29, 34, 30, 17, 25, 6, 14, 23, 28, 25, 31, 40, 22, 33, 37, 16, 33, 24, 41, 30, 24, 34, 17 };
unsigned int BfoxBookPsalmMinVerseCounts[] = { 6, 12, 8, 8, 12, 10, 17, 9, 20, 18, 7, 8, 6, 7, 5, 11, 15, 50, 14, 9, 13, 31, 6, 10, 22, 12, 14, 9, 11, 12, 24, 11, 22, 22, 28, 12, 40, 22, 13, 17, 13, 11, 5, 26, 17, 11, 9, 14, 20, 23, 19, 9, 6, 7, 23, 13, 11, 11, 17, 12, 8, 12, 11, 10, 13, 20, 7, 35, 36, 5, 24, 20, 28, 23, 10, 12, 20, 72, 13, 19, 16, 8, 18, 12, 13, 17, 7, 18, 52, 17, 16, 15, 5, 23, 11, 13, 12, 9, 9, 5, 8, 28, 22, 35, 45, 48, 43, 13, 31, 7, 10, 10, 9, 8, 18, 19, 2, 29, 176, 7, 8, 9, 4, 8, 5, 6, 5, 6, 8, 8, 3, 18, 3, 3, 21, 26, 9, 8, 24, 13, 10, 7, 12, 15, 21, 10, 20, 14, 9, 6 };
unsigned int BfoxBookPsalmMaxVerseCounts[] = { 6, 12, 8, 8, 12, 10, 17, 9, 20, 18, 7, 8, 6, 7, 5, 11, 15, 50, 14, 9, 13, 31, 6, 10, 22, 12, 14, 9, 11, 12, 24, 11, 22, 22, 28, 12, 40, 22, 13, 17, 13, 11, 5, 26, 17, 11, 9, 14, 20, 23, 19, 9, 6, 7, 23, 13, 11, 11, 17, 12, 8, 12, 11, 10, 13, 20, 7, 35, 36, 5, 24, 20, 28, 23, 10, 12, 20, 72, 13, 19, 16, 8, 18, 12, 13, 17, 7, 18, 52, 17, 16, 15, 5, 23, 11, 13, 12, 9, 9, 5, 8, 28, 22, 35, 45, 48, 43, 13, 31, 7, 10, 10, 9, 8, 18, 19, 2, 29, 176, 7, 8, 9, 4, 8, 5, 6, 5, 6, 8, 8, 3, 18, 3, 3, 21, 26, 9, 8, 24, 13, 10, 7, 12, 15, 21, 10, 20, 14, 9, 6 };
unsigned int BfoxBookProverbsMinVerseCounts[] = { 33, 22, 35, 27, 23, 35, 27, 36, 18, 32, 31, 28, 25, 35, 33, 33, 28, 24, 29, 30, 31, 29, 35, 34, 28, 28, 27, 28, 27, 33, 31 };
unsigned int BfoxBookProverbsMaxVerseCounts[] = { 33, 22, 35, 27, 23, 35, 27, 36, 18, 32, 31, 28, 25, 35, 33, 33, 28, 24, 29, 30, 31, 29, 35, 34, 28, 28, 27, 28, 27, 33, 31 };
unsigned int BfoxBookEcclesiastesMinVerseCounts[] = { 18, 26, 22, 16, 20, 12, 29, 17, 18, 20, 10, 14 };
unsigned int BfoxBookEcclesiastesMaxVerseCounts[] = { 18, 26, 22, 16, 20, 12, 29, 17, 18, 20, 10, 14 };
unsigned int BfoxBookSongofSolomonMinVerseCounts[] = { 17, 17, 11, 16, 16, 13, 13, 14 };
unsigned int BfoxBookSongofSolomonMaxVerseCounts[] = { 17, 17, 11, 16, 16, 13, 13, 14 };
unsigned int BfoxBookIsaiahMinVerseCounts[] = { 31, 22, 26, 6, 30, 13, 25, 22, 21, 34, 16, 6, 22, 32, 9, 14, 14, 7, 25, 6, 17, 25, 18, 23, 12, 21, 13, 29, 24, 33, 9, 20, 24, 17, 10, 22, 38, 22, 8, 31, 29, 25, 28, 28, 25, 13, 15, 22, 26, 11, 23, 15, 12, 17, 13, 12, 21, 14, 21, 22, 11, 12, 19, 12, 25, 24 };
unsigned int BfoxBookIsaiahMaxVerseCounts[] = { 31, 22, 26, 6, 30, 13, 25, 22, 21, 34, 16, 6, 22, 32, 9, 14, 14, 7, 25, 6, 17, 25, 18, 23, 12, 21, 13, 29, 24, 33, 9, 20, 24, 17, 10, 22, 38, 22, 8, 31, 29, 25, 28, 28, 25, 13, 15, 22, 26, 11, 23, 15, 12, 17, 13, 12, 21, 14, 21, 22, 11, 12, 19, 12, 25, 24 };
unsigned int BfoxBookJeremiahMinVerseCounts[] = { 19, 37, 25, 31, 31, 30, 34, 22, 26, 25, 23, 17, 27, 22, 21, 21, 27, 23, 15, 18, 14, 30, 40, 10, 38, 24, 22, 17, 32, 24, 40, 44, 26, 22, 19, 32, 21, 28, 18, 16, 18, 22, 13, 30, 5, 28, 7, 47, 39, 46, 64, 34 };
unsigned int BfoxBookJeremiahMaxVerseCounts[] = { 19, 37, 25, 31, 31, 30, 34, 22, 26, 25, 23, 17, 27, 22, 21, 21, 27, 23, 15, 18, 14, 30, 40, 10, 38, 24, 22, 17, 32, 24, 40, 44, 26, 22, 19, 32, 21, 28, 18, 16, 18, 22, 13, 30, 5, 28, 7, 47, 39, 46, 64, 34 };
unsigned int BfoxBookLamentationsMinVerseCounts[] = { 22, 22, 66, 22, 22 };
unsigned int BfoxBookLamentationsMaxVerseCounts[] = { 22, 22, 66, 22, 22 };
unsigned int BfoxBookEzekielMinVerseCounts[] = { 28, 10, 27, 17, 17, 14, 27, 18, 11, 22, 25, 28, 23, 23, 8, 63, 24, 32, 14, 49, 32, 31, 49, 27, 17, 21, 36, 26, 21, 26, 18, 32, 33, 31, 15, 38, 28, 23, 29, 49, 26, 20, 27, 31, 25, 24, 23, 35 };
unsigned int BfoxBookEzekielMaxVerseCounts[] = { 28, 10, 27, 17, 17, 14, 27, 18, 11, 22, 25, 28, 23, 23, 8, 63, 24, 32, 14, 49, 32, 31, 49, 27, 17, 21, 36, 26, 21, 26, 18, 32, 33, 31, 15, 38, 28, 23, 29, 49, 26, 20, 27, 31, 25, 24, 23, 35 };
unsigned int BfoxBookDanielMinVerseCounts[] = { 21, 49, 30, 37, 31, 28, 28, 27, 27, 21, 45, 13 };
unsigned int BfoxBookDanielMaxVerseCounts[] = { 21, 49, 30, 37, 31, 28, 28, 27, 27, 21, 45, 13 };
unsigned int BfoxBookHoseaMinVerseCounts[] = { 11, 23, 5, 19, 15, 11, 16, 14, 17, 15, 12, 14, 16, 9 };
unsigned int BfoxBookHoseaMaxVerseCounts[] = { 11, 23, 5, 19, 15, 11, 16, 14, 17, 15, 12, 14, 16, 9 };
unsigned int BfoxBookJoelMinVerseCounts[] = { 20, 32, 21 };
unsigned int BfoxBookJoelMaxVerseCounts[] = { 20, 32, 21 };
unsigned int BfoxBookAmosMinVerseCounts[] = { 15, 16, 15, 13, 27, 14, 17, 14, 15 };
unsigned int BfoxBookAmosMaxVerseCounts[] = { 15, 16, 15, 13, 27, 14, 17, 14, 15 };
unsigned int BfoxBookObadiahMinVerseCounts[] = { 21 };
unsigned int BfoxBookObadiahMaxVerseCounts[] = { 21 };
unsigned int BfoxBookJonahMinVerseCounts[] = { 17, 10, 10, 11 };
unsigned int BfoxBookJonahMaxVerseCounts[] = { 17, 10, 10, 11 };
unsigned int BfoxBookMicahMinVerseCounts[] = { 16, 13, 12, 13, 15, 16, 20 };
unsigned int BfoxBookMicahMaxVerseCounts[] = { 16, 13, 12, 13, 15, 16, 20 };
unsigned int BfoxBookNahumMinVerseCounts[] = { 15, 13, 19 };
unsigned int BfoxBookNahumMaxVerseCounts[] = { 15, 13, 19 };
unsigned int BfoxBookHabakkukMinVerseCounts[] = { 17, 20, 19 };
unsigned int BfoxBookHabakkukMaxVerseCounts[] = { 17, 20, 19 };
unsigned int BfoxBookZephaniahMinVerseCounts[] = { 18, 15, 20 };
unsigned int BfoxBookZephaniahMaxVerseCounts[] = { 18, 15, 20 };
unsigned int BfoxBookHaggaiMinVerseCounts[] = { 15, 23 };
unsigned int BfoxBookHaggaiMaxVerseCounts[] = { 15, 23 };
unsigned int BfoxBookZechariahMinVerseCounts[] = { 21, 13, 10, 14, 11, 15, 14, 23, 17, 12, 17, 14, 9, 21 };
unsigned int BfoxBookZechariahMaxVerseCounts[] = { 21, 13, 10, 14, 11, 15, 14, 23, 17, 12, 17, 14, 9, 21 };
unsigned int BfoxBookMalachiMinVerseCounts[] = { 14, 17, 18, 6 };
unsigned int BfoxBookMalachiMaxVerseCounts[] = { 14, 17, 18, 6 };
unsigned int BfoxBookMatthewMinVerseCounts[] = { 25, 23, 17, 25, 48, 34, 29, 34, 38, 42, 30, 50, 58, 36, 39, 28, 27, 35, 30, 34, 46, 46, 39, 51, 46, 75, 66, 20 };
unsigned int BfoxBookMatthewMaxVerseCounts[] = { 25, 23, 17, 25, 48, 34, 29, 34, 38, 42, 30, 50, 58, 36, 39, 28, 27, 35, 30, 34, 46, 46, 39, 51, 46, 75, 66, 20 };
unsigned int BfoxBookMarkMinVerseCounts[] = { 45, 28, 35, 41, 43, 56, 37, 38, 50, 52, 33, 44, 37, 72, 47, 20 };
unsigned int BfoxBookMarkMaxVerseCounts[] = { 45, 28, 35, 41, 43, 56, 37, 38, 50, 52, 33, 44, 37, 72, 47, 20 };
unsigned int BfoxBookLukeMinVerseCounts[] = { 80, 52, 38, 44, 39, 49, 50, 56, 62, 42, 54, 59, 35, 35, 32, 31, 37, 43, 48, 47, 38, 71, 56, 53 };
unsigned int BfoxBookLukeMaxVerseCounts[] = { 80, 52, 38, 44, 39, 49, 50, 56, 62, 42, 54, 59, 35, 35, 32, 31, 37, 43, 48, 47, 38, 71, 56, 53 };
unsigned int BfoxBookJohnMinVerseCounts[] = { 51, 25, 36, 54, 47, 71, 53, 59, 41, 42, 57, 50, 38, 31, 27, 33, 26, 40, 42, 31, 25 };
unsigned int BfoxBookJohnMaxVerseCounts[] = { 51, 25, 36, 54, 47, 71, 53, 59, 41, 42, 57, 50, 38, 31, 27, 33, 26, 40, 42, 31, 25 };
unsigned int BfoxBookActsMinVerseCounts[] = { 26, 47, 26, 37, 42, 15, 60, 40, 43, 48, 30, 25, 52, 28, 41, 40, 34, 28, 41, 38, 40, 30, 35, 27, 27, 32, 44, 31 };
unsigned int BfoxBookActsMaxVerseCounts[] = { 26, 47, 26, 37, 42, 15, 60, 40, 43, 48, 30, 25, 52, 28, 41, 40, 34, 28, 41, 38, 40, 30, 35, 27, 27, 32, 44, 31 };
unsigned int BfoxBookRomansMinVerseCounts[] = { 32, 29, 31, 25, 21, 23, 25, 39, 33, 21, 36, 21, 14, 23, 33, 24 };
unsigned int BfoxBookRomansMaxVerseCounts[] = { 32, 29, 31, 25, 21, 23, 25, 39, 33, 21, 36, 21, 14, 26, 33, 27 };
unsigned int BfoxBook1CorinthiansMinVerseCounts[] = { 31, 16, 23, 21, 13, 20, 40, 13, 27, 33, 34, 31, 13, 40, 58, 24 };
unsigned int BfoxBook1CorinthiansMaxVerseCounts[] = { 31, 16, 23, 21, 13, 20, 40, 13, 27, 33, 34, 31, 13, 40, 58, 24 };
unsigned int BfoxBook2CorinthiansMinVerseCounts[] = { 24, 17, 18, 18, 21, 18, 16, 24, 15, 18, 33, 21, 14 };
unsigned int BfoxBook2CorinthiansMaxVerseCounts[] = { 24, 17, 18, 18, 21, 18, 16, 24, 15, 18, 33, 21, 14 };
unsigned int BfoxBookGalatiansMinVerseCounts[] = { 24, 21, 29, 31, 26, 18 };
unsigned int BfoxBookGalatiansMaxVerseCounts[] = { 24, 21, 29, 31, 26, 18 };
unsigned int BfoxBookEphesiansMinVerseCounts[] = { 23, 22, 21, 32, 33, 24 };
unsigned int BfoxBookEphesiansMaxVerseCounts[] = { 23, 22, 21, 32, 33, 24 };
unsigned int BfoxBookPhilippiansMinVerseCounts[] = { 30, 30, 21, 23 };
unsigned int BfoxBookPhilippiansMaxVerseCounts[] = { 30, 30, 21, 23 };
unsigned int BfoxBookColossiansMinVerseCounts[] = { 29, 23, 25, 18 };
unsigned int BfoxBookColossiansMaxVerseCounts[] = { 29, 23, 25, 18 };
unsigned int BfoxBook1ThessaloniansMinVerseCounts[] = { 10, 20, 13, 18, 28 };
unsigned int BfoxBook1ThessaloniansMaxVerseCounts[] = { 10, 20, 13, 18, 28 };
unsigned int BfoxBook2ThessaloniansMinVerseCounts[] = { 12, 17, 18 };
unsigned int BfoxBook2ThessaloniansMaxVerseCounts[] = { 12, 17, 18 };
unsigned int BfoxBook1TimothyMinVerseCounts[] = { 20, 15, 16, 16, 25, 21 };
unsigned int BfoxBook1TimothyMaxVerseCounts[] = { 20, 15, 16, 16, 25, 21 };
unsigned int BfoxBook2TimothyMinVerseCounts[] = { 18, 26, 17, 22 };
unsigned int BfoxBook2TimothyMaxVerseCounts[] = { 18, 26, 17, 22 };
unsigned int BfoxBookTitusMinVerseCounts[] = { 16, 15, 15 };
unsigned int BfoxBookTitusMaxVerseCounts[] = { 16, 15, 15 };
unsigned int BfoxBookPhilemonMinVerseCounts[] = { 25 };
unsigned int BfoxBookPhilemonMaxVerseCounts[] = { 25 };
unsigned int BfoxBookHebrewsMinVerseCounts[] = { 14, 18, 19, 16, 14, 20, 28, 13, 28, 39, 40, 29, 25 };
unsigned int BfoxBookHebrewsMaxVerseCounts[] = { 14, 18, 19, 16, 14, 20, 28, 13, 28, 39, 40, 29, 25 };
unsigned int BfoxBookJamesMinVerseCounts[] = { 27, 26, 18, 17, 20 };
unsigned int BfoxBookJamesMaxVerseCounts[] = { 27, 26, 18, 17, 20 };
unsigned int BfoxBook1PeterMinVerseCounts[] = { 25, 25, 22, 19, 14 };
unsigned int BfoxBook1PeterMaxVerseCounts[] = { 25, 25, 22, 19, 14 };
unsigned int BfoxBook2PeterMinVerseCounts[] = { 21, 22, 18 };
unsigned int BfoxBook2PeterMaxVerseCounts[] = { 21, 22, 18 };
unsigned int BfoxBook1JohnMinVerseCounts[] = { 10, 29, 24, 21, 21 };
unsigned int BfoxBook1JohnMaxVerseCounts[] = { 10, 29, 24, 21, 21 };
unsigned int BfoxBook2JohnMinVerseCounts[] = { 13 };
unsigned int BfoxBook2JohnMaxVerseCounts[] = { 13 };
unsigned int BfoxBook3JohnMinVerseCounts[] = { 14 };
unsigned int BfoxBook3JohnMaxVerseCounts[] = { 14 };
unsigned int BfoxBookJudeMinVerseCounts[] = { 25 };
unsigned int BfoxBookJudeMaxVerseCounts[] = { 25 };
unsigned int BfoxBookRevelationMinVerseCounts[] = { 20, 29, 22, 11, 14, 17, 17, 13, 21, 11, 19, 17, 18, 20, 8, 21, 18, 24, 21, 15, 27, 20 };
unsigned int BfoxBookRevelationMaxVerseCounts[] = { 20, 29, 22, 11, 14, 17, 17, 13, 21, 11, 19, 17, 18, 20, 8, 21, 18, 24, 21, 15, 27, 21 };

const unsigned int BfoxBookChapterCounts[] = { 50, 40, 27, 36, 34, 24, 21, 4, 31, 24, 22, 25, 29, 36, 10, 13, 10, 42, 150, 31, 12, 8, 66, 52, 5, 48, 12, 14, 3, 9, 1, 4, 7, 3, 3, 3, 2, 14, 4, 28, 16, 24, 21, 28, 16, 16, 13, 6, 6, 4, 4, 5, 3, 6, 4, 3, 1, 13, 5, 5, 3, 5, 1, 1, 1, 22 };
const unsigned int *BfoxBookChapterMinVerseCounts[] = { BfoxBookGenesisMinVerseCounts, BfoxBookExodusMinVerseCounts, BfoxBookLeviticusMinVerseCounts, BfoxBookNumbersMinVerseCounts, BfoxBookDeuteronomyMinVerseCounts, BfoxBookJoshuaMinVerseCounts, BfoxBookJudgesMinVerseCounts, BfoxBookRuthMinVerseCounts, BfoxBook1SamuelMinVerseCounts, BfoxBook2SamuelMinVerseCounts, BfoxBook1KingsMinVerseCounts, BfoxBook2KingsMinVerseCounts, BfoxBook1ChroniclesMinVerseCounts, BfoxBook2ChroniclesMinVerseCounts, BfoxBookEzraMinVerseCounts, BfoxBookNehemiahMinVerseCounts, BfoxBookEstherMinVerseCounts, BfoxBookJobMinVerseCounts, BfoxBookPsalmMinVerseCounts, BfoxBookProverbsMinVerseCounts, BfoxBookEcclesiastesMinVerseCounts, BfoxBookSongofSolomonMinVerseCounts, BfoxBookIsaiahMinVerseCounts, BfoxBookJeremiahMinVerseCounts, BfoxBookLamentationsMinVerseCounts, BfoxBookEzekielMinVerseCounts, BfoxBookDanielMinVerseCounts, BfoxBookHoseaMinVerseCounts, BfoxBookJoelMinVerseCounts, BfoxBookAmosMinVerseCounts, BfoxBookObadiahMinVerseCounts, BfoxBookJonahMinVerseCounts, BfoxBookMicahMinVerseCounts, BfoxBookNahumMinVerseCounts, BfoxBookHabakkukMinVerseCounts, BfoxBookZephaniahMinVerseCounts, BfoxBookHaggaiMinVerseCounts, BfoxBookZechariahMinVerseCounts, BfoxBookMalachiMinVerseCounts, BfoxBookMatthewMinVerseCounts, BfoxBookMarkMinVerseCounts, BfoxBookLukeMinVerseCounts, BfoxBookJohnMinVerseCounts, BfoxBookActsMinVerseCounts, BfoxBookRomansMinVerseCounts, BfoxBook1CorinthiansMinVerseCounts, BfoxBook2CorinthiansMinVerseCounts, BfoxBookGalatiansMinVerseCounts, BfoxBookEphesiansMinVerseCounts, BfoxBookPhilippiansMinVerseCounts, BfoxBookColossiansMinVerseCounts, BfoxBook1ThessaloniansMinVerseCounts, BfoxBook2ThessaloniansMinVerseCounts, BfoxBook1TimothyMinVerseCounts, BfoxBook2TimothyMinVerseCounts, BfoxBookTitusMinVerseCounts, BfoxBookPhilemonMinVerseCounts, BfoxBookHebrewsMinVerseCounts, BfoxBookJamesMinVerseCounts, BfoxBook1PeterMinVerseCounts, BfoxBook2PeterMinVerseCounts, BfoxBook1JohnMinVerseCounts, BfoxBook2JohnMinVerseCounts, BfoxBook3JohnMinVerseCounts, BfoxBookJudeMinVerseCounts, BfoxBookRevelationMinVerseCounts };
const unsigned int *BfoxBookChapterMaxVerseCounts[] = { BfoxBookGenesisMaxVerseCounts, BfoxBookExodusMaxVerseCounts, BfoxBookLeviticusMaxVerseCounts, BfoxBookNumbersMaxVerseCounts, BfoxBookDeuteronomyMaxVerseCounts, BfoxBookJoshuaMaxVerseCounts, BfoxBookJudgesMaxVerseCounts, BfoxBookRuthMaxVerseCounts, BfoxBook1SamuelMaxVerseCounts, BfoxBook2SamuelMaxVerseCounts, BfoxBook1KingsMaxVerseCounts, BfoxBook2KingsMaxVerseCounts, BfoxBook1ChroniclesMaxVerseCounts, BfoxBook2ChroniclesMaxVerseCounts, BfoxBookEzraMaxVerseCounts, BfoxBookNehemiahMaxVerseCounts, BfoxBookEstherMaxVerseCounts, BfoxBookJobMaxVerseCounts, BfoxBookPsalmMaxVerseCounts, BfoxBookProverbsMaxVerseCounts, BfoxBookEcclesiastesMaxVerseCounts, BfoxBookSongofSolomonMaxVerseCounts, BfoxBookIsaiahMaxVerseCounts, BfoxBookJeremiahMaxVerseCounts, BfoxBookLamentationsMaxVerseCounts, BfoxBookEzekielMaxVerseCounts, BfoxBookDanielMaxVerseCounts, BfoxBookHoseaMaxVerseCounts, BfoxBookJoelMaxVerseCounts, BfoxBookAmosMaxVerseCounts, BfoxBookObadiahMaxVerseCounts, BfoxBookJonahMaxVerseCounts, BfoxBookMicahMaxVerseCounts, BfoxBookNahumMaxVerseCounts, BfoxBookHabakkukMaxVerseCounts, BfoxBookZephaniahMaxVerseCounts, BfoxBookHaggaiMaxVerseCounts, BfoxBookZechariahMaxVerseCounts, BfoxBookMalachiMaxVerseCounts, BfoxBookMatthewMaxVerseCounts, BfoxBookMarkMaxVerseCounts, BfoxBookLukeMaxVerseCounts, BfoxBookJohnMaxVerseCounts, BfoxBookActsMaxVerseCounts, BfoxBookRomansMaxVerseCounts, BfoxBook1CorinthiansMaxVerseCounts, BfoxBook2CorinthiansMaxVerseCounts, BfoxBookGalatiansMaxVerseCounts, BfoxBookEphesiansMaxVerseCounts, BfoxBookPhilippiansMaxVerseCounts, BfoxBookColossiansMaxVerseCounts, BfoxBook1ThessaloniansMaxVerseCounts, BfoxBook2ThessaloniansMaxVerseCounts, BfoxBook1TimothyMaxVerseCounts, BfoxBook2TimothyMaxVerseCounts, BfoxBookTitusMaxVerseCounts, BfoxBookPhilemonMaxVerseCounts, BfoxBookHebrewsMaxVerseCounts, BfoxBookJamesMaxVerseCounts, BfoxBook1PeterMaxVerseCounts, BfoxBook2PeterMaxVerseCounts, BfoxBook1JohnMaxVerseCounts, BfoxBook2JohnMaxVerseCounts, BfoxBook3JohnMaxVerseCounts, BfoxBookJudeMaxVerseCounts, BfoxBookRevelationMaxVerseCounts };

static inline BfoxBCV BfoxPassageEnd(BfoxBook book, BfoxChapter chapter, bool is_earliest) {
	if (BfoxBookNotSet == book) return BfoxBookCount;
	if ((book - 1) < BfoxBookCount) {
		unsigned int chapter_count = BfoxBookChapterCounts[book - 1];
		if (BfoxChapterNotSet == chapter) return (BfoxChapter) chapter_count;

		if (chapter < chapter_count) {
			const unsigned int *chapter_verse_counts;
			if (is_earliest) chapter_verse_counts = BfoxBookChapterMinVerseCounts[book - 1];
			else chapter_verse_counts = BfoxBookChapterMaxVerseCounts[book - 1];

			return (BfoxVerse) chapter_verse_counts[chapter];
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

static inline BfoxVerse BfoxEarliestLastVerseInChapter(BfoxBook book, BfoxChapter chapter) {
	return (BfoxVerse) (BfoxPassageEnd(book, chapter, true));
}

static inline BfoxVerseIndex PreviousVerseIndex(BfoxVerseIndex verseIndex) {
	return 0;
}

#endif // BFOX_BOOK_META_H_
