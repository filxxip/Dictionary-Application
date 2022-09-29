#pragma once

#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../index_boxes/double_index_box.h"
#include "../index_boxes/index_box.h"
#include "../swiper/swiper.h"
#include "../text_label/text_label.h"
#include "../vertical_label/vertical_label.h"
#include "../word_pair/word_pair.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

#include <memory>

/** Word Window class which is base class used for viewing the wordlist */
class WordWindow : public QObject {
  Q_OBJECT
private:
  QWidget main_widget;      ///< main widget on which everything will be placed
  Dictionary *dictionary;   ///< pointer to dictionary which is on window
  ImageButton close_button; ///< close button which close given
  VerticalLabel title;      ///< vertical label with title of dictionary
  Swiper from_language;     ///< swiper class intance which allows to choose
                            ///< language of word
  Swiper to_language; ///< swiper class intance which allows to choose language
                      ///< of translation
  QScrollArea scrollarea;
  QVBoxLayout mainlayout; ///< main layout on which everything will be placed
  QHBoxLayout high_bar_layout; ///< layout with language bar component
  QHBoxLayout down_bar_layout; ///< layout with words component
  std::unique_ptr<QGroupBox>
      groupbox; ///< unique pointer to groupbox with dicts
  std::unique_ptr<QVBoxLayout>
      baselayout; ///< unique pointer to base layout with groupbox
  std::vector<std::unique_ptr<IndexBox>>
      current_words; ///< vector with unique pointers to each word translation
                     ///< on widget

  /**
   * @brief swiper_connect method which connect swipers with some functions
   */
  void swiper_connect();

  /**
   * @brief close_button_configuration method which add some functionalities to
   * close button
   */
  void close_button_configuration();

  /**
   * @brief configurate_swiper method which configurate swiper and add it to
   * given position
   * @param swiper swiper to configure
   * @param position_x x position of swiper
   * @param position_y y position of swiper
   */
  void configurate_swiper(Swiper *swiper, int position_x, int position_y);

  /**
   * @brief configurate_swiper method which configurate swiper
   * @param swiper swiper to configure
   */
  void configurate_swiper(Swiper *swiper);

  /**
   * @brief create_word_layout method which creates word layout with two entries
   * @param word_base_language language of base word
   * @param word_translation_language language of translated word
   */
  void create_word_layout(Word::Language word_base_language,
                          Word::Language word_translation_language);

  /**
   * @brief create_word_layout method which creates word layout with one entry
   * @param word_base_language language of word
   */
  void create_word_layout(Word::Language word_base_language);

public:
  /**
   * @brief WordWindow constructor method
   * @param dictionary_ dictionary whose data will be on widget
   */
  WordWindow(Dictionary *dictionary_);

  /**
   * @brief get_widget methdo which provides main widget
   * @return pointer to widget where whole data is placed
   */
  QWidget *get_widget();

  /**
   * @brief clear_layout method which clears layouts
   */
  void clear_layout();

  /**
   * @brief set_layout method which set new languages to dictionary
   * @param word_base_language base language
   * @param word_translation_language translated language, if it is not defined,
   * create one entry layout
   */
  void set_layout(Word::Language word_base_language,
                  Word::Language word_translation_language);
signals:

  /**
   * @brief close_signal signal used to close tab window
   * @param widget widget which should be closed
   */
  void close_signal(QWidget *widget);
};
