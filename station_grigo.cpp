#include <StandardCplusplus.h>
#include <iostream>
byte foto = A0;
bool lighlow = 0;
bool lighthigh = 1;
bool value = 0;
int timerlow=0;
int timerhigh=0;
long time2;
long time1;
String message = "";
String messagefor1="";
String messagefor1="0";
using namespace std;
void setup() {
  Serial.begin(9600);
  pinMode(foto,INPUT_PULLUP);
  time1 = millis();
  time2 = millis();

  // put your setup code here, to run once:

}

void loop() {
  if(analogRead(foto)<=50){
    timerhigh++;
    delay(1);
    if(timerhigh = 50){
      value = lighthigh;
      timerhigh=0;
      messagefor1="1"
    }
  }
  if(analogRead(foto)>50){
    timerlow++;
    delay(1);
    if(timerhigh = 50){
      value = lighlow;
      timerlow = 0;
      messagefor0="0" 
    }
  }
  message= messagefor1 + messagefor0;
  if ((time1-time2)<=350){
    Serial.println(message);
    message = 0;
    time 2 = millis()+100;
  }
  delay(50);
  time2=time2-50;
}
