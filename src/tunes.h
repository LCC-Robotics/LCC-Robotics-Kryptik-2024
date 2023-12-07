#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_

#include <CrcLib.h>

#include "const.h"

const Note VICTORY_TUNE[] {
    { 225, NOTE_AS4 },
    { 150, NOTE_D5 },
    { 150, NOTE_F5 },
    { 150, NOTE_SILENCE },
    { 150, NOTE_D5 },
    { 600, NOTE_F5 },
    Note::END()
};

const Note NON_NOBIS_SOLUM[] {
    { 125, NOTE_F4 },
    { 250, NOTE_AS4 },
    { 125, NOTE_A4 },
    { 125, NOTE_AS4 },
    { 250, NOTE_G4 },
    { 125, NOTE_F4 },
    { 125, NOTE_AS4 },
    { 125, NOTE_C5 },
    { 75, NOTE_D5 },
    { 75, NOTE_DS5 },
    { 250, NOTE_C5 },
    { 75, NOTE_AS4 },
    { 450, NOTE_AS4 },
    Note::END()
};

bool flop;

void tunes_update()
{
    if (CrcLib::ReadDigitalChannel(VICTORY_BUTTON)) {
        CrcLib::PlayTune(flop ? VICTORY_TUNE : NON_NOBIS_SOLUM, false);
        flop = !flop;
    }
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_
