#include <cmath>

const int lm35_pin = A0;

float lm35_raw_to_temperature(int raw) {
  float voltage = raw * 3.3 / (std::pow(2, 12));
  float temperature = 100.0 * voltage;
  return temperature;
}

void setup() {
  SerialUSB.begin(115200);
  analogReadResolution(12);
}

void loop() {
  int raw = analogRead(lm35_pin);
  float temperature = lm35_raw_to_temperature(raw);

  SerialUSB.println(temperature);

  delay(50);
}