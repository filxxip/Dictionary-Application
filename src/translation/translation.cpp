#include "translation.h"

#include <algorithm>
#include <ctime>
#include <vector>

const std::map<Word::Language, QString> Word::Language_names = {
    {Language::UNDEFINED, "none"},
    {Language::ENGLISH, "english"},
    {Language::POLISH, "polish"},
    {Language::GERMAN, "german"}};

const std::unordered_map<Word::Prioritity, QString> Word::Prioritity_names = {
    {Prioritity::UNDEFINED, "undefined"}, {Prioritity::LOW, "low"},
    {Prioritity::MOST, "most"},           {Prioritity::HIGHER, "higher"},
    {Prioritity::MEDIUM, "medium"},       {Prioritity::VERY_LOW, "very_low"}};

void Word::is_language_valid(Word::Language language) {
  if (static_cast<int>(language) == -1) {
    throw std::invalid_argument("language must be defined");
  }
}

void Word::basic_translation() {
  for (int value = static_cast<int>(Language::ENGLISH);
       value <= static_cast<int>(Language::GERMAN); value++) {
    auto language = static_cast<Language>(value);
    translations_dates.emplace(std::make_pair(language, get_current_date()));
    translations.emplace(std::make_pair(language, ""));
  }
}

Word::Word() : prioritity(Prioritity::UNDEFINED) { basic_translation(); }

Word::Word(Language language, const QString &word_base, Prioritity prioritity_)
    : prioritity(prioritity_) {
  is_language_valid(language);
  basic_translation();
  Date date_now = get_current_date();
  translations.at(language) = word_base;
  translations_dates.at(language) = date_now;
}

Word::Word(const std::map<Language, QString> &translations_,
           Prioritity prioritity_)
    : prioritity(prioritity_) { // wywolac kopiujacy dla mapy
  basic_translation();
  auto date_now = get_current_date();
  for (const auto &[language, translation] : translations_) {
    is_language_valid(language);
    translations.at(language) = translation;
    translations_dates.at(language) = date_now;
  }
}

const QString &Word::get_translation(Language to) const {
  is_language_valid(to);
  return translations.at(to);
}

const Date &Word::get_date(Language to) const {
  is_language_valid(to);
  return translations_dates.at(to);
}

void Word::change_translation(Language language,
                              const QString &new_translation) {
  is_language_valid(language);
  change_translation_date(language, get_current_date());
  translations.at(language) = new_translation;
}

void Word::change_translation_date(Language language,
                                   const Date &date) { // moga byc problemy
  is_language_valid(language);
  translations_dates.at(language) = date;
}

int Word::get_lenght(Language language) const {
  is_language_valid(language);
  return translations.at(language).length();
}

Word &Word::operator=(const Word &word) {
  if (this == &word) {
    return *this;
  }
  translations = word.translations;
  translations_dates = word.translations_dates;
  return *this;
}

bool Word::is_defined(Word::Language language) const {
  is_language_valid(language);
  return !((*translations.find(language)).second.isEmpty());
}

Word::Prioritity Word::get_prioritity() const { return prioritity; }

void Word::set_prioritity(Prioritity prioritity_) { prioritity = prioritity_; }

bool Word::operator==(const Word &word) {
  return translations == word.translations && prioritity == word.prioritity;
}

bool Word::contain(const Word &word) const {
  auto start1 = translations.begin();
  auto start2 = word.translations.begin();
  auto end1 = translations.end();
  auto end2 = word.translations.end();

  while (start1 != end1 || start2 != end2) {
    if (*start1 != *start2 && !start2->second.isEmpty()) {
      return false;
    }
    ++start1;
    ++start2;
  }
  return true;
}

int Word::get_defined_number() const { return get_defined_languages().size(); }
std::vector<Word::Language> Word::get_defined_languages() const {
  std::vector<Word::Language> languages;
  languages.reserve(static_cast<int>(Word::Language::ENGLISH) + 1);
  for (const auto &[language, translation] : translations) {
    if (!translation.isEmpty()) {
      languages.push_back(language);
    }
  }
  return languages;
}

void Word::set_not_defined(Language language) {
  change_translation(language, "");
}
