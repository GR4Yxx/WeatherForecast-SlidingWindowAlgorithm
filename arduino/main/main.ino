#include <ArduinoJson.h>
#include <FirebaseArduino.h>  
#include <ESP8266WiFi.h>
#include <DHTesp.h>



#define FIREBASE_HOST "nodeweatherforecast-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "lDnJfNzI6CmrzDFaxU3w8ovgB2ium9YaiLo0SnM8"

#define DHTpin 14  //D5

DHTesp dht;

const char* ssid = "Gray"; // Write here your router's username
const char* password = "lol12345";
void setup()
{
   pinMode(LED_BUILTIN, OUTPUT); 

  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
     digitalWrite(LED_BUILTIN, HIGH);  
     delay(1000);
     digitalWrite(LED_BUILTIN, LOW);    
     delay(1000);                        
  }
  Serial.println("");
  Serial.println("WiFi connected");
  //Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  if(Firebase.failed()){
    Serial.print(Firebase.error());
  }else{
    Serial.print("Firebase Connected");
   }
  
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");
  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
}

void loop()
{
  while(!Firebase.failed()){
    delay(dht.getMinimumSamplingPeriod());
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
  
    
    if(dht.getStatusString()=="TIMEOUT"){
      continue;
    }
    Firebase.setFloat("humidity",humidity);
    Firebase.setFloat("temperature",temperature);
    
    
  }
  Serial.print("firebase error");
  while(Firebase.failed()){
    Serial.print(Firebase.error());
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    
  }
  
  
}
