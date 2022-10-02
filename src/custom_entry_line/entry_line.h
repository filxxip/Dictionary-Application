#pragma once

#include "../base_tab_widget/base_tab_widget.h"

#include <QLineEdit>
#include <QMargins>
#include <QRect>
#include <QString>
#include <QWidget>

#include <memory>

/**
 * @brief The EntryLine class which determines basic widget to writing some text
 * inside it
 */
class EntryLine : public QLineEdit {
public:
  enum class Status { PASSWORD, NORMAL };

private:
  Status status; ///< Status of entryline

public:
  /**
   * @brief EntryLine constructor method which creates class instance
   * @param widget_ shared pointer to QWidget on which entryline is placed
   * @param entry_type type of entryline, password or normal
   */
  EntryLine(QWidget *widget_, Status entry_type = Status::NORMAL);

  /**
   * @brief append_text method which appends text to line edit's current text
   * @param text QString instance which will be added to line edit
   */
  void append_text(const QString &text);

  /**
   * @brief set_position method which sets new position of entryline
   * @param position_x position x of entryline
   * @param position_y position y of entryline
   */
  void set_position(int position_x, int position_y);

  /**
   * @brief get_status method which returns status of line edit
   * @return enum type Status (Password or Normal)
   */
  Status get_status() const;

  /**
   * @brief set_text_status method which sets mode of text inside line edit
   * @param mode mode of text in line edit
   */
  void set_text_status(EntryLine::Status new_status);

  /**
   * @brief set_object_name_stylesheet method which sets new style using
   * objectname of widget
   * @param object_name new object_name of entry
   */
  void set_object_name_stylesheet(const QString &object_name);
};
