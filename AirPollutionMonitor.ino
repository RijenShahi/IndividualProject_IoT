#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;
char auth[] = "2ImClLtzyoegsQXSNNnPPNs3NAcvo8zm"; // Blynk Authentication Code
// char ssid[] = "Silence_Of_The_LAN";
// char pass[] = "9862678539";
char ssid[] = "Killua"; // Name of WiFi hotspot
char pass[] = "tikitaka"; // Passwor for Wifi hotspot

int blueLed = 4; // Blue Led is connected with D4 
int greenLed = 3; // Green Led is connected with D3
int buzzer = 2; // Buzzer is connected with D2
int mq135A0 = A0; // MQ135 gas sensor is connected with the Analog Pin A0

int sensorThres = 200; // Initialization of threshold value
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
  int analogSensor = analogRead(mq135A0);
  Serial.print("Pin A0: ");
  Serial.println(analogSensor);

  timer.run(); // Initiates SimpleTimer
  Blynk.run();
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
  digitalWrite(blueLed, HIGH); // Blue Led glows
  digitalWrite(greenLed, LOW); // Green Led doesnot glow
    tone(buzzer, 200, 200); // Buzzer starts buzzing
  }
  else
  {
  digitalWrite(blueLed, LOW); // Blue Led doesnot glow
  digitalWrite(greenLed, HIGH); // Green Led glows
    noTone(buzzer); //Buzzer doesnot produce buzzing sound
  }
  delay(100);
}

void getSendData()
{
data = analogRead(mq135A0); // Analog output of the sensor is initialized to the data
  Blynk.virtualWrite(V2, data);
 
  if (data > 200 )  // If the value of data is greater then that of threshold
  {
    Blynk.notify("Air is contaminated!"); // Notifies in Blynk app as "Air is contaminated!"
  }
}
