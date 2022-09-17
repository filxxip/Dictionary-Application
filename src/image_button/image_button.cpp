#include "image_button.h"

#include <QDebug>
#include <QIcon>
#include <QPixmap>

ImageButton ::ImageButton(QWidget *widget_, const QString &source_to_image,
                          DisplayStyle style, int size)
    : QPushButton(widget_), image_source(source_to_image) {
  qDebug() << "constructor";
  setObjectName("ImageButton");
  auto icon = QIcon("../" + image_source);
  switch (style) {
  case ImageButton::DisplayStyle::SCALED_WIDTH: {
    scaled_to(size, ScaledPossibilities::HEIGHT);
    break;
  }
  case ImageButton::DisplayStyle::SCALED_HEIGHT: {
    scaled_to(size, ScaledPossibilities::WIDTH);
    break;
  }
  case ImageButton::DisplayStyle::CHANGED_WIDTH: {
    set_changable_measure(size, ScaledPossibilities::WIDTH);
    break;
  }
  case ImageButton::DisplayStyle::CHANGED_HEIGHT: {
    set_changable_measure(size, ScaledPossibilities::HEIGHT);
    break;
  }
  }
  setIcon(icon);
}

void ImageButton::scaled_to(int size,
                            ImageButton::ScaledPossibilities scaled_parameter) {
  auto pixmap = QPixmap("../" + image_source);
  switch (scaled_parameter) {
  case ImageButton::ScaledPossibilities::WIDTH: {
    pixmap = pixmap.scaledToWidth(size);
    break;
  }
  case ImageButton::ScaledPossibilities::HEIGHT: {
    pixmap = pixmap.scaledToHeight(size);
    break;
  }
  }
  const auto &geo = geometry();
  setGeometry(geo.x(), geo.y(), pixmap.width(), pixmap.height());
}

void ImageButton::set_changable_measure(int size,
                                        ScaledPossibilities changed_parameter) {
  qDebug() << "hello" << width();
  double ratio = width() / height();
  qDebug() << ratio;
  switch (changed_parameter) {
  case ImageButton::ScaledPossibilities::WIDTH: {
    setFixedHeight(size);
    setFixedWidth(height() * ratio);

    break;
  }
  case ImageButton::ScaledPossibilities::HEIGHT: {

    setFixedWidth(size);
    setFixedHeight(width() / ratio);
    break;
  }
  }
  //  setScaledContents(true);
}

void ImageButton::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}

const QString &ImageButton::get_image() { return image_source; }
