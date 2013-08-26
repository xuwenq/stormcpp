// Author: zhouyoudao@gmail.com

#ifndef STORM_CPP_PUBLIC_CONSTANTS_H_
#define STORM_CPP_PUBLIC_CONSTANTS_H_

#include <string>

namespace storm {
  static const std::string kEnd = "end";
  static const std::string kId = "id";
  static const std::string kComponent = "comp";
  static const std::string kStream = "stream";
  static const std::string kTask = "task";
  static const std::string kTuple = "tuple";
  static const std::string kPid = "pid";
  static const std::string kPidDir = "pidDir";
  static const std::string kAnchors = "anchors";
  static const std::string kMsg = "msg";
  static const std::string kConfig = "conf";
  static const std::string kContext = "context";
  // command and types
  static const std::string kCommand = "command";
  static const std::string kCommandEmit = "emit";
  static const std::string kCommandSync = "sync";
  static const std::string kCommandAck = "ack";
  static const std::string kCommandFail = "fail";
  static const std::string kCommandLog = "log";
  static const std::string kCommandNext = "next";
}

#endif   // CONSTANTS_H_
