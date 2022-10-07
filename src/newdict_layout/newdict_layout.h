#pragma once

#include "../custom_entry_line/entry_line.h"
#include "../custom_vbox_layout/custom_vbox_layout.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"

/** New Dictionary Layout class which acs role of widget used to creating new
 * dictionary for given user*/
class NewDictLayout : public CustomVBoxLayout {
  Q_OBJECT
private:
  EntryLine entry;           ///< entry with new dictionary name
  TextLabel label;           ///< label with title
  ImageButton clear_button;  ///< button which clears entry
  ImageButton create_button; ///< button which create new dictionary

  /**
   * @brief create_base_label mehtod which creates
   * @param align alignment of text
   */
  void create_base_label(Qt::Alignment align);

  /**
   * @brief create_layout method which creates main layout
   * @param align alignment of text on items
   */
  void create_layout(Qt::Alignment align);

  /**
   * @brief create_entry method which adding some functionalities to entryline
   * @param align alignment of text
   */
  void create_entry(Qt::Alignment align);

public:
  /**
   * @brief NewDictLayout constructor method
   * @param widget_ widget where whole layout will be placed
   * @param align alignment of text
   */
  NewDictLayout(QWidget &widget_, Qt::Alignment align);

  /**
   * @brief new_button_function mehtod which
   */
  void new_button_function();

  /**
   * @brief get_dictionary method which returns nullptr becouse this instance
   * cannot has any data
   * @return nullptr
   */
  //  virtual Dictionary &get_dictionary() final;
  virtual void update(){};

  bool has_dictionary() const final;
signals:

  /**
   * @brief new_box_signal signal used to create new dictionary
   * @param text title of dict
   */
  void new_box_signal(const QString &text);
};
