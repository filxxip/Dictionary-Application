#include "dictionary.h"

#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <regex>

Dictionary::Dictionary(Person *owner_, QString name_)
    : owner(owner_), name(name_) {}

Dictionary::Dictionary(Person *owner_, const std::vector<Word> &wordlist_ptr,
                       QString name_)
    : wordlist(wordlist_ptr), owner(owner_), name(name_) {}

int Dictionary::get_number_of_words() { return wordlist.size(); }

const std::vector<Word> Dictionary::get_words(Word::Language language,
                                              const QString &word) {
  std::vector<Word> results;
  auto func = [&word, language](const auto &value) {
    return value.get_translation(language) == word;
  };
  const auto &words = get_specific_words(language);
  auto point = std::find_if(words.begin(), words.end(), func);
  while (point != words.end()) {
    results.push_back(*point);
    point = std::find_if(point + 1, words.end(), func);
  }
  return results;
}

void Dictionary::add_word(const Word &word) {
  auto searched =
      std::find_if(wordlist.begin(), wordlist.end(),
                   [&word](const auto &value) { return word.contain(value); });
  if (searched != wordlist.end()) {
    if (searched->get_defined_number() < word.get_defined_number()) {
      *searched = word;
    }
  } else {
    wordlist.push_back(word);
  }
}

const std::vector<Word> Dictionary::regex_search(const QString &regex,
                                                 Word::Language language1) {
  QRegularExpression rx(regex + "[a-zA-Z0-9]*");
  auto result = get_specific_words(language1);
  auto new_end = std::remove_if(
      result.begin(), result.end(), [&rx, &language1](const auto &word) {
        auto word_translation = word.get_translation(language1);
        return rx.match(word_translation).hasMatch();
      });
  result.erase(new_end, result.end());
  return result;
}

const std::vector<Word> Dictionary::regex_search(const QString &regex,
                                                 Word::Language language1,
                                                 Word::Language language2) {
  QRegularExpression rx(regex + "[a-zA-Z0-9]*");
  auto result = get_specific_translations(language1, language2);
  auto new_end = std::remove_if(
      result.begin(), result.end(), [&rx, &language1](const auto &word) {
        auto word_translation = word.get_translation(language1);
        return rx.match(word_translation).hasMatch();
      });
  result.erase(new_end, result.end());
  return result;
}

Dictionary::Dictionary(const Dictionary &dictionary)
    : wordlist(dictionary.wordlist), owner(dictionary.owner),
      name(dictionary.name) {}

std::vector<Word> Dictionary::get_specific_words(Word::Language language) {
  std::vector<Word> result;
  for (auto &word : wordlist) {
    if (word.is_defined(language)) {
      result.push_back(word);
    }
  }
  return result;
}

std::vector<Word>
Dictionary::get_specific_translations(Word::Language language1,
                                      Word::Language language2) {
  std::vector<Word> result;
  for (auto &word : wordlist) {
    if (word.is_defined(language1) and word.is_defined(language2)) {
      result.push_back(word);
    }
  }
  return result;
}

void Dictionary::change_memory(int value) { wordlist.reserve(value); }

Word &Dictionary::get_word(const Word &word) {
  auto result = std::find(wordlist.begin(), wordlist.end(), word);
  return *result;
}

const Person *Dictionary::get_person() const { return owner; }

const std::vector<Word> &Dictionary::get_full_wordlist() const {
  return wordlist;
}

int Dictionary::get_number_of_words(Word::Language language) {
  int number = 0;
  for (auto &word : wordlist) {
    if (word.is_defined(language)) {
      number++;
    }
  }
  return number;
}

void Dictionary::set_name(const QString &name_) { name = name_; }
