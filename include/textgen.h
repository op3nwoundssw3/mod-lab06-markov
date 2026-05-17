#ifndef TEXTGEN_H
#define TEXTGEN_H

#include <deque>
#include <map>
#include <string>
#include <vector>

typedef std::deque<std::string> prefix;

class TextGen {
public:
    static const int NPREF = 2;
    static const int MAXGEN = 1200;

    void build(const std::string &filename);
    void generate(std::vector<std::string> &out, int nwords);

    const std::map<prefix, std::vector<std::string>>& getStateTable() const;

private:
    std::map<prefix, std::vector<std::string>> statetab;
    void addWord(const prefix &p, const std::string &s);
};

#endif // TEXTGEN_H
