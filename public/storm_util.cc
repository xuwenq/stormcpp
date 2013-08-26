// Author: zhouyoudao@gmail.com

#include "storm_util.h"
#include <deque>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>

using std::deque;

namespace storm {
deque<Json::Value> pending_taskids;
deque<Json::Value> pending_commands;

ModeEnum mode;
Tuple* anchor_tuple = NULL;

// Functions
Json::Value ReadMsg() {
  std::string msg;
  std::string line;
  bool read_line = false;
  while (true) {
    read_line = getline(std::cin, line).good();
    if (line == kEnd) {
      break;
    } else if (read_line) {
      msg += (line + "\n");
    }
  }
  Json::Value root;
  Json::Reader reader;
  bool parsing = reader.parse(msg, root);
  if (!parsing) {
    Log("Failed to parse JSON" + msg);
  }
  return root;
}

void SendMsgToParent(const Json::Value& v) {
  std::cout << v << std::endl;
  std::cout << kEnd << std::endl;
}

Json::Value ReadTaskIds() {
  if (!pending_taskids.empty()) {
    Json::Value v = pending_taskids.front();
    pending_taskids.pop_front();
    return v;
  } else {
    Json::Value msg = ReadMsg();
    while (!msg.isArray()) {
      pending_commands.push_back(msg);
      msg = ReadMsg();
    }
    return msg;
  }
}

Json::Value ReadCommand() {
  if (!pending_commands.empty()) {
    Json::Value v = pending_commands.front();
    pending_commands.pop_front();
    return v;
  } else {
    Json::Value msg = ReadMsg();
    while (msg.isArray()) {
      pending_taskids.push_back(msg);
      msg = ReadMsg();
    }
    return msg;
  }
}

Tuple ReadTuple() {
  Json::Value msg = ReadCommand();
  return Tuple(msg[kId].asString(), msg[kComponent].asString(),
      msg[kStream].asString(), msg[kTask].asInt(), msg[kTuple]);
}

void Sync() {
  Json::Value v;
  v[kCommand] = kCommandSync;
  SendMsgToParent(v);
}

void Ack(const std::string& id) {
  Json::Value v;
  v[kCommand] = kCommandAck;
  v[kId] = id;
  SendMsgToParent(v);
}

void Fail(const std::string& id) {
  Json::Value v;
  v[kCommand] = kCommandFail;
  v[kId] = id;
  SendMsgToParent(v);
}

void Log(const std::string& msg) {
  Json::Value v;
  v[kCommand] = kCommandLog;
  v[kMsg] = msg;
  SendMsgToParent(v);
}

void SendPid(const std::string& dir) {
  pid_t current_pid = getpid();
  Json::Value v;
  v[kPid] = current_pid;
  SendMsgToParent(v);
  std::stringstream full_name;
  full_name << dir << "/" << current_pid;
  std::ofstream temp(full_name.str().c_str());
  temp.close();
}

void EmitSpout(const Tuple& tuple, const std::string& id,
               const std::string& stream, int directTask) {
  Json::Value v;
  v[kCommand] = kCommandEmit;
  if (!stream.empty()) {
    v[kStream] = stream;
  }
  if (!id.empty()) {
    v[kId] = id;
  }
  if (directTask != -1) {
    v[kTask] = directTask;
  }
  v[kTuple] = tuple.ToJSON();
  SendMsgToParent(v);
}

void EmitBolt(const Tuple& tuple, const std::string& stream, int task,
    const std::vector<Tuple>& anchors) {
  Json::Value v;
  v[kCommand] = kCommandEmit;
  if (!stream.empty()) {
    v[kStream] = stream;
  }
  Json::Value json_anchors;
  if (anchor_tuple != NULL) {
    json_anchors.append((*anchor_tuple).Id());
  } else {
    for (int i = 0; i < anchors.size(); ++i) {
      json_anchors.append(anchors[i].Id());
    }
  }

  v[kAnchors] = json_anchors;
  if (task != -1) {
    v[kTask] = task;
  }

  v[kTuple] = tuple.ToJSON();

  SendMsgToParent(v);
}

void EmitSwitch(const Tuple& tuple,
                const std::string& stream, int task) {
  if (mode == BOLT) {
    std::vector<Tuple> anchors;
    EmitBolt(tuple, stream, task, anchors);
  } else {
    EmitSpout(tuple, "", stream, task);
  }
}

void EmitSwitch(const Tuple& tuple, const std::string& id,
                const std::string& stream, int task) {
  if (mode == SPOUT) {
    EmitSpout(tuple, id, stream, task);
  }
}

void EmitSwitch(const Tuple& tuple, const std::string& stream,
                      int task, const std::vector<Tuple>& anchors) {
  if (mode == BOLT) {
    EmitBolt(tuple, stream, task, anchors);
  }
}

void EmitDirect(int task, const Tuple& tuple,
                       const std::string& stream) {
  EmitSwitch(tuple, stream, task);
}

void EmitDirect(int task, const Tuple& tuple, const std::string& id,
                const std::string& stream) {
  EmitSwitch(tuple, id, stream, task);
}

void EmitDirect(int task, const Tuple& tuple, const std::string& stream,
    std::vector<Tuple> anchors) {
  EmitSwitch(tuple, stream, task, anchors);
}

Json::Value Emit(const Tuple& tuple, const std::string& stream,
                 int task) {
  EmitSwitch(tuple, stream, task);
  return ReadTaskIds();
}

Json::Value EmitWithId(const Tuple& tuple, const std::string& id,
                 const std::string& stream, int task) {
  EmitSwitch(tuple, id, stream, task);
  return ReadTaskIds();
}

Json::Value EmitWithAnchors(const Tuple& tuple,
                 const std::vector<Tuple>& anchors,
                 const std::string& stream, int task) {
  EmitSwitch(tuple, stream, task, anchors);
  return ReadTaskIds();
}

std::pair<Json::Value, Json::Value> InitComponent() {
  Json::Value setupInfo = ReadMsg();
  SendPid(setupInfo[kPidDir].asString());
  std::pair<Json::Value, Json::Value> ret = std::make_pair(setupInfo[kConfig],
      setupInfo[kContext]);
  return ret;
}

} /* namespace storm */
