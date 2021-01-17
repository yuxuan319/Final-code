import RPi.GPIO as GPIO
import time                #导入延时函数
GPIO.setmode(GPIO.BCM)     #使用BCM编码
GPIO.setup(25,GPIO.OUT)    #使用BCM编码的25号脚
 
print("P") 
print("O")
print("Exit: Q and q")
 
while True:
    user_choice=input("Choice:")
    if user_choice=="P":         #如果控制台输入P(继电器打开)
          GPIO.output(25,GPIO.HIGH)  #输出高电平
          
    elif user_choice=="O": 
          GPIO.output(25,GPIO.LOW)   #输出低电平
    elif user_choice=="q" or user_choice=="Q":        #如果输入q、Q
          GPIO.cleanup()             #退出本脚本