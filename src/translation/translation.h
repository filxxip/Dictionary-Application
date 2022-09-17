#pragma once

#include "../date/current_date.h"
#include "../date/date.h"

#include <QDebug>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

/** The Word class which represents word contained in dictionary*/
class Word {
public:
  /**
   * @brief The Language enum which determines possible translations of word
   */
  enum class Language { ENGLISH, POLISH, GERMAN };

  const static std::unordered_map<Language, QString>
      Language_names; ///< map used when user want to get string version of
                      ///< language name

  /**
   * @brief The Prioritity enum which determines possible prioritities of word
   */
  enum class Prioritity { UNDEFINED = -1, VERY_LOW, LOW, MEDIUM, HIGHER, MOST };

  const static std::unordered_map<Prioritity, QString>
      Prioritity_names; ///< nao used when user want to get string version of
                        ///< prioritity

private:
  Prioritity prioritity; ///< enum prioritity value used to sorting data
  std::map<Language, QString>
      translations; ///< map with all translations of word
  std::map<Language, Date>
      translations_dates; ///< map with dates when specified translations were
                          ///< added
public:
  /**
   * @brief change_translation_date private method which changes translation of
   * word in map
   * @param language specified language which date of translation user would
   * like to change
   * @param date specified Date class object when changes were added, defaulty
   * current date
   */
  void change_translation_date(Language language,
                               const Date &date = get_current_date());

private:
  /**
   * @brief basic_translation private method which sets all language translation
   * to defaulty sign '-'
   */

  void basic_translation();

public:
  /**
   * @brief Word default constructor
   */
  Word();
  Word(const Word &word) {
    //    qDebug() << "copy operator"; // cel edukacyjny
    prioritity = word.prioritity;
    translations = word.translations;
    translations_dates = word.translations_dates;
  }
  ~Word() {
    //      qDebug() << "destructor";
  } // cel edukacyjny
  /**
   * @brief Word contructor
   * @param language language in which word_base is given
   * @param word_base translation of word in given language
   * @param prioritity_ prioritity of this word, defaulty undefined
   */
  Word(Language language, const QString &word_base,
       Prioritity prioritity_ = Prioritity::UNDEFINED);

  /**
   * @brief Word contructor
   * @param translations_ map with language as key, translation of word in this
   * language as value
   * @param prioritity_ prioritity of this word, defaulty undefined
   */
  Word(const std::map<Language, QString> &translations_,
       Prioritity prioritity_ = Prioritity::UNDEFINED);

  /**
   * @brief get_translation method which returns translation of word in given
   * language
   * @param language specified languge which we want to get word to
   * @return QString object which contains translation of word in this given
   * language
   */
  const QString &get_translation(Language language) const;

  /**
   * @brief get_date method which returns date of translation of word in given
   * language
   * @param language specified languge which we want to get date of translation
   * to
   * @return Date class object which represents translation date of this word
   */
  const Date &get_date(Language language) const;

  /**
   * @brief change_translation method which changes specified translation of
   * word in given language
   * @param language specified languge which translation user want to change
   * @param new_translation new translation of word
   */
  void change_translation(Language language, const QString &new_translation);

  /**
   * @brief get_lenght method which provide lenght of word
   * @param language specified language of this word
   * @return number of letters in translation
   */
  int get_lenght(Language language) const;

  /**
   * @brief operator = overloading operator method which copy data from one
   * class instanc to another one
   * @param word constant reference to Word class instance
   * @return reference to Word class instance
   */
  Word &operator=(const Word &word);

  /**
   * @brief is_defined method determines if the translation is defined
   * @param language language in which the word is searched for
   * @return true if word translation is define, otherwise false
   */
  bool is_defined(Word::Language language) const;

  /**
   * @brief get_prioritity method which provides prioritity of word
   * @return prioritity enum class which defines prioririry of word
   */
  Prioritity get_prioritity() const;

  /**
   * @brief set_prioritity method which sets prioritity
   * @param prioritity_ new prioritity of word
   */
  void set_prioritity(Prioritity prioritity_);

  /**
   * @brief operator == used top compare two words
   * @param word word used to compare
   * @return true if two words are equal otherwise false
   */
  bool operator==(const Word &word);

  /**
   * @brief contain check if word is part of other word
   * @param word word which is used for checking
   * @return true if one word contains other, otherwise false
   */
  bool contain(const Word &word) const;

  /**
   * @brief get_defined_number method which provided number of defined languages
   * @return number of defined language
   */
  int get_defined_number() const;

  /**
   * @brief get_defined_languages method which provide all defined languages
   * @return vector with all defined languages.
   */
  std::vector<Word::Language> get_defined_languages() const;
};
