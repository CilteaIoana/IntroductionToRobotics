const int DEBOUNCE_DELAY_MS = 50;  // Timpul de debounce pentru butoane 
const int TRAVEL_TIME_MS = 2000;   // Durata calatoriei intre etaje 
const int BLINK_INTERVAL_MS = 100; 
const int DOOR_OPERATION_DELAY_MS = 200; // Timpul de operare a usii 
const int WAIT_TIME_MS = 2500;     //Timpul de asteptare cand usa este deschisa
const int blinkLedPin = 13;        
unsigned lastBlinkTime;            
bool isBlinkOn = false;            

const int NUM_FLOORS = 3;         

int elevatorLeds[NUM_FLOORS] = {10, 11, 12};  // Pini pentru LED-uri
int elevatorButtons[NUM_FLOORS] = {2, 3, 4}; // Pini pentru butoane
bool buttonIsPressed[NUM_FLOORS] = {false, false, false}; 
int buttonReading[NUM_FLOORS] = {LOW, LOW, LOW}; 
int buttonState[NUM_FLOORS] = {LOW, LOW, LOW};   
int lastButtonStateChange[NUM_FLOORS] = {0, 0, 0}; 
int lastDebounceTime[NUM_FLOORS] = {0, 0, 0}; 

int currentFloorIndex = 0;        
int elevatorCurrentFloor = 0; 
int doorState = 1;                
int doorOperationTime;  
int doorOpenTime = 0;   
int elevatorState = 0;            
int travelStartTime;    

void setup() {
  for (int i = 0; i < NUM_FLOORS; i++) {
    pinMode(elevatorButtons[i], INPUT_PULLUP); 
    pinMode(elevatorLeds[i], OUTPUT);         
    digitalWrite(elevatorLeds[i], LOW);       
  }
  digitalWrite(elevatorLeds[elevatorCurrentFloor], HIGH); // Aprind LED-ul pentru etajul curent

  pinMode(blinkLedPin, OUTPUT);
  Serial.begin(9600); 
}

void manageBlink() {
  bool isMoving = (elevatorState == 2 || elevatorState == -2);

  if (isMoving) {
    if (millis() > lastBlinkTime + BLINK_INTERVAL_MS) {
      isBlinkOn = !isBlinkOn; 
      digitalWrite(blinkLedPin, isBlinkOn); 
      lastBlinkTime = millis(); 
    }
  } else {
    isBlinkOn = true; 
    digitalWrite(blinkLedPin, isBlinkOn);
  }
}

void loop() {
  manageBlink(); 

  buttonReading[currentFloorIndex] = digitalRead(elevatorButtons[currentFloorIndex]);
  if (buttonReading[currentFloorIndex] != lastButtonStateChange[currentFloorIndex]) {
    lastDebounceTime[currentFloorIndex] = millis(); 
  }

  if (millis() - lastDebounceTime[currentFloorIndex] > DEBOUNCE_DELAY_MS) {
    if (buttonReading[currentFloorIndex] != buttonState[currentFloorIndex]) {
      buttonState[currentFloorIndex] = buttonReading[currentFloorIndex];
      if (buttonState[currentFloorIndex] == LOW) {
        buttonIsPressed[currentFloorIndex] = true; // Butonul este apasat
      }
    }
  }

  lastButtonStateChange[currentFloorIndex] = buttonReading[currentFloorIndex];

  if (doorState == -2) {
    if (millis() >= doorOperationTime + DOOR_OPERATION_DELAY_MS) {
      doorState = 0; 
      travelStartTime = millis();
    }
  } else if (doorState == -1) {
    if (millis() >= doorOperationTime + DOOR_OPERATION_DELAY_MS) {
      doorState = 1; // Usa se deschide complet
      doorOpenTime = millis();
    }
  } else if (doorOpenTime + WAIT_TIME_MS <= millis()) {
    if (elevatorState == 0) {
      for (int i = 0; i < NUM_FLOORS; i++) {
        if (buttonIsPressed[i] && i != elevatorCurrentFloor) {
          if (i > elevatorCurrentFloor) {
            elevatorState = 2;
          } else {
            elevatorState = -2;
          }

          doorState = -2; // Usa se inchide
          doorOperationTime = millis();
          travelStartTime = millis();
          break;
        }
      }
    } else if (elevatorState == 1) {
      for (int i = elevatorCurrentFloor + 1; i < NUM_FLOORS; i++) {
        if (buttonIsPressed[i]) {
          elevatorState = 2; 
          doorState = -2; 
          doorOperationTime = millis();
          travelStartTime = millis();
          break;
        }
      }
      if (elevatorState == 1) {
        elevatorState = 0; 
      }
    } else if (elevatorState == -1) {
      for (int i = elevatorCurrentFloor - 1; i >= 0; i--) {
        if (buttonIsPressed[i]) {
          elevatorState = -2; 
          doorState = -2; 
          doorOperationTime = millis();
          travelStartTime = millis();
          break;
        }
      }
      if (elevatorState == -1) {
        elevatorState = 0; 
      }
    } else if (elevatorState == 2) {
      if (millis() >= travelStartTime + TRAVEL_TIME_MS) {
        digitalWrite(elevatorLeds[elevatorCurrentFloor], LOW);
        elevatorCurrentFloor++;
        digitalWrite(elevatorLeds[elevatorCurrentFloor], HIGH); 
        elevatorState = 1; 
        if (buttonIsPressed[elevatorCurrentFloor]) {
          doorState = -1; 
          doorOperationTime = millis();
        }
      }
    } else if (elevatorState == -2) {
      if (millis() >= travelStartTime + TRAVEL_TIME_MS) {
        digitalWrite(elevatorLeds[elevatorCurrentFloor], LOW);
        elevatorCurrentFloor--;
        digitalWrite(elevatorLeds[elevatorCurrentFloor], HIGH); 
        elevatorState = -1; 
        if (buttonIsPressed[elevatorCurrentFloor]) {
          doorState = -1; 
          doorOperationTime = millis();
        }
      }
    }
  }

  if (doorState == 1) {
    buttonIsPressed[elevatorCurrentFloor] = false; 
  }
  currentFloorIndex = (currentFloorIndex + 1) % NUM_FLOORS; 
}
