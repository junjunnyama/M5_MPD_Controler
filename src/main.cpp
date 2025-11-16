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

// MPD クライアントライブラリ
#include "MPD.h"

// mDNS ライブラリ
// #include <ESPmDNS.h>

// WiFi setting
const char ssid[] = "Your SSID";
const char pass[] = "Your PASS";;

// MPD setting
MPD client;
IPAddress ip;
// mpd server by IP address
const char mpdserver[] = "192.168.xxx.xxx";
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
    delay(500);
    printEfont(".");
  }
  // printEfont("\n");
  printEfont("wifi connected\n");
  
  if (ip.fromString(mpdserver)){
    while (!client.connectMpd(ip, mpdport)) {
      M5.Lcd.print(".");
      delay(500);
    }
  }
  // printEfont("\n");
  printEfont("MPD connected\n");

  Serial.println("MPD connected");
  mpdStatus = client.getStatus();
  printEfont(String(mpdStatus.State) + "\n");
  printEfont(String(mpdStatus.Volume) + "\n");
  printEfont(String(mpdStatus.PlaylistLen) + "\n");
  printEfont(String(mpdStatus.Random) + "\n");
  printEfont(String(mpdStatus.Repeat) + "\n");
  printEfont(String(mpdStatus.Single) + "\n");
  printEfont(String(mpdStatus.PlaylistLen) + "\n");
  printEfont(String(mpdStatus.PlayNum) + "\n");
  printEfont(String(mpdStatus.Time) + "\n");
  printEfont(String(mpdStatus.TotalTime) + "\n");
  
  Serial.println("Current MPD status");
  currentSongStatus = client.getCurrentSong();
  printEfont(String(currentSongStatus.Title) + "\n");
  printEfont(String(currentSongStatus.Artist) + "\n");
  printEfont(String(currentSongStatus.Album) + "\n");
  printEfont(String(currentSongStatus.Time) + "\n");
}

void loop() {
  // printEfont(sprite, "Hello", 0, 16*0);
  // printEfont(sprite, "こんにちは", 0, 16*1);
}
