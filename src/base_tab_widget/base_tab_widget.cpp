#include "base_tab_widget.h"
#include "../data/config_file.h"

#include <QDebug>
#include <QFile>

BaseTabWidget::BaseTabWidget(QApplication *app, const QString &style_name)
    : application(app), tab_widget(std::make_unique<QTabWidget>()) {
  tab_widget->setGeometry(WidgetData::TAB_WIDGET_POSITION);
  tab_widget->show();
  if (!style_name.isEmpty()) {
    set_stylesheet("../" + style_name);
  }
}

void BaseTabWidget::add_widget(std::shared_ptr<QWidget> &widget,
                               const QString &tab_name) {
  tab_widget->addTab(widget.get(), tab_name);
}

void BaseTabWidget::add_widget(QWidget *widget, const QString &tab_name) {
  tab_widget->addTab(widget, tab_name);
}

void BaseTabWidget::delete_widget(QWidget *widget) {
  auto index = tab_widget->indexOf(widget);
  tab_widget->removeTab(index);
}

void BaseTabWidget::delete_widget(const std::shared_ptr<QWidget> &widget) {
  auto index = tab_widget->indexOf(widget.get());
  tab_widget->removeTab(index);
}

void BaseTabWidget::set_stylesheet(const QString &style_name) {
  QFile file(style_name);
  file.open(QFile::ReadOnly);
  QString stylesheet = QString(file.readAll());
  application->setStyleSheet(stylesheet);
  file.close();
}

void BaseTabWidget::set_widget(QWidget *widget) {
  tab_widget->setCurrentWidget(widget);
}

void BaseTabWidget::change_name(QWidget *widget, const QString &name) {
  auto index = tab_widget->indexOf(widget);
  tab_widget->setTabText(index, name);
}
