#include <CanSatKit.h>

void setup() {
  SerialUSB.begin(115200);

  bool ok = CanSatKitRadio.begin(CanSatPins_Radio_CS,
                                 CanSatPins_Radio_DIO0,
                                 433.0,
                                 Bandwidth_125000_Hz,
                                 SpreadingFactor_9,
                                 CodingRate_4_8);
  if (ok) {
      SerialUSB.println("Radio OK!");
      CanSatKitRadio.disable_debug();
  } else {
      SerialUSB.println("Radio failed!");
  }
} 

void loop() {
  bool ok = CanSatKitRadio.transmit("Hello World!");

  if (!ok) {
      SerialUSB.println("Transmit buffer full!");
  }

  delay(10);
}