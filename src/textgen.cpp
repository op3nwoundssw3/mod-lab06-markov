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
  statetab.clear();

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

  for (int i = 0; i < NPREF; i++) {
    addWord(p, "");
    p.pop_front();
    p.push_back("");
  }
}

const std::map<prefix, std::vector<std::string>>& TextGen::getStateTable()
    const {
  return statetab;
}

void TextGen::generate(std::vector<std::string>& out, int nwords) {
  out.clear();

  prefix start;
  for (int i = 0; i < NPREF; i++) {
    start.push_back("");
  }

  auto start_it = statetab.find(start);
  if (start_it == statetab.end() || start_it->second.empty()) {
    return;
  }

  bool has_word = false;
  for (const auto& word : start_it->second) {
    if (!word.empty()) {
      has_word = true;
      break;
    }
  }

  if (!has_word) {
    return;
  }

  prefix p = start;
  std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));

  while (static_cast<int>(out.size()) < nwords) {
    auto it = statetab.find(p);
    if (it == statetab.end() || it->second.empty()) {
      p = start;
      continue;
    }

    const auto& suffices = it->second;
    std::uniform_int_distribution<> dist(0, suffices.size() - 1);
    const std::string& next = suffices[dist(gen)];

    if (next.empty()) {
      p = start;
      continue;
    }

    out.push_back(next);

    p.pop_front();
    p.push_back(next);
  }
}
