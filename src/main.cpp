#include "textgen.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    TextGen tg;
    tg.build("input.txt");

    vector<string> result;
    tg.generate(result, TextGen::MAXGEN);

    ofstream out("result/gen.txt");
    for (auto &w : result) {
        out << w << " ";
    }
    out.close();

    cout << "Generated text saved to result/gen.txt\n";
    return 0;
}
