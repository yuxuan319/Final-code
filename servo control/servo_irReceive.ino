/***********************************************
* 湖南创乐博智能科技有限公司
* name:Infrared-Receiver
* function:press the CH- key of a remote control,
* and both the LED attached and that connected to pin 13 on the arduino Uno board will light up.
* Then press any other key, and the LEDs will go out.
**********************************************/
#include <IRremote.h>
#include <Servo.h>
const int irReceiverPin =7; //the SIG of receiver module attach to pin7——连接红外接收器的DO接口 
const int ledPin = 13;//pin 13 built-in led——连接LED灯的R接口
IRrecv irrecv(irReceiverPin); //Creates a variable of type IRrecv
decode_results results;
Servo myservo;  // 定义Servo对象来控制
void setup()
{
  pinMode(ledPin,OUTPUT);//set ledpin as OUTPUT
  Serial.begin(9600);//initialize serial 
  irrecv.enableIRIn(); //enable ir receiver module 
  myservo.attach(9);
}
void loop() 
{
  if (irrecv.decode(&results)) //if the ir receiver module receiver data
  { 
    Serial.print("irCode: "); //print"irCode: " 
    Serial.print(results.value, HEX); //print the value in hexdecimal 
    Serial.print(", bits: "); //print" , bits: " 
    Serial.println(results.bits); //print the bits
    irrecv.resume(); // Receive the next value 
  } 
  delay(600); //delay 600ms
  if(results.value == 0xFFA25D)//if receiver module receive OxFFA25D
  {
    digitalWrite(ledPin,HIGH);//turn on the led
    myservo.write(180); 
    //Serial.println("ok");
  }
   if(results.value == 0xFF30CF)//if receiver module receive 0xFF30CF
  {
    digitalWrite(ledPin,HIGH);//turn on the led
    myservo.write(-180); 
    //Serial.println("ok");
  }
  else
  {
    digitalWrite(ledPin,LOW);//turn off the led
    //Serial.println("no");
  }
  
}
