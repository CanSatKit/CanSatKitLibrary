#include <CanSatKit.h>

using namespace CanSatKit;

// set radio receiver parameters - see comments below
// remember to set the same radio parameters in
// transmitter and receiver boards!
Radio radio(Pins::Radio::ChipSelect,
            Pins::Radio::DIO0,
            433.0,                  // frequency in MHz
            Bandwidth_125000_Hz,    // bandwidth - check with CanSat regulations to set allowed value
            SpreadingFactor_9,      // see provided presentations to determine which setting is the best
            CodingRate_4_8);        // see provided presentations to determine which setting is the best

void setup() {
  SerialUSB.begin(115200);

  
  radio.begin();
}

void loop() {
  // prepare empty space for received frame
  char data[256];
  uint8_t length;

  // receive data and save it to data array, save also length of the message
  radio.receive(data, length);
  
  // add termination character to the end of the message
  data[length] = '\0';

  // get and print signal level (rssi)
  SerialUSB.print("Received (RSSI = ");
  SerialUSB.print(radio.get_rssi_last());
  SerialUSB.print("): ");

  // print received message
  SerialUSB.println(data);
}
