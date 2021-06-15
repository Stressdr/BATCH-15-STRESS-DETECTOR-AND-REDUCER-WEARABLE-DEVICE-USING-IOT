#include <ESP8266WiFi.h>

const char* ssid = "smk";
const char* password = "12345678";

WiFiServer server(80);
String data;
void setup() {
  Serial.begin(9600);
  // Connect to WiFi network
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
  Serial.println(WiFi.localIP());
}

void loop() {
  if(Serial.available() > 0)  
    {
      //data=Serial.readStringUntil('\n');
      data=Serial.readString();
      //delay(2000);
      //data ="hb="+String(80)+"&gsr="+String(1)+"&ecg="+String(100);
  WiFiClient client = server.available();
   
  if (client.connect("www.stressdr.live",80)) 
  { 
    // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /add.php HTTP/1.1"); 
    client.println("Host:www.stressdr.live"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.println(data);
    data="";
  }
  if (client.connected()) 
  { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
    }
  delay(30000); // WAIT 10 seconds BEFORE SENDING AGAIN
}
