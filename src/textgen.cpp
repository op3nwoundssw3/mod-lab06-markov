#include "textgen.h"
#include <fstream>
#include <sstream>
#include <random>
#include <iterator>
#include <iostream>

using namespace std;

void TextGen::addWord(const prefix &p, const string &s) {
    statetab[p].push_back(s);
}

void TextGen::build(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Cannot open input file\n";
        return;
    }

    prefix p;
    // initialize prefix with NPREF empty strings
    for (int i = 0; i < NPREF; i++)
        p.push_back("");

    string word;
    while (in >> word) {
        addWord(p, word);
        p.pop_front();
        p.push_back(word);
    }
    // add termination
    addWord(p, "");
}

const map<prefix, vector<string>>& TextGen::getStateTable() const {
    return statetab;
}

void TextGen::generate(vector<string> &out, int nwords) {
    out.clear();
    prefix p;
    for (int i = 0; i < NPREF; i++)
        p.push_back("");

    std::mt19937 gen((unsigned)time(nullptr));

    for (int i = 0; i < nwords; i++) {
        auto it = statetab.find(p);
        if (it == statetab.end())
            break;

        const auto &suffices = it->second;
        if (suffices.empty())
            break;

        // choose random suffix
        uniform_int_distribution<> dist(0, suffices.size() - 1);
        const string &next = suffices[dist(gen)];

        if (next.empty())
            break;

        out.push_back(next);

        p.pop_front();
        p.push_back(next);
    }
}
