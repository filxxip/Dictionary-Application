#include "language_swiper.h"

void LanguageSwiper::swipe_method() {
  auto result = options.at(current_index);
  set_text(result);
  emit swipe_signal(result);
}

void LanguageSwiper::set_text(Word::Language language) {
  auto content = Word::Language_names.at(language);
  main_label.setText(content);
  //  current_language = language;
}
void LanguageSwiper::set_options(std::vector<Word::Language> options_) {
  options = std::move(options_);
  current_index = 0;
  set_text(Word::Language::UNDEFINED);
  left_arrow.setDisabled(true);
  right_arrow.setDisabled(options.size() == 0);
}
Word::Language LanguageSwiper::get_text() const {
  return options.at(current_index);
}

LanguageSwiper::LanguageSwiper(QWidget *widget_, int label_width,
                               int image_size)
    : Swiper(widget_, label_width, image_size) {}
