#include "secrets.h"

// --- Configuración de Blynk ---
/* #define BLYNK_TEMPLATE_ID "Your_Template_ID"
#define BLYNK_TEMPLATE_NAME "Your_Template_Name"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token" */
//* Descomentar y completar con los datos de tu plantilla de Blynk

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// --- Configuración WiFi ---
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

// --- API OpenWeather ---
const char* apiKey = OPENWEATHER_API_KEY; // API Key de OpenWeather
const char* city = "Huacho,PE"; // Ciudad
const char* unit = "metric"; // metric = Celsius, imperial = Fahrenheit, standard = Kelvin

// --- Timer ---
unsigned long lastTime = 0;
unsigned long interval = 600000; // 10 minutos

void hacerPeticionClima(); // Llamar función para hacer la petición de clima

void setup() {
  Serial.begin(115200);
  delay(1000);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);

  // Llamamos a la función al iniciar
  hacerPeticionClima();
  lastTime = millis();
}

void loop() {
  Blynk.run(); // Ejecutar Blynk

  // --- Timer para hacer la petición cada 10 minutos ---
  if (millis() - lastTime > interval) {
    hacerPeticionClima();
    lastTime = millis();
  }
}

void hacerPeticionClima() {
  Serial.println("Haciendo petición a OpenWeather...");

  if (WiFi.status() == WL_CONNECTED) {
    // Petición para el clima
    HTTPClient http;
    String url = "http://api.openweathermap.org/data/2.5/weather?q=" + String(city) + "&appid=" + apiKey + "&units=" + unit;

    http.begin(url);
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();

      // Parsear el JSON de clima
      const size_t capacity = 1024;
      DynamicJsonDocument doc(capacity);
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        //* --- Datos del clima ---
        String cityName = doc["name"]; // Ciudad
        float temperature = doc["main"]["temp"]; // Temperatura
        float humidity = doc["main"]["humidity"]; // Humedad
        float windSpeed = doc["wind"]["speed"]; // Velocidad del viento
        int pressure = doc["main"]["pressure"]; // Presión
        float lat = doc["coord"]["lat"];
        float lon = doc["coord"]["lon"];

        //* --- Imprimir datos en el monitor serial ---
        Serial.println("-----------------------------");
        Serial.println("--- Datos del Clima Actual ---");
        Serial.print("Ciudad: "); Serial.println(cityName);
        Serial.print("Temperatura: "); Serial.print(temperature); Serial.println(" °C");
        Serial.print("Humedad: "); Serial.print(humidity); Serial.println(" %");
        Serial.print("Viento: "); Serial.print(windSpeed); Serial.println(" m/s");
        Serial.print("Presión: "); Serial.print(pressure); Serial.println(" hPa");

        //* --- Enviar datos a Blynk ---
        Blynk.virtualWrite(V0, temperature); // Temperatura
        Blynk.virtualWrite(V1, cityName);    // Ciudad
        Blynk.virtualWrite(V2, humidity);    // Humedad
        Blynk.virtualWrite(V3, pressure);    // Presión
        Blynk.virtualWrite(V5, windSpeed);   // Viento
        
        http.end(); // Cerrar conexión HTTP del clima
        
        // Petición para calidad de aire
        HTTPClient airHttp;
        String airUrl = "http://api.openweathermap.org/data/2.5/air_pollution?lat=" + String(lat, 6) + "&lon=" + String(lon, 6) + "&appid=" + apiKey;
        airHttp.begin(airUrl);
        int airCode = airHttp.GET();

        if (airCode > 0) {
          String airPayload = airHttp.getString();

          // Parsear el JSON de calidad de aire
          DynamicJsonDocument airDoc(1024);
          DeserializationError airError = deserializeJson(airDoc, airPayload);

          if (!airError) {
            //* --- Datos de calidad del aire ---
            int aqi = airDoc["list"][0]["main"]["aqi"];

            //* Imprimir datos de calidad del aire
            Serial.print("Calidad del aire (AQI): ");
            Serial.print(aqi);
            Serial.print(" - ");

            //* Convertir AQI a texto
            String airQuality;
            switch (aqi) {
              case 1: airQuality = "Buena"; break;
              case 2: airQuality = "Aceptable"; break;
              case 3: airQuality = "Moderada"; break;
              case 4: airQuality = "Mala"; break;
              case 5: airQuality = "Muy Mala"; break;
              default: airQuality = "Desconocida"; break;
            }

            //* --- Imprimir calidad del aire en texto ---
            Serial.println(airQuality.c_str());

            //* --- Enviar datos de calidad del aire a Blynk ---
            Blynk.virtualWrite(V4, aqi); // Calidad del aire
            Blynk.virtualWrite(V6, airQuality); // Calidad del aire en texto
          } else {
            Serial.print("Error al parsear calidad del aire: ");
            Serial.println(airError.c_str());
          }
        } else {
          Serial.print("Error en la petición de calidad del aire: ");
          Serial.println(airCode);
        }

        airHttp.end(); // Cerrar conexión HTTP de calidad del aire

        Serial.println("-----------------------------");

      } else {
        Serial.print("Error al parsear JSON: ");
        Serial.println(error.c_str());
      }

    } else {
      Serial.print("Error en la petición HTTP: ");
      Serial.println(httpResponseCode);
    }

    http.end();

  } else {
    Serial.println("WiFi desconectado.");
  }
}
