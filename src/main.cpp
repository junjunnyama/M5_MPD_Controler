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
}

void loop() {
  M5.update();

  if (M5.BtnB.wasPressed()){
    switch (mpdStatus.State){
      case Play:
        client.pouse();
        break;
      case Pause || Stop:
        client.play();
        break;
    }
  }
}

void ResetCanvas(int dir){
  canvas.clear();
  canvas.setRotation(dir);
  canvas.setCursor(0, 0);
  printEfont(&canvas, "Direction: " + String(dir) + "\n");
}
