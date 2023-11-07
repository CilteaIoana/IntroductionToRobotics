// Definirea pinilor pentru segmentele LED
const int pinA = 12;
const int pinB = 10;
const int pinC = 9;
const int pinD = 8;
const int pinE = 7;
const int pinF = 6;
const int pinG = 5;
const int pinDP = 4;

// Definirea pinilor pentru joystick (X, Y) si butonul SW
const int pinX = A0;
const int pinY = A1;
const int pinSW = 2;

const int minThreshold = 400;  // Prag minim pentru joystick
const int maxThreshold = 700;  // Prag maxim pentru joystick

// Starea initiala a joystick-ului si butonului SW
bool joyIsNeutral = true;  // Indicator pentru a verifica daca joystick-ul este in pozitie neutra
bool pinSWState = HIGH;    // Starea curenta a butonului SW
bool pinSWPrevState = HIGH;  // Starea anterioara a butonului SW

int currentState = 1;      // 1 - Stare de miscare, 2 - Stare de afisare
const int segSize = 8;     // Numarul total de segmente LED
int currentPosition = segSize - 1;  // Initializarea pozitiei curente la ultimul segment (adica la punct)

bool commonAnode = false;  

// Array pentru stocarea pinilor fiecarui segment LED
int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

// Array pentru stocarea starii segmentelor LED (pornite/oprite)
byte segmentsValues[segSize] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

// Matricea pentru miscarea joystick-ului
int movementsMatrix[segSize][4] = {
  // Fiecare linie reprezinta un segment (a, b, c, d, e, f, g, dp)
  // Valorile reprezinta directiile (deplasarea segmentului curent in functie de joystick)
  // De exemplu: {-1, 6, 5, 1} inseamna ca segmentul a se poate muta in sus (0 este pozitia sa curenta), in dreapta (6), in jos (5) sau inapoi (1)
  {-1, 6, 5, 1}, // a
  {0, 6, 5, -1}, // b
  {6, 3, 4, 7},  // c
  {6, -1, 4, 2}, // d
  {6, 3, -1, 2}, // e
  {0, 6, -1, 1}, // f
  {0, 3, -1, -1}, // g
  {-1, -1, 2, -1}, // dp
};

// Momentul ultimei clipiri a segmentelor LED pentru efectul de clipire
unsigned long lastBlink = 0;
const int blinkInterval = 500;  // Intervalul de timp pentru efectul de clipire
int blinkValue = LOW;           // Starea actuala a clipirii (aprins/stins)

// Momentul ultimei apasari a butonului SW
unsigned long lastPinSWPress = 0;
const int pinSWPressThreshold = 700;  // Pragul pentru o apasare valida a butonului SW

// Initializarea pinilor si starea butonului SW in functia de initializare
void setup() {
  for (int i = 0; i < segSize; i++) 
    pinMode(segments[i], OUTPUT);  // Initializeaza pinii segmentelor LED ca iesiri
  pinMode(pinSW, INPUT_PULLUP);  // Initializeaza pinul butonului SW 
}

void loop() {
  int pinXValue = analogRead(pinX);  // Citeste valoarea pinului X al joystick-ului
  int pinYValue = analogRead(pinY);  // Citeste valoarea pinului Y al joystick-ului
  
  // Verifica daca a sosit momentul de a schimba starea efectului de clipire
  if (millis() - lastBlink > blinkInterval) {
    blinkValue = !blinkValue;  
    lastBlink = millis();  // Actualizeaza momentul ultimei clipiri
  }

  if (currentState == 1)  // Stare de miscare a joystick-ului
    move(pinXValue, pinYValue);  // Apel la functia care manipuleaza miscarea segmentelor
  else if ((pinXValue > maxThreshold && joyIsNeutral) || (pinXValue < minThreshold && joyIsNeutral)) {
    segmentsValues[currentPosition] = !segmentsValues[currentPosition];  // Inverteaza starea led-ului curent
    joyIsNeutral = false;  // Joystick-ul nu mai este in pozitie neutra
  }

  // Verifica daca joystick-ul a revenit la pozitia neutra
  if (pinXValue > minThreshold && pinXValue < maxThreshold && pinYValue > minThreshold && pinYValue < maxThreshold) 
    joyIsNeutral = true;
  
  setSegments();  // Apel la functia care afiseaza starea segmentelor pe LED-uri

  pinSWState = digitalRead(pinSW);  // Citeste starea curenta a butonului SW
  if (pinSWState != pinSWPrevState) {  // Verifica daca starea butonului SW s-a schimbat
    if (pinSWState == LOW) {
      lastPinSWPress = millis();  // Daca butonul SW a fost apasat, retine momentul apasarii
    }
    else {
      if (millis() - lastPinSWPress < pinSWPressThreshold) 
        segmentsValues[currentPosition] = !segmentsValues[currentPosition];  // Schimba starea LED-ului curent
      else 
        resetDisplay();  // Daca butonul SW a fost apasat pentru o perioada mai lunga, reseteaza afisajul     
    }
  }
  pinSWPrevState = pinSWState;  // Actualizeaza starea anterioara a butonului SW
}

// Functia care afiseaza starea segmentelor pe LED-uri
void setSegments() {
  if (currentState == 1)
    digitalWrite(segments[currentPosition], blinkValue);  // Afiseaza efectul de clipire pe segmentul curent
  for (int i = 0; i < segSize; i++) 
    if (currentState == 2 || i != currentPosition)
      digitalWrite(segments[i], segmentsValues[i] ^ commonAnode);  // Afiseaza starea segmentelor pe LED-uri
}

// Functia care manipuleaza miscarea segmentelor pe baza joystick-ului
void move(int pinXValue, int pinYValue){
  int nextLed = -1;  // Initializeaza pozitia segmentului in care se va face urmatoarea miscare
  if (pinXValue > maxThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][0];  // Sus
  if (pinXValue < minThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][1];  // Jos
  if (pinYValue < minThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][2];  // Stanga
  if (pinYValue > maxThreshold && joyIsNeutral) 
    nextLed = movementsMatrix[currentPosition][3];  // Dreapta
  if (nextLed != -1)
      currentPosition = nextLed;  // Actualizeaza pozitia segmentului curent
  joyIsNeutral = false;  // Joystick-ul nu mai este in pozitie neutra
}

// Functia care reseteaza afisajul
void resetDisplay() {
  for (int i = 0; i < segSize; i++)
    segmentsValues[i] = LOW;  // Reseteaza starea tuturor segmentelor LED
  currentPosition = segSize - 1;  // Reseteaza pozitia curenta la ultimul segment
  currentState = 1;  // Seteaza starea curenta la starea de miscare
}
