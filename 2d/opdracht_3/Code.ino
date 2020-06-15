int led = 13;

int solenoidPin1 = 12;     
int solenoidPin2 = 11;
int solenoidPin3 = 10;
int solenoidPin4 = 9;
int solenoidPin5 = 8;

char currentSolenoidPin; //Selects what solenoid to turn on/off

int potPin1 = 0;
int potVal1;
int potPin2 = 1;
int potVal2;

int solenoidOnTime = 20 ; //how long the solenoide will stay at "HIGH" state

unsigned long delayTime;
unsigned long delayStart = 0; // the time the delay started

bool ledOn = false;

void setup() {
  
  pinMode(solenoidPin1, OUTPUT);
  pinMode(solenoidPin2, OUTPUT);
  pinMode(solenoidPin3, OUTPUT);
  pinMode(solenoidPin4, OUTPUT);
  pinMode(solenoidPin5, OUTPUT);
  pinMode(led, OUTPUT);
  
  digitalWrite(led, LOW); // turn led off
  ledOn = false;

  // start delay
  delayStart = millis();

}

void loop() {
  
  potVal1 = analogRead(potPin1);
  potVal2 = analogRead(potPin2);
 
  delayTime = (potVal2);//pot 2 controls solenoid speed

  //pot 1 controls the selection of solenoid (frequency)
  if(potVal1 <= 203) {
    currentSolenoidPin = solenoidPin1;
  }
  if((potVal1 >= 204) && (potVal1 <= 407)) {
    currentSolenoidPin = solenoidPin2;
  }
  if((potVal1 >= 408) && (potVal1 <= 612)) {
    currentSolenoidPin = solenoidPin3;
  }
  if((potVal1 >= 613) && (potVal1 <= 817)) {
    currentSolenoidPin = solenoidPin4;
  }
  if((potVal1 >= 818) && (potVal1 <= 1024)) {
    currentSolenoidPin = solenoidPin5;
  }
 

  // check if delay has timed out
  if ((millis() - delayStart) >= delayTime) {
    delayStart += delayTime; // this prevents drift in the delays
    // toggle the led
    ledOn = !ledOn;
    digitalWrite(currentSolenoidPin, HIGH); // turn solenoid on
    delay(solenoidOnTime); 
    digitalWrite(currentSolenoidPin, LOW); // turn solenoid off
    }
    if (ledOn) {
      digitalWrite(led, HIGH); // turn led on
    } else {
      digitalWrite(led, LOW); // turn led off
    }
}
