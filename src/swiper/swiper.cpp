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
      main_label(widget, "NONE") {
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

void Swiper::set_font(int value) { main_label.set_font_size(value); }

void Swiper::swipe_right() {
  left_arrow.setDisabled(false);
  current_index++;
  if (current_index == get_options_size() - 1) {
    right_arrow.setDisabled(true);
  }
  swipe_method();
}

void Swiper::swiper_left() {
  right_arrow.setDisabled(false);
  if (--current_index == 0) {
    left_arrow.setDisabled(true);
  }
  swipe_method();
}

int Swiper::get_index() const { return current_index; }
