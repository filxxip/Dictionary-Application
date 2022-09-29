#pragma once

#include <QHBoxLayout>
#include <QString>
#include <QWidget>

#include "../custom_entry_line/entry_line.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

/** IndexBox class which contain index label with entry*/
class IndexBox : public QHBoxLayout {
protected:
  QWidget *widget;           ///< widget on which layout will be placed
  Word &word;                ///< word which data will be on layout
  TextLabel index_label;     ///< label with given index
  EntryLine from_word_entry; ///< entryline which contains first word

public:
  enum class Status { READ_ONLY, EDIT };
  /**
   * @brief IndexBox
   * @param widget_
   * @param word_
   * @param index
   * @param l1
   */
  IndexBox(QWidget *widget_, Word &word_, const QString &index,
           Word::Language l1);

  /**
   * @brief set_status method which change status of entry
   * @param status status enum type, ReadOnly or Edit
   */
  void set_status(Status status);

  /**
   * @brief set_entry_basic_options method which sets some options to entryline
   * @param entry pointer to entry which user want to change
   * @param language language of data in entryline
   */
  void set_entry_basic_options(EntryLine *entry, Word::Language language);
};
