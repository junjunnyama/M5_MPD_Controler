#ifndef _MPD_H_
#define _MPD_H_

// Wifi 関連ライブラリ
#include <WiFi.h>
#include <WiFiClient.h>

// 曲の再生状態
typedef enum {
  Play,
  Pause,
  Stop
} PlayState;

// MPD ステータス構造体
typedef struct {
  // State           :  曲の状態(play, pause, stop)
  // Volume          :  音量
  // Repeat          :  リピート再生
  // Random          :  ランダム再生
  // Single          :  シングル再生
  // Playlistlength  :  プレイリストの曲数
  // Song            :  プレイリスト内の曲番号(0始まり)
  // Time            :  再生時間
  // TotalTime       :  曲の総時間
  PlayState State;
  int Volume;
  bool Repeat;
  bool Random;
  bool Single;
  int PlaylistLen;
  int PlayNum;
  int Time;
  int TotalTime;
} MPDStatus;

// MPD 楽曲情報構造体
typedef struct {
  // Title            : タイトル
  // Artist           : アーティスト
  // Album            : アルバム名
  // Time             : 曲の総時間(秒)
  String Title;
  String Artist;
  String Album;
  String Time;
} CurrentSongStatus;

class MPD : public WiFiClient {
  private:
    IPAddress MpdIPAddress;
    uint16_t MpdPort;
    
    MPDStatus MpdStatus;
    CurrentSongStatus SongStatus;

  public:
    bool connectMpd();
    bool connectMpd(IPAddress ip, uint16_t port);
    CurrentSongStatus getCurrentSong();
    String getResponse();
    MPDStatus getStatus();
    void sendCommand(String cmd);
    void setMpdServer(IPAddress ip, uint16_t port);
    PlayState toPlayState(String stateStr);
};

#endif /* _MPD_H_ */