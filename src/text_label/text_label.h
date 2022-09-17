#pragma once

#include <QLabel>

class TextLabel : public QLabel {
public:
  /**
   * @brief TextLabel constructor method which creates class instance
   * @param widget_ pointer to QWidget on which main_widget is placed
   * @param text_ text which will be placed on label
   */
  TextLabel(QWidget *widget_, const QString &text_);

  /**
   * @brief set_font_size method which sets size of text's font on label
   * @param size new size of font
   */
  void set_font_size(int size);

  /**
   * @brief set_position method which sets new position of label with text
   * @param position_x x position of label
   * @param position_y y position of label
   */
  void set_position(int position_x, int position_y);
};
