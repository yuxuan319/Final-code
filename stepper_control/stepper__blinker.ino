#include <Stepper.h>
#define BLINKER_WIFI
 
#include <Blinker.h>
const int stepsPerRevolution = 400;
char auth[] = "45e5b713ca3f";   //key
char ssid[] = "xiaomi";             //wifi名称
char pswd[] = "caa5510dd70b";      //wifi密码

BlinkerButton Button1("btn-max");   //逆时针转动
BlinkerButton Button2("btn-min");   //顺时针转动
Stepper myStepper(stepsPerRevolution, 2, 0, 4, 5);
BlinkerSlider Slider1("max-num");   //逆时针转动速度
BlinkerSlider Slider2("min-num");   //顺时针转动速度

int stepper_max = 0;
int stepper_min = 0;

// for your motor

void button1_callback(const String & state) {    //位置1按钮
    BLINKER_LOG("get button state: ", stepper_max);
    myStepper.setSpeed(stepper_max);//更改速度
    myStepper.step(stepsPerRevolution);//逆时针转动
    Blinker.vibrate();
}
  
void button2_callback(const String & state) {   //位置2按钮
    BLINKER_LOG("get button state: ", stepper_min); 
    myStepper.setSpeed(stepper_min);//更改速度
    myStepper.step(-stepsPerRevolution);//顺时针转动
    Blinker.vibrate();
}


void slider1_callback(int32_t value)
{
    stepper_max = value;
    Slider1.color("#1E90FF");
    Slider1.print();
    
    BLINKER_LOG("get slider value: ", value);
}

void slider2_callback(int32_t value)
{
    stepper_min = value;
    Slider2.color("#FFF8DC");
    Slider2.print();
    BLINKER_LOG("get slider value: ", value);
}
void setup() {
  // initialize the serial port:
  Serial.begin(9600);
   BLINKER_DEBUG.stream(Serial);
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Slider1.attach(slider1_callback);
    Slider2.attach(slider2_callback);
    stepper_max=70;
    stepper_min=120;
    
}

void loop() {
   Blinker.run();
}

