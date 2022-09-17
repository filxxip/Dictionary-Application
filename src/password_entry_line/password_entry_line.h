#pragma once

#include "../custom_entry_line/entry_line.h"

#include <QLineEdit>

/** Password class which is child of EntryLine class,  */
class PasswordEntryLine : public EntryLine {
public:
  using Mode = QLineEdit::EchoMode; ///< enum class used to defining password
                                    ///< mode, substitutes QLineEdit::EchoMode

  /**
   * @brief EntryLine constructor method which creates class instance
   * @param widget_  pointer to QWidget on which entryline is placed
   */
  PasswordEntryLine(QWidget *widget_);

  /**
   * @brief get_status method which returns status of line edit
   * @return enum type Status (Password or Normal)
   */
  Status get_status() const;

  /**
   * @brief set_text_status method which sets mode of text inside line edit
   * @param mode mode of text in line edit
   */
  void set_text_status(Mode mode);
};
