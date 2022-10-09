#pragma once

#include <QHBoxLayout>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include <map>
#include <memory>
#include <vector>

#include "../change_color/change_color.h"
#include "../config_detail_view_panel/config_detail_view_panel.h"
#include "../custom_entry_line/entry_line.h"
#include "../custom_label_entry_box/custom_label_entry_box.h"
#include "../dictionary/dictionary.h"
#include "../image_button/image_button.h"
#include "../image_label/image_label.h"
#include "../swiper/swiper.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

class AddNewWord : public QObject {
  Q_OBJECT
private:
  QWidget main_window;
  Dictionary &dict;
  QVBoxLayout main_layout;
  ImageLabel title_image;
  std::map<Word::Language, std::unique_ptr<LabelEntryBox>> language_panels;
  CustomizeImageButton confirm_button;
  CustomizeImageButton cancel_button;
  CustomizeImageButton clear_button;
  Word::Language main_language;

  void create_config_panel_layout();
  void create_entryboxes();
  void create_single_entrybox(int height, Word::Language language);

public:
  AddNewWord(Word::Language main_language_, Dictionary &dictionary);
  QWidget *get_widget();
  Dictionary &get_dictionary();

  std::map<Word::Language, QString> get_defined_translations() const;
  void clear();

public slots:
  void add_new_word();

signals:
  void add_new_word_signal(Dictionary &dict);
  void exit_signal(QWidget *widget);
};
