#include "image_button.h"

#include <QDebug>
#include <QIcon>
#include <QPixmap>

ImageButton ::ImageButton(QWidget *widget_, const QString &source_to_image,
                          Displays::DisplayStyle style, int size)
    : QPushButton(widget_), image_source(source_to_image) {
  setObjectName("imagebutton");
  setFlat(true);
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
    break;
  }
  case Displays::DisplayStyle::CHANGED_HEIGHT: {
    set_changable_measure(size, Displays::ScaledPossibilities::HEIGHT);
    break;
  }
  }
}

void ImageButton::scaled_to(int size,
                            Displays::ScaledPossibilities scaled_parameter) {
  auto pixmap = QPixmap("../" + image_source);
  auto icon = QIcon(pixmap);
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
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); //??
  setGeometry(geo.x(), geo.y(), pixmap.width() - 1, pixmap.height() - 1);
  setIcon(icon);

  setIconSize(pixmap.size());
}

void ImageButton::set_changable_measure(
    int size, Displays::ScaledPossibilities changed_parameter) {
  auto pixmap = QPixmap("../" + image_source);
  auto psize = pixmap.size();
  double ratio = static_cast<double>(psize.width()) / psize.height();
  switch (changed_parameter) {
  case Displays::ScaledPossibilities::WIDTH: {
    setFixedHeight(size);
    setFixedWidth(size * ratio);

    break;
  }
  case Displays::ScaledPossibilities::HEIGHT: {

    setFixedWidth(size);
    setFixedHeight(size / ratio);
    break;
  }
  }
  QIcon icon(pixmap);
  setIcon(icon);
  setIconSize(QSize(width(), height()));
}

void ImageButton::set_position(int position_x, int position_y) {
  setGeometry(position_x, position_y, geometry().width(), geometry().height());
}

const QString &ImageButton::get_image() { return image_source; }

void ImageButton::change_image(const QString &new_path) {
  image_source = new_path;
  auto current_size = size();
  auto new_pixmap = QPixmap("../" + new_path);
  auto new_icon = QIcon(new_pixmap);
  setIcon(new_icon);
  setIconSize(current_size);
}
