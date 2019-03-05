/*  More-Inputs-Timer Board
 *  5/3/19
 *  Greg McIntyre
 *  
 *  Arduino more than default interrupts and a timer interrupt
 *  
 *  https://github.com/gregorymcintyre/ProgrammingParadigms.git
 *  
 */
 
#define PIR 2
#define SWITCH 3
#define SOUND 4

volatile int interruptNumber = 0;
bool LEDstate = false;


void setup() {
  Serial.begin(9600);
  Serial.println("Program Running...");

  pinMode(PIR, INPUT);
  pinMode(SWITCH, INPUT);
  pinMode(SOUND, INPUT);
  
  //attachInterrupt(digitalPinToInterrupt(PIR), externalInterrupt1, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(SWITCH), externalInterrupt2, RISING);
  //attachInterrupt(digitalPinToInterrupt(SOUND), externalInterrupt3, RISING);

  
  
}

void loop() {
  /*
  switch (interruptNumber) {
    case 0:
      //no event
      break;
    case 1:
      //external 1
      Serial.println("External interrupt 1 has occured");
      break;
    case 2:
      //external 2
      Serial.println("External interrupt 2 has occured");
      break;
    case 3:
      //external 3
      Serial.println("External interrupt 3 has occured");
      break;
    case 4:
      //timer
      LEDstate = !LEDstate;
      digitalWrite(LED_BUILTIN, LEDstate);
      Serial.println("A Timer interrupt has occured");
      break;
    default:
      Serial.println("Something unexpected has happened");
      break;
  }
  interruptNumber = 0; //reset interrupt 'register'
  */
  
}


void timerInterrput(){
  interruptNumber = 4;
}

void externalInterrupt1(){
  interruptNumber = 1;
}

void externalInterrupt2(){
  interruptNumber = 2;
}

void externalInterrupt3(){
  interruptNumber = 3;
}

