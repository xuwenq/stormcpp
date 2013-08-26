// Author: zhouyoudao@gmail.com
#include "base/flags.h"
#include "split_sentences.h"

using storm::SplitSentences;

int main(int argc, char *argv[]) {
  base::ParseCommandLineFlags(&argc, &argv, true);
  SplitSentences ss;
  ss.Run();

  return 0;
}
