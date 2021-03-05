#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
//char auth[] = "2ImClLtzyoegsQXSNNnPPNs3NAcvo8zm"; // Blynk Authentication Code
char auth[] = "z7K9ZVxlN7ryAs1_be8ljLwBy2r8vmnv";
// char ssid[] = "Silence_Of_The_LAN";
// char pass[] = "9862678539";
char ssid[] = "Killua"; // Name of WiFi hotspot
char pass[] = "tikitaka"; // Passwor for Wifi hotspot

int blueLed = D4; // Blue Led is connected with D4 
int greenLed = D3; // Green Led is connected with D3
int buzzer = D5; // Buzzer is connected with D5
int mq135A0 = A0; // MQ135 gas sensor is connected with the Analog Pin A0

int sensorThres = 120; // Initialization of threshold value
int data = 0; // Value of data is initialized to 0

void setup() {
  pinMode(blueLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(mq135A0, INPUT);
  Serial.begin(115200);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}

void loop() {
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

void getSendData(){
data = analogRead(mq135A0); // Analog output of the sensor is initialized to the data
Serial.print("Pin A0: ");
Serial.println(data);
  Blynk.virtualWrite(V2, data);
 
  if (data > sensorThres )  // Checks if it has reached the threshold value
  {
    tone(buzzer,500,500); // Buzzer starts buzzing
    digitalWrite(blueLed, LOW); // Blue Led doesnot glow
    digitalWrite(greenLed, HIGH); // Green Led glows
    Blynk.notify("Air is contaminated!"); // Notifies in Blynk app as "Air is contaminated!"
  }
  else
  {
    noTone(buzzer);
    digitalWrite(blueLed, HIGH); // Blue Led glows
    digitalWrite(greenLed, LOW); // Green Led doesnot glow
  }
  delay(200); // 0.2 second is delayed
}
