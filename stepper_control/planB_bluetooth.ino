#include <SoftwareSerial.h>
#include <Stepper.h>
int stepsPerRevolution = 40;
int stepper_speed = 400;
int TxD = 11;
int RxD = 10;
SoftwareSerial bluetooth(TxD, RxD);

Stepper myStepper(stepsPerRevolution, 3, 4, 5, 6);

void setup() {
  Serial.begin(9600);       // start serial communication at 9600bps
  bluetooth.begin(9600);
}

void loop() {
 if (bluetooth.available()){
  String value = bluetooth.readString();
   if (value.toInt() == 1)
   {
    myStepper.setSpeed(stepper_speed);//更改速度
    for(int i = 0; i <= stepsPerRevolution; i++)
    {
    if (value.toInt()==2)
    {
     myStepper.step(0);//停止
     Serial.println(2);
    }
    myStepper.step(-i);//顺时针转动
    Serial.println(1);
    }
   }
   if (value.toInt()==0)
   {
     myStepper.setSpeed(stepper_speed);//更改速度
    for(int i = 0; i <= stepsPerRevolution; i++)
    {
    if (value.toInt()==2)
    {
     myStepper.step(0);//停止
     Serial.println(2);
    }
    myStepper.step(i);//逆时针转动
    Serial.println(0);
    }
   }
   }
   }
          
   
 



