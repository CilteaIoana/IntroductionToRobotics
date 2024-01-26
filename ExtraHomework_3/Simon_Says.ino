const byte BUZZER = 7;
const byte INPUT_A = 13;
const byte INPUT_B = 12;
const byte INPUT_C = 11;
const byte INPUT_D = 10;
const byte OUTPUT_A = 2;
const byte OUTPUT_B = 3;
const byte OUTPUT_C = 4;
const byte OUTPUT_D = 5;

const byte LED_GREEN = 8;
const byte LED_RED = 9;

int currentLevel = 1;
int speed = 500;
const int MAX_LEVEL = 100; 
int sequence[MAX_LEVEL];
int userSequence[MAX_LEVEL];

void setup(){
  pinMode(INPUT_A, INPUT);
  pinMode(INPUT_B, INPUT);
  pinMode(INPUT_C, INPUT);
  pinMode(INPUT_D, INPUT);
  pinMode(OUTPUT_A, OUTPUT);
  pinMode(OUTPUT_B, OUTPUT);
  pinMode(OUTPUT_C, OUTPUT);
  pinMode(OUTPUT_D, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(OUTPUT_A, LOW);
  digitalWrite(OUTPUT_B, LOW);
  digitalWrite(OUTPUT_C, LOW);
  digitalWrite(OUTPUT_D, LOW);   
}

void loop(){
   if(currentLevel == 1){
      generateSequence();
      showSequence();
      readSequence();
   }
   if(currentLevel != 1){
      showSequence();
      readSequence();
   }
}

// Arata secventa folosind tonuri si LED-uri
void showSequence(){
   digitalWrite(OUTPUT_A, LOW);
   digitalWrite(OUTPUT_B, LOW);
   digitalWrite(OUTPUT_C, LOW);
   digitalWrite(OUTPUT_D, LOW);
   for(int i = 0; i < currentLevel; i++){
      if(sequence[i] == OUTPUT_A){
         tone(BUZZER, 200);
         delay(200);
         noTone(BUZZER);
      }
      if(sequence[i] == OUTPUT_B){
         tone(BUZZER, 300);
         delay(200);
         noTone(BUZZER);
      }
      if(sequence[i] == OUTPUT_C){
         tone(BUZZER, 400);
         delay(200);
         noTone(BUZZER);
      }
      if(sequence[i] == OUTPUT_D){
         tone(BUZZER, 500);
         delay(200);
         noTone(BUZZER);
      }
      digitalWrite(sequence[i], HIGH);
      delay(speed);
      digitalWrite(sequence[i], LOW);
      delay(200);
   }
}

// Citeste si verifica secventa introdusa de player
void readSequence(){
   int flag = 0; // Flag pentru a indica daca s-a detectat un buton apasat
   for(int i = 0; i < currentLevel; i++){
      flag = 0;
      // Bucla care asteapta ca jucatorul sa apese un buton
      while(flag == 0){
        
        // Verifica daca butonul A este apasat
        if(digitalRead(INPUT_A) == LOW){
          digitalWrite(OUTPUT_A, HIGH); // Aprinde LED-ul A
          tone(BUZZER, 200); // Reda un ton pe buzzer 
          delay(300); 
          noTone(BUZZER); 

          // se inregistreaza ca jucatorul a apasat butonul A
          userSequence[i] = OUTPUT_A; 
          flag = 1; // Seteaza flag-ul pentru a indica detectarea unei apasari

          // daca secventa jucatorului se potriveste cu secventa jocului, apeleaza sequenceError()
          if(userSequence[i] != sequence[i]){
            sequenceError(); 
            return; // Iese din functie daca jucatorul greseste
          }

          // Stinge LED-ul A
          digitalWrite(OUTPUT_A, LOW); 
        }
          
          //se face aceleasi lucruri si pentru restul butoanelor
         if(digitalRead(INPUT_B) == LOW){
            digitalWrite(OUTPUT_B, HIGH);
            tone(BUZZER, 300);
            delay(300);
            noTone(BUZZER);
            userSequence[i] = OUTPUT_B;
            flag = 1;
            delay(200);
            if(userSequence[i] != sequence[i]){
               sequenceError();
               return;
            }
            digitalWrite(OUTPUT_B, LOW);
         }


         if(digitalRead(INPUT_C) == LOW){
            digitalWrite(OUTPUT_C, HIGH);
            tone(BUZZER, 400);
            delay(300);
            noTone(BUZZER);
            userSequence[i] = OUTPUT_C;
            flag = 1;
            delay(200);
            if(userSequence[i] != sequence[i]){
               sequenceError();
               return;
            }
            digitalWrite(OUTPUT_C, LOW);
         }

         if(digitalRead(INPUT_D) == LOW){
            digitalWrite(OUTPUT_D, HIGH);
            tone(BUZZER, 500);
            delay(300);
            noTone(BUZZER);

            userSequence[i] = OUTPUT_D;
            flag = 1; 

            if(userSequence[i] != sequence[i]){
               sequenceError();
               return; 
            }
            digitalWrite(OUTPUT_D, LOW);
         }
      }
   }
   sequenceCorrect();
}

// Genereaza o noua secventa aleatoare
void generateSequence(){
   randomSeed(millis());
   for(int i = 0; i < MAX_LEVEL; i++){
      sequence[i] = random(2, 6);
   }
}

// Sunet pentru cand secventa introdusa este gresita
void errorMelody(){
    tone(BUZZER, 100, 300);
    delay(350);
    noTone(BUZZER);
}

// actiuni in cazul unei secvente gresite
void sequenceError(){
    errorMelody();
    currentLevel = 1;
    speed = 500;
    digitalWrite(LED_RED, HIGH);
    delay(200);
    digitalWrite(LED_RED, LOW);
}

// actiuni in cazul unei secvente corecte
void sequenceCorrect(){
    if(currentLevel < MAX_LEVEL)
        currentLevel++;
    speed -= 50;
    playSuccessTone();
    digitalWrite(LED_GREEN, HIGH);
    delay(200);
    digitalWrite(LED_GREEN, LOW);
}

// sunet pentru cand secventa introdusa este corecta
void playSuccessTone(){
    tone(BUZZER, 1000, 100);
    delay(150);
    tone(BUZZER, 1500, 100);
    delay(150);
}
