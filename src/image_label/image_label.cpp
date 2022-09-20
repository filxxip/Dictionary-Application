#include "image_label.h"

#include <QDebug>
#include <QPixmap>

ImageLabel::ImageLabel(QWidget *widget_, const QString &source_to_image,
                       Displays::DisplayStyle style, int size)
    : QLabel(widget_), image_source(source_to_image) {
  setObjectName("imagelabel");
  auto pixmap = QPixmap("../" + image_source);
  switch (style) {
  case Displays::DisplayStyle::SCALED_WIDTH: {
    scaled_to(size, Displays::ScaledPossibilities::HEIGHT);
    break;
  }
  case Displays::DisplayStyle::SCALED_HEIGHT: {
    scaled_to(size, Displays::ScaledPossibilities::WIDTH);
    break;
  }
  case Displays::DisplayStyle::CHANGED_WIDTH: {
    set_changable_measure(size, Displays::ScaledPossibilities::WIDTH);
    setPixmap(pixmap);
    break;
  }
  case Displays::DisplayStyle::CHANGED_HEIGHT: {
    set_changable_measure(size, Displays::ScaledPossibilities::HEIGHT);
    setPixmap(pixmap);
    break;
  }
  }
  //  setPixmap(pixmap);
}

void ImageLabel::scaled_to(int size,
                           Displays::ScaledPossibilities scaled_parameter) {
  auto pixmap = QPixmap("../" + image_source);
  switch (scaled_parameter) {
  case Displays::ScaledPossibilities::WIDTH: {
    pixmap = pixmap.scaledToWidth(size);
    break;
  }
  case Displays::ScaledPossibilities::HEIGHT: {
    pixmap = pixmap.scaledToHeight(size);
    break;
  }
  }
  const auto &geo = geometry();
  setGeometry(geo.x(), geo.y(), pixmap.width(), pixmap.height());
  setPixmap(pixmap);
}

void ImageLabel::set_changable_measure(
    int size, Displays::ScaledPossibilities changed_parameter) {
  switch (changed_parameter) {
  case Displays::ScaledPossibilities::WIDTH: {
    setFixedHeight(size);
    break;
  }
  case Displays::ScaledPossibilities::HEIGHT: {
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
