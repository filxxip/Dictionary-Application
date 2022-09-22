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

class WordlistWindow : public QObject {
  Q_OBJECT

private:
  QWidget main_widget;     ///< main widget on which everything will be placed
  ImageButton exit_button; ///< button which is responsible for logging out
  ImageLabel main_label;   ///< main label with title image
  QScrollArea scrollarea;  ///< scrollarea with some dictionaries
  std::unique_ptr<QGroupBox> groupbox;     ///< pointer to groupbox with dicts
  QVBoxLayout mainlayout;                  ///< main layout with some widgets
  std::unique_ptr<QVBoxLayout> baselayout; ///< base layout with groupbox
  std::vector<Dictionary *> dict; ///< vecotr with pointers to user dictionaries

  /**
   * @brief create_groupbox method which create groupbox with one dictionary
   * @param dict dict whose data will be placed on groupbox
   * @return  pointer to groupbox
   */
  QGroupBox *create_groupbox(Dictionary *dict);

  /**
   * @brief create_pair method which creates pair of two groupbox, combines them
   * in one layout
   * @param first left groupbox of layout
   * @param second right groupbox of layout
   * @return pointer to layout
   */
  QHBoxLayout *create_pair(QGroupBox *first, QGroupBox *second = nullptr);

  /**
   * @brief setting_scroll_options method which sets some options of scrollbar
   */
  void setting_scroll_options();

  /**
   * @brief create_base_groupbox method which creates some basic functionalities
   * for groupbox
   * @return pointer to groupbox
   */
  QGroupBox *create_base_groupbox();

  /**
   * @brief create_new_dict_groupbox method which creates groupbox for adding
   * new dictionary
   * @return pointer to groupbox
   */
  QGroupBox *create_new_dict_groupbox();

  /**
   * @brief create_base_label method which creates base for every groupbox with
   * some text
   * @param text text on label
   * @return pointer to text label
   */
  TextLabel *create_base_label(const QString &text);

public:
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
   * @param dictionary vector with user's dictionaries
   */
  void set_dict(std::vector<Dictionary *> dictionary);

public slots:

  /**
   * @brief method which runs after clicking set button
   */
  void method() { qDebug() << "kliknietp"; }
};
