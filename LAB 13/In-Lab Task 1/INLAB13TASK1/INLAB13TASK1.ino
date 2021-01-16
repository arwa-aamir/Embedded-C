#include <WiFi.h> #include <WebServer.h> #include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
#define DHTTYPE DHT11  // DHT 11
//#define DHTTYPE DHT21 // DHT 21 (AM2301)data:image/pjpeg;base64,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
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321

/*Put your SSID & Password*/
const char* ssid = "PinkPanther"; // Enter SSID here
const char* password = "AFA123E185"; //Enter Password here

WebServer server(80);

// DHT Sensor uint8_t DHTPin = 15;

// Initialize DHT sensor. DHT dht(DHTPin, DHTTYPE);

float Temperature; float Humidity;

void setup() { Serial.begin(115200); delay(100);

pinMode(DHTPin, INPUT);
dht.begin();

Serial.println("Connecting to "); Serial.println(ssid);
data:image/pjpeg;base64,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
//connect to your local wi-fi network WiFi.begin(ssid, password);

//check wi-fi is connected to wi-fi network while (WiFi.status() != WL_CONNECTED) { delay(1000);
Serial.print(".");
}
Serial.println(""); Serial.println("WiFi connected..!");
Serial.print("Got IP: "); Serial.println(WiFi.localIP());

server.on("/", handle_OnConnect); server.onNotFound(handle_NotFound);

server.begin();
Serial.println("HTTP server started");

}
void loop() { server.handleClient();
}

void handle_OnConnect() {

Temperature = dht.readTemperature(); // Gets the values of the temperature
Humidity = dht.readHumidity(); // Gets the values of the humidity
server.send(200, "text/html", SendHTML(Temperature,Humidity));
}

void handle_NotFound(){
server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){ String ptr = "<!DOCTYPE html> <html>\n";
ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
ptr +="<title>ESP32 Weather Report</title>\n";
ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n"; ptr +="</style>\n";
ptr +="</head>\n"; ptr +="<body>\n";
ptr +="<div id=\"webpage\">\n";
ptr +="<h1>ESP32 Weather Report</h1>\n";

ptr +="<p>Temperature: "; ptr +=(int)Temperaturestat; ptr +="°C</p>";
ptr +="<p>Humidity: "; ptr +=(int)Humiditystat; ptr +="%</p>";

ptr +="</div>\n"; ptr +="</body>\n"; ptr +="</html>\n"; return ptr;
}
