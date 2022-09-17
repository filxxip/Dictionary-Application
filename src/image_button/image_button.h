#pragma once

#include <QPushButton>

class ImageButton : public QPushButton {
public:
  /** enum which represents possibilities of positioning button on screen */
  enum class DisplayStyle {
    SCALED_WIDTH,  ///< represent positioning with constant height and with the
                   ///< adjusted width
    SCALED_HEIGHT, ///< represent positioning with constant width and with the
                   ///< adjusted height
    CHANGED_WIDTH, ///< represent positioning with constant height and with the
                   ///< maximum width
    CHANGED_HEIGHT ///< represent positioning with constant widht and with the
                   ///< maximum height
  };

  /** enum which represents two measures of button placed on widget */
  enum class ScaledPossibilities {
    WIDTH, ///< represent widht measure of object
    HEIGHT ///< represent height measure of object
  };
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
              DisplayStyle style, int size);
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

private:
  QString image_source; ///< source to image file from main

  /**
   * @brief scaled_to method which sets width and height of image depe
   * @param size new size of image, second parameter is automatically adjusted
   * to scaled parameter
   * @param scaled_parameter param from with depends if width is auto scaled or
   * height
   */
  void scaled_to(int size, ScaledPossibilities scaled_parameter);

  /**
   * @brief set_changable_measure method which sets constant one measere, second
   * one is changeable
   * @param size new size of constant measure of item
   * @param changed_parameter enum parameter which will be auto adjust to
   * window
   */
  void set_changable_measure(int size, ScaledPossibilities changed_parameter);
};
