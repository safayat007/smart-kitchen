#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int lpg_sensor = A0;
int buzzer = 13;
int fan = 10;
int green = 9;
int red = 8;


void setup() 
{
  pinMode(lpg_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  pinMode(red, OUTPUT);
  digitalWrite(red, LOW);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);

  lcd.begin(16, 2);
  lcd.setCursor (0,0);
  lcd.print ("   Welcome To   ");
  lcd.setCursor (0,1);
  lcd.print (" SMART  KITCHEN ");
  delay(3000);
  lcd.setCursor (0,0);
  lcd.print ("    Made  By     ");
  lcd.setCursor (0,1);
  lcd.print (" Team  INFINITY ");
  delay(4000);
  Serial.begin(9600);
}

void loop() 
{
  int analogSensor = analogRead(lpg_sensor);
  Serial.println(analogSensor);
  
  lcd.setCursor (0, 0);
  lcd.print (" SMART  KITCHEN ");
  lcd.setCursor (0,1);
   if (analogSensor > 230)
  {
    lcd.print(" Leakage  Found ");
    digitalWrite(red, HIGH);
    digitalWrite(fan, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(300);
 
  }
  
  else  {
    lcd.print("   No Leakage   ");
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    digitalWrite(fan, LOW);
    digitalWrite(buzzer, LOW);
  }
}
