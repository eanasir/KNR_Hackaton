int PinSerducho = 6;    

void setup()  { 
} 


void serducho() {
  for(int fadeValue = 0 ; fadeValue <= 255; fadeValue +=5) { 
    // sets the value (range from 0 to 255):
    analogWrite(PinSerducho, fadeValue);         
    // wait for 20 milliseconds to see the dimming effect    
    delay(30);} 
  for(int fadeValue = 200 ; fadeValue >= 0; fadeValue -=5) { 
    // sets the value (range from 0 to 200):
    analogWrite(PinSerducho, fadeValue);         
    // wait for 30 milliseconds to see the dimming effect    
    delay(30);} }


void loop()  { 
  serducho();
}
