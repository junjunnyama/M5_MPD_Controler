#include <M5Unified.h>  // M5Stack ライブラリ

// フォント関連ヘッダ
// 使用する言語データを選択
// #include "efontEnableAll.h"
#include "efontEnableAscii.h"
#include "efontEnableCJK.h"
#include "efontEnableJa.h"
// M5Stack用描画ライブラリ
#include "efontM5Stack.h"

// Wifi
#include <WiFi.h>
// #include <WiFiClient.h>
#include <WiFiMulti.h>

WiFiClient client;
const char ssid[] = "Your SSID";
const char pass[] = "Your PASS";

// // mpd server
// // by IP address
// // const char mpdserver[] = "IP:192.168.xxx.xxx";
// // by server name
// const char mpdserver[] = "moode";
// // char mpdserver[] = "volumio";
// // const char mpdserver[] = "smpd";

// //mpdport
// uint16_t mpdport = 6600;

// // mDNS
// #include <ESPmDNS.h>

// IPAddress mpdaddr;
// const char hostname[] = "m5mpdclint";
WiFiMulti WiFimulti;

// // Grobal valiables
// String artist, partist;
// String title, ptitle;
// String file, pfile;
// String name, pname;

// static volatile uint16_t shiftreset_cnt = 0, mpd_poll_cnt = 0;
// byte shift = 0, pshift = -1;
// boolean randomf,prandomf = false, repeatf,prepeatf = false;
// int16_t volume, pvolume = -2;
// int16_t playlistlength, pplaylistlength = -1,  id, pid = -1;
// String  mpd_stat, pmpd_stat="";

// Mpd icons

void setup() {
  M5.begin();
  Serial.begin(115200);
  M5.Lcd.setRotation(1);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);

  // WiFi connection
  // WiFimulti.addAP(ssid, pass);
  // while (WiFimulti.run() != WL_CONNECTED) {
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    printEfont(".");
  }
  printEfont("wifi connected\n");
  printEfont("IP address: ");
  printEfont(WiFi.localIP().toString());
}

void loop() {
  // printEfont(sprite, "Hello", 0, 16*0);
  // printEfont(sprite, "こんにちは", 0, 16*1);
}
