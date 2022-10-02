#pragma once

#include "../person/person.h"
#include "../translation/translation.h"

#include <memory>
#include <vector>

/** The Dictionary class which contains full list of words*/
class Dictionary {
private:
  std::vector<Word> wordlist; ///< vector with Word class instances
  Person *owner;              ///< pointer to owner of this dictionary
  QString name;               ///< unique name of dictionary
public:
  /**
   * @brief Dictionary copy constructor
   * @param dictionary instance of dictionary class from which data will be
   * copied
   */
  Dictionary(const Dictionary &dictionary);

  /**
   * @brief Dictionary constructor
   * @param owner_ instance of Person class
   */
  Dictionary(Person *owner_, QString name_ = "");

  /**
   * @brief Dictionary constructor
   * @param owner_ instance of Person class
   * @param wordlist_ptr vector with unique pointers to instance of Word class
   */
  Dictionary(Person *owner_, const std::vector<Word> &wordlist_ptr,
             QString name_ = "");

  /**
   * @brief get_number_of_words method which returns number of words in
   * dictionary
   * @return number of words in dictionary
   */
  int get_number_of_words();

  /**
   * @brief get_number_of_words method which returns number of words in
   * dictionary in given language
   * @param language specific language
   * @return number of words in specific language
   */
  int get_number_of_words(Word::Language language);

  /**
   * @brief get_person method which provides the owner of dictionary
   * @return Person class instance who is owner of dictionary
   */
  const Person *get_person() const;

  /**
   * @brief get_full_wordlist method which return full list of words in
   * ditionary
   * @return reference to std::vector of Words instance
   */
  const std::vector<Word> &get_full_wordlist() const;

  /**
   * @brief get_word method which provide reference of word;
   * @param word word which is searched
   * @return reference to word in wordlist
   */
  Word &get_word(const Word &word);

  /**
   * @brief get_wordsmethod which provide vector of pointers to Word class
   * @param language language in which the translation of word is being passed
   * @param word translation of word in given language
   * @return
   */
  const std::vector<Word> get_words(Word::Language language,
                                    const QString &word);

  /**
   * @brief get_specific_words method which provides all specified
   * words in given laguage
   * @param language1 language in which word is given
   * @return vector with all words which are specified in given laguage
   */
  std::vector<Word> get_specific_words(Word::Language language);

  /**
   * @brief get_specific_translations method which provided all words which have
   * translation for language1 and language2
   * @param language1 first language in which translation is searched
   * @param language2 second language in which translation is searched
   * @return vector with all words which are defined in both languages
   */
  std::vector<Word> get_specific_translations(Word::Language language1,
                                              Word::Language language2);

  /**
   * @brief add_word method which add new word to vector
   * @param word word preperaed to add
   */
  void add_word(Word &word);

  /**
   * @brief change_memory method which change capacity of vector
   * @param value new capacity of vector
   */
  void change_memory(int value);

  /**
   * @brief regex_search method which provides all of the words from dictionary
   * for which possible is conversion from language1 parameter to language2
   * parameter and also its type in languge1 fits to regex string
   * @param regex regex string used for searching words
   * @param language1 language in which word is defined, also used for matching
   * to the regex model
   * @param language2 language in which word is defined,
   */
  const std::vector<Word> regex_search(const QString &regex,
                                       Word::Language language1,
                                       Word::Language language2);

  /**
   * @brief regex_search method which provides all of the words from dictionary
   * for which it is known the word in given language, also its type in languge1
   * fits to regex string
   * @param regex regex string used for searching words
   * @param language1 language in which word is defined, also used for matching
   * to the regex model
   */
  const std::vector<Word> regex_search(const QString &regex,
                                       Word::Language language1);
  /**
   * @brief get_name method which provides name of dictionary
   * @return qstring instance with name of dictionary
   */
  QString get_name() const { return name; }

  /**
   * @brief set_name method which sets new name of dictionary
   * @param name_ new name of dictionary
   */
  void set_name(const QString &name_);
};
