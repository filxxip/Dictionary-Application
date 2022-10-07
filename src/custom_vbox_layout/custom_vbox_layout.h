#pragma once

#include "../dictionary/dictionary.h"

#include <QGroupBox>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>

/** CustomVBoxLayout class which is the base class for element of window with
 * each dict of user */
class CustomVBoxLayout : public QObject {
  Q_OBJECT
protected:
  QWidget &widget;                     ///< widget where layout will be placed
  std::unique_ptr<QGroupBox> groupbox; ///< groupbox dictionary data
  std::unique_ptr<QVBoxLayout> layout; ///< layout with every element

  /**
   * @brief create_groupbox method which provides groupbox with basic
   * configuration
   * @return unique pointer to groupbox
   */
  std::unique_ptr<QGroupBox> create_groupbox();

public:
  /**
   * @brief CustomVBoxLayout constructor method
   * @param widget_ widget where layout will be placed
   */
  CustomVBoxLayout(QWidget &widget_);

  /**
   * @brief get_groupbox method which provides groupbox
   * @return constant reference of unique pointer of groupbox
   */
  const std::unique_ptr<QGroupBox> &get_groupbox();

  /**
   * @brief get_layout method which provides layout with dictionary data
   * @return constant unique pointer reference to layout
   */
  const std::unique_ptr<QVBoxLayout> &get_layout();

  /**
   * @brief get_dictionary virtual method which
   * @return poiner to Dictionary which is on layout
   */
  //  virtual Dictionary *get_dictionary() = 0;
  virtual bool has_dictionary() const = 0;
  virtual void update() = 0;
};
