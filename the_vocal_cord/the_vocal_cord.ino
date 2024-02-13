
#define VRX_PIN_0  A0 // Arduino pin connected to VRX pin
#define VRY_PIN_0  A1 // Arduino pin connected to VRY pin

#define VRX_PIN_1  A2 // Arduino pin connected to VRX pin
#define VRY_PIN_1  A3 // Arduino pin connected to VRY pin


int xValue0 = 0; // To store value of the X axis
int yValue0 = 0; // To store value of the Y axis

int xValue1 = 0; // To store value of the X axis
int yValue1 = 0; // To store value of the Y axis

void setup() {
  Serial.begin(9600) ;
}

void loop() {
  // read analog X and Y analog values
  xValue0 = analogRead(VRX_PIN_0);
  yValue0 = analogRead(VRY_PIN_0);

  xValue1 = analogRead(VRX_PIN_1);
  yValue1 = analogRead(VRY_PIN_1);

  Serial.print(yValue0);
  Serial.print('a');

  Serial.print(yValue1);
  Serial.print('b');

  Serial.print(xValue0);
  Serial.print('c');

  Serial.print(xValue1);
  Serial.print('d');

  delay(1);


}







