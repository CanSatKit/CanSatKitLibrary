#include <CanSatKit.h>

using namespace CanSatKit;

Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,
            Bandwidth_125000_Hz,
            SpreadingFactor_9,
            CodingRate_4_8);

void setup() {
  SerialUSB.begin(115200);
  radio.begin();
}

void loop() {
  char buffer[256] = {'\0'};
  uint8_t length;

  radio.receive(buffer, length);

  SerialUSB.print("Received ");
  SerialUSB.print(length);
  SerialUSB.print("bytes: ");
  SerialUSB.print(buffer);
  SerialUSB.print(" RSSI: ");
  SerialUSB.println(radio.get_rssi_last());
}