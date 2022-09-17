#pragma once

#include <QPushButton>

class TextButton : public QPushButton {
  Q_OBJECT
public:
  /**
   * @brief TextButton constructor method
   * @param widget_ widget on which button will be placed
   * @param text_ text which appears on button
   */
  TextButton(QWidget *widget_, const QString &text_);
  /**
   * @brief set_font_size method which sets size of text's font on button
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
