#include <Arduino.h>
#include <M5Unified.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const char SSID[] = "udp_screen";
const char PASSWORD[] = "samplePass";

// UDP設定
WiFiUDP wifiudp;
const int port = 3000;

void setup() {
    // セットアップ
    auto cfg = M5.config();
    M5.begin(cfg);
    // アクセスポイント設定
    WiFi.softAP(SSID, PASSWORD);
    // 画面
    M5.Display.setRotation(1);
    M5.Display.setTextSize(2);
    M5.Display.println("receiver");
    M5.Display.printf("SSID:%s\n", SSID);
    M5.Display.printf("PASSWORD:%s\n", PASSWORD);
    M5.Display.println(WiFi.softAPIP());  // ホストIPアドレス

    // pinMode(10, OUTPUT);     // LEDピン設定
    // digitalWrite(10, HIGH);  // LED_OFF

    wifiudp.begin(port);  // UDP開始
}

void loop() {
    int packetSize = wifiudp.parsePacket();
    if (packetSize) {
        // digitalWrite(10, LOW);  // LED_ON
        // sleep(1);
        // digitalWrite(10, HIGH);  // LED_OFF
        static uint8_t img[65536];  // 受信用バッファ
        int len = wifiudp.read(img, sizeof(img));
        M5.Display.drawJpg(img, len);  // 画像表示
    }
}