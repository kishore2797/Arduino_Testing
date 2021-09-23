//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Set these to run example.
#define FIREBASE_HOST "mytube-7ad95.firebaseio.com"
#define FIREBASE_AUTH "Wkor1q5WA8iNKfTactUu84m5b00tROrjUMqaCdjd"

#define WIFI_SSID "deffe"
#define WIFI_PASSWORD "podanaye"

FirebaseData fbdo;

FirebaseJson json;

void setup() {
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  //Initialize the library with the Firebase authen and config.
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
  // set value
  Firebase.setInt(fbdo, "/Users/Numbers", 42);

  json.clear().add("Data" + String(100), 50);

  Firebase.pushJSON(fbdo, "/JsonData", json);

  Firebase.setString(fbdo, "/StringData/Text", "Hello");

  if (Firebase.getString(fbdo, "/StringData/Text")) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
      Serial.println("ETag: " + fbdo.ETag());
      Serial.println("Data:" + fbdo.stringData());
      Serial.print("VALUE: ");
      Serial.println("------------------------------------");
      Serial.println();
  }
  else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

  if(Firebase.getInt(fbdo, "/Users/Numbers") == 42) {
    Serial.println(42);
  }
}

void loop() {
  
  
}
