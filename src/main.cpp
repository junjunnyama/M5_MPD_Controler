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

// タイマー用変数
unsigned long times = 0;
unsigned long prevtime = 0;

// 画面の向き(0: X=-1G, 1: X=1G, 2: Y=-1G, 3: Y=1G, -1: Error)
int dir = 0;

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
int DisplayDirection();

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
  times = millis() - prevtime;

  // 画面の向きを取得
  if (times > 500) {
    prevtime = millis();
    dir = DisplayDirection();
    ResetCanvas(dir);
  }

  // 画面の向きに合わせモード変更
  switch (dir){
    case 0:
      // 楽曲情報表示モード
      
      // 再生・停止切り替え
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
      break;
    case 1:
      // 音量調整モード
      
      break;
    case 2:
      break;
    case 3:
      break;
  }
}

void ResetCanvas(int dir){
  canvas.clear();
  canvas.setRotation(dir);
  canvas.setCursor(0, 0);
  printEfont(&canvas, "Direction: " + String(dir) + "\n");
}

int DisplayDirection(){
  // 加速度。センサで取得できる値の単位は[g, gravity]
  float accX, accY, accZ = 0;
  float Xcoord, Ycoord = 0;
  int angle = 0;
  int direction = 0;

  // 加速度取得
  M5.Imu.getAccelData(&accX, &accY, &accZ);
  // printf("AccX: %f, AccY: %f, AccZ: %f\n", accX, accY, accZ);
  Xcoord = constrain(accX, -1.0, 1.0);
  Ycoord = constrain(accY, -1.0, 1.0);

  // 角度計算
  if (Xcoord < Ycoord) {
    // angle = asin(Ycoord) * 180 / M_PI;
    angle = 360 + asin(Xcoord) * 180 / M_PI;
  } else {
    // angle = 180 + acos(Xcoord) * 180 / M_PI;
    angle = acos(Ycoord) * 180 / M_PI;
  }
  // printf("Angle: %d\n", angle);

  // 方向判定
  if (angle < 45 || angle >= 315) {
    direction = 0;  // X=-1G
  } else if (angle < 135) {
    direction = 1;  // X=1G
  } else if (angle < 225) {
    direction = 2;  // Y=-1G
  } else if (angle < 315) {
    direction = 3;  // Y=1G
  } else {
    direction = -1;  // Error
  }
  
  return direction;
}
