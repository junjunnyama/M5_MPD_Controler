// M5Stack ライブラリ
#include <M5Unified.h>

// フォント関連ヘッダ
// 使用する言語データを選択
// #include "efontEnableAll.h"
#include "efontEnableAscii.h"
#include "efontEnableCJK.h"
#include "efontEnableJa.h"
// M5Stack用描画ライブラリ
#include "efontM5Stack.h"

// Wifi 関連ライブラリ
#include <WiFi.h>
#include <WiFiClient.h>
// #include <WiFiMulti.h>

// MPD クライアントライブラリ
#include "MPD.h"

// mDNS ライブラリ
// #include <ESPmDNS.h>

// WiFi setting
const char ssid[] = "Your SSID";
const char pass[] = "Your PASS";
// WiFiClient client;
// WiFiMulti WiFimulti;

// MPD setting
MPD client;
IPAddress ip;
// mpd server by IP address
const char mpdserver[] = "IP:192.168.xxx.xxx";
// mpd port
uint16_t mpdport = 6600;

// mpd icons
MPDStatus mpdStatus;
CurrentSongStatus currentSongStatus;

void setup() {
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.setRotation(1);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);

  // WiFi connection
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
  // WiFimulti.addAP(ssid, pass);
  // while (WiFimulti.run() != WL_CONNECTED) {
    delay(500);
    printEfont(".");
  }
  printEfont("\n");
  printEfont("wifi connected\n");
  // printEfont("IP address: ");
  // printEfont(WiFi.localIP().toString());
  
  if (ip.fromString(mpdserver)){
    client.setMpdServer(ip, mpdport);
    while (!client.connectMpd()) {
      M5.Lcd.print(".");
      delay(10);
    }
  }

  Serial.println("MPD connected");
  mpdStatus = client.getStatus();
  Serial.println("Current MPD status");
  currentSongStatus = client.getCurrentSong();
  printEfont(mpdStatus.State + "\n");
  printEfont(String(mpdStatus.Volume) + "\n");
  printEfont(String(mpdStatus.PlaylistLen) + "\n");
  printEfont(String(mpdStatus.Randomf) + "\n");
  printEfont(String(mpdStatus.Repeatf) + "\n");
}

void loop() {
  // printEfont(sprite, "Hello", 0, 16*0);
  // printEfont(sprite, "こんにちは", 0, 16*1);
}
