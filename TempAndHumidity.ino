//DHT11 Sensor:
#include "DHT.h"
#define DHTPIN 8     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
#define LED 9 //digital pin connected to led 
#define FAN 10 //digital pin connected to fan

DHT dht(DHTPIN, DHTTYPE);


//I2C LCD:
#include <Wire.h> // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h> // Library for LCD

// Set the LCD I2C address
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adress for 16x2 LCD.

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2);
  Serial.println("Dennis Fundi Temp and Humidity Sensor");
  dht.begin();
  pinMode(LED,OUTPUT);
  pinMode(FAN,OUTPUT);
  digitalWrite(LED,LOW);
  digitalWrite(FAN,LOW);
  
}

void loop() {
    // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  int rh = dht.readHumidity();
  int t = dht.readTemperature();

  if (isnan(rh) || isnan(t)){
    Serial.println("failed to read from DHT");
    lcd.print("DHT ERROR");
    return;
  }
  delay(2000);
  lcd.setCursor(0,0);
  // print from 0 to 9:
  lcd.clear();

   lcd.print("Temp: ");
   lcd.print(t);
   lcd.print("C");
  
  // set the cursor to (16,1):
  lcd.setCursor(0,1);
  lcd.print("Humidity:");
  lcd.print(rh);
  lcd.print(" %RH");
  delay(2000);
    
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.print("C, Humidity: ");
  Serial.print(rh);
  Serial.println("%");
  delay(2000);
  

  if (t >22){
  digitalWrite(LED, LOW);
  lcd.setCursor(0,1);
  lcd.clear();
  lcd.print("temp is ok"); 
  lcd.setCursor(1,1);
  lcd.print("LED is OFF "); 
  delay(1000);
}
  else{
  digitalWrite(LED, HIGH);
  lcd.setCursor(0,1);
  lcd.clear();
  lcd.print("low temp");
  lcd.setCursor(1,1); 
  lcd.print("LED is ON "); 
  delay(2000);
}

  if(rh>=15){
    digitalWrite(FAN,HIGH);
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.print("high humidity");
    lcd.setCursor(1,1);
    lcd.print("FAN is ON");
    delay(2000);
  }
  else{
    digitalWrite(FAN, LOW);
    lcd.setCursor(0,1);
    lcd.clear();
    lcd.print("normal humidity");
    lcd.setCursor(1,1);
    lcd.print("FAN is OFF");
    delay(2000);
    
  }

 
}
