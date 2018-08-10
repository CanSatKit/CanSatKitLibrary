#include <CanSatKit.h>

void setup() {
  SerialUSB.begin(115200);
  CanSatKitRadio.begin(CanSatPins_Radio_CS,
                       CanSatPins_Radio_DIO0,
                       433.0,
                       Bandwidth_125000_Hz,
                       SpreadingFactor_9,
                       CodingRate_4_8);
}

void loop() {
  char buffer[256] = {'\0'};
  uint8_t length;

  CanSatKitRadio.receive(buffer, length);

  SerialUSB.print("Received ");
  SerialUSB.print(length);
  SerialUSB.print("bytes: ");
  SerialUSB.print(buffer);
  SerialUSB.print(" RSSI: ");
  SerialUSB.println(CanSatKitRadio.get_rssi_last());
}