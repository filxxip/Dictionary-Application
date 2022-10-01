#pragma once

#include "../image_button/image_button.h"
#include "index_box.h"

/** DobuleIndexBox class which is basic class for content of dictionary word
 * window*/
class DoubleIndexBox : public IndexBox {
  Q_OBJECT
private:
  EntryLine to_word_entry; ///< entryline with word translation
  std::unique_ptr<QWidget> widget_change_bar_layout; ///< layout's widget
  std::unique_ptr<QHBoxLayout> change_bar_layout;
  ImageButton edit_button;    ///< button which allows to edit entries
  ImageButton confirm_button; ///< button which applies changes
  ImageButton cancel_button;  ///< button which cancels changes
  ImageButton delete_button;  ///< button which removes given translation
  Word::Language translated_language; ///< language of second entry box's word

  /**
   * @brief set_edit_style method which sets editable style to given
   * entryline
   * @param entryline pointer to entryline
   */
  void set_edit_style(EntryLine *entryline);

  /**
   * @brief set_read_style method which sets given entryline readeable
   * appearence
   * @param entryline entryline which user want to change
   */
  void set_read_style(EntryLine *entryline);

  /**
   * @brief apply_button_configuration method which add some basic configuration
   * to button
   * @param button qpushbutton pointer
   */
  void apply_button_configuration(QPushButton *button);

public:
  /**
   * @brief DoubleIndexBox constructor method
   * @param widget_ pointer to widget on which data will be placed
   * @param word_ reference to word whose data will be placed on widget
   * @param index index of word
   * @param base_language abse language of word
   * @param translated_language translation of word
   */
  DoubleIndexBox(QWidget *widget_, Word &word_, const QString &index,
                 Word::Language base_language_,
                 Word::Language translated_language_);

  /**
   * @brief set_status method which change status of entry
   * @param status status enum type, ReadOnly or Edit
   */
  virtual void set_status(Status status);

  /**
   * @brief change_status_images method which change visibility of button
   * depends on status
   * @param status
   */
  void change_status_images(Status status);

public slots:
  /**
   * @brief edit_method method which allows to edit entries
   */
  void edit_method();

  /**
   * @brief cancel_changes used to canceling changes
   */
  void cancel_changes();

  /**
   * @brief confirm_changes slot used to confirming changes
   */
  void confirm_changes();

  /**
   * @brief delete_translation slot used to delete given translation
   */
  void delete_translation();
signals:
  void cancel_changes_signal();
};
