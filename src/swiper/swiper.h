#pragma once
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

#include <memory>
#include <vector>

#include <QHBoxLayout>
#include <QPoint>
#include <QString>

/** Swiper class which give user possibility of choosing an option and apply
 * some advantages on widget*/
class Swiper : public QObject {
  Q_OBJECT
private:
  QWidget *widget; ///*widget on which swiper will be placed
  QPoint position; /// position of swiper

protected:
  ImageButton left_arrow;  ///< left arrow of swiper
  ImageButton right_arrow; ///< right arrow of swiper
  TextLabel main_label;    ///< main label of swiper with some text
  int current_index = 0;   ///< current index of swiper's data

  /**
   * @brief set_text method which sets new text on widget
   * @param index index of text which should be shown on label
   */
  void set_text(int index);
  virtual int get_options_size() = 0;

public:
  /**
   * @brief Swiper constructor method
   * @param widget_ widget on which swiper will be placed
   * @param label_width width of swiper's main label
   * @param image_size size of arrow
   */
  Swiper(QWidget *widget_, int label_width, int image_size);

  /**
   * @brief set_position method which sets new position of swiper
   * @param position_x position x of swiper
   * @param position_y postion y of swiper
   */
  void set_position(int position_x, int position_y);

  /**
   * @brief set_font method which sets size of font on label
   * @param value new value of font size
   */
  void set_font(int value);

  /**
   * @brief get_index method which provides current index of widget
   * @return current index of swiper data
   */
  int get_index() const;

  /**
   * @brief create_layout method which provides layout with swiper items
   * @return pointer to created layout object
   */
  QHBoxLayout *create_layout();
  virtual void swipe_method() = 0;

public slots:
  /**
   * @brief swiper_left slot used when left button is pressed
   */
  void swiper_left();
  /**
   * @brief swiper_left slot used when right button is pressed
   */
  void swipe_right();
};
