#include <ESP8266WiFi.h>

//my hub and eSP8266 NodeMCU have manually assigned, fixed IP addresses
const unsigned int serverPort = 9070; // ESP8266 server port (pick any unused port)
IPAddress hubIp(192, 168, 1, XXX); // Smartthings hub ip
const unsigned int hubPort = 39500; //Smartthings hub port

byte switchstate = 0;  // 0 is off, 1 is on
WiFiServer server(serverPort);
WiFiClient client;

// use a json string to post the state of the switch to the hub
String jsonString = "{\"name\":\"switch\",\"state\":";

void handleOf(String xx) {
  if (xx == "on") {
  digitalWrite(LED_BUILTIN, LOW);
  switchstate = 1;
  } else {
  digitalWrite(LED_BUILTIN, HIGH);
  switchstate = 0;
  }
}

void notifyHub(String jsonString){
if (client.connect(hubIp, hubPort)) {
    client.println("POST / HTTP/1.1");
    client.print("Host: ");
    client.print(hubIp);
    client.print(":");
    client.println(hubPort);
    sendJSONData(client);
   }
 
while (client.connected() && !client.available()) delay(1);
    while (client.connected() || client.available())
    {
      char c = client.read();
    }

    delay(1);
    client.stop();
  }

void sendJSONData(WiFiClient client){
 client.println("CONTENT-TYPE: application/json");
 client.println("CONTENT-LENGTH: 27");
 client.println();
 client.print(jsonString);
 client.print(switchstate);
 client.println("}");  
}


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial.begin(115200);
  Serial.println();
  WiFi.begin("your network name"); // my network is open
  // WiFi.begin("ssid", "password"); for a password-protected network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  delay(1000);
  notifyHub(jsonString);
  Serial.println();
  Serial.println("closing connection");
  delay(1000);
}

void readHub(){
  // read the post from the hub and extract the on or off command
  String readmyString; 
  String tempString; 
  
  WiFiClient client = server.available();
  if (client) {
  boolean currentLineIsBlank = true;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      //read char by char HTTP request
      if (readmyString.length() < 100) {
        //store characters to string
        readmyString += c;
      }
      if (c == '\n' && currentLineIsBlank) {
       tempString = readmyString.substring(readmyString.indexOf('/') + 1, readmyString.indexOf('?'));
       //tempstring will either contain on or off
       if (tempString.length() > 0) {
             handleOf(tempString);
             client.println("HTTP/1.1 200 OK");
             sendJSONData(client);
        }
        else {
          client.println(F("HTTP/1.1 204 No Content"));
          client.println();
          client.println();
        }
        break;
      }
      if (c == '\n') {
        // you're starting a new line
        currentLineIsBlank = true;
      } else if (c != '\r') {
        // you've gotten a character on the current line
        currentLineIsBlank = false;
      }
    }
  }
  readmyString = "";
  tempString = "";
  delay(1);
  //stopping client
  client.stop();
}}

void loop() {
readHub();
}
