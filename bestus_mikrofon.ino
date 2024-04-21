#include <Servo.h> 

Servo servo; // servo object representing the MG 996R servo


#define sound_sensorL  A1
#define sound_sensorR  A2/ //assign to pin A2

int eps =5; 
int krok=1;
int current = 90;
void setup() 
{
  Serial.begin(9600); //begin Serial Communication
  servo.attach(5);
}
 
void loop()
{
  mikrofon();
}

void mikrofon(){
  servo.write(current);
  Serial.print("LEFT: "); 
  Serial.print(analogRead(A1)); //print the value of sound sensor
  Serial.print("RIGHT: "); 
  Serial.println(analogRead(A2)); 
  while ((analogRead(A1)-analogRead(A2))>eps){
    current=current-krok;
    servo.write(current);
    delay(100);
  }
  while ((analogRead(A2)-analogRead(A1))>eps){
    current=current+krok;
    servo.write(current);
    delay(100);
  }
}
