#pragma once

#include "../custom_label_entry_box/custom_label_entry_box.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../register_window/register_window.h"

#include <memory>

class PersonDataWindow : public QObject {

private:
  QWidget main_widget;     ///< main widget on which everything will be placed
  QVBoxLayout main_layout; ///< main layout of main_widget
  std::map<Person::Data, std::unique_ptr<LabelEntryBox>>
      items_map; ///< cpp map with every box in which user will fill data about
                 ///< yourself
  ImageLabel title_label;    ///< title label with app main image
  Person *person;            ///< custom person instance with data of user
  TextButton changes_button; ///< button which is responsible for possibility of
                             ///< doing changes in data
  TextButton savebutton;     ///< button which is responsible for saving changes
  ImageButton exit_button;   ///< button which is responsible for logging out

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
   * @return instance of layout which contain label and entry
   */
  QHBoxLayout *create_entry_box(Person::Data entry_name);

  /**
   * @brief set_person_data method which sets data to dafault person data
   * @param entry_name name of entry
   */
  void set_person_data(Person::Data entry_name);
  /**
   * @brief get_line_edit method which provides entry
   * @param entry_enum entries enum sign of entry
   * @return entryline based on entry enum
   */
  EntryLine *get_line_edit(Person::Data entry_enum);

public:
  /**
   * @brief PersonDataWindow constructor method
   */
  PersonDataWindow();

  /**
   * @brief get_widget method which provides main widget
   * @return pointer to QWidget class instance
   */
  QWidget *get_widget();

  /**
   * @brief set_person method which sets new person
   * @param person_pointer pointer to person whose data should be set
   */
  void set_person(Person *person_pointer);
  /**
   * @brief get_exit_button method which provides button
   * @return reference to exit button
   */
  ImageButton &get_exit_button();

public slots:

  /**
   * @brief change_button_function slot which turn on user possibility of apply
   * changes in personal data
   */
  void change_button_function();

  /**
   * @brief discard_changes slot which discards all changes which was applied by
   * user in personal data
   */
  void discard_changes();

  /**
   * @brief save_function slot which saves data applied by user
   */
  void save_function();

  /**
   * @brief every_change_event method which is running every time when some data
   * is changed
   * @param entry_enum entry sign where data is changed
   */
  void every_change_event(Person::Data entry_enum);
};
