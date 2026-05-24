// Copyright 2021 GHA Test Team

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "textgen.h"

int main() {
  TextGen tg;
  tg.build("input.txt");

  std::vector<std::string> result;
  tg.generate(result, TextGen::MAXGEN);

  std::ofstream out("result/gen.txt");
  for (const auto& w : result) {
    out << w << " ";
  }
  out.close();

  std::cout << "Generated text saved to result/gen.txt\n";
  return 0;
}
