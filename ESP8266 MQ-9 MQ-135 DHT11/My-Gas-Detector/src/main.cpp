#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <IPAddress.h>
#include <WiFiUDP.h>
#include <TroykaMQ.h>
#include <DHT.h>
/*---------------------------------*/
// DHT11 temperature  & Humidity
/*--------------------------------*/
DHT dht;
#define pin_data_DHT D5

// имя для пина, к которому подключен датчик
#define PIN_MQ135  A0
#define PIN_MQ9  A0
/*-----------------------*/
// analog mux-demux 4051
/*----------------------*/
#define MUX_A D2
#define MUX_B D3
#define MUX_C D4

// создаём объект для работы с датчиком и передаём ему номер пина
MQ135 mq135(PIN_MQ135);
MQ9 mq9(PIN_MQ9);


/*---------------*/
// wifi config
/*----------------*/
char* ssid = "r2";
char* password = "qt2016c++";

/*---------------*/
// UDP packet handler
/*----------------*/
IPAddress ipBroadCast;
unsigned int udpRemotePort=45454; // port output data
unsigned int udplocalPort=45455;  // port input data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
WiFiUDP udp;

bool changeMux(int pinAnalog)
{
    if(pinAnalog < 0 || pinAnalog > 7 )
      return false ;


    digitalWrite(MUX_A, bitRead(pinAnalog, 0));
    digitalWrite(MUX_B, bitRead(pinAnalog, 1));
    digitalWrite(MUX_C, bitRead(pinAnalog, 2));

    return true ;
}

void setup()
{

  //start serial interface for debuging...
  Serial.begin(115200);

  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);
  pinMode(MUX_C, OUTPUT);

  digitalWrite(MUX_A, LOW);
  digitalWrite(MUX_B, LOW);
  digitalWrite(MUX_C, LOW);

  //start connecting to wifi....
  WiFi.begin(ssid,password);


  // wait untill esp8266 connected to wifi...
  while(WiFi.status()!=WL_CONNECTED)
  {
      Serial.print(".");
      delay(500);
  }
  // debuging ...
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // todo: config ip broadcast

  ipBroadCast = WiFi.localIP() ;
  ipBroadCast[3] = 255;
  // set udp port for listen...
  udp.begin(udplocalPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());

  changeMux(0);
  mq135.calibrate();
  changeMux(1);
  mq9.calibrate();

  Serial.print("Ro = ");
  Serial.println(mq135.getRo());

  dht.setup(pin_data_DHT);
}

void myUdpSend(String msg)
{
    // convert string to char array
    int UDP_PACKET_SIZE = msg.length()+1;
    char udpBuffer[UDP_PACKET_SIZE] ;
    msg.toCharArray(udpBuffer, UDP_PACKET_SIZE) ;

    // send msg broadcast to port destinie
    udp.beginPacket(ipBroadCast, udpRemotePort);
    udp.write(udpBuffer, sizeof(udpBuffer));
    udp.endPacket();
}

void loop()
{

  // for(int i = 0 ; i < 8 ; i++)
  // {
  //   changeMux(i);
  //   Serial.print("changeMux("+String(i)+") A0: "+String(analogRead(A0)));
  //   Serial.println(" // "+String(bitRead(i, 1))+String(bitRead(i, 1))+String(bitRead(i, 0)));
  // }


  changeMux(0);

  Serial.print("Ratio: ");
  Serial.print(mq135.readRatio());
  Serial.print("\tCO2: ");
  Serial.print(mq135.readCO2());
  Serial.println(" ppm");
  myUdpSend("<MQ135>"+String(mq135.readCO2()));


  changeMux(1);
  Serial.print("Ratio: ");
  Serial.print(mq9.readRatio());
  Serial.print(" LPG: ");
  Serial.print(mq9.readLPG());
  Serial.print(" ppm ");
  Serial.print(" CH4: ");
  Serial.print(mq9.readMethane());
  Serial.print(" ppm ");
  Serial.print(" CO: ");
  Serial.print(mq9.readCarbonMonoxide());
  Serial.println(" ppm ");

  // myUdpSend("<MQ9_LPG>"+String(mq9.readLPG()));
  // myUdpSend("<MQ9_CH4>"+String(mq9.readMethane()));
  int readCarbonMonoxide = mq9.readCarbonMonoxide() ;
  myUdpSend("<MQ9>"+String(readCarbonMonoxide));
  delay(dht.getMinimumSamplingPeriod());

   myUdpSend("<DHT11_temperateur>"+String(dht.getTemperature()));
   myUdpSend("<DHT11_humidity>"+String(dht.getHumidity()));

  delay(1000);



}
