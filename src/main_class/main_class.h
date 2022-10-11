#pragma once

#include "../add_new_word/add_new_word.h"
#include "../base_tab_widget/base_tab_widget.h"
#include "../custom_list/custom_list.h"
#include "../custom_message_box/custom_message_box.h"
#include "../detail_view/detail_view.h"
#include "../login_view/login_view.h"
#include "../person_data_window/person_data_window.h"
#include "../register_window/register_window.h"
#include "../word_window/word_window.h"
#include "../wordlist_widget/wordlist_widget.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QTimer>

/** Main Class which controls each part of app*/
class MainClass : public QObject {
  Q_OBJECT
private:
  int value = 10;
  BaseTabWidget base; ///< Base for whole app
  CustomList
      list; ///< Custom list with information about users and its dictionaries
  LoginView login_window;         ///< Personalize Login Window
  RegisterWindow register_window; ///< Personalize Register Window
  PersonDataWindow data_window;   ///< Personalize window about data of user
  WordlistWindow wordlist_window; ///< Personalize window with wordlist
  std::vector<std::unique_ptr<WordWindow>> word_windows;
  std::vector<std::unique_ptr<DetailView>> detail_tabs;
  std::vector<std::unique_ptr<AddNewWord>> add_new_word_tabs;

public:
  /**
   * @brief MainClass constructor method
   * @param app QAppliction class instance
   */
  MainClass(QApplication &app);

  void add_login_tabs();
  //  void add_basic_personal_tabs();
  void remove_personal_tabs();
  void remove_every_dict_from_list();
  void remove_every_dict_detail_tab_from_list();
  void remove_every_new_word_from_list();
  /**
   * @brief widget_change_title method which changes title of widget
   * @param widget widget which title should be changed
   */
  void widget_change_title(QWidget *widget);

  //  void remove_given_word_from_tabs(Word &word);

  /**
   * @brief remove_every_dict_from_list method which removes specified dict from
   * tabs
   * @param dict dictionary to remove
   */
  void remove_every_dict_from_list(Dictionary &dict);

  /**
   * @brief remove_every_dict_detail_tab_from_list method which removes every
   * detail tab with specified dictionary
   * @param dict dictionary which is removed
   */
  void remove_every_dict_detail_tab_from_list(Dictionary &dict);

  /**
   * @brief remove_every_dict_detail_tab_from_list method which removes every
   * detail tab with specified word
   * @param word word which is removed
   */
  void delete_given_word_from_tabs(Word &word);

  /**
   * @brief delete_given_word_from_list method which removes specified detail
   * tab from detail tab lists
   * @param word word whose tabs will be removed
   */
  void delete_given_word_from_list(Word &word);

  /**
   * @brief update_word_windows method which updates data of every detail tab
   * @param dict dict for which word belongs
   */
  void update_word_windows(Dictionary &dict);

  /**
   * @brief update_dict_windows method which updates every dictionary tab
   * @param dict dict which is updating
   */
  void update_dict_windows(Dictionary &dict);

  void update_new_word_windows(Dictionary &dict);

  //  void update_base_window();

public slots:
  /**
   * @brief setting_new_person_data method which set new data on data window
   * @param email unique email of new person
   */
  void setting_new_person_data(const QString &email);

  /**
   * @brief get_list method which returns list with data about users
   * @return CustomList reference with data about users
   */
  CustomList &get_list();

  /**
   * @brief logout method which logout user from app
   */
  void logout();

  /**
   * @brief add_new_dictionary method which adds new dictionary to list
   * @param name name of dict
   * @param owner owner of dict
   */
  void add_new_dictionary(const QString &name, const QString &owner);

  /**
   * @brief remove_dictionary method which removes dictionary
   * @param dictionary dictionary which will be removed
   * @param person_mail mail of person whose dict will be removed
   */
  void remove_dictionary(Dictionary &dictionary);

  void add_new_dict_window(Dictionary &dictionary);

  void close_widget_tab(QWidget *widget);
  void remove_dictionary_from_list(Dictionary &dict);
  void change_every_dict_bar_title(Dictionary &dict);

  void update_every_tab(Dictionary &dict);
  void add_new_detail_view(Dictionary &dict, Word &word,
                           Word::Language language);
  void add_new_new_word_window(Word::Language language, Dictionary &dictionary);
  void remove_new_word_window(QWidget *widget);
};
