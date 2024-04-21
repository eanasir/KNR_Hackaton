#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "bitmapy.h"
#include "hackathon.h"
#include <DS3231.h>
#include <RTC.h>
#include <Servo.h> 



#define i2c_Address 0x3c // adres wysweitlacza
#define trigPin 13 // pin triggerujacy hc sr04
#define echoPin 12 // echo z hc sr04
#define bezpiecznyDystans 5




DS3231 rtc; //zegar czasu rzeczywistego
Servo servo1; //servo mg996r
Servo servo2; // servo 270
String displayString; //string do wyswetlania czasu

int buttonPin = 2; // przycisk do pomodoro
int mode = 1; // zmeinna do switch case'a

//DEFINICJE MIKROFON//
int sound_sensorL = A1;
int sound_sensorR = A2; //assign to pin A2
int soundValueL = 0;
int soundValueR = 0;
int eps =5; 
int krok=1;
int current = 90;
//KONIEC DEFINICJII//

int counter = 0;

//DEFINICJA SERWO2
int pozycja = 90;
//

//DEFINICJE MRUCZENIE//
int STBY = 7; // standby
int PWMA = 3; // Speed control
int AIN2 = 8; // Direction
int mruczeniePin = A3; // Button connected to pin 2
int PinSerducho = 9;   
////////
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1   //   QT-PY / XIAO
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint64_t lastDebounceTime = 0; // czas dzialnia czujnika
uint64_t debouncingTime = 100; // czas, prze ktory musi dzialc czujnik by zazialla w milisekundach

int timerMinutes;
int timerSeconds;
unsigned long timerPrevMillis = 0;

bool h24,hPM;
;




void setup() {
  Serial.begin(9600);
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  // INICJALIZACJA OLEDA
  delay(250); // wait for the OLED to power up
  display.begin(i2c_Address, true); // Address 0x3C default
  display.clearDisplay();
  delay(2000);
  //KONIEC INICJALIZACJI OLEDA

  //INICJALIZACJA HC SR04
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin,INPUT_PULLUP);
  //KONIEC INICJALIZACJI

  //INICJALIZACJA RTC//
  
  rtc.setClockMode(false);
  rtc.setDoW(6);
  rtc.setYear(24);
  rtc.setMonth(4);
  rtc.setDate(20);
  rtc.setHour(18);
  rtc.setMinute(9);
 //KONIEC INICJALIZACJI//
 
 //INICJALIZACJA SERWA//
 servo1.attach(5);
 servo2.attach(6);
 servo1.write(pozycja);
 servo2.write(pozycja);
 //KONIEC INICJALIZACJI//

//MRUCZENIE INICJALIZACJA
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(mruczeniePin, INPUT_PULLUP); // Set the button pin as input with pull-up resistor

}

void loop() {
  switch (mode){
    case 1:
    standby();
    //mikrofon();
    //mruczenie();
    serducho();
    break;
    case 0:
    pomodoroMode();
    break;

  }
  
  delay(100);

}
int zmierzOdleglosc() {
  long czas, dystans;
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;
 
  return dystans;
}
void rysujOczko(){
 display.clearDisplay();
 display.drawBitmap(0,0,wesoly,128,64,1);
 display.display();
}
void rysujGniew(){
display.clearDisplay();
 display.drawBitmap(0,0,gniew,128,64,1);
 display.display();
}
void rysujSen(){
display.clearDisplay();
 display.drawBitmap(0,0,sen,128,64,1);
 display.display();
}
int convertTime(){
return rtc.getHour(h24,hPM)*3600 + rtc.getMinute()*60 + rtc.getSecond();
}
void standby(){
  
  if(zmierzOdleglosc() <= bezpiecznyDystans){
    lastDebounceTime = millis();
    if(lastDebounceTime >= debouncingTime){
    rysujGniew();
    counter = 0;
    }
  }
  else {
    lastDebounceTime = millis();
    if(lastDebounceTime >= debouncingTime){
    rysujOczko();
    counter++;
    }
    if(counter > 3){
      animujOczka();
      counter = 0;
    }
 }

 if (digitalRead(mruczeniePin) == HIGH){
  mruczenie();
 }
 if(digitalRead(buttonPin)==LOW){
  mode = 0;
 }
}
void animujOczka(){
  for(int i =0;i < epd_bitmap_allArray_LEN; i++){
    display.clearDisplay();
    display.drawBitmap(0,0,epd_bitmap_allArray[i],128,64,1);
    display.display();
    delay(50);
  }
}
void pomodoroMode(){
  int countdownStart = convertTime();
  int64_t minutes = rtc.getMinute();
  int64_t seconds = rtc.getSecond();
  timerMinutes = 25;
  timerSeconds = 0;
  while(convertTime() - countdownStart < 25000000){

  display.clearDisplay();
  display.setTextSize(2);
  updateTimer();
  updateDisplayString();
  display.setCursor(40,32);
  display.println(displayString);
  display.display();
  if(timerMinutes == 0 && timerSeconds == 0){
    display.clearDisplay();
    display.setCursor(20, 32);
    display.setTextSize(1);
    display.println("Pora na przerwe!");
    display.display();
    delay(3000);
    timerMinutes = 5;
    timerSeconds = 0;
    while(convertTime() - countdownStart < 25000000){
    display.clearDisplay();
    display.setTextSize(2);
    updateTimer();
    updateDisplayString();
    display.setCursor(40,32);
    display.println(displayString);
    display.display();
    if(timerMinutes == 0 && timerSeconds == 0){
      
      display.clearDisplay();
      display.setCursor(20, 32);
      display.setTextSize(1);
      display.println("Koniec przerwy!");
      display.display();
      delay(3000);
      break;
    }
    }
    break;
  }
  }
  mode = 1;
}

void updateTimer() {
  if (timerMinutes > 0 || timerSeconds > 0) {
    if (timerSeconds > 0) {
      timerSeconds--;
    }
    else {
      timerSeconds = 59;
  
      if (timerMinutes > 0)
        timerMinutes--;
    }

    timerPrevMillis = millis();
  }
}

void updateDisplayString() {
  String minutes = String(timerMinutes);
  String seconds = String(timerSeconds);
  
  if (timerMinutes < 10) {
    minutes = "0" + minutes;
  }

  if (timerSeconds < 10) {
    seconds = "0" + seconds;
  }

  displayString = minutes + ":" + seconds;
  
}
void mikrofon(){
  servo1.write(current);
  Serial.print("LEFT: "); 
  Serial.print(analogRead(A1)); //print the value of sound sensor
  Serial.print("RIGHT: "); 
  Serial.println(analogRead(A2)); 
  if((analogRead(A1)-analogRead(A2))>eps){
  
    current=current-krok;
    servo1.write(current);
    delay(200);
  }
    if((analogRead(A2)-analogRead(A1))>eps){
    current=current+krok;
    servo1.write(current);
    delay(200);
  }

}
void mruczenie() {
   

   
   
   digitalWrite(STBY, HIGH);
  // Set motor A speed, 0-255 (255 being the fastest)
  analogWrite(PWMA, 100);
  digitalWrite(AIN2, HIGH);
  delay(5000);// The motor will spin in one direction for 0.5 seconds
  // Enable standby to make the motors stop spinning
  digitalWrite(STBY, LOW);
  
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
    delay(30);} 
    }
void maleserwo(){
  for (int i = 0; i<4;i++){
  servo2.write(pozycja+15);
  delay(100);
  servo2.write(pozycja -15);
  delay(100);
  }
  servo2.write(pozycja);
}
