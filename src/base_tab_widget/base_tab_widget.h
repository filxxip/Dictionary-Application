#pragma once

#include <QApplication>
#include <QTabWidget>

#include <memory>

/** Base tab widget class which shares the possibility of adding and deleting
 * widgets from application */
class BaseTabWidget {
private:
  QApplication *application; ///< main app object
  std::unique_ptr<QTabWidget>
      tab_widget; ///< main tab widget which is used for adding new
                  ///< elements and also removing its from app

public:
  /**
   * @brief BaseTabWidget constructor method
   * @param app QApplication class instance which is base for whole app
   * @param style_name path to styling file from main file
   */
  BaseTabWidget(QApplication *app, const QString &style_name = "");

  /**
   * @brief add_widget method which add widget to tab
   * @param widget pointer to QWidget class instance
   * @param tab_name name of tab which is also the title of widget
   */
  void add_widget(QWidget *widget, const QString &tab_name);

  /**
   * @brief add_widget method which add widget to tab
   * @param widget shared pointer to QWidget class instance
   * @param tab_name name of tab which is also the title of widget
   */
  void add_widget(std::shared_ptr<QWidget> &widget, const QString &tab_name);

  /**
   * @brief delete_widget method which removes tab from tab widget
   * @param widget pointer to widget to remove
   */
  void delete_widget(QWidget *widget);

  /**
   * @brief delete_widget method which removes tab from tab widget
   * @param widget shared pointer to widget to remove
   */
  void delete_widget(const std::shared_ptr<QWidget> &widget);

  /**
   * @brief set_stylesheet method which sets stylesheet for whole app
   * @param style_name path to styling file from main file
   */
  void set_stylesheet(const QString &style_name);

  /**
   * @brief set_widget method which sets widget on active
   * @param widget qwidget instance
   */
  void set_widget(QWidget *widget);

  /**
   * @brief change_name method which changes title of tab
   * @param widget widget which name should be changed
   * @param name new name of widget
   */
  void change_name(QWidget *widget, const QString &name);
};
