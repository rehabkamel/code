#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h> // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>
#include "DHT.h"
#define DHTPIN 4 
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Wifi network station credentials
#define WIFI_SSID "@"
#define WIFI_PASSWORD "@Ashraf1357689&"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5825993132:AAEAZiBhnBhxF_SlbTRr2N7RmWrE7pry2wk" //"6074784599:AAEkqaL7Vr02V4yTi_Q7wwjamCmuVvj5QrQ"
#define CHAT_ID "961908684"    //"1133690338"
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
DHT dht(DHTPIN, DHTTYPE);
const unsigned long BOT_MTBS = 1000; // mean time between scan messages
unsigned long bot_lasttime; // last time messages' scan has been done
float temperatureC;
float temperatureF;
float humidity;
void setup()
{
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "/start system work", "");
}
void loop()
{
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
   temperatureC = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  temperatureF = dht.readTemperature(true);
  
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);
  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID )
    {
      bot.sendMessage(chat_id, "Unauthorized user", "");
    }
    else
    {
      String text = bot.messages[i].text;
      String from_name = bot.messages[i].from_name;
      if (from_name == "")
        from_name = "Guest";
      if (text == "/temperature")
      {   String msg = "human body temperature is ";
          msg += msg.concat(temperatureC);
          msg += "degrees";
          bot.sendMessage(chat_id,msg, ""); 
      }
      if (text == "/pressure")
      {  
          String msg = "human body pressure is ";
          msg += msg.concat(temperatureF);
          msg += "mmHg";
          bot.sendMessage(chat_id,msg, ""); 
      }
      if (text == "/oxygen")
      {  
          String msg = "oxygen percentage is ";
          msg += msg.concat(humidity);
          msg += "%"; 
          bot.sendMessage(chat_id,msg, ""); 
      }
      if (text == "/start")
      {
        String welcome = "Patient follow-up system.\n";
        welcome += "/temperature : human body temperature \n";
        welcome += "A normal body temperature level is 37 degrees Celsius\n";
        welcome += "/pressure : human body pressure \n";
        welcome += "A normal blood pressure level is less than 120/80 mmHg\n";
        welcome += "/oxygen : oxygen percentage \n";
        welcome += "A normal pulse oximeter reading for your oxygen saturation level is between 95% and 100% \n";
        bot.sendMessage(chat_id, welcome, "Markdown");
      }
    }
  }
}