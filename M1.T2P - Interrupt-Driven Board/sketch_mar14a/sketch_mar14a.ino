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
#define LED_PIN 5

int input = 0;
volatile bool LEDstate = false;

ISR(INT0_vect)
{
  //LEDstate = !LEDstate;
  //digitalWrite(LED_BUILTIN, LEDstate);
  PORTD ^= (1 << LED_PIN);
  
  Serial.println("Interrupt has occured");
  puts("Interrupt has occured");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Program Running...");
  puts("Program Running...");
  
  //pinMode(LED_BUILTIN, OUTPUT);     //built in LED
  DDRD |= (1<<LED_PIN);
  
  //pinMode(PIR, INPUT);
  DDRD &= ~(1 << PIR);    //PIR Input
  
  //attachInterrupt(digitalPinToInterrupt(PIR), change, CHANGE);
  //falling edge TODO CHANGE
  EICRA |= (1 << ISC01);
  EICRA &= ~(1 << ISC00);

  //ENABLE interrupts on INT0
  EIMSK |= (1 << INT0);

  //set Global interrupts
  sei();

  
}

void loop() {
  delay(1000);
  
}
