#pragma once

#include <unordered_map>
#include <vector>

#include "../dictionary/dictionary.h"
#include "../person/person.h"

/** CustomList class which contain all application users*/
class CustomList {
private:
  std::vector<Person> person_list; ///< list which contain every person in app
  std::vector<Dictionary> dictionary_list;

public:
  /**
   * @brief CustomList default constructor
   */
  CustomList();

  /**
   * @brief add_person methdo which add person to list
   * @param new_person new person which will be added
   */
  void add_person(const Person &new_person);

  /**
   * @brief add_dictionary method which add dictionary to dictionary list
   * @param dictionary dictionary which will be added
   */
  void add_dictionary(const Dictionary &dictionary);

  /**
   * @brief remove_person method which remove given person from list
   * @param person person who will be removed
   */
  void remove_person(const Person &person);

  /**
   * @brief remove_person method which remove person with given email
   * @param email email whose owner will be deleted from list
   */
  void remove_person(const QString &email);

  /**
   * @brief get_person method which provide person from list
   * @param email unique email of person
   * @return instance of person with given email
   */
  Person &get_person(const QString &email);

  /**
   * @brief get_number_users method which provides number of users
   * @return number of users
   */
  int get_number_users();

  /**
   * @brief get_list mwthod which return list with all users
   * @return list with users
   */
  const std::vector<Person> &get_person_list() const;

  /**
   * @brief update_json method which updates all json files with current status
   * of person list and dictionary list
   */
  void update_json();

  /**
   * @brief create_from_json method which create dictionary list and person list
   * from json data files
   */
  void create_from_json();

  /**
   * @brief person_list_reserve method which reserves place in vector person
   * list vector
   * @param value value which determines ammount of reserved place
   */
  void person_list_reserve(int value);

  /**
   * @brief dictionary_list_reserve method which reserves place in vector
   * dictionary list vector
   * @param value value which determines ammount of reserved place
   */
  void dictionary_list_reserve(int value);

  const std::map<QString, QString> get_logs_data() const;
};
