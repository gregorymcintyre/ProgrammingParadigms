#define PIR 2

int input = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Program Running...");
  pinMode(LED_BUILTIN, OUTPUT);     //built in LED
  pinMode(PIR, INPUT);
  
}

void loop() {
  input = digitalRead(PIR);
  //Serial.println(input);
  if(input){
    digitalWrite(LED_BUILTIN, 1);
    Serial.println("Motion Detected");
  }else{
    digitalWrite(LED_BUILTIN, 0);
    Serial.println("Motion Has ceased");
  }
  
  delay(1000);
  
}
