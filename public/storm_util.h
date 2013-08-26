// Author: zhouyoudao@gmail.com

#ifndef STORM_CPP_PUBLIC_STORM_UTIL_H_
#define STORM_CPP_PUBLIC_STORM_UTIL_H_

#include <string>
#include <vector>
#include <stdexcept>
#include "constants.h"
#include "jsoncpp-0.6.0/include/json.h"

namespace storm {

enum ModeEnum {
  NONE,
  BOLT,
  SPOUT
};

class Tuple {
 public:
  Tuple(const std::string& id, const std::string& component,
        const std::string& stream,
        int task, const Json::Value& values) :
        id_(id), component_(component), stream_(stream),
        task_(task), values_(values) {
    if (!values.isArray()) {
      throw std::runtime_error("Cannot create tuple, values is not an array");
    }
  }

  explicit Tuple(const Json::Value& values) :
        id_(""), component_(""), stream_(""),
        task_(-1), values_(values) { }
  const std::string& Id() const { return id_; }
  const std::string& Component() const { return component_; }
  const std::string& Stream() const { return stream_; }
  int Task() const { return task_; }
  const Json::Value& Values() const { return values_; }
  // Converts Tuple to Json object
  const Json::Value& ToJSON() const { return values_; }
 private:
  std::string id_;
  std::string component_;
  std::string stream_;
  int task_;
  Json::Value values_;
};

void SendMsgToParent(const Json::Value& v);
void SendPid(const std::string& dir);

// read msg from stdin
Json::Value ReadMsg();
Json::Value ReadTaskIds();
Json::Value ReadCommand();
Tuple ReadTuple();

// command type processing
void Sync();
void Ack(const std::string& id);
void Fail(const std::string& id);
void Log(const std::string& msg);

// emit without read taskid, we do not use it in most situation
void EmitDirect(int task, const Tuple& tuple,
                const std::string& stream = "");
void EmitDirect(int task, const Tuple& tuple, const std::string& id,
                const std::string& stream);
void EmitDirect(int task, const Tuple& tuple,
                const std::string& stream,
                const std::vector<Tuple>& anchors);
// Emit a tuple in spout and bolt without message id
Json::Value Emit(const Tuple& tuple,
                 const std::string& stream = "",
                 int task = -1);
// Emit a tuple in spout with a message id in Guaranteeing message processing
Json::Value EmitWithId(const Tuple& tuple, const std::string& id,
                 const std::string& stream = "", int task = -1);
// Emit a tuple in bolt with anchors  in Guaranteeing message processing
Json::Value EmitWithAnchors(const Tuple& tuple,
                 const std::vector<Tuple>& anchors,
                 const std::string& stream = "", int task = -1);
std::pair<Json::Value, Json::Value> InitComponent();
} /* namespace storm */
#endif   // STORM_CPP_PUBLIC_STORM_UTIL_H_
