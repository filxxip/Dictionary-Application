//#include "searched_regex.h"

//#include <QDebug>
//#include <chrono>
//#include <fstream>
//#include <iterator>
//#include <map>
//#include <memory>
//#include <regex>
//#include <vector>

// namespace WordLists {
// std::unordered_map<Word::Language, std::string> LanguageFiles{
//    {Word::Language::POLISH, "/usr/share/dict/polish"},
//    {Word::Language::GERMAN, "/usr/share/dict/ngerman"},
//    {Word::Language::ENGLISH, "/usr/share/dict/british-english"}};

// std::unordered_map<Word::Language, int> LanguageWordNumber{
//    {Word::Language::POLISH, 4150000},
//    {Word::Language::GERMAN, 357000},
//    {Word::Language::ENGLISH, 105000}};
//// std::unordered_map<Word::Language,
/// std::shared_ptr<std::vector<std::string>>> /    LanguageLists{ /
///{Word::Language::POLISH, language_list(Word::Language::POLISH)}, /
///{Word::Language::ENGLISH, language_list(Word::Language::ENGLISH)}, /
///{Word::Language::GERMAN, language_list(Word::Language::GERMAN)}};
//} // namespace WordLists

// std::shared_ptr<std::vector<std::string>>
// searched_regex(std::string pred, Word::Language language) {
//  auto lista = WordLists::LanguageLists.at(language);
//  std::vector<std::string *> results;
//  for (auto &object : *lista) {
//    if (std::regex_match(object, std::regex(pred))) {
//      results.push_back(&object);
//    }
//  }
//  //  std::copy_if(lista->begin(), lista->end(), std::back_inserter(results),
//  //               [&pred](const auto &value) {
//  //                 return (std::regex_match(value, std::regex(pred)));
//  //               });
//  //  auto stream = std::ostream_iterator<std::string>(std::cout, " ");
//  //  for (auto value : results) {
//  //    std::cout << value;
//  //  }
//  std::cout << results.size();
//  //  std::for_each(results.begin(), results.end(), stream);
//}

// std::shared_ptr<std::vector<std::string>>
// language_list(Word::Language language) {
//  int lines_number = WordLists::LanguageWordNumber.at(language);
//  std::ifstream stream(WordLists::LanguageFiles.at(language));
//  auto start = std::chrono::system_clock::now();
//  std::vector<std::string> words;
//  words.reserve(lines_number);
//  words = std::vector<std::string>(std::istream_iterator<std::string>(stream),
//                                   std::istream_iterator<std::string>());
//  auto ptr = std::make_shared<std::vector<std::string>>(std::move(words));
//  auto end = std::chrono::system_clock::now();
//  std::chrono::duration<double> diff = end - start;
//  std::cout << diff.count() << std::endl;
//  return ptr;
//}
