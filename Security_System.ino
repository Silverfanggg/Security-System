#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

int Buzzer 2
int Sensor 4

const char* ssid = "Wifi ID";
const char* password = "Wifi Password";

String phoneNumber = "Phone Number"; 
String apiKey = "API KEY";

void setup() {
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);
  pinMode(Sensor, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  
  sendAlert("Your system is ready!");
}

void loop() {
  bool sensorValue = digitalRead(Sensor);
  if (sensorValue == 1) {
    digitalWrite(Buzzer, HIGH);
    sendAlert("Warning!");
  } else {
    digitalWrite(Buzzer, LOW);
  }
}


void sendAlert(String message) {

  
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  }
  else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  
  http.end();
}
