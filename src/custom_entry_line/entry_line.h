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
  /**
   * @brief EntryLine constructor method which creates class instance
   * @param master_ shared pointer to BaseTabWidget class instance on which
   * every widget of app will be placed
   * @param widget_ shared pointer to QWidget on which entryline is placed
   */
  EntryLine(QWidget *widget_);

  /**
   * @brief append_text method which appends text to line edit's current text
   * @param text QString instance which will be added to line edit
   */
  void append_text(const QString &text);
  void set_position(int position_x, int position_y);
};
