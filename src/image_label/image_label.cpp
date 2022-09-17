#include "image_label.h"

#include <QDebug>
#include <QPixmap>

ImageLabel::ImageLabel(QWidget *widget_, const QString &source_to_image,
                       DisplayStyle style, int size)
    : QLabel(widget_), image_source(source_to_image) {
  setObjectName("imagelabel");
  auto pixmap = QPixmap("../" + image_source);
  switch (style) {
  case ImageLabel::DisplayStyle::SCALED_WIDTH: {
    scaled_to(size, ScaledPossibilities::HEIGHT);
    break;
  }
  case ImageLabel::DisplayStyle::SCALED_HEIGHT: {
    scaled_to(size, ScaledPossibilities::WIDTH);
    break;
  }
  case ImageLabel::DisplayStyle::CHANGED_WIDTH: {
    set_changable_measure(size, ScaledPossibilities::WIDTH);
    break;
  }
  case ImageLabel::DisplayStyle::CHANGED_HEIGHT: {
    set_changable_measure(size, ScaledPossibilities::HEIGHT);
    break;
  }
  }
  setPixmap(pixmap);
}

void ImageLabel::scaled_to(int size,
                           ImageLabel::ScaledPossibilities scaled_parameter) {
  auto pixmap = QPixmap("../" + image_source);
  switch (scaled_parameter) {
  case ImageLabel::ScaledPossibilities::WIDTH: {
    pixmap = pixmap.scaledToWidth(size);
    break;
  }
  case ImageLabel::ScaledPossibilities::HEIGHT: {
    pixmap = pixmap.scaledToHeight(size);
    break;
  }
  }
  const auto &geo = geometry();
  setGeometry(geo.x(), geo.y(), pixmap.width(), pixmap.height());
}

void ImageLabel::set_changable_measure(int size,
                                       ScaledPossibilities changed_parameter) {
  switch (changed_parameter) {
  case ImageLabel::ScaledPossibilities::WIDTH: {
    setFixedHeight(size);
    break;
  }
  case ImageLabel::ScaledPossibilities::HEIGHT: {
    setFixedWidth(size);
    break;
  }
  }
  setScaledContents(true);
}

void ImageLabel::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}

const QString &ImageLabel::get_image() { return image_source; }
