#include "custom_list.h"
#include "../data/setting_person_list.h"

#include "../data/config_file.h"

#include <algorithm>
#include <exception>
#include <iterator>
#include <map>

CustomList::CustomList() {
  person_list_reserve(MaxValues::MAX_PERSON_NUM);
  dictionary_list_reserve(MaxValues::MAX_DICT_NUM);
  create_from_json();
}

void CustomList::add_person(const Person &new_person) {
  auto index = std::find(person_list.begin(), person_list.end(), new_person);
  if (index == person_list.end()) {
    person_list.push_back(new_person); // dokladnie tu
  } else {
    throw std::invalid_argument("Person with this email exists");
  }
}

void CustomList::remove_person(const Person &person) {
  auto index = std::find(person_list.begin(), person_list.end(), person);
  if (index != person_list.end()) {
    person_list.erase(index);
  }
  auto new_end = std::remove_if(dictionary_list.begin(), dictionary_list.end(),
                                [&person](const Dictionary &dict) {
                                  return dict.get_person()->get_email() ==
                                         person.get_email();
                                });
  dictionary_list.erase(new_end, dictionary_list.end());
}

Person &CustomList::get_person(const QString &email) {
  auto index = std::find_if(
      person_list.begin(), person_list.end(),
      [&email](const auto &person) { return person.get_email() == email; });
  if (index == person_list.end()) {
    throw std::invalid_argument("Person with this email doesnt exists!");
  }
  return *index;
}

int CustomList::get_number_users() { return person_list.size(); }

void CustomList::remove_person(const QString &email) {
  auto person = get_person(email);
  remove_person(person);
}

const std::vector<Person> &CustomList::get_person_list() const {
  return person_list;
}

void CustomList::add_dictionary(const Dictionary &dictionary) {
  auto index = std::find(person_list.begin(), person_list.end(),
                         *dictionary.get_person());
  if (index == person_list.end()) {
    add_person(*dictionary.get_person());
  }
  dictionary_list.push_back(dictionary);
}

void CustomList::add_last_dictionary_to_box() {
  auto size = dictionary_list.size();
  emit adding_to_box(dictionary_list.at(size - 1));
}

void CustomList::update_json() {
  updating_person_json_file(*this);
  update_json_dictionary_file(dictionary_list);
}

void CustomList::create_from_json() {
  create_person_list(*this);
  create_dictionary_list(*this);
}

void CustomList::dictionary_list_reserve(int value) {
  dictionary_list.reserve(value);
}

void CustomList::person_list_reserve(int value) { person_list.reserve(value); }

const std::map<QString, QString> CustomList::get_logs_data() const {
  std::map<QString, QString> logs;
  for (auto &person : person_list) {
    logs.emplace(std::pair(person.get_email(), person.get_password()));
  }
  return logs;
}

const std::vector<QString> CustomList::get_emails_list() const {
  std::vector<QString> list;
  for (auto &person : person_list) {
    list.push_back(person.get_email());
  }
  return list;
}

std::vector<Dictionary> &CustomList::get_dictionary_list() {
  return dictionary_list;
}

// std::vector<Dictionary *>
// CustomList::get_dictionary_list(const QString &email) {
//  std::vector<Dictionary *> dictionary_list_result;
//  for (auto &dict : dictionary_list) {
//    auto dict_email = dict.get_person()->get_email();
//    if (dict_email == email) {
//      dictionary_list_result.push_back(&dict);
//    }
//  }
//  return dictionary_list_result;
//}
auto CustomList::get_iterator(Dictionary &dictionary) {
  auto dict = std::find_if(dictionary_list.begin(), dictionary_list.end(),
                           [&dictionary](auto &iter_dictionary) {
                             return &iter_dictionary == &dictionary;
                           });
  return dict;
}

void CustomList::remove_dictionary(Dictionary &dictionary) {
  if (dictionary_exists(dictionary)) {
    auto dict_itr = get_iterator(dictionary);
    dictionary_list.erase(dict_itr);
  }
}

bool CustomList::dictionary_exists(Dictionary &dictionary) {
  auto dict = get_iterator(dictionary);
  return dict != dictionary_list.end();
}
