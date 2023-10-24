//declararea pinilor analogici pentru citirea potentiometrelor
const int blueInputPin = A0;
const int greenInputPin = A1;
const int redInputPin = A2;

//declararea pinilor pentru RGB
const int blueLedPin = 9;
const int greenLedPin = 10;
const int redLedPin = 11;

//declararea variabilelor pentru potentiometre si RGB
int redInputValue;
int greenInputValue;
int blueInputValue;
int redLedValue;
int greenLedValue;
int blueLedValue;

//valori maxime si minime pentru citirile analogice si pentru controlul culorilor
const int minInitialValue = 0;
const int minValue = 0;
const int maxValue = 255;
const int maxInitialValue = 1023;

void setup() {
  pinMode(redInputPin, INPUT);
  pinMode(greenInputPin, INPUT);
  pinMode(blueInputPin, INPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
}

void setColor(int redValue, int greenValue, int blueValue) {
  //setarea culorilor LED-urilor in functie de valorile primite
  analogWrite(redLedPin, redValue); 
  analogWrite(greenLedPin, greenValue);
  analogWrite(blueLedPin, blueValue);
}

void loop() {
  //citirea valorilor potentiometrelor
  redInputValue = analogRead(redInputPin);
  greenInputValue = analogRead(greenInputPin);
  blueInputValue = analogRead(blueInputPin);
  
  //maparea in intervalul tinta ([minValue, maxValue])
  redLedValue = map(redInputValue, minInitialValue, maxInitialValue, minValue, maxValue);
  greenLedValue = map(greenInputValue, minInitialValue, maxInitialValue, minValue, maxValue);
  blueLedValue = map(blueInputValue, minInitialValue, maxInitialValue, minValue, maxValue);

  setColor(redLedValue, greenLedValue, blueLedValue);
}
