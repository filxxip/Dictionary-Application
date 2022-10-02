#pragma once

#include <QHBoxLayout>
#include <QObject>

#include "../custom_entry_line/entry_line.h"
#include "../custom_label_entry_box/custom_label_entry_box.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

/** DetailViewOneLanguageLayout which is main component of base word class
 * widget, contains whole information about one word translation language*/
class DetailViewOneLanguageLayout : public QHBoxLayout {
  Q_OBJECT
private:
  QWidget *widget;             ///< widget on which layout will be placed
  Word &word;                  ///< word which part of data is on layout
  Word::Language language;     ///< language of data
  EntryLine translation_entry; ///< entryline with translation
  EntryLine date_entry;        ///< entryline with date
  TextLabel language_label;  ///< label which specifies language of translation
  ImageButton delete_button; ///< button which removes given translation
  const Dictionary *dictionary;

public:
  /**
   * @brief DetailViewOneLanguageLayout constructor method
   * @param widget_ widget on which layout will be placed
   * @param word_ word whose data is on layout
   * @param language_ language of data
   */
  DetailViewOneLanguageLayout(QWidget *widget_, Word &word_,
                              Word::Language language_, const Dictionary *dict);

  /**
   * @brief set_entries_read_only which sets whether data should be only
   * readable or also changeable
   * @param status
   */
  void set_entries_read_only(bool status);

  /**
   * @brief set_entries_new_object_names method which changes style of entries
   * @param new_object_name string instance with new object name
   */
  void set_entries_new_object_names(const QString &new_object_name);

  /**
   * @brief set_height method which sets height of layout
   * @param height new height of layout
   */
  void set_height(int height);

  /**
   * @brief update_content method which updates whole content on layout
   */
  void update_content();

  const Dictionary *get_dictionary() const;
public slots:

  /**
   * @brief delete_translation method which removes given translation
   */
  void delete_translation();
signals:

  /**
   * @brief update_rest_dictionaries signal used to update every tab
   * @param dict dictionary which data was changed
   */
  void update_rest_dictionaries(const Dictionary *dict);
};
