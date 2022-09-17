#include "setting_person_list.h"
#include "config_file.h"

#include <QByteArray>
#include <QDebug>
#include <QDir>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QList>
#include <QString>

#include <string>

template <typename T, typename TT>
T get_key(const TT &value, const std::unordered_map<T, TT> &map) {
  auto x = std::find_if(map.begin(), map.end(), [value](const auto &pair) {
    return pair.second == value;
  });
  return x->first;
}

auto create_json_response(QFile &file) {
  file.open(QIODevice::ReadOnly);
  auto file_text = file.readAll();
  auto json_response = QJsonDocument::fromJson(file_text);
  auto json_object = json_response.object();
  return json_object;
}

void create_person_list(CustomList &list) {
  QFile fin("../src/data/person_data.json");
  auto json_object = create_json_response(fin);
  Person person;
  auto keys = json_object.keys();
  list.person_list_reserve(keys.size());
  for (const auto &key : keys) {
    auto key_result = json_object[key].toObject();
    auto name = key_result[Json::NAME].toString();
    auto age = key_result[Json::AGE].toInt();
    auto surname = key_result[Json::SURNAME].toString();
    auto country = key_result[Json::COUNTRY].toString();
    auto password = key_result[Json::PASSWORD].toString();
    auto email = key;
    auto school = key_result[Json::SCHOOL].toString();
    person = Person(name, surname, age, school, country, email, password);
    list.add_person(person);
  }
  fin.close();
}

void updating_person_json_file(const CustomList &list) {
  QFile fin("../src/data/person_data.json");
  fin.open(QIODevice::WriteOnly);
  QJsonObject main_object;
  for (const auto &person : list.get_person_list()) {
    QJsonObject obj;
    obj[Json::NAME] = person.get_name();
    obj[Json::SURNAME] = person.get_surname();
    obj[Json::AGE] = person.get_age();
    obj[Json::COUNTRY] = person.get_country();
    obj[Json::PASSWORD] = person.get_password();
    obj[Json::SCHOOL] = person.get_school();
    auto email = person.get_email();
    main_object[email] = obj;
  }
  auto text = QJsonDocument(main_object).toJson();
  fin.write(text);
  fin.close();
}

void create_dictionary_list(CustomList &list) {
  std::vector<Dictionary> dictionaries;
  QFile fin("../src/data/word_data.json");
  auto json_object = create_json_response(fin);
  Word word;
  for (const auto &email : json_object.keys()) {
    qDebug() << email;
    auto &owner = list.get_person(email);
    auto email_dictionaries_data = json_object.take(email).toArray();
    for (const auto &dictionary : email_dictionaries_data) {
      Dictionary dict(&owner);
      for (const auto &word_data : dictionary.toArray()) {
        auto word_data_object = word_data.toObject();
        for (int value = static_cast<int>(Word::Language::ENGLISH);
             value <= static_cast<int>(Word::Language::GERMAN); value++) {
          auto language = static_cast<Word::Language>(value);
          auto language_string = Word::Language_names.at(language);
          auto word_trans_date =
              word_data_object.take(language_string).toArray();
          auto word_translation = word_trans_date.at(0).toString();
          auto word_date = word_trans_date.at(1).toString();
          auto word_prioritity = word_trans_date.at(2).toString();
          auto word_prioritity_enum =
              get_key(word_prioritity, Word::Prioritity_names);

          word.change_translation(language, word_translation);
          word.change_translation_date(language, to_date(word_date));
          word.set_prioritity(word_prioritity_enum);
        }
        dict.add_word(word);
      }

      dictionaries.push_back(dict);
    }
  }
  list.dictionary_list_reserve(dictionaries.size());
  for (auto dict : dictionaries) {
    list.add_dictionary(dict);
  }
}

void update_json_dictionary_file(std::vector<Dictionary> &dictionaries) {
  QFile fin("../src/data/word_data.json");
  fin.open(QIODevice::WriteOnly);
  QJsonObject main_object;
  for (auto &dictionary : dictionaries) {
    auto &user_mail = dictionary.get_person()->get_email();
    QJsonObject::iterator mail_exists;
    if (main_object.isEmpty()) {
      mail_exists = main_object.end();
    } else {
      mail_exists = main_object.find(user_mail);
    }
    if (mail_exists == main_object.end()) {
      QJsonArray main_array;
      main_object.insert(user_mail, main_array);
    }
    QJsonArray dictionary_array;
    auto &wordlist = dictionary.get_full_wordlist();
    for (const auto &word : wordlist) {
      QJsonObject word_data;
      for (int value = static_cast<int>(Word::Language::ENGLISH);
           value <= static_cast<int>(Word::Language::GERMAN); value++) {
        auto language = static_cast<Word::Language>(value);
        auto language_string = Word::Language_names.at(language);
        auto language_translation = word.get_translation(language);
        QJsonArray result_word_array;
        result_word_array.append(language_translation);
        result_word_array.append(word.get_date(language).to_string());
        auto prioritity_as_string =
            Word::Prioritity_names.at(word.get_prioritity());
        result_word_array.append(prioritity_as_string);
        word_data.insert(language_string, result_word_array);
      }
      dictionary_array.append(word_data);
    }
    auto value = main_object.take(user_mail).toArray();
    value.append(dictionary_array);
    main_object.insert(user_mail, value);
  }
  auto text = QJsonDocument(main_object).toJson();
  fin.write(text);
  fin.close();
}
