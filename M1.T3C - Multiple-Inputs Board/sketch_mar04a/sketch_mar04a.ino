/*  Multiple-Inputs Board
 *  4/3/19
 *  Greg McIntyre
 *  
 *  Arduino using multiple interrupts
 *  
 *  https://github.com/gregorymcintyre/ProgrammingParadigms.git
 *  
 */
 
#define PIR 2
#define SWITCH 3

int input = 0;
volatile bool LEDstate = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Running...");
  pinMode(LED_BUILTIN, OUTPUT);     //built in LED
  pinMode(PIR, INPUT);
  pinMode(SWITCH, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIR), PIRchange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SWITCH), ButtonPress, RISING);
  
}

void loop() {
  delay(1000);
  
}

void PIRchange()
{
  LEDstate = !LEDstate;
  digitalWrite(LED_BUILTIN, LEDstate);
  Serial.println("Interrupt one has occured");
  
}

void ButtonPress(){
  Serial.println("Interrupt two has occured");
  
}

