// Author: zhouyoudao@gmail.com

#ifndef STORM_CPP_SAMPLES_WORD_COUNT_SENTENCE_CREATER_H_
#define STORM_CPP_SAMPLES_WORD_COUNT_SENTENCE_CREATER_H_

#include "storm.h"

namespace storm {

class SentenceCreater: public storm::Spout {
 public:
  SentenceCreater();
  virtual ~SentenceCreater();
  virtual void Initialize(const Json::Value& conf, const Json::Value& context);
  virtual void NextTuple();
};

} /* namespace storm */
#endif  // STORM_CPP_SAMPLES_WORD_COUNT_SENTENCE_CREATER_H_
