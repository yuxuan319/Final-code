#include <SoftwareSerial.h>
#define vcc 3
#define pls 4
#define dir 5
#define ena 6
int TxD = 11;
int RxD = 10;
SoftwareSerial bluetooth(TxD, RxD);

void setup() {
Serial.begin(9600);       // start serial communication at 9600bps
bluetooth.begin(9600);
pinMode(vcc,OUTPUT);
pinMode(pls,OUTPUT);
pinMode(dir,OUTPUT);
pinMode(ena,OUTPUT);
}

void loop() {
 if (bluetooth.available()){
  String value = bluetooth.readString();
   if (value.toInt() == 1)
   {
  digitalWrite(vcc,HIGH);
  digitalWrite(pls,HIGH);
  digitalWrite(dir,HIGH);
  digitalWrite(ena,HIGH);
  tone(pls,500);
   }
   if (value.toInt() == 0)
   {
  digitalWrite(vcc,HIGH);
  digitalWrite(pls,HIGH);
  digitalWrite(dir,HIGH);
  digitalWrite(ena,LOW);
  tone(pls,500);
    }
   if (value.toInt() == 2)
   {
  digitalWrite(vcc,LOW);
  digitalWrite(pls,HIGH);
  digitalWrite(dir,HIGH);
  digitalWrite(ena,HIGH);
   }
   }
   }       
   
 



