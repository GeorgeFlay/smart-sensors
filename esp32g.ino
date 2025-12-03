// #include <DHT.h>

// #define DHTPIN 15
// #define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(115200);
//   delay(1000);
//   Serial.println("Inicjalizacja DHT22...");

//   dht.begin();
//   Serial.println("Gotowe. Odczyt co 2 sekundy.");
// }

// void loop() {
 
//   float hum = dht.readHumidity();
//   float temp = dht.readTemperature();

//   Serial.println("----- DHT22 -----");

//   if (isnan(hum) || isnan(temp)) {
//     Serial.println("Błąd odczytu DHT22! (NaN). Sprawdź połączenia.");
//   } else {
//     Serial.print("Temperatura: ");
//     Serial.print(temp);
//     Serial.println(" °C");

//     Serial.print("Wilgotność: ");
//     Serial.print(hum);
//     Serial.println(" %");
//   }

//   Serial.println("-----------------");
//   delay(2000); // 2 sekundy
// }




// void setup() {}
// void loop() {}





// #include <Wire.h>
// #include <BH1750.h>
// #include <DHT.h>

// // ----- DHT22 -----
// #define DHTPIN 15     
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);

// // ----- BH1750 -----
// BH1750 lightMeter; 


// void setup() {
//   Serial.begin(115200);
//   delay(500);
//   Serial.println("Inicjalizacja czujników...");

//   // DHT
//   dht.begin();
//   Serial.println("DHT22 initialized.");

//   // I2C for BH1750: SDA=21, SCL=22
//   Wire.begin(21, 22);
//   if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
//     Serial.println("BH1750 działa poprawnie.");
//   } else {
//     Serial.println("[BH1750] Device is not configured!");
//   }

//   Serial.println("Gotowe!\n");
// }

// void loop() {
//   // --- DHT22 ---
//   float temp = dht.readTemperature();
//   float hum  = dht.readHumidity();

//   // --- BH1750 ---
//   float lux = lightMeter.readLightLevel();

//   Serial.println("----- Dane czujników -----");

//   // DHT22
//   if (isnan(temp) || isnan(hum)) {
//     Serial.println("DHT22: błąd odczytu!");
//     Serial.println("Sprawdź: DATA pin, zasilanie, pull-up (jeśli brak modułu)");
//   } else {
//     Serial.print("Temperatura: ");
//     Serial.print(temp);
//     Serial.println(" °C");

//     Serial.print("Wilgotność: ");
//     Serial.print(hum);
//     Serial.println(" %");
//   }

//   // BH1750
//   if (lux < 0) {
//     Serial.print("Natężenie światła: błąd odczytu! (lux=");
//     Serial.print(lux);
//     Serial.println(")");
//     Serial.println("Sprawdź: SDA/SCL, zasilanie, adres ADDR.");
//   } else {
//     Serial.print("Natężenie światła: ");
//     Serial.print(lux);
//     Serial.println(" lx");
//   }

//   Serial.println("--------------------------\n");
//   delay(2000);
// }








#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <DHT.h>
#include <BH1750.h>

// --------------------
// CONFIG
// --------------------
const char* ssid = "UPC2051908";
const char* password = "dbBnv2ssbFay";

// Firebase Realtime Database REST endpoint:
// NIE KOŃЧИ на /
// przykład:
// https://smartsensors-default-rtdb.europe-west1.firebasedatabase.app
String firebaseURL = "https://smartsensors-dbf09-default-rtdb.europe-west1.firebasedatabase.app/";

// // --------------------
// // DHT22
// // --------------------
// #define DHTPIN 15
// #define DHTTYPE DHT22
// DHT dht(DHTPIN, DHTTYPE);

// // --------------------
// // BH1750
// // --------------------
// BH1750 lightMeter;

// // --------------------
// // Setup
// // --------------------
// void setup() {
//   Serial.begin(115200);
//   delay(1000);

//   // WiFi
//   Serial.println("Łączenie z WiFi...");
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("\nPołączono!");

//   // Czujniki
//   dht.begin();
//   Wire.begin(21, 22);
//   if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
//     Serial.println("BH1750 OK");
//   } else {
//     Serial.println("BŁĄD BH1750!");
//   }
// }

// // --------------------
// // Funkcja: wyślij dane do Firebase
// // --------------------
// void sendToFirebase(float temp, float hum, float lux) {
//   if (WiFi.status() != WL_CONNECTED) return;

//   HTTPClient http;

//   String url = firebaseURL + "/data.json";

//   http.begin(url);

//   http.addHeader("Content-Type", "application/json");

//   String payload = "{";
//   payload += "\"temperature\": " + String(temp) + ",";
//   payload += "\"humidity\": " + String(hum) + ",";
//   payload += "\"light\": " + String(lux) + ",";
//   payload += "\"timestamp\": " + String(millis());
//   payload += "}";

//   int httpCode = http.PUT(payload);

//   Serial.print("Wysyłanie do Firebase: ");
//   Serial.println(payload);

//   if (httpCode > 0) {
//     Serial.print("Odpowiedź: ");
//     Serial.println(http.getString());
//   } else {
//     Serial.print("Błąd HTTP: ");
//     Serial.println(httpCode);
//   }

//   http.end();
// }

// // --------------------
// // Loop
// // --------------------
// void loop() {
//   float temp = dht.readTemperature();
//   float hum = dht.readHumidity();
//   float lux = lightMeter.readLightLevel();

//   Serial.println("----- Odczyt -----");

//   Serial.print("Temp: ");
//   Serial.println(temp);

//   Serial.print("Hum: ");
//   Serial.println(hum);

//   Serial.print("Lux: ");
//   Serial.println(lux);

//   sendToFirebase(temp, hum, lux);

//   delay(5000);
// }





// -------------------------
// CZUJNIKI
// -------------------------
#define DHTPIN 15
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

BH1750 lightMeter;

// -------------------------
// SETUP
// -------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Wi-Fi
  Serial.println("Łączenie z WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("\nPołączono z WiFi.");

  // Inicjalizacja czujników
  dht.begin();
  Wire.begin(21, 22);

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
      Serial.println("BH1750 OK");
  } else {
      Serial.println("Błąd BH1750!");
  }
}

// -------------------------
// FUNKCJA WYSYŁANIA DO FIREBASE
// -------------------------
void sendToFirebase(float temp, float hum, float lux) {
  if (WiFi.status() != WL_CONNECTED) return;

  HTTPClient http;

  String url = firebaseURL + "/data.json";
  http.begin(url);

  http.addHeader("Content-Type", "application/json");

  // JSON wysyłany do bazy
  String payload = "{";
  payload += "\"temperature\": " + String(temp) + ",";
  payload += "\"humidity\": " + String(hum) + ",";
  payload += "\"light\": " + String(lux) + ",";
  payload += "\"timestamp\": " + String(millis());
  payload += "}";

  Serial.println("\nWysyłanie danych:");
  Serial.println(payload);

  int httpCode = http.PUT(payload);

  Serial.print("Kod odpowiedzi: ");
  Serial.println(httpCode);

  if (httpCode > 0) {
      Serial.println(http.getString());
  }

  http.end();
}

// -------------------------
// LOOP
// -------------------------
void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float l = lightMeter.readLightLevel();

  Serial.println("------ ODCZYT ------");

  Serial.print("Temperatura: ");
  Serial.println(t);

  Serial.print("Wilgotność: ");
  Serial.println(h);

  Serial.print("Światło (lx): ");
  Serial.println(l);

  sendToFirebase(t, h, l);

  delay(5000);
}
