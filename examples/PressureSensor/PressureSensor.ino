#include <CanSatKitBMP280.h>
#define P0 1013.25
BMP280 bmp;

void setup() {
  SerialUSB.begin(9600);
  if(!bmp.begin()) {
    SerialUSB.println("BMP init failed!");
    while(1);
  } else {
    SerialUSB.println("BMP init success!");
  }
  
  bmp.setOversampling(4);
  
}

void loop() {
  double T,P;
  char result = bmp.startMeasurment();
 
  if(result != 0) {
    delay(result);
    result = bmp.getTemperatureAndPressure(T,P);
    
      if(result != 0) {
        double A = bmp.altitude(P,P0);
        
        SerialUSB.print("T = \t"); SerialUSB.print(T,2); SerialUSB.print(" degC\t");
        SerialUSB.print("P = \t"); SerialUSB.print(P,2); SerialUSB.print(" mBar\t");
        SerialUSB.print("A = \t"); SerialUSB.print(A,2); SerialUSB.println(" m");
       
      } else {
        SerialUSB.println("Error.");
      }
  } else {
    SerialUSB.println("Error.");
  }
  
  delay(100);
}