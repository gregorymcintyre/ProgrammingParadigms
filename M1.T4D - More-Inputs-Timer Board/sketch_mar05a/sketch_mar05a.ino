/*  More-Inputs-Timer Board
 *  5/3/19
 *  Greg McIntyre
 *  
 *  Arduino more than default interrupts and a timer interrupt
 *  
 *  https://github.com/gregorymcintyre/ProgrammingParadigms.git
 *  
 *  
 *  TODO: Tidy up timer setup into functions
 *  
 */

#include "PinChangeInt.h"
 
#define PIR 2
#define BUTTON 11
#define ROTARTY 3

volatile int interruptNumber = 0;

//Pins
const int led_pin = PB5;

//Counter and compare
const uint16_t timer1_load = 0;
const uint16_t timer1_compare = 15625;    //1 second with 1024 scaler


void setup() {
  Serial.begin(9600);
  
  pinMode(PIR, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(ROTARTY, INPUT);
  
  //pinMode(LED_BUILTIN, OUTPUT);
  DDRB |= (1 << led_pin);
  
  attachInterrupt(digitalPinToInterrupt(PIR), externalInterrupt1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARTY), externalInterrupt2, RISING);
  attachPinChangeInterrupt(BUTTON, externalInterrupt3, RISING);

  //reset timer1 control reg A
  TCCR1A = 0;

  //Clear on compare
  TCCR1B &= ~(1<<WGM13);   //CLEAR (0)
  TCCR1B |= (1<< WGM12);   //1

  //set prescaler 1024
  TCCR1B |= (1<< CS12);   //1
  TCCR1B &= ~(1<<CS11);   //0
  TCCR1B |= (1<< CS10);   //1

  //reset timer1 set and compare values
  TCNT1 = timer1_load;
  OCR1A = timer1_compare;

  //enable timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A);

  // enable global interrupts
  sei();

  Serial.println("Program Running...");
  
}

void loop() {
  /*
  switch (interruptNumber) {
    case 0:
      //no event
      break;
    case 1:
      //external 1
      Serial.println("External interrupt 1 has occured (PIR)");
      break;
    case 2:
      //external 2
      Serial.println("External interrupt 2 has occured (Button)");
      break;
    case 3:
      //external 3
      Serial.println("External interrupt 3 has occured (Rotary Dial)");
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
  delay(100);
  
}

ISR(TIMER1_COMPA_vect){
  PORTB ^= (1 << led_pin);
  Serial.println("A Timer interrupt has occured");
}

void externalInterrupt1(){
  interruptNumber = 1;
  Serial.println("External interrupt 1 has occured (PIR)");
}

void externalInterrupt2(){
  delay(1); //bounce
  interruptNumber = 2;
  Serial.println("External interrupt 2 has occured (Rotary)");
}

void externalInterrupt3(){
  delay(1); //bounce
  interruptNumber = 3;
  Serial.println("External interrupt 3 has occured (Button)");
}

