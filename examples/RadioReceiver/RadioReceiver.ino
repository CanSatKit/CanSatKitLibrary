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
  char data[256];
  uint8_t length;
  CanSatKitRadio.receive(data, length);
  
  data[length] = '\0';

  SerialUSB.print("Received (RSSI = ");
  SerialUSB.print(CanSatKitRadio.get_rssi_last());
  SerialUSB.print("): ");
  SerialUSB.println(data);
}