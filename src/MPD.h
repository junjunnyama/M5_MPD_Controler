#ifndef _MPD_H_
#define _MPD_H_

// Wifi 関連ライブラリ
#include <WiFi.h>
#include <WiFiClient.h>

// MPD ステータス構造体
typedef struct {
  String State;
  int Volume;
  int PlaylistLen;
  bool Randomf;
  bool Repeatf;
} MPDStatus;

// MPD 楽曲情報構造体
typedef struct {
  int Id;
  String Artist;
  String Title;
  String Name;
  String File;
} CurrentSongStatus;

class MPD : public WiFiClient {
  private:
    IPAddress MpdIPAddress;
    uint16_t MpdPort;
    
    MPDStatus MpdStatus;
    CurrentSongStatus SongStatus;

  public:
    bool connectMpd();
    CurrentSongStatus getCurrentSong();
    String getResponse();
    MPDStatus getStatus();
    void sendCommand(String cmd);
    void setCurrentSong(CurrentSongStatus status);
    void setMpdServer(IPAddress ip, uint16_t port);
    void setMpdStatus(MPDStatus status);
    // getCurrentSong();
};

#endif /* _MPD_H_ */