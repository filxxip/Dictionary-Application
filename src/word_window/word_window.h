#pragma once

#include "../add_new_word/add_new_word.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../index_boxes/double_index_box.h"
#include "../index_boxes/index_box.h"
#include "../swiper/direction_swiper.h"
#include "../swiper/language_swiper.h"
#include "../swiper/sort_swiper.h"
#include "../swiper/swiper.h"
#include "../text_label/text_label.h"
#include "../vertical_label/vertical_label.h"

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
  Dictionary &dictionary;   ///< pointer to dictionary which is on window
  ImageButton close_button; ///< close button which close given
  VerticalLabel title;      ///< vertical label with title of dictionary
  LanguageSwiper from_language; ///< swiper class intance which allows to choose
                                ///< language of word
  LanguageSwiper to_language;   ///< swiper class intance which allows to choose
  ///< language of translation
  SortSwiper sort_swiper;
  DirectionSwiper direction_swiper;
  QScrollArea scrollarea;
  QVBoxLayout mainlayout; ///< main layout on which everything will be placed
  QHBoxLayout high_bar_layout; ///< layout with language bar component
  QHBoxLayout down_bar_layout; ///< layout with words component
  QHBoxLayout down_layout_swiper;
  std::unique_ptr<QGroupBox>
      groupbox; ///< unique pointer to groupbox with dicts
  std::unique_ptr<QVBoxLayout>
      baselayout; ///< unique pointer to base layout with groupbox
  std::vector<std::unique_ptr<IndexBox>>
      current_words; ///< vector with unique pointers to each word translation
                     ///< on widget
  ImageButton new_word_button;

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
  void configurate_swiper(LanguageSwiper *swiper, int position_x,
                          int position_y);

  /**
   * @brief configurate_swiper method which configurate swiper
   * @param swiper swiper to configure
   */
  void configurate_swiper(LanguageSwiper *swiper);
  void configurate_swiper(SortSwiper *swiper);
  void configurate_swiper(DirectionSwiper *swiper);

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

  void sort_layout(SortSwiper::SortOptions option,
                   DirectionSwiper::DirectionsOptions direction);

public:
  /**
   * @brief WordWindow constructor method
   * @param dictionary_ dictionary whose data will be on widget
   */
  WordWindow(Dictionary &dictionary_);

  /**
   * @brief change_title method which changes title of window
   * @param title new title of window
   */
  void change_title(const QString &title);

  /**
   * @brief get_dictionary method which provides dictionary of widget
   * @return pointer to dictionary instance
   */
  Dictionary &get_dictionary();
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

  /**
   * @brief reload method which updates data on widget
   */
  void reload();

  /**
   * @brief add_detail_view method which emit signal which is used to adding new
   * detail view
   * @param word word which data will be on detail view
   * @param language language in which word is defined
   */
  void add_detail_view(Word &word, Word::Language language);

  /**
   * @brief get_tab_title method which provides title of tab
   * @return QString instance with tab title
   */
  QString get_tab_title() const;
signals:

  /**
   * @brief close_signal signal used to close tab window
   * @param widget widget which should be closed
   */
  void close_signal(QWidget *widget);

  void add_detail_view_signal(Dictionary &dict, Word &word,
                              Word::Language language);

  void update_rest_tabs(Dictionary &dict);
  void add_new_word_signal(Word::Language, Dictionary &dictionary);

public slots:
  void update_whole_dictionary();
  void add_new_word();
};
