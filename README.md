# rubbish-bin
### 引言



>在朋友家见到感应垃圾桶后，觉得很有趣。好在用Arduino实现这个想法并不困难，花了大概三个小时自己做了一个。使用的是HC-SR04超声波测距模块和SG90舵机，都相当便宜，性能也基本满足要求。成品如下，右边是自己DIY的树莓派电脑。



<img src="https://pic3.zhimg.com/80/v2-be0eba56f59a81fca7590e217738ad82_hd.jpg" style="zoom:80%">


### 制作过程



#### 一、制作箱体



>制作箱体花了好些时间，原本是全部使用硬纸板制作的，做完后发现存在变形的问题，于是改用木板制作了背面和左右两个面。背面使用木板是为了盒盖的开关更加稳定，右面使用木板是为了固定开关装置。



<img src="https://pic4.zhimg.com/80/v2-7b42709fee4e7a16baeb8ec4bfdeb193_hd.jpg" style="zoom:80%">



>舵机控制的盒盖开关部分固定在右侧板子上。舵机控制的盒盖开关部分制作时有点难度，可以通过画示意图的方法找到合适的连杆。简图与实物的对比如下，a是铰链的转动点与舵机的转动点的连线，b是舵机柄，c是连杆。其中铰链的转动点（A点）和连杆的末端（D点）是固定的，可以转动不能移动。启动时舵机柄（b）顺时针旋转90度，带动a和c的运动。这样就可以根据盒盖需要打开的角度（即a变化的角度），选择合适的连杆以及固定点。



<img src="https://pic1.zhimg.com/80/v2-2e24312ccd3dfc9a92dd6be2cb266c70_hd.jpg" style="zoom:80%">



#### 二、连接电路



>电路图如下，接线很简单。值得注意的是，Arduino自带`servo`函数进行舵机的控制，使用`servo`函数控制舵机时，舵机的控制线要接PWM数字口。我使用的板子是Arduino   UNO，所有PWM数字口都有~标识。选择了其中的D9作为舵机的控制接口。这里AA电池只是示意，5V供电即可，可以用5V2.1A输出的移动电源供电。



<img src="https://pic2.zhimg.com/80/v2-da8488c125ca8f97b8970c4b51ee81ad_hd.jpg" style="zoom:80%">



####  三、写入代码


```

#include <Servo.h>   

Servo servo;

int servoPin = 9;

int trigPin = 6;    

int echoPin = 7;   

long duration, distance;   

long aver[3];   



void setup() {     

  servo.attach(servoPin);  

  pinMode(trigPin, OUTPUT);  

  pinMode(echoPin, INPUT); 

  servo.write(0); 

  delay(1000);

  servo.detach();

} 



void measure() {  

  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(15);

  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);

  duration = pulseIn(echoPin, HIGH);

  distance = duration *0.034 / 2;

}



void loop() { 

  for (int i=0;i<=2;i++) {   

    measure();               

    aver[i]=distance;            

    delay(50);           

  }

 

  distance=(aver[0]+aver[1]+aver[2])/3; 

  

  if (distance<40) {

    servo.attach(servoPin);

    delay(1);

    servo.write(90);  

    delay(5000);  

    servo.write(0);    

    delay(1000);

    servo.detach();      

  }

}

```

### 演示视频


<iframe src="//player.bilibili.com/player.html?aid=52387782&cid=91687346&page=1" scrolling="no" border="0" frameborder="no" framespacing="0" allowfullscreen="true" width="600" height="300"> </iframe>
