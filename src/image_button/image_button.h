#pragma once

#include "../image_label/image_label.h"

#include <QPushButton>

class ImageButton : public QPushButton {
public:
  /**
   * @brief ImageButton constructor method which creates class instance, use
   * width to specife size of item
   * @param widget_ pointer to QWidget on which main_widget is placed
   * @param source_to_image path to image file from main file
   * @param style enum value which specified style of positioning widget on
   * screen
   * @param size new value size of image, its meaning depends on style parameter
   */
  ImageButton(QWidget *widget_, const QString &source_to_image,
              Displays::DisplayStyle style, int size);
  /**
   * @brief get_image method which provides path to image
   * @return QString class instance determines path to image
   */
  const QString &get_image();

  /**
   * @brief set_image method which sets image to button
   * @param source_to_image source path to image
   * @param width new width of image, height is automatically adjusted
   */
  void set_image(const QString &source_to_image, int width = 0);

  /**
   * @brief set_position method which sets new position of button with img
   * @param position_x x position of button
   * @param position_y y position of button
   */
  void set_position(int position_x, int position_y);

  /**
   * @brief change_image method which changes image to another one ( with same
   * width and height)
   * @param new_path new qstring instance with path to image from main file
   */
  void change_image(const QString &new_path);

private:
  QString image_source; ///< source to image file from main

  /**
   * @brief scaled_to method which sets width and height of image depe
   * @param size new size of image, second parameter is automatically adjusted
   * to scaled parameter
   * @param scaled_parameter param from with depends if width is auto scaled or
   * height
   */
  void scaled_to(int size, Displays::ScaledPossibilities scaled_parameter);

  /**
   * @brief set_changable_measure method which sets constant one measere, second
   * one is changeable
   * @param size new size of constant measure of item
   * @param changed_parameter enum parameter which will be auto adjust to
   * window
   */
  void set_changable_measure(int size,
                             Displays::ScaledPossibilities changed_parameter);
};
