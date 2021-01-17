# 超声波引脚
  TRIG = 20
  ECHO = 21
# 初始化接收端电平
  GPIO.output(TRIG, 0)
# 防止错误，提供间隔时间
   time.sleep(0.000002)
# 发射
GPIO.output(TRIG, 1)
time.sleep(0.00001)
GPIO.output(TRIG, 0)
# 接收
while GPIO.input(ECHO) == 0:
    pass
emitTime = time.time()
while GPIO.input(ECHO) == 1:
    pass
    acceptTime = time.time()
# 计算距离
 totalTime = acceptTime - emitTime
distanceForReturn = totalTime * 340 / 2 * 100
