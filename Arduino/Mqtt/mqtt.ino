//#include <EspMQTTClient.h>

#include "EspMQTTClient.h"

void onConnectionEstablished();


EspMQTTClient client(
 "ABBIndgymIoT_2.4GHz",           // Wifi ssid
  "ValkommenHit!",           // Wifi password
  "192.168.0.120",  // MQTT broker ip
  1883,             // MQTT broker port
  "jocke",            // MQTT username
  "apa",       // MQTT password
  "microdator",          // Client name
  onConnectionEstablished, // Connection established callback
  true,             // Enable web updater
  true              // Enable debug messages
);

/*
EspMQTTClient client(
  ""ABB_Indgym"",                 // Wifi ssid
  "7Laddaremygglustbil",                 // Wifi password
  onConnectionEstablished,// MQTT connection established callback
  "10.22.2.220"                    // MQTT broker ip
);
*/

#define led_pin 5

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  Serial.begin(115200);
}

bool off=false;

void lampa(){
  if(off==true){
    off=false;
    Serial.println("Släckt");
  } else {
    off= true;
    Serial.println("Tänt");
  }
  digitalWrite(led_pin, off);
}


void onConnectionEstablished()
{
  // Subscribe to "mytopic/test" and display received message to Serial
  client.subscribe("lampa/lamp", [](const String & payload) {
    Serial.println(payload);
//    if(payload=="on"){
//      onlampa();
//    }
    lampa();
  });

  // Publish a message to "mytopic/test"
  client.publish("mess", "This is a message");

  // Execute delayed instructions
  client.executeDelayed(5 * 1000, []() {
    client.publish("mess", "This is a message sent 5 seconds later");
  });
}

void loop()
{
  client.loop();
}
