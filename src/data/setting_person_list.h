#pragma once

#include "../custom_list/custom_list.h"
#include "../dictionary/dictionary.h"

#include <QJsonObject>
#include <vector>

#include <QFile>

template <typename T, typename TT>
/**
 * @brief get_key method which provides key from std::map using its unique
 * value;
 * @param value value which is using to find key
 * @param map map through which function is searching
 * @return key from this map
 */
T get_key(const TT &value, const std::unordered_map<T, TT> &map);

/**
 * @brief setting_person_list function which create person list from json file
 * @param list list to which people will be added (empty)
 */
void create_person_list(CustomList &list);

/**
 * @brief updating_json_file function which update json file with every person
 * data
 * @param list CustomList instance with every user of app
 */
void updating_person_json_file(const CustomList &list);

/**
 * @brief create_dictionary_list method which creates dictionary list from json
 * data file
 * @param list list with all users of app
 * @return vector with dictionaries
 */
void create_dictionary_list(CustomList &list);

/**
 * @brief update_json_dictionary_file method which updates json file with dict
 * data
 * @param vector with all dictionaries
 */
void update_json_dictionary_file(std::vector<Dictionary> &dictionaries);

/**
 * @brief create_json_response function which create response object from QFile
 * instance
 * @param file QFile instance with json inside
 */
auto create_json_response(QFile &file);
