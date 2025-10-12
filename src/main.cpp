#include <M5Unified.h>  // M5Stack ライブラリ

// フォント関連ヘッダ
// 使用する言語データを選択
// #include "efontEnableAll.h"
#include "efontEnableAscii.h"
#include "efontEnableCJK.h"
#include "efontEnableJa.h"
// フォントデータ追加ライブラリ
#include "efont.h"
// M5Stack用描画ライブラリ
#include "efontM5Stack.h"

void setup() {
  M5.begin();
  M5.Lcd.setRotation(0);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(2);

  // M5.Lcd.println(display.getTextSizeX());
  // M5.Lcd.println(display.getTextSizeY());

  printEfont("Hello");
  printEfont("こんにちは");
  char buf1[16];
  sprintf(buf1, "%.2f", M5.Lcd.getTextSizeX());
  printEfont(buf1);
  char buf2[16];
  sprintf(buf2, "%.2f", M5.Lcd.getTextSizeY());
  // printEfont(display, buf2, 0, 16*3);

  // sprite.setColorDepth(16);
  // sprite.setTextSize(1);
  // sprite.createSprite(M5.Lcd.width(), M5.Lcd.height());
}

void loop() {
  // printEfont(sprite, "Hello", 0, 16*0);
  // printEfont(sprite, "こんにちは", 0, 16*1);
}
