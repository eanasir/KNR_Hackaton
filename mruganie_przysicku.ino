int LED_PRZYCISK=13;      //  
                          //    !!! zadeklarowanie analoga sterującego mruganiem diody
                          //
                         

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize digital pin LED_PRZYCISK as an output.
  pinMode(LED_PRZYCISK, OUTPUT);
}


void mrygajacy_przycisk() {
  
  
  digitalWrite(LED_PRZYCISK, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_PRZYCISK, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}



// the loop function runs over and over again forever
void loop() {
  mrygajacy_przycisk();  // call the blink function
}
