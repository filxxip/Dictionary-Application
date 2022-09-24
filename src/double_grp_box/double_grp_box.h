#pragma once

#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"

#include <QGroupBox>
#include <QObject>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <vector>

class DoubleGrpBox : public QHBoxLayout {
  Q_OBJECT
private:
  QWidget &widget;                   ///< reference to main widget
  Dictionary *dictionary1;           ///< pointer to first dicitonary
  Dictionary *dictionary2;           ///< pointer to second dictionary
  std::unique_ptr<QGroupBox> first;  ///< unique pointer to first groupbox
  std::unique_ptr<QGroupBox> second; ///< unique pointer to second groupbox
  std::unique_ptr<QVBoxLayout> first_layout; ///< unique pointer to first layout
  std::unique_ptr<QVBoxLayout>
      second_layout; ///< unique pointer to second layout

public:
  enum class Status { FIRST, SECOND };

  /**
   * @brief DoubleGrpBox constructor method
   * @param widget_ widget on which widget will be placed
   */
  DoubleGrpBox(QWidget &widget_);

  /**
   * @brief DoubleGrpBox constructor method
   * @param widget_ widget on which widget will be placed
   * @param dict1 pointer to dictionary of first element
   * @param dict2 pointer to dictionary of second element
   */
  DoubleGrpBox(QWidget &widget_, Dictionary *dict1, Dictionary *dict2);

  /**
   * @brief DoubleGrpBox constructor method
   * @param widget_ widget on which widget will be placed
   * @param dict1 pointer to dictionary of first element
   */
  DoubleGrpBox(QWidget &widget_, Dictionary *dict1);

  /**
   * @brief create_groupbox method which creates base for groupbox
   * @return unique pointer to groupbox
   */
  std::unique_ptr<QGroupBox> create_groupbox();

  /**
   * @brief create_layout method which creates layout with dictionary data
   * @param dict dict whose data will be shown on widget
   * @return unique pointer to QVBoxlayout instance
   */
  std::unique_ptr<QVBoxLayout> create_layout(Dictionary *dict);

  /**
   * @brief create_new_dict_layout method which create layout for widget which
   * is responsible for adding new dictionary
   * @param align text alignment
   * @return unique pointer to qvboxlayout
   */
  std::unique_ptr<QVBoxLayout> create_new_dict_layout(Qt::Alignment align);

  /**
   * @brief create_pair mehtod which creates layout
   */
  void create_pair();

  /**
   * @brief create_base_label label which creates base for label in widget
   * @param text text which will be shown on label
   * @return pointer to text label
   */
  TextLabel *create_base_label(const QString &text);

  /**
   * @brief get_pointer method which proivdes groupbox from hboxlaout
   * @param status status enum value which decides which groupbox will be
   * returned
   * @return reference to unique pointer to groupbox
   */
  const std::unique_ptr<QGroupBox> &get_pointer(Status status);

  /**
   * @brief get_layout method which proivdes layout from hboxlaout
   * @param status status enum value which decides which layout will be
   * returned
   * @return reference to unique pointer to qvboxlayout
   */
  const std::unique_ptr<QVBoxLayout> &get_layout(Status status);

  /**
   * @brief get_dict method which provides pointer to dictionary
   * @param status status enum value which decides which dictionary will be
   * returned
   * @return pointer to dictioary from hboxlayout
   */
  Dictionary *get_dict(Status status);
signals:

  /**
   * @brief new_box_signal signal which is emitted when user want to new dict
   * @param text name of dictionary
   */
  void new_box_signal(const QString &text);
};
