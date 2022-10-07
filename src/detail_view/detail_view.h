#pragma once

#include <QVBoxLayout>
#include <QWidget>

#include "../config_detail_view_panel/config_detail_view_panel.h"
#include "../detail_view_one_language_layout/detail_view_one_language_layout.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../image_label/image_label.h"
#include "../translation/translation.h"

#include <memory>
#include <vector>

/** DetailView class which is base class for viewing whole word data*/
class DetailView : public QObject {
  Q_OBJECT
private:
  Dictionary &dictionary;  ///< dictionary which contains word
  QWidget main_widget;     ///< widget on which class intance is placed
  ImageButton exit_button; ///< exit button to close tab
  QVBoxLayout main_layout; ///< main layout on which every component is placed
  TextLabel dictionary_title; ///< label with title of dictionary
  ImageLabel title_label;     ///< label with title of app
  std::vector<std::unique_ptr<DetailViewOneLanguageLayout>>
      language_detail_panels; ///< vector with every language layout
  ConfigDetailViewPanel edit_panel;
  Word &word; ///< word reference whose data is on window
  Word::Language base_language;

  /**
   * @brief create_dictionary_title method which add some basic configuration to
   * create title box
   */
  void create_dictionary_title();

public:
  /**
   * @brief DetailView constructor method
   * @param word_ word whose data is on widget
   * @param dictionary_ dictionary for which word belongs
   */
  DetailView(Word &word_, Dictionary &dictionary_,
             Word::Language base_language_);

  /**
   * @brief get_widget method which provides main widget
   * @return pointer to main widget
   */
  QWidget *get_widget();

  /**
   * @brief update method which updates whole view
   */
  void update();

  /**
   * @brief get_dictionary method which provides dictionary of word
   * @return const pointer to dictionary
   */
  Dictionary &get_dictionary() const;

  /**
   * @brief get_tab_title method which provides title of tab
   * @return QString instance with tab title
   */
  QString get_tab_title() const;

  /**
   * @brief update_title method which updates title of detail view
   */
  void update_title();

  /**
   * @brief get_word method which provides reference to word
   * @return reference of word whose data is on widget
   */
  Word &get_word();
signals:

  /**
   * @brief close_window_signal signal used during closing window
   * @param widget widget which will be closed
   */
  void close_window_signal(QWidget *widget);

  /**
   * @brief update_rest_dicts_signal signal used to updating every dict tab
   * @param dict constant pointer to dict
   */
  void update_rest_dicts_signal(Dictionary &dict);

  void delete_window_signal(Word &word, Dictionary &dict);
};
