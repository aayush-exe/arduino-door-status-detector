#include <Arduino.h>
#include <Discord_WebHook.h>
#include <HTTPClient.h>

// CHANGE THIS:
// Set delay between status update and message (this is 60 seconds)
const int MESSAGE_DELAY_MSEC = 60 * 1000;

long fetchEpochHTTP()
{
  HTTPClient http;
  if (http.begin("https://worldtimeapi.org/api/ip")) {   // auto-detects your TZ
    int code = http.GET();
    if (code == HTTP_CODE_OK) {
      String body = http.getString();
      int p = body.indexOf("\"unixtime\":");
      if (p > 0) {
        long epoch = body.substring(p + 11).toInt();
        return epoch;
      }
    }
  }
  return 0;                                             // error
}

Discord_Webhook discord; // Create a Discord_Webhook object

// CHANGE THIS:
// This is what your Discord webhook link will look like:
// https://discord.com/api/webhooks/1234567890123456789/bunchofgibberishhere_MveG2KSy0kzqeX0mFmTmHW5iLs
//        this is the channel id -> ___________________|_______________________________________________ <- this is the token

// Replace your channel id and token below like the example
String channel_id = "1234567890123456789";
String token = "bunchofgibberishhere_MveG2KSy0kzqeX0mFmTmHW5iLs";

static const uint8_t switchPin = 7; // pin connected to arduino for limit switch
bool currentState;
bool prevState;

bool lab_status = true;
bool queue_message = false;
unsigned long prev_time = 0;
bool last_message_sent = true;

void setup() {
  Serial.begin(115200);
  delay(300);
  discord.begin(channel_id, token); // Initialize the Discord_Webhook object

  // CHANGE THIS:
  // Replace your wifi name and password below

  discord.addWiFi("WIFI_NAME_HERE","WIFI_PASSWORD_HERE"); // Add WiFi credentials (you can add multiples WiFi SSID)
  // discord.setTTS(true); // Add TTS
  discord.connectWiFi(); // Connect to WiFi
  pinMode(switchPin, INPUT_PULLUP); // for limit switch
  currentState = digitalRead(switchPin) == LOW ? true : false;

  Serial.println("Serials started");
}

void loop() {

  prevState = currentState;
  currentState = digitalRead(switchPin) == LOW ? true : false;
  // if (currentState && !prevState) {
  if (currentState != prevState) {
    // lab_status = !lab_status;
    lab_status = !currentState; // closed switch == true == closed lab
    queue_message = true;
    prev_time = millis();
    Serial.print("set to ");
    Serial.println(lab_status ? "open" : "closed");
  }

  if (millis() - prev_time > (MESSAGE_DELAY_MSEC) || millis() < prev_time){
    prev_time = millis();
    if (queue_message){
      if (last_message_sent == lab_status)
        queue_message = false;
      else {
        // long epoch = fetchEpochHTTP();
        // if (epoch==0){
        //   delay(3000);
        //   epoch = fetchEpochHTTP();
        //   if (epoch==0){
        //     delay(3000);
        //     epoch = fetchEpochHTTP();
        //   }
        // }
        delay(300);
        String open_or_closed = (lab_status ? "**open**" : "**closed**");
        String message_str = "Lab is currently " + open_or_closed;
        // if (epoch!=0) message_str = message_str + ", last updated: <t:"+ epoch +":R>";
        if (discord.send(message_str) == true) {
          queue_message = false;
          last_message_sent = lab_status;
        }
      }
    }
  }

  delay(100);

}
