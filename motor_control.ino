#include <LiquidCrystal.h>

LiquidCrystal lcd(13,11,5,4,3,6);

int target_speed=0,lasttar=-1;
int sim_speed=0,lastsim=-1;
bool currentDirection = true;
bool firstRun = true;

void setup()
{
  lcd.begin(16,2);
  pinMode(12,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
}

void reverse(bool change){
  analogWrite(9,LOW);
  delay(200);
  digitalWrite(7,change);
  digitalWrite(8,!change);
  currentDirection = change;
}

void alert()
{
  int melody[] = {
    587, 659, 698, 659,
    880, 880, 784, 698,
    659, 587, 523
  };

  int duration[] = {
    250, 250, 250, 250,
    500, 250, 250, 250,
    250, 500, 750
  };

  for (int i = 0; i < 11; i++) {
    tone(12, melody[i], duration[i]);
    delay(duration[i] * 1.3);
  }

  noTone(12);
}

void loop()
{
  target_speed=map(analogRead(A0),0,1023,0,255);
  bool clkwise=(target_speed>127);
  if (firstRun || clkwise != currentDirection) {
    reverse(clkwise);
    firstRun = false;
  }
  
  int error = target_speed - sim_speed;
  if(error>0) sim_speed+=1;
  else if(error<0) sim_speed-=1;
  else alert();
  
  analogWrite(9,sim_speed);
  
  if(lasttar!=target_speed){
  	lcd.setCursor(0,0);
  	lcd.print("Target:");
    lcd.print(target_speed);
    lcd.print("   ");
    lasttar=target_speed;
  }
  if(lastsim!=sim_speed){
  	lcd.setCursor(0,1);
  	lcd.print("Current:");
    lcd.print(sim_speed);
    lcd.print("   ");
    lastsim=sim_speed;
  }
  delay(20);
}