#include "direction_swiper.h"

void DirectionSwiper::swipe_method() {
  auto result = options.at(current_index);
  set_text(result);
  emit swipe_signal(result);
}

void DirectionSwiper::set_text(DirectionsOptions option) {
  auto content = directions.at(option);
  main_label.setText(content);
  //  current_language = language;
}
void DirectionSwiper::set_options(std::vector<DirectionsOptions> options_) {
  options = std::move(options_);
  current_index = 0;
  set_text(DirectionsOptions::UP);
  left_arrow.setDisabled(true);
  right_arrow.setDisabled(options.size() == 0);
}
DirectionSwiper::DirectionsOptions DirectionSwiper::get_text() const {
  return options.at(current_index);
}

DirectionSwiper::DirectionSwiper(QWidget *widget_, int label_width,
                                 int image_size)
    : Swiper(widget_, label_width, image_size) {}
