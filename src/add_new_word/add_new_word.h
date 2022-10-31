#pragma once

#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include <map>
#include <memory>
#include <vector>

#include "../change_color/change_color.h"
#include "../config_detail_view_panel/config_detail_view_panel.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_label_entry_box/custom_label_entry_box.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../image_label/image_label.h"
#include "../swiper/swiper.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

/** AddNewWord class which implements a widget with basics operations which are
 * used for adding new word to given dictionary*/
class AddNewWord : public QObject {
  Q_OBJECT
private:
  QWidget main_window;     ///< main widget with data of new word
  Dictionary &dict;        ///< dictionary which word will be added to
  QVBoxLayout main_layout; ///< main layout where some widgets are placed
  ImageLabel title_image;
  std::map<Word::Language, std::unique_ptr<LabelEntryBox>>
      language_panels; ///< map with language as key and relevant label with
                       ///< entry as value
  CustomizeImageButton
      confirm_button; ///< confirm button used for adding new word
  CustomizeImageButton cancel_button; ///< close button used for closing window
  CustomizeImageButton
      clear_button; ///< clear button used for clearing each entryline
  Word::Language main_language; ///< main language of new word

  const static Word::Language
      MAIN_BASE_LANGUAGE; ///< main language used when main language is not
                          ///< defined, basically english

  /**
   * @brief create_config_panel_layout method which creates panel with confirm,
   * clear and cancel buttons
   */
  void create_config_panel_layout();
  /**
   * @brief create_entryboxes method which creates entryboxes for every defined
   * language
   */
  void create_entryboxes();

  /**
   * @brief create_single_entrybox method which creates entrybox for given
   * language
   * @param height defined height of entrybox
   * @param language defined language
   */
  void create_single_entrybox(int height, Word::Language language);

  /**
   * @brief adding_undefined_main_language method which add new word to
   * dictionary, main language is undefined
   * @param information_language language which substitutes main language
   */
  void adding_undefined_main_language(Word::Language information_language);

  /**
   * @brief adding_defined_main_language method which add new word to
   * dictionary, main language is defined
   */
  void adding_defined_main_language();

public:
  /**
   * @brief AddNewWord constructor method
   * @param main_language_ main language of new word, it has to be defined
   * @param dictionary dictionary to which word will be added
   */
  AddNewWord(Word::Language main_language_, Dictionary &dictionary);

  /**
   * @brief get_widget method which provides main widget
   * @return pointer to widget of window
   */
  QWidget *get_widget();
  /**
   * @brief get_dictionary method which provides dictionary to which word
   * belongs
   * @return reference of dicitonary
   */
  Dictionary &get_dictionary();

  /**
   * @brief get_defined_translations method which takes data from entries and
   * passes it to map
   * @return map with language as key and its translation as value
   */
  std::map<Word::Language, QString> get_defined_translations() const;

  /**
   * @brief clear which clears entries
   */
  void clear();

public slots:

  /**
   * @brief add_new_word method which is used for adding new word
   */
  void add_new_word();

signals:
  void add_new_word_signal(Dictionary &dict);
  void exit_signal(QWidget *widget);
}; /// wyrzucic mozliwosc pustego i cos zrobic z tym zaweierraniem
