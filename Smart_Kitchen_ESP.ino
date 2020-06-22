#include <ESP8266WiFi.h>
 
const char* ssid = "ROUTER ID HERE";
const char* password = "PASSWORD";
 
int ledPin = 12; //LED

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // DESIGN

  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #004E05; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #CFBE05;}</style></head>");

  //  Heading
  client.println("<body><h1>SMART KITCHEN</h1>");\
  client.println("<body><h3>Created By TEAM INFINITY</h4>");
  
  client.print("<body><h5>Led is now: </h3>");
 
  if(value == HIGH) {
    client.print("ON");
  } else {
    client.print("OFF");
  }
           
  client.println("<p><a href=\"/LED=ON\"><button class=\"button\">TURN ON</button></a></p>");
           
  client.println("<p><a href=\"/LED=OFF\"><button class=\"button button2\">TURN OFF</button></a></p>");
                   

  client.println("</body></html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
