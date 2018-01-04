#include "application.h"

// Test app outputs PWM signal on wakeup pin, which is connected to buzzer on BrewPi Spark V3

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
SerialLogHandler traceLog(LOG_LEVEL_TRACE);

void setup() {
    Serial.begin(115200);
    pinMode(WKP, OUTPUT);
}

void loop() {
    static uint32_t last_update = millis();
    static TCPServer tcpServer = TCPServer(6666);
    static TCPClient tcpClient;
    static bool tcpServerRunning = false;

    // Tic/toc on WiFi over TCP
    // reply to 't' with 'toc' over TCP, print other characters to serial
    if (WiFi.ready() && WiFi.localIP()[0] != 0) {
       if(!tcpServerRunning) {
           tcpServer.begin();
           tcpServerRunning = true;
       }
       else {
		   // if a new client appears, drop the old one
		   TCPClient newClient = tcpServer.available();
		   if(newClient) {
			   tcpClient.stop();
			   tcpClient = newClient;
		   }
       }
    }
    else {
       tcpClient.stop();
       tcpServer.stop();
       tcpServerRunning = false;

       if (WiFi.hasCredentials() && !WiFi.connecting()) {
           WiFi.connect();
       }
    }
    while (tcpClient.available() > 0) {
        char inByte = tcpClient.read();
        switch(inByte){
        case ' ':
        case '\n':
        case '\r':
            break;
        case 't':
            tcpClient.write("toc");
            break;
        default:
            Serial.printf("<-%c", inByte);
        }
    }

    // print status on serial every second
    if ( millis() - last_update > 1000UL ) {
        last_update = millis();
        bool wifiReady = WiFi.ready();
        IPAddress ip = WiFi.localIP();
        Serial.printf("WiFi.ready(): %d - IP: %d.%d.%d.%d\n", wifiReady, ip[0],ip[1],ip[2],ip[3]);
        analogWrite(WKP, 128, 3000);
        delay(50);
        analogWrite(WKP, 0, 3000);
    }
}
