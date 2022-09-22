#pragma once

#include "../custom_completer/custom_completer.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_label_entry_box/custom_label_entry_box.h"
#include "../custom_list/custom_list.h"
#include "../data/config_file.h"
#include "../image_button/image_button.h"
#include "../image_label/image_label.h"
#include "../text_button/text_button.h"
#include "../text_label/text_label.h"

#include <QHBoxLayout>
#include <QMargins>
#include <QVBoxLayout>
#include <QWidget>

#include <algorithm>
#include <unordered_map>

class LoginView : public QObject {
  Q_OBJECT //?
      private :

      /** enum class which represents type of entries on window, used during
         changing color to specify which entry should be changed*/
      enum class ENTRIES_SIGNS {
        PASSWORD, ///< password entry
        LOGIN,    ///< login entry
        BOTH      ///< password and login entries
      };
  const CustomList &user_list; ///< list with all data about each person
  QWidget main_widget;     ///< main widget on which everything will be placed
  QVBoxLayout main_layout; ///< main layout of main_widget
  ImageLabel main_image_label;        ///< label with app sign
  LabelEntryBox entry_line_box_login; ///< entryline with label box for login
  LabelEntryBox
      entry_line_box_password; ///< entryline with label box for password
  ImageButton image_button;
  TextButton
      submit_button; ///< button which checks correctness of email and password
  TextButton clear_button; ///< button with clicked signal which clear lineedits
  CustomCompleter completer; ///< completer with every email

  /**
   * @brief create_main_vboxlayout method which create login and password boxes
   */
  void create_main_vboxlayout();
  /**
   * @brief creating_buttons_layout private method which create horizontal
   * layout clear and submit button
   * @param margin margins of qhboxlayout, defaulty set to {60,0,60,0}
   * @param logs_map map with email as keys, passwords as values
   * @return instance of QHBoxLayout
   */
  QHBoxLayout *
  creating_buttons_layout(const CustomList &list,
                          const QMargins &margin = WidgetData::DEFAULT_MARGINS);

public:
  /**
   * @brief LoginView constructor method
   * @param logs_map map with email as key, password as value
   */
  LoginView(const CustomList &list);

  /**
   * @brief get_widget method which returns pointer to main_widget
   * @return pointer to QWidget class instance - main widget
   */
  QWidget *get_widget();

  /**
   * @brief get_completer method which provides completer
   * @return CustomCompleter reference instance
   */
  const CustomCompleter &get_completer() const;

public slots:

  /**
   * @brief clear_function method which is used to clear line edits
   */
  void clear_function();

  /**
   * @brief submit_function which is used to check correctness of email and
   * password
   */
  void submit_function(const std::map<QString, QString> &logs_map);

  /**
   * @brief set_to_visible method which sets password to normal mode
   */
  void set_to_visible();

  /**
   * @brief set_to_hidden method which sets password to password mode
   */
  void set_to_hidden();

  void entry_changed();
signals:

  void data_window_create(const QString &text);
};
