// Author: zhouyoudao@gmail.com

#include "sentence_creater.h"
#include <stdlib.h>
#include <string>
#include "base/time.h"
#include "base/logging.h"

using std::string;
using Json::Value;

DEFINE_int32(spout_interval, 1000,
     "The inteval of spout sentences, microseconds: 1s = 1000000microseconds");

namespace storm {

SentenceCreater::SentenceCreater() {
}

SentenceCreater::~SentenceCreater() {
}

void SentenceCreater::Initialize(const Json::Value& conf,
                                 const Json::Value& context) {}

void SentenceCreater::NextTuple() {
  if (FLAGS_spout_interval > 0) {
    usleep(FLAGS_spout_interval);
  }
  string sens[] = {
    "this is a joke",
    "lambo use cooker",
    "but no one cares luna",
    "what a stupid shoot"
  };
  unsigned int sd  = static_cast<unsigned int>(base::GetTimeInUsec());
  string one = sens[rand_r(&sd)%4];
  Value j_sens;
  j_sens.append(one);
  Tuple t(j_sens);
  Emit(t);

  // Log messages for debug
  Log("I am a debug message");
}

} /* namespace storm */
