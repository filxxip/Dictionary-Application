#include "sort_swiper.h"

void SortSwiper::swipe_method() {
  auto result = options.at(current_index);
  set_text(result);
  emit swipe_signal(result);
}

void SortSwiper::set_text(SortOptions option) {
  auto content = sort_names.at(option);
  main_label.setText(content);
  //  current_language = language;
}
void SortSwiper::set_options(std::vector<SortOptions> options_) {
  options = std::move(options_);
  current_index = 0;
  set_text(SortOptions::NUMERIC);
  left_arrow.setDisabled(true);
  right_arrow.setDisabled(options.size() == 0);
}
SortSwiper::SortOptions SortSwiper::get_text() const {
  return options.at(current_index);
}

SortSwiper::SortSwiper(QWidget *widget_, int label_width, int image_size)
    : Swiper(widget_, label_width, image_size) {}
