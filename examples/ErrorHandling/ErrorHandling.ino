#include <CanSatKit.h>

void setup() {
  SerialUSB.begin(115200);

  // CanSatKitRadio.begin returns true if communication with radio module
  // onboard is correct
  bool ok = CanSatKitRadio.begin(CanSatPins_Radio_CS,
                                 CanSatPins_Radio_DIO0,
                                 433.0,
                                 Bandwidth_125000_Hz,
                                 SpreadingFactor_9,
                                 CodingRate_4_8);

  if (ok) {
      // print that radio is ok
      SerialUSB.println("Radio OK!");
      // stop printing radio debug to SerialUSB since everything is OK
      CanSatKitRadio.disable_debug();
  } else {
      // print that radio configuration failed...
      SerialUSB.println("Radio failed!");
  }
} 

void loop() {

  // CanSatKitRadio.transmit returns true if there is enough space in
  // radio transmission buffer
  bool ok = CanSatKitRadio.transmit("Hello World!");

  if (!ok) {
      // if CanSatKitRadio.transmit returned false -- print that buffer is full
      // to prevent from buffer overflow - increase delay or send less data...
      SerialUSB.println("Transmit buffer full!");
  }

  // adjust delay to prevent from radio transmission buffer overflow
  delay(10);
}