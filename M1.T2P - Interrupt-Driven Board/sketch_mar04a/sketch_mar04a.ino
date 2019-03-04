/*  Interrupt-driven Board
 *  4/3/19
 *  Greg McIntyre
 *  
 *  Interrupt implementation of T1
 *  
 *  https://github.com/gregorymcintyre/ProgrammingParadigms.git
 *  
 */
 
#define PIR 2

int input = 0;
volatile bool LEDstate = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Running...");
  pinMode(LED_BUILTIN, OUTPUT);     //built in LED
  pinMode(PIR, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIR), change, CHANGE);
}

void loop() {
  delay(1000);
  
}

void change()
{
  LEDstate = !LEDstate;
  digitalWrite(LED_BUILTIN, LEDstate);
  Serial.println("Interrupt has occured");
}

