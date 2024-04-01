#include <MQ135.h>
#include <DHT.h>
#define PIN_MQ135 A2
#define DHTPIN 2
#define DHTTYPE DHT11
MQ135 mq135_sensor(PIN_MQ135);
DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity;
void setup() {
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(correctedPPM);
  delay(300);
}
