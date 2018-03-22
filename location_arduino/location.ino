

// ====================================================================================
// Title  :  location 
// Author :  Eng. Mohamed Sayed Yousef  -  Mansoura, Egypt
//            https://electronics010.blogspot.com.eg/
// Date   :  25/02/2018
// ver    :  1.0
// Board  :  NodeMCU 1.0 
// ====================================================================================

// Libraries
#include <ESP8266WiFi.h>
#include "location.h"
//#include <UbidotsMicroESP8266.h>

const char* host = "aymen.dyndns.org";
String phpScript = "/aymen/update.php";
char ssid[] = "JessQuig";    // your network SSID (name) 
char pass[] = "Lily!1234";   // your network password


int keyIndex = 0;
WiFiClient client;
//int wifiStatus;

// Google API key
String geolocationKey = "AIzaSyBtaFmjAb-w73nKFADTEFvrXBMOufZTLAA";
String geocodingKey   = "AIzaSyAADqrPxp7HyEQC5xAF6xTzwUpwXOSv_ZU";

// From http://www.mcc-mnc.com/
int MCC = 302;  // Canada Country Code
int MNC = 720;    // Canada  Network Code
String carrier = "Rogers AT&T Wireless";

float latitude = 0.0;
float longitude = 0.0;


Location myLocation;

//Ubidots TOKEN
//--------------
//#define TOKEN "BBFF-GCxQniuhISuC6PBZAGHcmSyJTNyt9L"
//Ubidots client(TOKEN);
//char context[50];
// ===========================================================================================

void setup() {
  Serial.begin(115200);  

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");        
  }
        
  Serial.println("."); 
  Serial.println("WiFi connected");
  Serial.print("local IP: ");
  Serial.println(WiFi.localIP());

  // initialize the myLocation
  myLocation.begin(geolocationKey, geocodingKey, MCC, MNC, carrier);

    //Ubidots
    //-------------
    //client.wifiConnection(ssid, pass);
    //client.setDataSourceName("NodeMcu-1");
    //client.setDataSourceLabel("NodeMcu-1");
}

// ===========================================================================================

void loop() {  

   float latDir = 0.0;
  
  myLocation.getLocation();

  Serial.print("Latitude = ");     Serial.println(myLocation.latitude,7);
  Serial.print("Longitude = ");    Serial.println(myLocation.longitude,7);
  Serial.print("Accuracy = ");     Serial.println(myLocation.accuracy);
  Serial.print("Address: ");       Serial.println(myLocation.address); 
  Serial.println("-------------------------");

 //sprintf(context,"lat=%.6f$lng=%.6f",myLocation.latitude, myLocation.longitude );
 //client.add("position",1,context);
 //client.sendAll(true);
 String data1 = "&dir1=" + String(myLocation.latitude, 6);
  data1 += "&dir2=" + String(myLocation.longitude, 6);
   // String  data2= "&dir2=" + String(myLocation.longitude, 6);

   
   Serial.println("- connected!");
  // post data using HTTP POST
  Serial.println("Connecting to server...");
  const int httpPort = 80;

  if (client.connect(host, httpPort)) {
    Serial.println("- connected");
    Serial.println("Posting sensor data...");
    client.print("POST ");
    client.print(phpScript);
    client.println(" HTTP/1.1");
    client.println("Host:  aymen.dyndns.org");
    client.println("User-Agent: Arduino/1.0");
    client.println("Connection: close");
    client.println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    client.print("Content-Length: ");
    client.println(data1.length());
    client.println();
    client.print(data1);
    Serial.println("- done");
  }
  // disconnect when done
  Serial.println("Disconnecting from server...");
  client.stop();
  Serial.println("- bye!");
  // Wait for 1 Min.
  delay(20000);      
  
}

