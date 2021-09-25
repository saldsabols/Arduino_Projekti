int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 1000;  

boolean lockLow = true;
boolean takeLowTime;  
boolean buttonPressed;

int pirPin = 7;    //the digital pin connected to the PIR sensor's output
int ledPin = 5;    //the digital pin connected to the LED output
int Buzzer = 6;    //the digital pin connected to the BUZZER output
int buttonPin = 8;    //Button

/////////////////////////////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(pirPin, LOW);
  digitalWrite(buttonPin, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

////////////////////////////
//LOOP
void loop(){
     digitalWrite(buttonPin, LOW);
     delay(1000);
     if (digitalRead(buttonPin) == HIGH) {
      noTone(Buzzer);
        Serial.println("Button pressed");
        Serial.println("5");
        delay(1000);
        Serial.println("4");
        delay(1000);
        Serial.println("3");
        delay(1000);
        Serial.println("2");
        delay(1000);
        Serial.println("1");
        delay(1000);
        if (digitalRead(buttonPin) == HIGH) {
          Serial.println("button - done");
          buttonPressed = true;
        }
        
        while (buttonPressed = true){
          Serial.println("Waiting for action...");
          delay(2000);
          if (digitalRead(buttonPin) == HIGH) {
            delay(2000);
            buttonPressed = false;
            digitalWrite(buttonPin, LOW);
            break;
          }
        }
       }
       
       else {

        if(digitalRead(pirPin) == HIGH){
      Serial.println("HIGH");
      delay(100);
          digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state

         tone(Buzzer,500);
         if(lockLow){  
           //makes sure we wait for a transition to LOW before any further output is made:
           lockLow = false;            
           Serial.println("---");
           Serial.print("motion detected at ");
           Serial.print(millis()/1000);
           Serial.println(" sec"); 
           delay(50);
           }         
           takeLowTime = true;
       }
       
       }

     if(digitalRead(pirPin) == LOW){
      Serial.println("LOW");
      delay(100);       
       digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
       noTone(Buzzer);
       if(takeLowTime){
        lowIn = millis();          //save the time of the transition from high to LOW
        takeLowTime = false;       //make sure this is only done at the start of a LOW phase
        }
       //if the sensor is low for more than the given pause, 
       //we assume that no more motion is going to happen
       if(!lockLow && millis() - lowIn > pause){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
           lockLow = true;                        
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
           }
       }
  }
