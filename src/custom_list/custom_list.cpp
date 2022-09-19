#include "custom_list.h"
#include "../data/setting_person_list.h"

#include "../data/config_file.h"

#include <algorithm>
#include <exception>
#include <map>
CustomList::CustomList() { person_list_reserve(MaxValues::MAX_PERSON_NUM); }

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
  std::map<QString, QString> logs; /// why connot create unordered map
  for (auto &person : person_list) {
    logs.emplace(std::pair(person.get_email(), person.get_password()));
  }
  return logs;
}
