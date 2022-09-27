#pragma once

#include "../content_layout/content_layout.h"
#include "../dictionary/dictionary.h"
#include "../double_grp_box/double_grp_box.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"

#include <QGroupBox>
#include <QObject>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>
#include <vector>

class WordlistWindow : public QObject {
  Q_OBJECT

private:
  QString owner;
  QWidget main_widget;     ///< main widget on which everything will be placed
  ImageButton exit_button; ///< button which is responsible for logging out
  ImageLabel main_label;   ///< main label with title image
  QScrollArea scrollarea;  ///< scrollarea with some dictionaries
  std::unique_ptr<QGroupBox> groupbox;     ///< pointer to groupbox with dicts
  QVBoxLayout mainlayout;                  ///< main layout with some widgets
  std::unique_ptr<QVBoxLayout> baselayout; ///< base layout with groupbox
  std::vector<Dictionary *> dict; ///< vecotr with pointers to user dictionaries
  std::vector<std::unique_ptr<DoubleGrpBox>>
      groupbox_dict; ///< dictionary with pair of groupbox

  /**
   * @brief connect_doublebox method which connect doublebox with removing
   * functions
   * @param box box to connect
   */
  void connect_doublebox(DoubleGrpBox *box);

public:
  /**
   * @brief setting_scroll_options method which sets some options of scrollbar
   */
  void setting_scroll_options();

  /**
   * @brief add_groupbox method which add new groupbox to window
   * @param dict dict which will be represented by groupbox
   */
  void add_groupbox(Dictionary *dict);

  /**
   * @brief WordlistWindow constructor method
   */
  WordlistWindow();

  /**
   * @brief get_widget method which provides main widget instance
   * @return pointer to qWidget instance
   */
  QWidget *get_widget();

  /**
   * @brief get_exit_button method which provides exit button
   * @return reference to exit button
   */
  ImageButton &get_exit_button();

  /**
   * @brief set_dict method which set new user on widget
   * @param person_mail mail of person whose dict is set
   * @param dictionary vector with user's dictionaries
   */
  void set_dict(const QString &person_mail,
                std::vector<Dictionary *> dictionary);

public slots:

  /**
   * @brief method which runs after clicking set button
   */
  void method() { qDebug() << "kliknietp"; }

signals:
  /**
   * @brief new_dict_signal signal which is emitted when user want to create new
   * dictionary
   * @param name name of dictionary
   * @param email email of user
   */
  void new_dict_signal(const QString &name, const QString &email);

  /**
   * @brief removing_dict_signal signal used to removing dictionary from list
   * @param dict poitner to dictionary to remove
   * @param email given person whose dict is removed
   */
  void removing_dict_signal(Dictionary *dict, const QString &email);
};
