#ifndef __EFONT_M5STACK_H__
#define __EFONT_M5STACK_H__
#include <M5Unified.h>
#include "efont.h"
// #include <TFT_eSPI.h>   // 描画用 ライブラリ
// 文字カラー定義ヘッダ
// #include "efontColors.h"

//#define EFONT_DEBUG

void printEfont(char *str) {
  int posX = M5.Lcd.getCursorX();
  int posY = M5.Lcd.getCursorY();
  uint8_t textsizeX = M5.Lcd.getTextSizeX();
  uint8_t textsizeY = M5.Lcd.getTextSizeY();
  uint16_t textcolor = WHITE;
  uint16_t textbgcolor = BLACK;
  
  byte font[32];
  
  while( *str != 0x00 ){
    // 改行処理
    if( *str == '\n' ){
      // 改行
      posY += 16 * textsizeY;
      posX = M5.Lcd.getCursorX();
      str++;
      continue;
    }

    // フォント取得
    uint16_t strUTF16;
    str = efontUFT8toUTF16( &strUTF16, str );
    getefontData( font, strUTF16 );

    // 文字横幅
    int width = 16 * textsizeX;
    if( strUTF16 < 0x0100 ){
      // 半角
      width = 8 * textsizeX;
    }


#ifdef EFONT_DEBUG
    Serial.printf( "str : U+%04X\n", strUTF16 );
#endif


    // 背景塗りつぶし
    M5.Lcd.fillRect(posX, posY, width, 16 * textsizeY, textbgcolor);

    // 取得フォントの確認
    for (uint8_t row = 0; row < 16; row++) {
      word fontdata = font[row*2] * 256 + font[row*2+1];
      for (uint8_t col = 0; col < 16; col++) {
#ifdef EFONT_DEBUG
        Serial.write( ( (0x8000 >> col) & fontdata ) ? "#" : " " );
#endif
        if( (0x8000 >> col) & fontdata ){
          int drawX = posX + col * textsizeX;
          int drawY = posY + row * textsizeY;
          if( textsizeX == 1 && textsizeY == 1 ){
            M5.Lcd.drawPixel(drawX, drawY, textcolor);
          } else {
            M5.Lcd.fillRect(drawX, drawY, textsizeX, textsizeY, textcolor);
          }
        }
      }
#ifdef EFONT_DEBUG
        Serial.write( "\n" );
#endif
    }

    // 描画カーソルを進める
    posX += width;

    // 折返し処理
    if( M5.Lcd.width() <= posX ){
      posX = 0;
      posY += 16 * textsizeY;
    }
  }

  // カーソルを更新
  M5.Lcd.setCursor(posX, posY);
}

void printEfont(char *str, int x, int y) {
  M5.Lcd.setCursor(x, y);
  printEfont(str);
}

void printEfont(char *str, int x, int y, int textsize) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsize);
  printEfont(str);
}

void printEfont(char *str, int x, int y, int textsizeX, int textsizeY) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsizeX, textsizeY);
  printEfont(str);
}


#endif //__EFONT_M5STACK_H__
