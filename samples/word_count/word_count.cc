// Author: zhouyoudao@gmail.com

#include "word_count.h"

#include <string>
#include <vector>
#include "base/string_util.h"

using std::string;
using std::vector;
using storm::Tuple;
using Json::Value;

namespace storm {

WordCount::WordCount() {
}

WordCount::~WordCount() {
}

void WordCount::Initialize(const Value& conf,
                          const Value& context) {}
void WordCount::Process(const Tuple& tuple) {
  string word = tuple.Values()[0].asString();
  if (counts.find(word) == counts.end()) {
    counts[word] = 1;
  } else {
    counts[word] += 1;
  }
  Value j_word;
  j_word.append(word);
  j_word.append(StringPrintf("%d", counts[word]));
  Tuple t(j_word);
  Emit(t);
}

} /* namespace storm */
