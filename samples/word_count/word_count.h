// Author: zhouyoudao@gmail.com

#ifndef STORM_CPP_SAMPLES_WORD_COUNT_WORD_COUNT_H_
#define STORM_CPP_SAMPLES_WORD_COUNT_WORD_COUNT_H_

#include <string>
#include <map>
#include "storm.h"


namespace storm {

class WordCount: public storm::BasicBolt {
 public:
  WordCount();
  virtual ~WordCount();
  virtual void Initialize(const Json::Value& conf,
                            const Json::Value& context);
  virtual void Process(const Tuple& tuple);
 private:
  std::map<std::string, int> counts;
};

} /* namespace storm */
#endif  // STORM_CPP_SAMPLES_WORD_COUNT_WORD_COUNT_H_
