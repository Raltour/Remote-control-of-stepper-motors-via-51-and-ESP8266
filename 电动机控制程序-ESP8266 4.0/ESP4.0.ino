#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>

const char* WIFI = "vivo Y200i";  // 热点名称
const char* password = "limingze";  // 热点密码


//这个函数只在程序启动时执行一次
void setup() {
  Serial.begin(9600);//串口通信的比特率
  Serial.print("Hello World!\r\n");//随便测试一下
  delay(100);

  // 开始连接到 Wi-Fi
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI, password);

  // 等待连接成功
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // 打印连接成功信息
  Serial.println();
  Serial.println("Connected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // 显示设备的 IP 地址
}
 

//这个函数在启动后持续执行
void loop() {
  if(Serial.available()){  //检测是否有可以发送的数据
    int data = Serial.parseInt();//1字节大小的数据，对应51单片机程序中的Signal变量
    Serial.println(data);
    Serial.write(data);//通过TXD引脚发送出去
    delay(100);
  }
}   