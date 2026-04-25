#include "MPD.h"

// M5Stack ライブラリ
#include <M5Unified.h>

// Wifi 関連ライブラリ
#include <WiFi.h>
#include <WiFiClient.h>

void MPD::sendCommand(String cmd){
  this->println(cmd);
}

bool MPD::connectMpd(){
  if (this->connect(MpdIPAddress, MpdPort)) {
    return getAck();
  }else{
    return false;
  }
}

bool MPD::connectMpd(IPAddress ip, uint16_t port){
  setMpdServer(ip, port);
  return connectMpd();
}

bool MPD::getAck(){
  String resp;

  resp = getResponse();
  if (resp.startsWith("TOUT")) {
    return false;
  } else {
    return true;
  }
}

// CurrentSong 楽曲情報取得
CurrentSongStatus MPD::getCurrentSong(){
  // Title            : タイトル
  // Artist           : アーティスト
  // Album            : アルバム名
  // Time             : 曲の総時間(秒)

  String resp = "";
  String val = "";
  const char command[] = "currentsong";

  sendCommand(command);
  while (!resp.startsWith("OK")) {
    resp = getResponse();
    val = resp.substring(resp.indexOf(' ')+1);

    if (resp.startsWith("Title:")) {
      SongStatus.Title = val;
    } else if (resp.startsWith("Artist:")) {
      SongStatus.Artist = val;
    } else if (resp.startsWith("Album:")) {
      SongStatus.Album = val;
    } else if (resp.startsWith("Time:")) {
      SongStatus.Time = val;
    } else if (resp.startsWith("TOUT")) {
      sendCommand(command);
    }
  }

  return SongStatus;
}

String MPD::getResponse(){
  String response;
  int16_t timeout;

  timeout = 2000;
  unsigned long start = millis();

  while(millis() - start < timeout) {
    if(! this->available()) {
      delay(10);
    }else{
      response = this->readStringUntil('\n');
      return response;
    }
  }
  return "TOUT";
};

// MPD ステータス情報取得
MPDStatus MPD::getStatus(){
  // state           :  曲の状態(play, pause, stop)
  // volume          :  音量
  // repeat          :  リピート再生
  // random          :  ランダム再生
  // single          :  シングル再生
  // playlistlength  :  プレイリストの曲数
  // song            :  プレイリスト内の曲番号(0始まり)
  // time            :  再生時間:曲の総時間

  String resp = "";
  String val = "";
  const char command[] = "status";

  sendCommand(command);  
  while (!resp.startsWith("OK")) {
    resp = getResponse();
    val = resp.substring(resp.indexOf(' ')+1);

    if (resp.startsWith("state:")) {
      MpdStatus.State = toPlayState(val);
    } else if (resp.startsWith("volume:")) {
      MpdStatus.Volume = val.toInt();
    } else if (resp.startsWith("repeat:")) {
      MpdStatus.Repeat = val.toInt();
    } else if (resp.startsWith("random:")) {
      MpdStatus.Random = val.toInt();
    } else if (resp.startsWith("single:")) {
      MpdStatus.Single = val.toInt();
    } else if (resp.startsWith("playlistlength:")) {
      MpdStatus.PlaylistLen = val.toInt();
    } else if (resp.startsWith("song:")) {
      MpdStatus.PlayNum = val.toInt();
    } else if (resp.startsWith("time:")) {
      MpdStatus.Time = val.substring(0, val.lastIndexOf(':')).toInt();
      MpdStatus.TotalTime = val.substring(val.lastIndexOf(':') + 1).toInt();
    } else if (resp.startsWith("TOUT")) {
      sendCommand(command);
    }
  }

  return MpdStatus;
}

void MPD::play(){
  sendCommand("play");
}

void MPD::pouse(){
  sendCommand("pause");
}

void MPD::stop(){
  sendCommand("stop");
}

void MPD::setMpdServer(IPAddress ip, uint16_t port){
  MpdIPAddress = ip;
  MpdPort = port;
}

PlayState MPD::toPlayState(String stateStr){
  if(stateStr.equals("play")){
    return Play;
  }else if(stateStr.equals("pause")){
    return Pause;
  }else if(stateStr.equals("stop")){
    return Stop;
  }
}