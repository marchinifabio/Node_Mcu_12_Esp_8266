#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include "ts_connect.h"


// Nome e senha do seu wifi
 const char* ssid = WIFI_SSID; 
 const char* password = WIFI_PASSWORD; 
WiFiClient client;


// ThingSpeak information
char thingSpeakAddress[] = TS_ADDRS;
unsigned long channelID = TS_CHANNEL_ID;
char* readAPIKey = TS_READAPIKEY;
char* writeAPIKey =TS_WRITEAPIKEY;


float readTSData( long TSChannel, unsigned int TSField )
{
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;
}

// Use this function if you want to write a single field.
int writeTSData( long TSChannel, unsigned int TSField, float data )
{
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess )
  {  
    Serial.println( String(data) + " written to Thingspeak." );
  }
  return writeSuccess;
}

// Use this function if you want to write multiple fields simultaneously.
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data, unsigned int TSField3, long field3Data )
{
  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
  ThingSpeak.setField( TSField3, field3Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}



void TS_connect_init( void )
{
  // Serial.println("Start\n");
   Serial.print("Connecting to WiFi ");
   Serial.print( ssid );

  // Inicializando a conexao
  WiFi.begin( ssid, password ); 
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(1000);
    Serial.print("."); 
  }

  Serial.println("");
  Serial.print("WiFi connectado em  ");
  Serial.println( ssid );
  Serial.println("");
  
  ThingSpeak.begin( client );
}


void TS_data_write( unsigned int TSField, float data )
{
  writeTSData( channelID, TSField, data );
}

int TS_dht_write( unsigned int TSField1, float field1Data, unsigned int TSField2, float field2Data )
{
  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
   
  int writeSuccess = ThingSpeak.writeFields( channelID, writeAPIKey );
  return writeSuccess;
}
