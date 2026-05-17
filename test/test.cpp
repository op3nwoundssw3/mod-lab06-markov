#include "textgen.h"
#include <gtest/gtest.h>
#include <fstream>

// --- 1. Формирование префикса из двух слов
TEST(TextGenTest, PrefixFormation) {
    TextGen t;
    t.build("testdata1.txt");
    auto &tab = t.getStateTable();
    prefix p;
    p.push_back("");
    p.push_back("hello");
    ASSERT_TRUE(tab.find(p) != tab.end());
}

// --- 2. Добавление записи "префикс-суффикс"
TEST(TextGenTest, PrefixSuffixPairing) {
    TextGen t;
    t.build("testdata2.txt");
    auto &tab = t.getStateTable();
    prefix p;
    p.push_back("a");
    p.push_back("b");
    ASSERT_TRUE(tab.find(p) != tab.end());
    ASSERT_EQ(tab.at(p).size(), 1);
}

// --- 3. Единственный суффикс
TEST(TextGenTest, SingleSuffixChoice) {
    TextGen t;
    t.build("testdata3.txt");
    auto &tab = t.getStateTable();
    prefix p;
    p.push_back("");
    p.push_back("x");
    ASSERT_EQ(tab.at(p).front(), "Y");
}

// --- 4. Случайный выбор суффикса
TEST(TextGenTest, RandomSuffixChoice) {
    TextGen t;
    t.build("testdata4.txt");
    auto &tab = t.getStateTable();
    prefix p;
    p.push_back("");
    p.push_back("z");
    ASSERT_GT(tab.at(p).size(), 1);
}

// --- 5. Генерация заданной длины текста
TEST(TextGenTest, GenerateLength) {
    TextGen t;
    t.build("testdata5.txt");
    vector<string> out;
    t.generate(out, 50);
    ASSERT_EQ(out.size(), 50);
}
