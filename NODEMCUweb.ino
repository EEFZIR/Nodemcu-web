#include <ESP8266WiFi.h>

const char* ssid = "net name";
const char* password = "net password";
 
int ledPin = 13;
int L;
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
  WiFiClient client = server.available();
  if (!client){
  return;}
 
  Serial.println("new client");
  while(!client.available()){
  delay(1);}
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  if (request.indexOf("/LED=ON") != -1)  {
  digitalWrite(ledPin, HIGH);
  L = HIGH;}
  if (request.indexOf("/LED=OFF") != -1)  {
  digitalWrite(ledPin, LOW);
  L = LOW;}
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 //********************************************************************* 
   client.print("<center><h1>WWW.EEFZ.IR</h1></center><br>");
 
if(L==LOW){
client.print("<center><h1>LED is now : LED OFF</h1></center>");  
}
else{
client.print("<center><h1>LED is now : LED ON</h1></center>"); 
} 

  client.println("<br><br>");
  client.println("<center>");
  client.println("<a href=\"/LED=ON\"\"><h1><button>On </button></h1></a>");
  client.println("</center>");
  client.println("<center>");
  client.println("<a href=\"/LED=OFF\"\"><h1><button>Off </button><h1></a><br />");  
  client.println("</center>");
  client.println("</html>");
 
}
