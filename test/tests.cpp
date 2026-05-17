// Copyright 2021 GHA Test Team
#include "textgen.h"
#include <gtest/gtest.h>
#include <fstream>
#include <vector>
#include <string>

// --- 1. Префикс формируется из NPREF слов
TEST(TextGenTests, PrefixFormation) {
    TextGen gen;
    std::ofstream f("test1.txt");
    f << "hello world";
    f.close();

    gen.build("test1.txt");
    prefix p;
    p.push_back("");
    p.push_back("hello");

    auto &table = gen.getStateTable();
    ASSERT_NE(table.find(p), table.end());
}

// --- 2. Добавление префикс -> суффикс
TEST(TextGenTests, PrefixSuffixPairing) {
    TextGen gen;
    std::ofstream f("test2.txt");
    f << "a b c";
    f.close();

    gen.build("test2.txt");
    prefix p;
    p.push_back("a");
    p.push_back("b");

    auto &table = gen.getStateTable();
    ASSERT_EQ(table.at(p).front(), "c");
}

// --- 3. Единственный суффикс
TEST(TextGenTests, SingleSuffixChoice) {
    TextGen gen;
    std::ofstream f("test3.txt");
    f << "x y z";
    f.close();

    gen.build("test3.txt");
    prefix p;
    p.push_back("x");
    p.push_back("y");

    auto &table = gen.getStateTable();
    ASSERT_EQ(table.at(p).size(), 1);
}

// --- 4. Случайный выбор суффикса
TEST(TextGenTests, RandomSuffixChoice) {
    TextGen gen;
    std::ofstream f("test4.txt");
    f << "a b c a b d";
    f.close();

    gen.build("test4.txt");
    prefix p;
    p.push_back("a");
    p.push_back("b");

    auto &table = gen.getStateTable();
    ASSERT_GT(table.at(p).size(), 1);
}

// --- 5. Генерация текста заданной длины
TEST(TextGenTests, GenerateTextLength) {
    TextGen gen;
    std::ofstream f("test5.txt");
    f << "the quick brown fox jumps over the lazy dog";
    f.close();

    gen.build("test5.txt");
    std::vector<std::string> out;
    gen.generate(out, 20);

    ASSERT_EQ(out.size(), 20);
}

// --- 6. Пустой файл
TEST(TextGenTests, EmptyFile) {
    TextGen gen;
    std::ofstream f("test6.txt"); // пустой файл
    f.close();

    gen.build("test6.txt");
    std::vector<std::string> out;
    gen.generate(out, 10);

    ASSERT_TRUE(out.empty());
}

// --- 7. Короткий текст меньше NPREF
TEST(TextGenTests, ShortText) {
    TextGen gen;
    std::ofstream f("test7.txt");
    f << "only";
    f.close();

    gen.build("test7.txt");
    std::vector<std::string> out;
    gen.generate(out, 5);

    ASSERT_TRUE(out.empty() || out.size() <= 5);
}

// --- 8. Генерация нескольких слов и проверка наличия слов
TEST(TextGenTests, GeneratedWordsPresent) {
    TextGen gen;
    std::ofstream f("test8.txt");
    f << "one two three four";
    f.close();

    gen.build("test8.txt");
    std::vector<std::string> out;
    gen.generate(out, 10);

    for (auto &w : out) {
        ASSERT_TRUE(w == "one" || w == "two" || w == "three" || w == "four");
    }
}

// --- 9. Проверка таблицы после нескольких одинаковых префиксов
TEST(TextGenTests, MultipleSamePrefixes) {
    TextGen gen;
    std::ofstream f("test9.txt");
    f << "a b c a b d a b e";
    f.close();

    gen.build("test9.txt");
    prefix p;
    p.push_back("a");
    p.push_back("b");

    auto &table = gen.getStateTable();
    ASSERT_EQ(table.at(p).size(), 3); // c, d, e
}

// --- 10. Проверка генерации текста из таблицы с циклом
TEST(TextGenTests, CyclicGeneration) {
    TextGen gen;
    std::ofstream f("test10.txt");
    f << "hello world hello world hello world";
    f.close();

    gen.build("test10.txt");
    std::vector<std::string> out;
    gen.generate(out, 10);

    ASSERT_EQ(out.size(), 10);
}

// --- 11. Проверка префикса с пустой строкой на конце
TEST(TextGenTests, PrefixWithEmptySuffix) {
    TextGen gen;
    std::ofstream f("test11.txt");
    f << "a b";
    f.close();

    gen.build("test11.txt");
    prefix p;
    p.push_back("b");
    p.push_back(""); // последний пустой
    auto &table = gen.getStateTable();
    ASSERT_TRUE(table.find(p) != table.end());
}

// --- 12. Проверка генерации текста с точным количеством слов
TEST(TextGenTests, ExactWordCountGeneration) {
    TextGen gen;
    std::ofstream f("test12.txt");
    f << "alpha beta gamma delta epsilon zeta eta theta";
    f.close();

    gen.build("test12.txt");
    std::vector<std::string> out;
    gen.generate(out, 15);

    ASSERT_EQ(out.size(), 15);
}
