// Author: zhouyoudao@gmail.com
#include "base/flags.h"
#include "sentence_creater.h"

using storm::SentenceCreater;

int main(int argc, char *argv[]) {
  base::ParseCommandLineFlags(&argc, &argv, true);
  SentenceCreater sc;
  sc.Run();

  return 0;
}
