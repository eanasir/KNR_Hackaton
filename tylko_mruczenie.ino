//  motor mruczenie

// Motor A connected between A01 and A02
int STBY = 9; // standby
// Motor A
int PWMA = 3; // Speed control

int AIN2 = 8; // Direction
int buttonPin = 2; // Button connected to pin 2

void setup() {

//  mruczenie
  
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(AIN2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with pull-up resistor
}

void mruczenie() {
  if (digitalRead(buttonPin) == HIGH) {

      // Disable standby to make the motors run
  digitalWrite(STBY, HIGH);
  // Set motor A speed, 0-255 (255 being the fastest)
  analogWrite(PWMA, 255);

  digitalWrite(AIN2, HIGH);
  delay(500); // The motor will spin in one direction for 0.5 seconds
  // Enable standby to make the motors stop spinning
  digitalWrite(STBY, LOW);


  }
}


void loop() {
 
  mruczenie();
}
