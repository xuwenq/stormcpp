// Author: zhouyoudao@gmail.com

#ifndef STORM_CPP_SAMPLES_WORD_COUNT_SPLIT_SENTENCES_H_
#define STORM_CPP_SAMPLES_WORD_COUNT_SPLIT_SENTENCES_H_

#include "storm.h"

namespace storm {

class SplitSentences: public storm::BasicBolt {
 public:
  SplitSentences();
  virtual ~SplitSentences();
  virtual void Initialize(const Json::Value& conf,
                          const Json::Value& context);
  virtual void Process(const Tuple& tuple);
};

} /* namespace storm */
#endif  // STORM_CPP_SAMPLES_WORD_COUNT_SPLIT_SENTENCES_H_
