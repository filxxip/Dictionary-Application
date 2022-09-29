#pragma once
#include "../custom_entry_line/entry_line.h"
#include "../custom_vbox_layout/custom_vbox_layout.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../text_button/text_button.h"
#include "../text_label/text_label.h"

#include <QLineEdit>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

/** Content Layout class which acts as a part of view which contain data about a
 * dictionary and shares some operations*/
class ContentLayout : public CustomVBoxLayout {
  Q_OBJECT
private:
  EntryLine entry_title;    ///< title of dictionary with posibility of changing
  ImageButton trash_button; ///< button which removes dictionary from list
  ImageButton edit_button; ///< edit button which makes possible to change title
                           ///< of dictionary
  ImageButton confirm_button; ///< confirm button used to applying changes
  ImageButton cancel_button;  ///< cancel button used to removing changes
  TextButton
      set_button; ///< button used to open new window with dictionary data
  Dictionary *dictionary; ///< dictionary from which data is taken

  /**
   * @brief create_base_entryline method which create entry_title instance
   */
  void create_base_entryline();

  /**
   * @brief create_base_label method which create label with some text and
   * configuration
   * @param text text which is placed on label
   * @return  pointer to TextLabel instance
   */
  TextLabel *create_base_label(const QString &text);

  /**
   * @brief create_layout method which create layout from base class
   */
  void create_layout();

  /**
   * @brief create_language_hbox mehtod which create bar with language flag and
   * word content
   * @param language language of data
   * @param source path to language image
   * @return pointer to initialized hboxlayout
   */
  QHBoxLayout *create_language_hbox(Word::Language language,
                                    const QString &source);

  /**
   * @brief create_operation_layout method which creates operation layout with
   * button, connect slots to signals
   * @return pointer to initialized hboxlayout
   */
  QHBoxLayout *create_operation_layout();

  /**
   * @brief entry_configuration method which adds some basic configuration for
   * entryline
   */
  void entry_configuration();

public:
  /**
   * @brief ContentLayout constructor method of class
   * @param widget_ main widget where widget will be placed
   * @param dict dictionary with data needed to initialized widget
   */
  ContentLayout(QWidget &widget_, Dictionary *dict);

  /**
   * @brief get_dictionary method which provides dictionary
   * @return pointer to dictionary
   */
  virtual Dictionary *get_dictionary() final;

  /**
   * @brief set_confirm_cancel_panel method which sets confirm and cancel panel
   * on bottom bar
   */
  void set_confirm_cancel_panel();

  /**
   * @brief set_edit_panel method which sets edit panel on bottom bar
   */
  void set_edit_panel();

  /**
   * @brief get_trash_button method which returns pointer to trash button
   * @return
   */
  ImageButton *get_trash_button();
public slots:

  /**
   * @brief change_title method which changes title of dictionary
   */
  void change_title();

  /**
   * @brief trash_element method which removes given dicitonary
   */
  void trash_element();

  /**
   * @brief confirm_title method which confirmed new title of dictionary
   */
  void confirm_title();

  /**
   * @brief cancel_title method which removes title changes
   */
  void cancel_title();

  /**
   * @brief set_box signal used to open new window with dictionary data
   */
  void set_box();
signals:

  /**
   * @brief trash_dict signal used to removing dictionary
   * @param dictionary pointer to dictionary which has to be removed
   */
  void trash_dict(Dictionary *dictionary);

  /**
   * @brief set_signal signal used to opening new window with dictionary
   * @param dictionary dictionary which data will be shown
   */
  void set_signal(Dictionary *dictionary);
};
