#pragma once

#include "../text_label/text_label.h"

#include <QPaintEvent>
#include <QPainter>
#include <QString>
#include <QWidget>

/** VerticalLabel class which is derived class from TextLabel class with
 * vertical text*/
class VerticalLabel : public TextLabel {
public:
  /**
   * @brief VerticalLabel consturctor method
   * @param widget_ widget on which label will be placed
   * @param text_ text on label
   */
  VerticalLabel(QWidget *widget_, const QString &text_);

  /**
   * @brief paintEvent override method which create rotated text
   */
  void paintEvent(QPaintEvent *) final;
};
