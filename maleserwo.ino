
int pozycja = 90
void setup() {
  // put your setup code here, to run once:
servo2.attach(6);
servo2.write(pozycja);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void maleserwo(){
  for (int i = 0; i<4;i++){
  servo2.write(pozycja+15);
  delay(100);
  servo2.write(pozycja -15));
  delay(100);
  }
  servo2.write(pozycja);
}