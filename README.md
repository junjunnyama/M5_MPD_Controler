# M5_MPD_Controler

# 開発メモ
* M5GFX.hに登録されているカラーコードは16bit(RGB:5,6,5bitずつ)で割り振られている
  * efontでは32bitで色を管理しているため意図しない色に変化する
  * 16bit管理に変更済み

* TFTからM5GFXに移行
  * ライブラリ書き換え
  * 文字色，背景色の任意変更が未実装

* WiFiの設定について
  * ルーターが2.4GHz帯で動作していることを確認  
  ESP32は5GHz帯非対応

# 参考文献
## 日本語表示
<https://karakuri-musha.com/inside-technology/arduino-m5stack-efont_timer01/>
<https://github.com/tanakamasayuki/efont/tree/master>

## MPD client
<https://qiita.com/tt-yawata/items/ce34580dd97ede449d9f>
