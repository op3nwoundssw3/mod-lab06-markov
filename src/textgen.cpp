// Copyright 2021 GHA Test Team

#include "textgen.h"

#include <ctime>

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>

void TextGen::addWord(const prefix& p, const std::string& s) {
  statetab[p].push_back(s);
}

void TextGen::build(const std::string& filename) {
  std::ifstream in(filename);
  if (!in) {
    std::cerr << "Cannot open input file\n";
    return;
  }

  prefix p;
  for (int i = 0; i < NPREF; i++) {
    p.push_back("");
  }

  std::string word;
  while (in >> word) {
    addWord(p, word);
    p.pop_front();
    p.push_back(word);
  }

  addWord(p, "");
}

const std::map<prefix, std::vector<std::string>>& TextGen::getStateTable()
    const {
  return statetab;
}

void TextGen::generate(std::vector<std::string>& out, int nwords) {
  out.clear();

  prefix p;
  for (int i = 0; i < NPREF; i++) {
    p.push_back("");
  }

  std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

  for (int i = 0; i < nwords; i++) {
    auto it = statetab.find(p);
    if (it == statetab.end()) {
      break;
    }

    const auto& suffices = it->second;
    if (suffices.empty()) {
      break;
    }

    std::uniform_int_distribution<> dist(0, suffices.size() - 1);
    const std::string& next = suffices[dist(gen)];

    if (next.empty()) {
      break;
    }

    out.push_back(next);

    p.pop_front();
    p.push_back(next);
  }
}
