#pragma once

#include "../custom_entry_line/entry_line.h"

#include <QDebug>
#include <QLabel>

/** Login class which is child of EntryLine class,  */
class LoginLineEntry : public EntryLine {
public:
  /**
   * @brief EntryLine constructor method which creates class instance
   * @param widget_ pointer to QWidget on which entryline is placed
   */
  LoginLineEntry(QWidget *widget_);

  /**
   * @brief get_status method which returns status of line edit
   * @return enum type Status (Password or Normal)
   */
  EntryLine::Status get_status() const;
};
