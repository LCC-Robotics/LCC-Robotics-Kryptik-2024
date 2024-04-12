#pragma once

#include <CrcLib.h>

#include "const.h"

namespace Tunes {
const Note VICTORY_TUNE[] {
    { 225, NOTE_AS4 },
    { 150, NOTE_D5 },
    { 150, NOTE_F5 },
    { 150, NOTE_SILENCE },
    { 150, NOTE_D5 },
    { 600, NOTE_F5 },
    Note::END
};

const Note NON_NOBIS_SOLUM[] {
    { 400, NOTE_F4 },
    { 800, NOTE_AS4 },
    { 400, NOTE_A4 },
    { 400, NOTE_AS4 },
    { 800, NOTE_G4 },
    { 400, NOTE_F4 },
    { 400, NOTE_AS4 },
    { 400, NOTE_C5 },
    { 180, NOTE_D5 },
    { 160, NOTE_DS5 },
    { 750, NOTE_C5 },
    { 160, NOTE_AS4 },
    { 1300, NOTE_AS4 },
    Note::END
};

void CustomUpdate()
{
    static bool flop;

    if (CrcLib::ReadDigitalChannel(VICTORY_BUTTON)) {
        CrcLib::PlayTune(flop ? VICTORY_TUNE : NON_NOBIS_SOLUM, false);
        flop = !flop;
    }
}
}
