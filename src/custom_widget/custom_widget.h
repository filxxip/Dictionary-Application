#pragma once

#include "../base_tab_widget/base_tab_widget.h"

#include <QLineEdit>
#include <QMargins>
#include <QRect>
#include <QString>
#include <QWidget>

#include <memory>

/**
 * @brief The CustomWidget class which determines basic widget in app
 * inside it
 */
class CustomWidget : public QObject {
protected:
  std::unique_ptr<QWidget>
      main_widget; ///< QWidget instance which is base for whole class
private:
  std::shared_ptr<QWidget>
      widget; ///< shared pointer to QWidget on which entryline is placed
  std::shared_ptr<BaseTabWidget>
      master; ///< shared pointer to BaseTabWidget class instance on which every
              ///< widget of app is placed

public:
  enum class Status { PASSWORD, NORMAL };
  /**
   * @brief CustomWidget constructor method which creates class instance
   * @param master_ shared pointer to BaseTabWidget class instance on which
   * every widget of app will be placed
   * @param widget_ shared pointer to QWidget on which main_widget is placed
   */
  CustomWidget(std::shared_ptr<BaseTabWidget> master_,
               std::shared_ptr<QWidget> widget_);

  /**
   * @brief ~EntryLine destructor
   */
  virtual ~CustomWidget() = default;
  /**
   * @brief set_geometry method sets new position and measures of main_widget
   * @param rect QRect which determines position and measures
   */
  void set_geometry(const QRect &rect);

  /**
   * @brief set_text method which sets new text on main_widget
   * @param text QString instance which will be set on lineedit
   */
  void set_text(const QString &text);

  /**
   * @brief set_margins method which sets new margins of main_widget
   * @param margins QMargins instance which will be new margins of main_widget
   */
  void set_margins(const QMargins &margins);

  /**
   * @brief set_object_name method which sets new object name of main_widget,
   * always used to ascribe stylesheet of object
   * @param object_name new object name of main_widget
   */
  void set_object_name(const QString &object_name);

  /**
   * @brief get_object_name method which provides object name of main_widget,
   * used during ascribing its stylesheet
   * @return QString class instance with object name
   */
  QString get_object_name() const;

  /**
   * @brief get_geometry method which porvides geometry of main_widget
   * @return constant QRect reference to line edit geometry
   */
  QRect get_geometry() const;

  /**
   * @brief get_margins method which provides margins of main_widget
   * @return constant QMargins reference to margins of main_widget
   */
  QMargins get_margins() const;

  /**
   * @brief set_width method which sets width of main_widget
   * @param width new width of main_widget
   */
  void set_width(int width);

  /**
   * @brief set_height method which sets new height of main_widget
   * @param height new height of main_widget
   */
  void set_height(int height);
  /**
   * @brief get_text method which provides text from mainwidget
   * @return text on widget
   */
  virtual QString get_text() = 0;
};
