// Replace with your own Blynk credentials
#define BLYNK_TEMPLATE_ID "TMPL3_p9T5jnL"
#define BLYNK_TEMPLATE_NAME "SmartLEDS"
#define BLYNK_AUTH_TOKEN "XVoGxQX2SixExD8HsHjno6IYukvBF1Vq"

#define BLYNK_PRINT Serial

//libraries
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BlynkLED D4 // server state indicator led

//button pins
#define btn1 D0
#define btn2 D1
#define btn3 D2 
#define btn4 D3 

// Led/Relay pins
#define led1 D5
#define led2 D6
#define led3 D7 
#define led4 D8 

// relay/LED states
bool led1State = false;
bool led2State = false;
bool led3State = false; 
bool led4State = false; 

// server state
bool onlineMode = false;

// replace with your wifi config
char ssid[] = "AR~Yan";
char pass[] = "00000000";

// instence for blynk timer
BlynkTimer timer;

// function which check server state
void isServerConnected() {
  bool isConnected = Blynk.connected();
  if (isConnected == true) {
    onlineMode = true;
    digitalWrite(BlynkLED, HIGH);
    Serial.println("Connected");
  }
  if (isConnected == false) {
    if (onlineMode == true) {
      onlineMode = false;
    }
    Serial.println("Not Connected");
    digitalWrite(BlynkLED, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  timer.setInterval(2000L, isServerConnected); 

//pinmodes for all input outputs
  pinMode(BlynkLED, OUTPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT); 
  pinMode(led4, OUTPUT); 

  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP); 
  pinMode(btn4, INPUT_PULLUP); 
//

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // start blynk server
}

void loop() {
  timer.run();

  if (onlineMode) {
    Blynk.run();
    whenOnline(); // handles online functionalities
  } else {
    whenOffline(); // handles offline functionalities
  }
}


void whenOnline() {
  if (digitalRead(btn1) == LOW) {
    led1State = !led1State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn1) == LOW);
    updateBlynkServer();
  }

  if (digitalRead(btn2) == LOW) {
    led2State = !led2State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn2) == LOW);
    updateBlynkServer();
  }

  if (digitalRead(btn3) == LOW) {
    led3State = !led3State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn3) == LOW);
    updateBlynkServer();
  }

  if (digitalRead(btn4) == LOW) {
    led4State = !led4State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn4) == LOW);
    updateBlynkServer();
  }
}


void whenOffline() {
  if (digitalRead(btn1) == LOW) {
    led1State = !led1State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn1) == LOW);
  }

  if (digitalRead(btn2) == LOW) {
    led2State = !led2State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn2) == LOW);
  }

  if (digitalRead(btn3) == LOW) {
    led3State = !led3State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn3) == LOW);
  }

  if (digitalRead(btn4) == LOW) {
    led4State = !led4State;
    updateLEDs();
    delay(50);
    while (digitalRead(btn4) == LOW);
  }
}

// function to update led/relays with state values
void updateLEDs() {
  digitalWrite(led1, led1State);
  digitalWrite(led2, led2State);
  digitalWrite(led3, led3State);
  digitalWrite(led4, led4State);
}

// function to update states with blynk server
void updateBlynkServer() {
  Blynk.virtualWrite(V0, led1State);
  Blynk.virtualWrite(V1, led2State);
  Blynk.virtualWrite(V2, led3State);
  Blynk.virtualWrite(V3, led4State);
}


// functions to control led/relay with blynk app or dashboard
BLYNK_WRITE(V0) {
  led1State = param.asInt();
  Serial.println(led1State);
  updateLEDs();
}

BLYNK_WRITE(V1) {
  led2State = param.asInt();
  Serial.println(led2State);
  updateLEDs();
}

BLYNK_WRITE(V2) {
  led3State = param.asInt();
  Serial.println(led3State);
  updateLEDs();
}

BLYNK_WRITE(V3) {
  led4State = param.asInt();
  Serial.println(led4State);
  updateLEDs();
}

