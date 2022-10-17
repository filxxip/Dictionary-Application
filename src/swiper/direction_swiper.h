#pragma once
#include "swiper.h"

class DirectionSwiper : public Swiper {
  Q_OBJECT
public:
  enum class DirectionsOptions { UP, DOWN };
  std::map<DirectionsOptions, QString> directions = {
      {DirectionsOptions::UP, "sort up"},
      {DirectionsOptions::DOWN, "sort down"}};

private:
  std::vector<DirectionsOptions> options;
  void swipe_method() override;
  int get_options_size() override { return options.size(); }

public:
  /**
   * @brief DirectionSwiper constructor method
   * @param widget_ widget on which swiper will be placed
   * @param label_width width of swiper's main label
   * @param image_size size of arrow
   */
  DirectionSwiper(QWidget *widget_, int label_width, int image_size);

  /**
   * @brief set_text method which sets new option on swiper
   * @param option
   */
  void set_text(DirectionsOptions option);

  /**
   * @brief set_options method which sets options which are used during swiping
   * on widget
   * @param options_ options which user can choose
   */
  void set_options(std::vector<DirectionsOptions> options_);

  /**
   * @brief get_text method which provide current option on swiper
   * @return enum class DirectionsOptions instance
   */
  DirectionsOptions get_text() const;

signals:
  void swipe_signal(DirectionsOptions language);
};
