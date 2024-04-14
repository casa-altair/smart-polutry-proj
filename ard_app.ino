#include <MQ135.h>
#include <DHT.h>

#define PIN_MQ135 A2
#define DHTPIN 2
#define temp_fan_pin 7
#define temp_thresold 30.00
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
MQ135 mq135_sensor(PIN_MQ135);

float temperature, humidity;
void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(temp_fan_pin, OUTPUT);
  digitalWrite(temp_fan_pin, HIGH);
}
void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  digitalWrite(temp_fan_pin, ((temperature < temp_thresold) ? HIGH : LOW));
 
  
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  Serial.print(temperature);
  Serial.print(",");
  Serial.print(humidity);
  Serial.print(",");
  Serial.println(correctedPPM);
  delay(300);
}
