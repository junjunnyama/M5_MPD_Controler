#include "efontM5Stack.h"

#include <M5Unified.h>
#include "efont.h"

void printEfont(char *str) {
  int posX = M5.Lcd.getCursorX();
  int posY = M5.Lcd.getCursorY();
  uint8_t textsizeX = M5.Lcd.getTextSizeX();
  uint8_t textsizeY = M5.Lcd.getTextSizeY();
  uint16_t textcolor = M5.Lcd.getTextStyle().fore_rgb888;
  uint16_t textbgcolor = M5.Lcd.getTextStyle().back_rgb888;
  
  byte font[32];
  
  while( *str != 0x00 ){
    // 改行処理
    if( *str == '\n' ){
      // 改行
      // posX = M5.Lcd.getCursorX();
      posX = 0;
      posY += 16 * textsizeY;
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

void printEfont(const String &str){
  int len = str.length();
  char buf[len + 1];
  str.toCharArray(buf, len + 1);
  printEfont(buf);
}

void printEfont(char *str, int x, int y) {
  M5.Lcd.setCursor(x, y);
  printEfont(str);
}

void printEfont(const String &str, int x, int y) {
  M5.Lcd.setCursor(x, y);
  printEfont(str);
}

void printEfont(char *str, int x, int y, int textsize) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsize);
  printEfont(str);
}

void printEfont(const String &str, int x, int y, int textsize) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsize);
  printEfont(str);
}

void printEfont(char *str, int x, int y, int textsizeX, int textsizeY) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsizeX, textsizeY);
  printEfont(str);
}

void printEfont(const String &str, int x, int y, int textsizeX, int textsizeY) {
  M5.Lcd.setCursor(x, y);
  M5.Lcd.setTextSize(textsizeX, textsizeY);
  printEfont(str);
}

void printEfont(M5Canvas *canvas, char *str) {
  int posX = canvas->getCursorX();
  int posY = canvas->getCursorY();
  uint8_t textsizeX = canvas->getTextSizeX();
  uint8_t textsizeY = canvas->getTextSizeY();
  uint16_t textcolor = canvas->getTextStyle().fore_rgb888;
  uint16_t textbgcolor = canvas->getTextStyle().back_rgb888;
  
  byte font[32];
  
  while( *str != 0x00 ){
    // 改行処理
    if( *str == '\n' ){
      // 改行
      posX = 0;
      posY += 16 * textsizeY;
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
    canvas->fillRect(posX, posY, width, 16 * textsizeY, textbgcolor);

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
            canvas->drawPixel(drawX, drawY, textcolor);
          } else {
            canvas->fillRect(drawX, drawY, textsizeX, textsizeY, textcolor);
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
    if( canvas->width() <= posX ){
      posX = 0;
      posY += 16 * textsizeY;
    }
  }

  // カーソルを更新
  canvas->setCursor(posX, posY);

  // 画面更新
  canvas->pushSprite(0, 0);
}

void printEfont(M5Canvas *canvas, const char *str) {
  printEfont(canvas, const_cast<char*>(str));
}

void printEfont(M5Canvas *canvas, const String &str){
  int len = str.length();
  char buf[len + 1];
  str.toCharArray(buf, len + 1);
  printEfont(canvas, buf);
}

void printEfont(M5Canvas *canvas, char *str, int x, int y) {
  canvas->setCursor(x, y);
  printEfont(canvas, str);
}

void printEfont(M5Canvas *canvas, const String &str, int x, int y) {
  canvas->setCursor(x, y);
  printEfont(canvas, str);
}

void printEfont(M5Canvas *canvas, char *str, int x, int y, int textsize) {
  canvas->setCursor(x, y);
  canvas->setTextSize(textsize);
  printEfont(canvas, str);
}

void printEfont(M5Canvas *canvas, const String &str, int x, int y, int textsize) {
  canvas->setCursor(x, y);
  canvas->setTextSize(textsize);
  printEfont(canvas, str);
}

void printEfont(M5Canvas *canvas, char *str, int x, int y, int textsizeX, int textsizeY) {
  canvas->setCursor(x, y);
  canvas->setTextSize(textsizeX, textsizeY);
  printEfont(canvas, str);
}

void printEfont(M5Canvas *canvas, const String &str, int x, int y, int textsizeX, int textsizeY) {
  canvas->setCursor(x, y);
  canvas->setTextSize(textsizeX, textsizeY);
  printEfont(canvas, str);
}
