#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "dht.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)


DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void dht_init( void )
{
  // Initialize device.
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

sensors_event_t dht_event;

unsigned char dht_status = 0;

float dht_temperatura( void )
{
  dht.temperature().getEvent(&dht_event);
  if (isnan(dht_event.temperature)) 
  {
    Serial.println(F("Error reading temperature!"));
    dht_status = 1; 
    return( 0.0 );
  }
  else 
  {
    dht_status = 0; 
    return( dht_event.temperature );
  }
}

float dht_umidade( void )
{
  dht.humidity().getEvent( &dht_event );
  if (isnan(dht_event.relative_humidity)) 
  {
    Serial.println(F("Error reading humidity!"));
    dht_status = 1; 
    return( 0.0 );
  }
  else
  {
    dht_status = 0; 
    return( dht_event.relative_humidity );
  }
}

unsigned char dht_error( void )
{
  return( dht_status );
}
