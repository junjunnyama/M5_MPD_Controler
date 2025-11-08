#include "mpd.h"

// M5Stack ライブラリ
#include <M5Unified.h>

// Wifi 関連ライブラリ
#include <WiFi.h>
#include <WiFiClient.h>

bool MPD::connectMpd(){
  String resp;

  if (this->connect(MpdIPAddress, MpdPort)) {
    resp = getResponse();
    if (resp.startsWith("TOUT")) {
      return false;
    } else {
      return true;
    }
  }else{
    return false;
  }
}

CurrentSongStatus MPD::getCurrentSong(){
  String resp;
  String val;

  sendCommand("currentsong");
  resp = getResponse();
  val = resp.substring(resp.indexOf(' ')+1);
  
  while (!resp.startsWith("OK")) {
    if (resp.startsWith("Id:")) {
      SongStatus.Id = val.toInt();
    } else if (resp.startsWith("Artist:")) {
      SongStatus.Artist = val;
    } else if (resp.startsWith("Title:")) {
      SongStatus.Title = val;
    } else if (resp.startsWith("Name:")) {
      SongStatus.Name = val;
    } else if (resp.startsWith("file:")) {
      SongStatus.File = val.substring(val.lastIndexOf('/') + 1, val.lastIndexOf('.'));
    } else if (resp.startsWith("TOUT")) {
      sendCommand("currentsong");
    }

    resp = getResponse();
    val = resp.substring(resp.indexOf(' ')+1);
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

MPDStatus MPD::getStatus(){
  String resp;
  String val;

  sendCommand("status");
  resp = getResponse();
  val = resp.substring(resp.indexOf(' ')+1);
  
  while (!resp.startsWith("OK")) {
    Serial.println(resp);
    if (resp.startsWith("state")) {
      MpdStatus.State = val;
    } else if (resp.startsWith("volume:")) {
      MpdStatus.Volume = val.toInt();
    } else if (resp.startsWith("playlistlength:")) {
      MpdStatus.PlaylistLen = val.toInt();
    } else if (resp.startsWith("random:")) {
      MpdStatus.Randomf = val.toInt();
    } else if (resp.startsWith("repeat:")) {
      MpdStatus.Repeatf = val.toInt();
    } else if (resp.startsWith("TOUT")) {
      sendCommand("status");
    }

    resp = getResponse();
    val = resp.substring(resp.indexOf(' ')+1);
  }

  return MpdStatus;
}

void MPD::sendCommand(String cmd){
  this->println(cmd);
}

void MPD::setCurrentSong(CurrentSongStatus status){
  SongStatus = status;
}

void MPD::setMpdServer(IPAddress ip, uint16_t port){
  MpdIPAddress = ip;
  MpdPort = port;
}

void MPD::setMpdStatus(MPDStatus status){
  MpdStatus = status;
}
