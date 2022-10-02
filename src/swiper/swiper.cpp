#include "swiper.h"
#include "../data/config_file.h"

namespace {
constexpr char LEFT_ARROW_IMAGE[] = "images/left_arrow.png";
constexpr char RIGHT_ARROW_IMAGE[] = "images/right_arrow.png";

} // namespace

Swiper::Swiper(QWidget *widget_, int label_width, int image_size)
    : QObject(), widget(widget_),
      left_arrow(widget, LEFT_ARROW_IMAGE,
                 Displays::DisplayStyle::SCALED_HEIGHT, image_size),
      right_arrow(widget, RIGHT_ARROW_IMAGE,
                  Displays::DisplayStyle::SCALED_HEIGHT, image_size),
      main_label(widget, "NONE"), current_language(Word::Language::UNDEFINED) {
  main_label.setFixedWidth(label_width);
  main_label.setFixedHeight(left_arrow.height());
  left_arrow.setDisabled(true);
  right_arrow.setDisabled(true);
  QObject::connect(&left_arrow, &QPushButton::clicked, this,
                   &Swiper::swiper_left);
  QObject::connect(&right_arrow, &QPushButton::clicked, this,
                   &Swiper::swipe_right);
}

QHBoxLayout *Swiper::create_layout() {
  auto layout = new QHBoxLayout;
  layout->setSpacing(0);
  layout->addWidget(&left_arrow);
  layout->addWidget(&main_label);
  layout->addWidget(&right_arrow);
  return layout;
}

void Swiper::set_position(int position_x, int position_y) {
  left_arrow.set_position(position_x, position_y);
  main_label.set_position(position_x + WidgetData::ARROW_SIZE, position_y);
  right_arrow.set_position(
      position_x + (WidgetData::ARROW_SIZE + main_label.width()), position_y);
}

void Swiper::set_options(std::vector<Word::Language> options_) {
  options = std::move(options_);
  current_index = 0;
  set_text(current_language);
  left_arrow.setDisabled(true);
  right_arrow.setDisabled(options.size() == 0);
}

void Swiper::set_font(int value) { main_label.set_font_size(value); }

void Swiper::set_text(Word::Language language) {
  auto content = Word::Language_names.at(language);
  main_label.setText(content);
  current_language = language;
}
Word::Language Swiper::get_text() const { return current_language; }

Word::Language Swiper::get_option(int index) { return options.at(index); }

void Swiper::swipe_right() {
  left_arrow.setDisabled(false);
  current_index++;
  if (static_cast<unsigned long>(current_index) == options.size() - 1) {
    right_arrow.setDisabled(true);
  }
  auto result = options.at(current_index);
  set_text(result);
  emit swipe_signal(result);
}

void Swiper::swiper_left() {
  right_arrow.setDisabled(false);
  if (static_cast<unsigned long>(--current_index) == 0) {
    left_arrow.setDisabled(true);
  }
  auto result = options.at(current_index);
  set_text(result);
  emit swipe_signal(result);
}
