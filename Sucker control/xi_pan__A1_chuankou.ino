int incomedate = 0;

void setup(){
  Serial.begin(115200);//初始化波特率
}

void loop(){
  if (Serial.available() > 0)//串口接收到数据
  {
    incomedate = Serial.read();//获取串口接收到的数据
    if (incomedate == 'a')
    {
  Serial.println("#255P2500T0000!");//吸附
  Serial.println("正转!");
    }
    if (incomedate == 'd')
    {
  Serial.println("#255P1500T0000!");//释放
  Serial.println("反转");
    }
  }
  delay(800);
  Serial.flush();//清除串口缓存
}
