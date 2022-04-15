#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFiUdp.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

char ssid[] = "Wifi_name";
char password[] = "Wifi_Password";
int strength;
int motor;
char * token;

WiFiUDP Udp;
char packetBuffer[255];

void setup() {
  Serial.begin(9600);
  delay(3000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("OHL WiFi Vest Starting");
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print('.');
      delay(1000);
    }
  if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("---------------");
      Serial.print("Connected! to {");
      Serial.print(ssid);
      Serial.print("}");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      Serial.println("Listening on port:");
      Udp.begin(69);
      Serial.println(69);
      Serial.println("Waiting for connection");
    }
  


  pwm.begin();
  pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
}

void loop() {

    //for (uint8_t pwmnum=0; pwmnum <= 16; pwmnum++)
   // {
 
    //  pwm.setPin(pwmnum, 4095);
     // delay(150);
    //  pwm.setPin(pwmnum, 0);
   // }

     // if there's data available, read a packet

  int packetSize = Udp.parsePacket();

  if (packetSize) {


    int len = Udp.read(packetBuffer, 255);

    if (len > 0) {

      packetBuffer[len] = 0;

    }

    Serial.println(packetBuffer);
    
    token = strtok(packetBuffer, ":");
    Serial.println(atoi(token));
    motor = atoi(token);
    
    token = strtok(NULL, " ");
    Serial.println(atoi(token));
    strength = atoi(token);
    
    pwm.setPin(motor, strength);

    }

    }
