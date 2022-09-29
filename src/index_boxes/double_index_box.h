#pragma once

#include "../image_button/image_button.h"
#include "index_box.h"

/** DobuleIndexBox class which is basic class for content of dictionary word
 * window*/
class DoubleIndexBox : public IndexBox {
  Q_OBJECT
private:
  EntryLine to_word_entry; ///< entryline with word translation
  ImageButton edit_button; ///< button which allows to edit entries

  /**
   * @brief set_edit_style method which sets editable style to given entryline
   * @param entryline pointer to entryline
   */
  void set_edit_style(EntryLine *entryline);

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
                 Word::Language base_language,
                 Word::Language translated_language);

public slots:
  /**
   * @brief edit_method method which allows to edit entries
   */
  void edit_method();
};
