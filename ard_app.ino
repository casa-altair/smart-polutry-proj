#include <MQ135.h>
#include <DHT.h>

#define PIN_MQ135 A2
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

MQ135 mq135_sensor(PIN_MQ135);

float temperature, humidity;
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}
void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  digitalWrite(7, ((temperature < 35.0) ? LOW : HIGH));
  (temperature < 35.0) ? Serial.println("LOW") : Serial.println("HIGH");
 
  
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(correctedPPM);
  delay(300);
}
