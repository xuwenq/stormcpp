// Author: zhouyoudao@gmail.com
#ifndef STORM_CPP_PUBLIC_STORM_H_
#define STORM_CPP_PUBLIC_STORM_H_

#include <string>
#include <deque>
#include "storm_util.h"
#include "jsoncpp-0.6.0/include/json.h"

namespace storm {
extern std::deque<Json::Value> pending_taskids;
extern std::deque<Json::Value> pending_commands;
extern ModeEnum mode;
extern Tuple* anchor_tuple;

class Spout {
 public:
  Spout() {}
  virtual ~Spout() {}
  virtual void Initialize(const Json::Value& conf,
      const Json::Value& context) = 0;
  virtual void NextTuple() = 0;
  virtual void Ack(const Json::Value& msg) {
    storm::Ack(msg[kId].asString());
  }
  virtual void Fail(const Json::Value& msg) {
    storm::Fail(msg[kId].asString());
  }
  virtual void Close() {}
  void Run();
};

class Bolt {
 public:
  Bolt() {}
  virtual ~Bolt() {}
  virtual void Initialize(const Json::Value& conf,
                          const Json::Value& context) = 0;
  virtual void Process(const Tuple& tuple) = 0;
  virtual void Ack(const Tuple& tuple) {
    storm::Ack(tuple.Id());
  }
  virtual void Fail(const Tuple& tuple) {
    storm::Fail(tuple.Id());
  }
  void Run();
};

class BasicBolt {
 public:
  BasicBolt() {}
  virtual ~BasicBolt() {}
  virtual void Initialize(const Json::Value& conf,
                          const Json::Value& context) = 0;
  virtual void Process(const Tuple& tuple) = 0;
  void Run();
};

} /* namespace storm */
#endif  // STORM_CPP_PUBLIC_STORM_H_
