//Pins
const int led_pin = PB5;

//Counter and compare
const uint16_t timer1_load = 0;
const uint16_t timer1_compare = 31250;
/*
 * 
 */


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  //pinMode(LED_BUILTIN, OUTPUT);
  DDRB |= (1 << led_pin);

  //reset timer1 control reg A
  TCCR1A = 0;

  //Clear on compare
  TCCR1B &= ~(1<<WGM13);   //CLEAR
  TCCR1B |= (1<< WGM12);   //1

  //set prescaler
  TCCR1B |= (1<< CS12);   //1
  TCCR1B &= ~(1<<CS11);   //0
  TCCR1B &= ~(1<<CS10);   //0

  //reset timer1 set and compare values
  TCNT1 = timer1_load;
  OCR1A = timer1_compare;

  //enable timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A);

  // enable global interrupts
  sei();
  
}

// the loop function runs over and over again forever
void loop() {
  //PORTB ^= (1 << led_pin);
  delay(500);
}

ISR(TIMER1_COMPA_vect){
  //TCNT1 = timer1_load;
  PORTB ^= (1 << led_pin);
}

