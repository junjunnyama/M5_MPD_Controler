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

// M5Stack 画面用キャンバス
M5Canvas canvas(&M5.Lcd);

// WiFi setting
const char ssid[] = "Your SSID";
const char pass[] = "Your PASS";

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

// プロトタイプ宣言
void ResetCanvas(int dir);

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(1);
  Serial.begin(115200);

  // キャンバス初期化
  canvas.createSprite(M5.Lcd.width(), M5.Lcd.height());
  canvas.fillScreen(BLACK);
  ResetCanvas(0);

  // WiFi connection
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    printEfont(&canvas, ".");
  }
  printEfont(&canvas, "\n");
  printEfont(&canvas, "wifi connected\n");
  
  // MPD connection
  if (ip.fromString(mpdserver)){
    while (!client.connectMpd(ip, mpdport)) {
      canvas.print(".");
      delay(500);
    }
  }
  printEfont(&canvas, "\n");
  printEfont(&canvas, "MPD connected\n");

  Serial.println("MPD connected");
  mpdStatus = client.getStatus();
  printEfont(&canvas, String(mpdStatus.State) + "\n");
  printEfont(&canvas, String(mpdStatus.Volume) + "\n");
  printEfont(&canvas, String(mpdStatus.PlaylistLen) + "\n");
  printEfont(&canvas, String(mpdStatus.Random) + "\n");
  printEfont(&canvas, String(mpdStatus.Repeat) + "\n");
  printEfont(&canvas, String(mpdStatus.Single) + "\n");
  printEfont(&canvas, String(mpdStatus.PlaylistLen) + "\n");
  printEfont(&canvas, String(mpdStatus.PlayNum) + "\n");
  printEfont(&canvas, String(mpdStatus.Time) + "\n");
  printEfont(&canvas, String(mpdStatus.TotalTime) + "\n");
  
  Serial.println("Current MPD status");
  currentSongStatus = client.getCurrentSong();
  printEfont(&canvas, String(currentSongStatus.Title) + "\n");
  printEfont(&canvas, String(currentSongStatus.Artist) + "\n");
  printEfont(&canvas, String(currentSongStatus.Album) + "\n");
  printEfont(&canvas, String(currentSongStatus.Time) + "\n");
}

void loop() {
  // printEfont(sprite, "Hello", 0, 16*0);
  // printEfont(sprite, "こんにちは", 0, 16*1);
}

void ResetCanvas(int dir){
  canvas.clear();
  canvas.setRotation(dir);
  canvas.setCursor(0, 0);
  printEfont(&canvas, "Direction: " + String(dir) + "\n");
}
