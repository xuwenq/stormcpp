// Author:zhouyoudao@gmail.com

#include "storm.h"
#include <utility>

using std::deque;
using storm::Tuple;
using storm::ModeEnum;
using Json::Value;

namespace storm {

void Spout::Run() {
  mode = SPOUT;
  std::pair<Json::Value, Json::Value> confContext = InitComponent();
  Initialize(confContext.first, confContext.second);

  Json::Value msg;
  std::string command;
  while (true) {
    msg = ReadCommand();
    command = msg[kCommand].asString();
    if (command == kCommandNext) {
      NextTuple();
    } else if (command == kCommandAck) {
      this->Ack(msg);
    } else if (command == kCommandFail) {
      this->Fail(msg);
    }
    Sync();
  }  // while

  Close();
}

void Bolt::Run() {
  mode = BOLT;
  std::pair<Json::Value, Json::Value> confContext = InitComponent();
  Initialize(confContext.first, confContext.second);
  while (true) {
    Tuple tuple = ReadTuple();
    Process(tuple);
  }
}

void BasicBolt::Run() {
  mode = BOLT;
  std::pair<Json::Value, Json::Value> confContext = InitComponent();
  Initialize(confContext.first, confContext.second);

  while (true) {
    Tuple tuple = ReadTuple();
    anchor_tuple = &tuple;

    Process(tuple);
    storm::Ack(tuple.Id());
  }
}
}
/* namespace storm */
