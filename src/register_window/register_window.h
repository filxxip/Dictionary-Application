#pragma once

#include "../custom_entry_line/entry_line.h"
#include "../custom_list/custom_list.h"
#include "../data/config_file.h"
#include "../image_label/image_label.h"
#include "../text_button/text_button.h"
#include "../text_label/text_label.h"

#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include <map>

class RegisterWindow : public QObject {
public:
  enum class Entries {
    NAME,
    SURNAME,
    AGE,
    COUNTRY,
    SCHOOL,
    EMAIL,
    PASSWORD,
    REPEAT_PASSWORD
  };

private:
  enum class Entry_Style {
    PASSWORD,
    NORMAL
  };                       ///< enum class which defines type of entry
  QWidget main_widget;     ///< main widget on which everything will be placed
  QVBoxLayout main_layout; ///< main layout of main_widget
  std::map<Entries, std::pair<TextLabel *, EntryLine *>>
      items_map; ///< cpp map with every box in which user will fill data about
                 ///< yourself
  ImageLabel title_label;     ///< title label with app main image
  TextButton clear_button;    ///< button which clears every entryline
  TextButton register_button; ///< register button which saves the entered data
  CustomList &list; ///< custom list instance with data with every user
  /**
   * @brief creating_buttons_layout private method which create horizontal
   * layout clear and submit button
   * @param margin margins of qhboxlayout, defaulty set to {60,0,60,0}
   * @return instance of QHBoxLayout
   */
  QHBoxLayout *
  creating_buttons_layout(const QMargins &margin = WidgetData::DEFAULT_MARGINS);
  /**
   * @brief creating_entries_layout method which create layout with entries
   * @return pointer to layout
   */
  QVBoxLayout *creating_entries_layout();

  /**
   * @brief create_entry_box method which creats entry with label
   * @param entry_name name of entry
   * @param type type of entry, normal or password
   * @return instance of layout which contain label and entry
   */
  QHBoxLayout *create_entry_box(Entries entry_name,
                                Entry_Style type = Entry_Style::NORMAL);

public:
  /**
   * @brief RegisterWindow contructor method
   * @param main_list custom list with data about users
   */
  RegisterWindow(CustomList &main_list);

  /**
   * @brief get_widget method which provides main widget
   * @return pointer to QWidget class instance
   */
  QWidget *get_widget();

  /**
   * @brief get_line_edit method which provides entry
   * @param entry_enum entries enum sign of entry
   * @return entryline based on entry enum
   */
  EntryLine *get_line_edit(Entries entry_enum);

  /**
   * @brief change_color method which changes entry color on given time
   * @param il initializer list with entry which should be changed
   * @param miliseconds_sleep period on which new color will be applied
   * @param change_color new color of widget
   */
  void change_color(std::vector<Entries> il, int miliseconds_sleep,
                    const QString &change_color);

public slots:

  /**
   * @brief clear_method method which clear data written in entries
   */
  void clear_method();

  /**
   * @brief user_register method which creates new user
   */
  void user_register();
};
