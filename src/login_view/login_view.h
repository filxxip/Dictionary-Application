#pragma once

#include "../custom_entry_line/entry_line.h"
#include "../custom_list/custom_list.h"
#include "../data/config_file.h"
#include "../image_button/image_button.h"
#include "../image_label/image_label.h"
#include "../login_entry_line/login_entry_line.h"
#include "../password_entry_line/password_entry_line.h"
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
  QWidget main_widget;     ///< main widget on which everything will be placed
  QVBoxLayout main_layout; ///< main layout of main_widget
  ImageLabel main_image_label; ///< label with app sign
  TextLabel login_label;       ///< label with some text - LOGIN
  TextLabel password_label;    ///< label with some text - PASSWORD
  LoginLineEntry login_entry;  ///< entryline where user will write their login
  ImageButton image_label;
  PasswordEntryLine
      password_entry; ///< entryline where user will write their password
  TextButton
      submit_button; ///< button which checks correctness of email and password
  TextButton clear_button; ///< button with clicked signal which clear lineedits
  /**
   * @brief creating_log_layout private method which create horizontal layout
   * for password and login
   * @param login_status enum status which defines password or login
   * @param margin margins of qhboxlayout, defaulty set to {60,0,60,0}
   * @return instance of QHBoxLayout
   */
  QHBoxLayout *
  creating_log_layout(EntryLine::Status login_status,
                      const QMargins &margin = WidgetData::DEFAULT_MARGINS);

  /**
   * @brief creating_buttons_layout private method which create horizontal
   * layout clear and submit button
   * @param margin margins of qhboxlayout, defaulty set to {60,0,60,0}
   * @param logs_map map with email as keys, passwords as values
   * @return instance of QHBoxLayout
   */
  QHBoxLayout *
  creating_buttons_layout(const std::map<QString, QString> &logs_map,
                          const QMargins &margin = WidgetData::DEFAULT_MARGINS);

  /**
   * @brief change_color method which changes color of item on the gived period
   * @param lineedit sign of widget/widgets which will be changed
   * @param miliseconds_sleep time on which item will change its color
   * @param change_color color which will replace current one
   */
  void change_color(ENTRIES_SIGNS lineedit, int miliseconds_sleep,
                    const QString &change_color);

public:
  /**
   * @brief LoginView constructor method
   * @param logs_map map with email as key, password as value
   */
  LoginView(const std::map<QString, QString> &logs_map);

  /**
   * @brief get_widget method which returns pointer to main_widget
   * @return pointer to QWidget class instance - main widget
   */
  QWidget *get_widget();

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
};
