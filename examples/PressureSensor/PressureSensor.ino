#include <CanSatKit.h>

BMP280 bmp;

void setup() {
  SerialUSB.begin(9600);
  if(!bmp.begin()) {
    SerialUSB.println("BMP init failed!");
    while(1);
  } else {
    SerialUSB.println("BMP init success!");
  }
  
  bmp.setOversampling(16);
  
}

void loop() {
  double T,P;
  int result = bmp.startMeasurment();

  delay(result);
  bmp.getTemperatureAndPressure(T,P);
    
  SerialUSB.print("Pressure = ");
  SerialUSB.print(P,2);
  SerialUSB.println(" hPa");
}