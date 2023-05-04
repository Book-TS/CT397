#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJSon.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// const char *ssid = "BookTS";
// const char *password = "12345678";

const char *ssid = "Yescoffee&tea2G";
const char *password = "66668888";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

LiquidCrystal_I2C myLCD(0x27, 16, 2);

struct dataJSON {
    int type;
    int mangoCost;
    int longanCost;
    int durianCost;
    float weight;
};

dataJSON dataESP32;

void Json_to_Value(String s);
void Value_to_JSon();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, 
                AwsEventType type, void *arg, uint8_t *data, size_t len);
void initWebSocket();

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    myLCD.init();
    myLCD.backlight();
    myLCD.setCursor(0, 0);
    myLCD.print("Cau hinh ...");

    WiFi.begin(ssid, password);

    for(size_t i = 0; i < 10; i++) {
        if(WiFi.status() != WL_CONNECTED) {
            myLCD.setCursor(9 + i%3 , 0);
            myLCD.print(".  ");
            if(i == 9) {
                myLCD.clear();
                myLCD.setCursor(2, 0);
                myLCD.print("That bai");
            }
            delay(1000);
        }
        else {
            Serial.println(WiFi.localIP());
            myLCD.clear();
            myLCD.setCursor(3, 0);
            myLCD.print("Hoan thanh");
            myLCD.setCursor(1, 1);
            myLCD.print(WiFi.localIP());

            initWebSocket();
            server.begin();
            return;
        }
    }
}

void loop()
{
    ws.cleanupClients();
    
    Value_to_JSon();

    delay(1000);
}

void initWebSocket()
{
    ws.onEvent(onEvent);
    server.addHandler(&ws);;
}

void Json_to_Value(String s) {
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, s);

    if (error) {
        Serial.println("Failed to parse JSON string.");
    }
    else {
        dataESP32.type = doc["type"];
        dataESP32.mangoCost = doc["mangoCost"];
        dataESP32.longanCost = doc["longanCost"];
        dataESP32.durianCost = doc["durianCost"];

        Serial.println(String(dataESP32.type) + " | " + String(dataESP32.mangoCost) + " | " + String(dataESP32.longanCost) + " | " + String(dataESP32.durianCost));
    }
    
}

void Value_to_JSon() {
    StaticJsonDocument<200> jsonVal;

    dataESP32.type = 2;
    dataESP32.weight = 200.01;

    jsonVal["type"] = dataESP32.type;
    jsonVal["weight"] = dataESP32.weight;
    
    String jsonString;
    serializeJson(jsonVal, jsonString);

    ws.textAll(jsonString);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
{
    AwsFrameInfo *info = (AwsFrameInfo *)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
    {
        data[len] = 0;
        Serial.println((char *)data);
        Json_to_Value((char *)data);
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, 
                AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        handleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
}