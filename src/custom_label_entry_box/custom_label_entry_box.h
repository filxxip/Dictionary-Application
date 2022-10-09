#pragma once

#include "../custom_entry_line/entry_line.h"
#include "../data/config_file.h"
#include "../text_label/text_label.h"

#include <QDebug>
#include <QHBoxLayout>

#include <memory>

class LabelEntryBox {

private:
  std::unique_ptr<TextLabel> label; ///< unique pointer to label with some text
  std::unique_ptr<EntryLine>
      entry; ///< unique pointer to entry where user can write some data

public:
  /**
   * @brief LabelEntryBox constructor method
   * @param widget widget on which entry and label are placed
   * @param label_text text which is shown on label
   * @param entry_placeholder placeholder text for entry
   * @param entry_type enum type of entry: password or normal
   */
  LabelEntryBox(QWidget *widget, const QString &label_text,
                const QString &entry_placeholder, EntryLine::Status entry_type);

  /**
   * @brief get_text method which provides text from entry
   * @return QString instance with text from entry
   */
  QString get_text();

  /**
   * @brief set_text method which sets some text to entry
   * @param text new text which is shown on entry
   */
  void set_text(const QString &text);

  /**
   * @brief create_layout which combines entry and label in custom hboxlayout
   * @param height height of elements of layout
   * @param spacing spacing beetween elements of layout
   * @param margin margin of layout
   * @return
   */
  QHBoxLayout *
  create_layout(int height, int spacing = WidgetData::LOGS_SPACING,
                const QMargins &margin = WidgetData::DEFAULT_MARGINS);

  /**
   * @brief set_label_width method which sets new width of label
   * @param width new value of width
   */
  void set_label_width(int width);

  /**
   * @brief set_label_width method which sets new width of entry
   * @param width new value of width
   */
  void set_entry_width(int width);

  /**
   * @brief clear method which clears entry
   */
  void clear();

  /**
   * @brief get_style_sheet method which return stylesheet of entry
   * @return stylesheet of entry
   */
  QString get_style_sheet();

  /**
   * @brief get_entryline method which provide entryline
   * @return pointer to entryline
   */
  EntryLine *get_entryline();

  /**
   * @brief set_read_only method which set read only status of entry
   * @param status if true then entry is read only, if false then user can write
   * text into it
   */
  void set_read_only(bool status);

  /**
   * @brief change_entry_line_object_name method which changes object name of
   * entry and apply new stylesheet
   * @param new_object_name new object name
   */
  void change_entry_line_object_name(const QString &new_object_name);
};
