// Author: zhouyoudao@gmail.com
#include "split_sentences.h"
#include <string>
#include <vector>
#include "base/string_util.h"

using std::string;
using std::vector;
using storm::Tuple;
using Json::Value;

namespace storm {

SplitSentences::SplitSentences() {
}

SplitSentences::~SplitSentences() {
}

void SplitSentences::Initialize(const Value& conf, const Value& context) {
}

void SplitSentences::Process(const Tuple& tuple) {
  string s = tuple.Values()[0].asString();
  vector<string> tokens;
  SplitString(s, ' ', &tokens);
  for (int i = 0; i < tokens.size(); ++i) {
    Value j_token;
    // tokens[i]
    j_token.append(tokens[i]);
    Tuple t(j_token);
    Emit(t);
  }
}

} /* namespace storm */
