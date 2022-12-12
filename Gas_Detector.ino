#define BLYNK_TEMPLATE_ID "TMPLpteNNCes"
#define BLYNK_DEVICE_NAME "Gaz Leakage"
#define BLYNK_AUTH_TOKEN "1Ow2Rj44-VlAtQOthU2qnmAfsKYPJQYG"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "ENSEIGNANT";  // type your wifi name
char pass[] ="$*en2022*#" ; // type your wifi password
 

BlynkTimer timer;

void sendSensor(){
 
 int data = analogRead(A0);
  Blynk.virtualWrite(V0, data);
  Serial.print("Pin A0: ");
  Serial.println(data);


  if(data > 500){
     digitalWrite(D6, HIGH);
      digitalWrite(D5, LOW);
      tone(D2,1000);
      delay(1000);
      noTone(D2 );
      delay(1000);
    Blynk.email("wiem.mseddi@enis.tn", "Alert", "Gas Leakage Detected!");
    Blynk.logEvent("gas_alert","Gas Leakage Detected");
  }
  else{
       digitalWrite(D6, LOW);
       digitalWrite(D5, HIGH);
       noTone(D2);
      
  }
}

void setup(){
 Serial.begin(9600); // Initialise le port série à 9600 bps // 
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
     

  pinMode(A0, INPUT);
   Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  //dht.begin();
  timer.setInterval(2500L, sendSensor);
}

void loop(){
  Blynk.run();
  timer.run();
}
