#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <DHT_U.h> 

#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include "ts_connect.h"
#include "dht.h"
#include "filtro_media_movel.h"

#define LED_PIN D4

const unsigned long postingInterval = 1L * 1000L;
unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0; 


void setup() 
{
  Serial.begin(115200); 
  delay(3000);

//  dht_init();

  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN, 0); 

  TS_connect_init();
}

void loop() 
{
  if( millis() - lastUpdateTime >=  postingInterval )
  {    
    float temp, umid;
    lastUpdateTime = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN) );

    temp = dht_temperatura();
//    temp = 41;
    Serial.print(F("Temperatura: "));
    Serial.print( String(temp) );
    Serial.println(F("°C"));

    umid = dht_umidade();
//    umid = 50;
    Serial.print(F("Umidade: "));
    Serial.print( String(umid));
    Serial.println(F("%"));

//    if( !dht_error() )
    {
      int t_indice;
      t_indice = fmm_add( temp );
      if( !t_indice )
      {
        TS_dht_write( TS_DATA_FIELD_TEMP, temp,  TS_DATA_FIELD_UMID, umid );
        Serial.println(F("TS"));
      }
    }
  }
}
