#pragma once

#include "../custom_entry_line/entry_line.h"
#include "../custom_vbox_layout/custom_vbox_layout.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../newdict_layout/newdict_layout.h"
#include "../text_label/text_label.h"

#include <QGroupBox>
#include <QLineEdit>
#include <QObject>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <vector>

/** Class which implements Double box for window with each dictionary of user,
 * containt two of them*/
class DoubleGrpBox : public QHBoxLayout {
  Q_OBJECT

private:
  QWidget &widget; ///< reference to main widget
  std::unique_ptr<CustomVBoxLayout>
      left_layout; ///< unique ptr to left custom layout
  std::unique_ptr<CustomVBoxLayout>
      right_layout; ///< unique ptr to right custom layout

  //  /**
  //   * @brief create_edit_trash_layout method which create bottom panel of
  //   layout
  //   * @return pointer to yet created layout
  //   */
  //  QHBoxLayout *create_edit_trash_layout();

public:
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
   * @brief get_dict_layout method which provides last layout of vboxlayout
   * @return pointer to new dictionary layout instance
   */
  NewDictLayout *get_dict_layout();

  /**
   * @brief create_pair mehtod which creates layout
   */
  void create_pair();

  /**
   * @brief get_left_groupbox method which provides left groupbox
   * @return left groupbox of hboxlayout
   */
  const std::unique_ptr<QGroupBox> &get_left_groupbox();

  /**
   * @brief get_left_groupbox method which provides right groupbox
   * @return right groupbox of hboxlayout
   */
  const std::unique_ptr<QGroupBox> &get_right_groupbox();

  /**
   * @brief get_left_groupbox method which provides left layout
   * @return left layout of hboxlayout
   */
  const std::unique_ptr<QVBoxLayout> &get_left_layout();

  /**
   * @brief get_left_groupbox method which provides right layout
   * @return right layout of hboxlayout
   */
  const std::unique_ptr<QVBoxLayout> &get_right_layout();

  /**
   * @brief get_left_groupbox method which provides dictionary of left groupbox
   * @return pointer to dictionary of left groupbox
   */
  Dictionary *get_left_dictionary();

  /**
   * @brief get_left_groupbox method which provides dictionary of right groupbox
   * @return pointer to dictionary of right groupbox
   */
  Dictionary *get_right_dictionary();

  /**
   * @brief get_left_item method which provides unique pointer of left box
   * @return unique pointer of customvboxlayout instance
   */
  const std::unique_ptr<CustomVBoxLayout> &get_left_item();

  /**
   * @brief get_left_item method which provides unique pointer of right box
   * @return unique pointer of customvboxlayout instance
   */
  const std::unique_ptr<CustomVBoxLayout> &get_right_item();

  /**
   * @brief has_dictionary method which checks if doubl
   * @param dict dictionary
   * @return true if doublebox contain dict, otherwise false
   */
  bool has_dictionary(Dictionary *dict);

  /**
   * @brief update_dictionary method which updates data on widget
   * @param dict dict which specifies which box, left or right contain
   * dictionary
   */
  void update_dictionary(Dictionary *dict);

signals:

  /**
   * @brief new_box_signal signal which is emitted when user want to new
   dict
   * @param text name of dictionary
   */
  void new_box_signal(const QString &text);
};
