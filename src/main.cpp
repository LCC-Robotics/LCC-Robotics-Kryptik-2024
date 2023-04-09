#include <Arduino.h>
#include <CrcLib.h> // https://robocrc.atlassian.net/wiki/spaces/AR/pages/403767325/CrcLib+Functions+-+An+overview
#include <Encoder.h>

using Crc::CrcLib, Crc::ANALOG, Crc::BUTTON;

void setup()
{
    CrcLib::Initialize();
}

void loop() 
{

}

