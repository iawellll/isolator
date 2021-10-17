 

## 1. 关于本项目

自己开发的温度变送器一直用电脑作为上位机组态软件，笔记本电脑在工业现场操作不太方便，用手操器现场组态很方便，但是需要另外开发一个手操器，成本不是很理想。现在人人都有手机，如果能把手机作为手操器就好了，基于这个需求有了本项目。

## 2. 技术方案

### 2.1 无线方案

无线方案有蓝牙、WIFI等，因为仪表上只有串口对外输出，选无线方案要实现无线协议到串口的转换，还需要给协议转换器供电，如此实现起来很麻烦。但好处是通用性变强，只要支持蓝牙的设备都可以调试。

### 2.2 有线方案

安卓在3.0之后都支持OTG USB功能，USB转串口芯片很多，而且可以通过手机给转换器供电，整个方案连线方式和独立手操器一样。本次开发选用此方案实现。

## 2. 安卓OTG USB转UART驱动的使用步骤：

2.1 在AndroidManifest.xml里注册USB设备。功能是插上USB后弹出启动APP的对话框。

```xml
<uses-feature android:name="android.hardware.usb.host" />
...
<activity
    android:name=".MainActivity"
    android:exported="true">
    <intent-filter>
        <action android:name="android.intent.action.MAIN" />

        <category android:name="android.intent.category.LAUNCHER" />
    </intent-filter>
    <intent-filter>
        <action android:name="android.hardware.usb.action.USB_DEVICE_ATTACHED" />
    </intent-filter>

    <meta-data
        android:name="android.hardware.usb.action.USB_DEVICE_ATTACHED"
        android:resource="@xml/device_filter" />
</activity>
```

2.2 在setting.gradle里添加  maven { url 'https://www.jitpack.io' } ，这是第三方库仓库。

 ![image4](/硬件/image4.png)

2.3 在buid.gradle(:app)里添加 implementation 'com.github.mik3y:usb-serial-for-android:3.4.0'。

 ![image5](/硬件/image5.png)

2.4 [github.com](https://github.com/mik3y/usb-serial-for-android) 这个网站有用

2.5 每次停止开发后，要写已经完成和还要继续做的小结，这样当继续开发时不用花太多时间就可以继续工作了。

2.6 安卓是可以用无线开发的，这样就可以调试串口了。

2.7 每一个activity对应一个.JAVA文件。在开发C#时也应该一个视窗对应一个文件。

## 3. 安卓串口调试方法

因为手机只有一个USB口，如果连接电脑进行开发调试，就无法调试串口了，可以用无线调试方法解决。具体实现方法如下：

3.1 开启开发者模式，使用USB数据线连接Android设备;

3.2  在dos命令行输入adb tcpip命令(例如:adb tcpip 9999);    

  ![image1](/硬件/image2.png)

3 .3 断开USB数据线(数据线和设备断开连接);

3.4 dos中输入adb connect <host>[:<port>]命令(例如:adb connect 192.168.1.112:9999)。

 ![image3](/硬件/image3.png)

3.5 命令行若显示 connected to 192.168.1.112:9999 恭喜你!连接成功了,可以开始无线调试啦!

