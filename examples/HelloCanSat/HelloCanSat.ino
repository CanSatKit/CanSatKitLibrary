int counter = 1;
bool led_state = false;
const int led_pin = 13;

  
void setup() {
  SerialUSB.begin(115200);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  digitalWrite(led_pin, led_state);
  led_state = !led_state;

  SerialUSB.print(counter);
  counter++;
  SerialUSB.println(". Hello CanSat!");

  delay(1000);
}