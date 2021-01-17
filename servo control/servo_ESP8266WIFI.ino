#include <ESP8266WiFi.h>
#include <Servo.h>
 
 
#define ANGLE_ON  0    //开灯时的舵机角度
#define ANGLE_OFF 180   //关灯时的舵机角度
#define ANGLE_NONE 0  //置空时的舵机角度
 
const char* ssid = "xiaomi";
const char* password = "caa5510dd70b";
int angle= 0;//舵机角度
Servo myservo;  //创造一个servo结构体
WiFiServer server(1);
 
void setup() {
  Serial.begin(9600);
  myservo.attach(4); //舵机信号线，接analogIn脚
  myservo.write(angle);// 0~180°
 
  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。
                                               
  Serial.println("");                          // WiFi连接成功后
  Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
  Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
  Serial.println(WiFi.localIP());   
}
 
void loop() {
  //监测客户端是否连接
  WiFiClient client = server.available();
  if (!client) {
    return;//如果未连接就重新循环监测
  }
//  Serial.println(F("new client"));
 
  client.setTimeout(1000); // default is 1000
 
  //读取请求内容的第一行
  String req = client.readStringUntil('\r');
  Serial.println(F("请求: "));
  Serial.println(req);
 
  //匹配 请求-->信号变量
  if (req.indexOf(F("/gpio/0")) != -1) {
    angle = ANGLE_ON;//如果/gpio/0在请求内容中，发出开灯的信号
    myservo.write(angle);// 0~180°
    delay(1000);
    myservo.write(ANGLE_NONE);//将舵机重新置空，以免一直受力损坏
  } 
  else if (req.indexOf(F("/gpio/1")) != -1) {
    angle = ANGLE_OFF;
    myservo.write(angle);// 0~180°
    delay(1000);
    myservo.write(ANGLE_NONE);//将舵机重新置空，以免一直受力损坏
  } 
  else {
    Serial.println(F("无效请求"));
  }
  //读取或忽略余下的请求内容
  while (client.available()) {
    client.read();
  }
  
  //向客户端发送回答，HTML网页代码内容
  //nagle算法会将它们分组为一个数据包
  client.print(F("<!DOCTYPE html>\r\n<html xmlns='http://www.w3.org/1999/xhtml'>\r\n"));
  client.print(F("<head>\r\n<meta charset='utf-8'/>\r\n<title>智能卧室灯</title>\r\n"));
  client.print(F("<style type='text/css'>.state{text-align:center;font-size:80px;}"));
  client.print(F(".on{text-align:center;font-size:200px;alink='#1a9e5f'}.off{text-align:center;font-size:200px;alink='#da4f43'}"));
  client.print(F("</style><body><div class='state'>灯状态："));
  client.print((angle>ANGLE_NONE) ? F("关</div>") : F("开</div>"));
  client.print(F("<br><br><div class='on'><a href='http://"));//<br>换行
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>开</a></div><br><br><div class='off'><a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>关</a></div></body></html>"));
 
  // 客户端实际上将被“刷新”,然后断开连接
  // 当函数返回并且“客户端”对象被销毁时
  // 刷新=确保书面数据被服务端接收
  Serial.println(F("客户端已挂起！"));
}
