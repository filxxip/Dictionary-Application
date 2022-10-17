#pragma once

#include <QHBoxLayout>
#include <QString>
#include <QWidget>

#include "../custom_entry_line/entry_line.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

/** IndexBox class which contain index label with entry*/
class IndexBox : public QHBoxLayout {
  Q_OBJECT
protected:
  QWidget *widget; ///< widget on which layout will be placed
  Word &word;      ///< word which data will be on layout
  std::unique_ptr<QWidget> widget_index_entry_layout; ///< layout's widget
  std::unique_ptr<QHBoxLayout>
      index_entry_layout;       ///< unique pointer to main layout
  TextLabel index_label;        ///< label with given index
  EntryLine from_word_entry;    ///< entryline which contains first word
  Word::Language base_language; ///< base language of searched word

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

  virtual void set_status(Status status) = 0;
  virtual void set_visible(bool status) = 0;
  int get_index() const { return index_label.text().toInt(); }
  const Word &get_word() const { return word; }

  /**
   * @brief set_entry_basic_options method which sets some options to
   * entryline
   * @param entry pointer to entry which user want to change
   * @param language language of data in entryline
   */
  void set_entry_basic_options(EntryLine *entry, Word::Language language);
signals:
  void update_window();
  void creating_detail_view(Word &word, Word::Language language);
};
