#ifndef LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_
#define LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_

#include <CrcLib.h>

constexpr BUTTON VICTORY_BUTTON = BUTTON::START;

const Note VICTORY_TUNE[] {
    { 500, NOTE_AS2 },
    { 250, NOTE_D3 },
    { 250, NOTE_F3 },
    { 250, NOTE_SILENCE },
    { 250, NOTE_D3 },
    { 2000, NOTE_F3 },
    Note::END()
};

void tunes_update() {
    if (CrcLib::ReadDigitalChannel(VICTORY_BUTTON)) {
        CrcLib::PlayTune(VICTORY_TUNE, false);
    }
}

#endif // LCC_ROBOTICS_KRYPTIK_2024_SRC_TUNES_H_
