unsigned long currentLapTime = 0;

// Definire pini pentru shift register
const int latchPin = 11; 
const int clockPin = 10; 
const int dataPin = 12;  

// Definire conexiuni pentru pinii de control ai cifrelor
const int segD1 = 4;
const int segD2 = 5;
const int segD3 = 6;
const int segD4 = 7;

// Stocare cifre intr-un array pentru acces usor
int displayDigits[] = {segD1, segD2, segD3, segD4};
const int displayCount = 4; // Numarul de cifre afisate

const int encodingsNumber = 16;

byte byteEncodings[encodingsNumber] = {
  // Reprezentarea binara pentru fiecare caracter
//A B C D E F G DP
    B11111100, // 0
    B01100000, // 1
    B11011010, // 2
    B11110010, // 3
    B01100110, // 4
    B10110110, // 5
    B10111110, // 6
    B11100000, // 7
    B11111110, // 8
    B11110110, // 9
    B11101110, // A
    B00111110, // b
    B10011100, // C
    B01111010, // d
    B10011110, // E
    B10001110  // F
};

// Variabile pentru controlul timpilor de actualizare a afisajului
unsigned long lastIncrement = 0;
unsigned long delayCount = 100; // Intarziere intre actualizari (milisecunde)
unsigned long number = 0;       // Numarul afisat

// Variabile legate de lap
unsigned long lapTimes[4] = {0}; // Array pentru stocarea timpilor de lap
int lapIndex = 0;                // Index pentru a tine evidenta lap-ului curent

// Pini pentru butoane
const int startPauseButtonPin = 2; // Conecteaza butonul Start/Pauza la pinul 2
const int resetButtonPin = 3;      // Conecteaza butonul Reset la pinul 3
const int lapButtonPin = 8;        // Conecteaza butonul Lap la pinul 8

// Flags pentru gestionarea starii butoanelor
bool startPauseButtonPressed = false;
bool resetButtonPressed = false;
bool lapButtonPressed = false;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void setup()
{
    // Initializare pini
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);

    // Initializez pinii pentru cifre si ii setez pe LOW (opriti)
    for (int i = 0; i < displayCount; i++)
    {
        pinMode(displayDigits[i], OUTPUT);
        digitalWrite(displayDigits[i], LOW);
    }

    // Initializez pinii de butoane 
    pinMode(startPauseButtonPin, INPUT_PULLUP);
    pinMode(resetButtonPin, INPUT_PULLUP);
    pinMode(lapButtonPin, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop()
{
    // Verifica daca timpul curent este mai mare decat 'lastIncrement' plus 'delayCount'
    if (millis() - lastIncrement > delayCount)
    {
        // Incrementeaza numarul daca cronometrul ruleaza
        if (!startPauseButtonPressed)
        {
            number++;
        }

        // Asigura ca 'number' se intoarce la 0 dupa ce atinge 9999
        number %= 10000; // Intoarce-te la 0 dupa 9999
        lastIncrement = millis();
    }

    // Verific butonul Start/Pauza
    if (digitalRead(startPauseButtonPin) == LOW && millis() - lastDebounceTime > debounceDelay)
    {
        startPauseInterrupt();
        lastDebounceTime = millis();
    }

    // Verific butonul Reset
    if (digitalRead(resetButtonPin) == LOW && millis() - lastDebounceTime > debounceDelay && startPauseButtonPressed)
    {
        resetInterrupt();
        lastDebounceTime = millis();
    }

    // Verific butonul Lap
    if (digitalRead(lapButtonPin) == LOW && millis() - lastDebounceTime > debounceDelay)
    {
        lapInterrupt();
        lastDebounceTime = millis();
    }

    // Afiseaza valoarea cronometrului pe afișajul cu 7 segmente
    writeNumber(number);
}

// Functie pentru scrierea unui byte in shift register
void writeReg(int digit)
{
    // Pregateste shift register pentru transferul datelor prin setarea pinului latch la LOW
    digitalWrite(latchPin, LOW);
    // Shift out byte-ul care reprezinta cifra curenta la shift register
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    // Fixam datele pe pini prin setarea pinului latch la HIGH
    digitalWrite(latchPin, HIGH);
}

// Functie pentru activarea afisajului pentru o anumita cifra
void activateDisplay(int displayNumber)
{
    for (int i = 0; i < displayCount; i++)
    {
        digitalWrite(displayDigits[i], HIGH);
    }
    digitalWrite(displayDigits[displayNumber], LOW);
}

// Functie pentru afisarea unui numar 
void writeNumber(int number)
{
    // Extrage cifrele individuale din numar
    int digit4 = (number / 1000) % 10;
    int digit3 = (number / 100) % 10;
    int digit2 = (number / 10) % 10;
    int digit1 = number % 10;

    // Afisez cifrele 
    writeReg(byteEncodings[digit1]);
    activateDisplay(3);
    delay(5);

    // Utilizez dp (punctul zecimal) pentru digit2
    writeReg(byteEncodings[digit2] | B00000001);// Setare bit dp la 1
    activateDisplay(2);
    delay(5);

    writeReg(byteEncodings[digit3]); 
    activateDisplay(1);
    delay(5);

    writeReg(byteEncodings[digit4]);
    activateDisplay(0);
    delay(5);
}

// Functie pentru gestionarea intreruperii Start/Pauza
void startPauseInterrupt()
{
    // Gestionare apasare buton Start/Pauza
    if (!resetButtonPressed)
    {
        startPauseButtonPressed = !startPauseButtonPressed;
    }
    else
    {
        // Resetez starea butonului Start/Pauza pentru a incepe dupa resetare
        startPauseButtonPressed = false;
        resetButtonPressed = false;
    }
}

// Functie pentru gestionarea intreruperii Reset
void resetInterrupt()
{
    // Gestionare apasare buton Reset
    resetButtonPressed = true;
    startPauseButtonPressed = false;
    lapButtonPressed = false;
    number = 0;
    for (int i = 0; i < 4; i++)
    {
        lapTimes[i] = 0;
    }
}

// Functie pentru afisarea timpului lap curent
void displayCurrentLapTime()
{
    Serial.print("Timpul curent de lap: ");
    Serial.println(getFormattedTime(currentLapTime));

    // Afisez timpul curent
    writeNumber(currentLapTime);
}

// Functie pentru obtinerea timpului formatat sub forma de sir de caractere
String getFormattedTime(unsigned long timeValue)
{
    // Convertim valoarea timpului in sir de caractere formatat (de ex., "011.0")
    int zecimi = (timeValue % 1000) / 100; // Obtinem zecimile de secundă
    int secunde = (timeValue / 1000) % 60;
    int minute = (timeValue / 60000) % 60;
    String formattedTime = String(minute, DEC) + String(secunde / 10, DEC) + String(secunde % 10, DEC) + "." + String(zecimi, DEC);
    return formattedTime;
}

// Functie pentru gestionarea intreruperii Lap
void lapInterrupt()
{
    // Gestionare apasare buton Lap
    if (!startPauseButtonPressed && !resetButtonPressed)
    {
        lapButtonPressed = true;
        displayCurrentLapTime();
    }
}
