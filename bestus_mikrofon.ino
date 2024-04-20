#include <Servo.h> 

Servo servo; // servo object representing the MG 996R servo


int sound_sensorL = A1;
int sound_sensorR = A2; //assign to pin A2
int soundValueL = 0;
int soundValueR = 0;
int eps =5; 
int krok=1;
int current = 90;
void setup() 
{
  Serial.begin(9600); //begin Serial Communication
  servo.attach(3);
}
 
void loop()
{
  mikrofon();
}

void mikrofon(){
  servo.write(current);
  Serial.print("LEFT: "); 
  Serial.print(analogRead(soundValueL)); //print the value of sound sensor
  Serial.print("RIGHT: "); 
  Serial.println(analogRead(soundValueR)); 
  while ((analogRead(soundValueL)-analogRead(soundValueR))>eps){
    current=current-krok;
    servo.write(current);
    delay(100);
  }
  while ((analogRead(soundValueR)-analogRead(soundValueL))>eps){
    current=current+krok;
    servo.write(current);
    delay(100);
  }
}
