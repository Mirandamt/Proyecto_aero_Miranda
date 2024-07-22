#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <StreamUtils.h>
#include <LoRa.h>
#include <SPI.h>
    String gpsData = "";
    float latitudb=0, longitudb=0;


TinyGPS gps;
SoftwareSerial ss(4, 3); // RX, TX

#define pinTx 3
#define pinRx 4

void setup() {
Serial.begin(115200);
ss.begin(9600);
Serial.println("Simple GPS test");
if (!LoRa.begin (902-928E6)){
    Serial.println("Starting LoRa failed");  
    while (1); 
}
}
void loop() {
  // put your main code here, to run repeatedly:
  bool newData = false;
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }

  if (newData)
  {

    gps.f_get_position(&latitudb, &longitudb);
    // Crear una cadena con los datos del GPS

    gpsData += "Latitud = " + String(latitudb, 6) + ", Longitud = " + String(longitudb, 6) + "\n";
    gpsData += "Altitude (meters): " + String(gps.f_altitude()) + "\n";
    // Imprimir los datos del GPS
    Serial.println(gpsData);
  }
  float array[] = {latitudb, longitudb};
  if (ss.available() > 0)
   {
  LoRa.beginPacket();
  LoRa.print(latitudb);
  LoRa.print(",");
  LoRa.print(longitudb);
  LoRa.endPacket();

  }  
  delay(2000);
}


