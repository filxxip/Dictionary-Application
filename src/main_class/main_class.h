#pragma once

#include "../base_tab_widget/base_tab_widget.h"
#include "../custom_list/custom_list.h"
#include "../custom_message_box/custom_message_box.h"
#include "../login_view/login_view.h"
#include "../person_data_window/person_data_window.h"
#include "../register_window/register_window.h"
#include "../wordlist_widget/wordlist_widget.h"

/** Main Class which controls each part of app*/
class MainClass : public QObject {
  Q_OBJECT
private:
  BaseTabWidget base; ///< Base for whole app
  CustomList
      list; ///< Custom list with information about users and its dictionaries
  LoginView login_window;         ///< Personalize Login Window
  RegisterWindow register_window; ///< Personalize Register Window
  PersonDataWindow data_window;   ///< Personalize window about data of user
  WordlistWindow wordlist_window; ///< Personalize window with wordlist

public:
  /**
   * @brief MainClass constructor method
   * @param app QAppliction class instance
   */
  MainClass(QApplication &app);

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
};
