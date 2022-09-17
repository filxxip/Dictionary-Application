#include "custom_widget.h"

CustomWidget::CustomWidget(std::shared_ptr<BaseTabWidget> master_,
                           std::shared_ptr<QWidget> widget_)
    : widget(widget_), master(master_) {
  main_widget->setParent(widget.get());
}

void CustomWidget::set_geometry(const QRect &rect) {
  main_widget->setGeometry(rect);
}

void CustomWidget::set_margins(const QMargins &margins) {
  main_widget->setContentsMargins(margins);
}

QRect CustomWidget::get_geometry() const { return main_widget->geometry(); }

QMargins CustomWidget::get_margins() const {
  return main_widget->contentsMargins();
}

void CustomWidget::set_object_name(const QString &object_name) {
  main_widget->setObjectName(object_name);
}

QString CustomWidget::get_object_name() const {
  return main_widget->objectName();
}

void CustomWidget::set_height(int height) {
  main_widget->setFixedHeight(height);
}

void CustomWidget::set_width(int width) { main_widget->setFixedWidth(width); }
