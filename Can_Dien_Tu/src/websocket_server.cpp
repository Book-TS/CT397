// #include <WiFi.h>
// #include <ESPAsyncWebServer.h>

// const char *ssid = "BookTS";
// const char *password = "12345678";

// bool ledState = 0;
// const int ledPin = 2;

// AsyncWebServer server(80);
// AsyncWebSocket ws("/ws");

// void notifyClients()
// {
//     ws.textAll(String(ledState));
// }

// void handleWebSocketMessage(void *arg, uint8_t *data, size_t len)
// {
//     AwsFrameInfo *info = (AwsFrameInfo *)arg;
//     if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT)
//     {
//         data[len] = 0;
//         if (strcmp((char *)data, "toggle") == 0)
//         {
//             ledState = !ledState;
//             notifyClients();
//         }
//     }
// }

// void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
//              void *arg, uint8_t *data, size_t len)
// {
//     switch (type)
//     {
//     case WS_EVT_CONNECT:
//         Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
//         break;
//     case WS_EVT_DISCONNECT:
//         Serial.printf("WebSocket client #%u disconnected\n", client->id());
//         break;
//     case WS_EVT_DATA:
//         handleWebSocketMessage(arg, data, len);
//         break;
//     case WS_EVT_PONG:
//     case WS_EVT_ERROR:
//         break;
//     }
// }

// void initWebSocket()
// {
//     ws.onEvent(onEvent);
//     server.addHandler(&ws);
// }

// String processor(const String &var)
// {
//     Serial.println(var);
//     if (var == "STATE")
//     {
//         if (ledState)
//         {
//             return "ON";
//         }
//         else
//         {
//             return "OFF";
//         }
//     }
//     return String();
// }

// void setup()
// {
//     Serial.begin(115200);

//     pinMode(ledPin, OUTPUT);
//     digitalWrite(ledPin, LOW);

//     WiFi.begin(ssid, password);
//     while (WiFi.status() != WL_CONNECTED)
//     {
//         delay(1000);
//         Serial.println("Connecting to WiFi..");
//     }

//     Serial.println(WiFi.localIP());

//     initWebSocket();

//     server.begin();
// }

// void loop()
// {
//     ws.cleanupClients();
//     digitalWrite(ledPin, ledState);
// }