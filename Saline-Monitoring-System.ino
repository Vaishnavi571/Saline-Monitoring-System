#include <Blynk.h>
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

 int val1 = 0;  
 int val2 = 0;
 int ml = 5;
 int ML = 20;
 int c1=0;
 int c2=0;
 int c3=0;

 int t1[21];
 int TotalTimeRequired, FirstDrop, TwentiethDrop, TimeDifference, MessageTime;
 int i=0;

 
// WiFi
const char *ssid = "Moto"; // Enter your WiFi name
const char *password = "chair@12";  // Enter WiFi password
const char *auth = "FjYFclKFcP-IzoK6vn4fQlLNTl1jzxpK"; 


void setup() {
 
  Serial.begin(9600);
  // connecting to a WiFi network
  Blynk.begin(auth, ssid, password, "blynk.cloud", 80);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  }

  void loop() {
  Blynk.run();
  val1 = digitalRead(5); // IR Sensor output pin connected to D1  
  val2 = digitalRead(4); // IR Sensor output pin connected to D2

  if(val1==0){
     for(i=0;i<=0;i++){
      t1[i] = millis();
      Serial.print("Time1=");
      Serial.println(t1[i]);
      c1++;
      while(c1 == 1){
          FirstDrop = t1[i]/1000;
          Serial.print("FisrtDrop=");
          Serial.println(FirstDrop);
          break;
      }
      while(c1 == 20){
          TwentiethDrop = t1[i]/1000;
          Serial.print("TwentiethDrop=");
          Serial.println(TwentiethDrop);
          TimeDifference = TwentiethDrop - FirstDrop;
          TotalTimeRequired = (ML * TimeDifference)/ml;
          Serial.print("TotalTimeRequired=");
          Serial.println(TotalTimeRequired);
          break;
        }
        
      MessageTime = TotalTimeRequired - 30;
      Serial.print("Drop=");
      Serial.println(c1);
      delay(1000);

      if (millis()/1000 >= MessageTime){
            Blynk.notify("The Saline Bottle will be empty in next 30 seconds");
            break;
        }
    }
  }
      else
      {
        c2++;
      }

  if (val2==0){
     Blynk.notify("The Saline Bottle is empty...");
    }
//  if (c3==3){
//        Blynk.notify("The Saline Bottle is empty...");
//    }


//   if(val2==1){
//      c3=1;
//    }
//   if (c3 && val2==0){
//      Blynk.notify("The Saline Bottle is empty...");
//    }
    
  
}
