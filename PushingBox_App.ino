// Adding Internet Functionality
#include <Bridge.h>
#include <HttpClient.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleYun.h>

// Declaring Variables and Constants
// Declaring sensor PIR
int PIR = 2;  

 // Declaring Connectivity Variables
char auth[] = "hzjSsmPuyFpkg2QpaH5oIHch3GyopwrW"; 
char devid[] = "v963896FDE673C9F";
char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;

boolean previous_mailStatus = 0;

void setup() {
   Serial.begin(9600);
   pinMode(PIR, INPUT);
   previous_mailStatus = digitalRead(PIR);
   Bridge.begin();
   Blynk.begin(auth);
   pinMode(13, OUTPUT);
   digitalWrite(13, LOW);
   Bridge.begin();
   digitalWrite(13, HIGH);

  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
}

void loop() {
    // Initialize the client library
    HttpClient client;
    boolean mail_status = digitalRead(PIR);
    Blynk.run();
    if (mail_status != previous_mailStatus && !mail_status ) {
    // Sending a notification users mobile phone
    // function takes the message as a parameter
    Serial.println("Mail received. \n Wait for 5secs to send notification");
    Blynk.notify("Mail Received!");
    delay(5000);
     }
   previous_mailStatus = mail_status;

  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue = analogRead(A0);
  
  //Testing value - when sensor is not connected - comment out when sketch is shown to be working - and take value from A0 instead
  //sensorValue=1500;

  // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp=50&TempC="+sensorValue;
  client.get (APIRequest);
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
  }
  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded temp value: ");
  Serial.print(sensorValue);
  delay(5000);
}
