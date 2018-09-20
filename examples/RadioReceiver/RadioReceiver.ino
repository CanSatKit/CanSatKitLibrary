#include <CanSatKit.h>

void setup() {
  SerialUSB.begin(115200);

  // set radio receiver parameters - see comments below
  // remember to set the same radio parameters in
  // transmitter and receiver boards!
  CanSatKitRadio.begin(CanSatPins_Radio_CS,
                       CanSatPins_Radio_DIO0,
                       433.0,                  // frequency in MHz
                       Bandwidth_125000_Hz,    // bandwidth - check with CanSat regulations to set allowed value
                       SpreadingFactor_9,      // see provided presentations to determine which setting is the best
                       CodingRate_4_8);        // see provided presentations to determine which setting is the best
}

void loop() {
  // prepare empty space for received frame
  char data[256];
  uint8_t length;

  // receive data and save it to data array, save also length of the message
  CanSatKitRadio.receive(data, length);
  
  // add termination character to the end of the message
  data[length] = '\0';

  // get and print signal level (rssi)
  SerialUSB.print("Received (RSSI = ");
  SerialUSB.print(CanSatKitRadio.get_rssi_last());
  SerialUSB.print("): ");

  // print received message
  SerialUSB.println(data);
}
