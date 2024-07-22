#include <SoftwareSerial.h>
#include <Servo.h>
#include <math.h>
#include <LoRa.h>
#include <SPI.h>

String gpsData = "";
const int pi = 3.1416;
Servo servoMotor;
const int pinServ = 3;

float latituda = -99.185169;
float longituda = 19.279507;
float latitudb, longitudb;
// Punto A: Origen, Punto B: Transmisor, Punto C: Referencia

unsigned long previousMillis = 0; // Almacena el último tiempo en que se imprimió el mensaje
const long interval = 2000; // Intervalo de 2 segundos
bool dataReceived = false; // Bandera para verificar si se han recibido datos

void setup() {
    Serial.begin(9600);
    servoMotor.attach(pinServ);
    while (!Serial);
    Serial.println("LoRa Receiver");

    if (!LoRa.begin(902E6)) { // Corrige el rango de frecuencias
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}

void loop() {
    // Try to receive a packet
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        // Received a packet
        dataReceived = true; // Se han recibido datos
        Serial.print("Received packet '");

        // Read packet
        while (LoRa.available()) {
            String data = LoRa.readStringUntil(',');
            if (data.length() > 0) {
                latitudb = data.toFloat();
            }
            data = LoRa.readStringUntil('\n');
            if (data.length() > 0) {
                longitudb = data.toFloat();
            }
        }

        float latitudc = latitudb;
        float longitudc = longituda;
        float cat_op = longitudb - longitudc;
        float cat_ad = latitudb - latituda;

        float ang = (atan(cat_op / cat_ad) * pi) / 180;

        if (ang > 0) {
            servoMotor.write(-ang);
        } else {
            servoMotor.write(ang);
        }

        gpsData += "Latitud = " + String(latitudb, 6) + ", Longitud = " + String(longitudb, 6) + "\n";
        Serial.println(gpsData);
        Serial.print("Ángulo de correcion: ");
        Serial.println(ang);
    } else {
        // Si no se han recibido datos, se verifica el tiempo
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval) {
            previousMillis = currentMillis; // Actualiza el tiempo
            if (!dataReceived) {
                Serial.println("No se están recibiendo datos.");
            }
        }
        dataReceived = false; // Reinicia la bandera
    }
}
