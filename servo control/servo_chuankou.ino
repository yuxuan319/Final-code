 #include <Servo.h>
int incomedate = 0;
Servo myservo;
void setup() {
  Serial.begin(9600); //开启串行通信接口并设置通信波特率为9600
  myservo.attach(9);
  myservo.write(0);
}

void loop() {
   if (Serial.available() > 0)//串口接收到数据
  {
    incomedate = Serial.read();//获取串口接收到的数据
    if (incomedate == 'a')
    {
      myservo.write(180); 
      Serial.println("正转!");
    }
    if (incomedate == 'd')
    {
      myservo.write(-180); 
      Serial.println("反转");
    }
  }
  delay(800);
  Serial.flush();//清除串口缓存

}
