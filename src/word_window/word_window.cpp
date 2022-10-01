#include "word_window.h"
#include "../data/config_file.h"
#include "../detail_view/detail_view.h"
#include "../index_boxes/once_index_box.h"
#include "../swiper/swiper.h"
#include "../translation/translation.h"
#include "../word_pair/word_pair.h"

#include <QFontMetrics>
#include <QPainter>
#include <QScrollBar>

namespace {
constexpr char IMAGE_EXIT[] = "images/exit2.png";
} // namespace

WordWindow::WordWindow(Dictionary *dictionary_)
    : QObject(), dictionary(dictionary_),
      close_button(&main_widget, IMAGE_EXIT,
                   Displays::DisplayStyle::SCALED_WIDTH,
                   WidgetData::EXIT_HEIGHT),
      title(&main_widget, dictionary->get_name()),
      from_language(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                    WidgetData::ARROW_SIZE),
      to_language(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                  WidgetData::ARROW_SIZE),
      scrollarea(&main_widget), groupbox(std::make_unique<QGroupBox>()),
      baselayout(std::make_unique<QVBoxLayout>()) {

  scrollarea.setWidgetResizable(true);
  scrollarea.horizontalScrollBar()->setDisabled(true);
  scrollarea.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
  scrollarea.setWidget(groupbox.get());
  scrollarea.setHorizontalScrollBarPolicy(
      Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

  title.setFixedWidth(WidgetData::TITLE_WIDTH);
  high_bar_layout.addLayout(from_language.create_layout());
  high_bar_layout.addLayout(to_language.create_layout());
  high_bar_layout.setContentsMargins(WidgetData::WORD_WINDOW_HIGHBAR_LAYOUT);
  mainlayout.addLayout(&high_bar_layout);

  down_bar_layout.addWidget(&title);
  down_bar_layout.addWidget(&scrollarea);
  down_bar_layout.setSpacing(WidgetData::WORD_WINDOW_DOWN_LAYOUT_SPACING);
  mainlayout.addLayout(&down_bar_layout);

  main_widget.setLayout(&mainlayout);
  mainlayout.setContentsMargins(WidgetData::WORD_WINDOW_MAIN_LAYOUT_MARGINS);
  mainlayout.setSpacing(WidgetData::WORD_WINDOW_MAIN_LAYOUT_SPACING);

  configurate_swiper(&to_language);
  configurate_swiper(&from_language);

  close_button_configuration();
  swiper_connect();
}

Dictionary *WordWindow::get_dictionary() { return dictionary; }

void WordWindow::swiper_connect() {
  QObject::connect(&from_language, &Swiper::swipe_signal, this,
                   [this](Word::Language language) {
                     auto translation_language = to_language.get_text();
                     set_layout(language, translation_language);
                   });
  QObject::connect(&to_language, &Swiper::swipe_signal, this,
                   [this](Word::Language language) {
                     auto base_language = from_language.get_text();
                     set_layout(base_language, language);
                   });
}

void WordWindow::set_layout(Word::Language word_base_language,
                            Word::Language word_translation_language) {
  clear_layout();
  try {
    Word::is_language_valid(word_base_language);
    try {
      Word::is_language_valid(word_translation_language);
      if (word_base_language != word_translation_language) {
        create_word_layout(word_base_language, word_translation_language);
      } else {
        create_word_layout(word_base_language);
      }
    } catch (std::invalid_argument &) {
      create_word_layout(word_base_language);
    }
  } catch (std::invalid_argument &) {
    return;
  }
}

void WordWindow::change_title(const QString &new_title) {
  title.setText(new_title);
}

void WordWindow::create_word_layout(Word::Language word_base_language) {
  int index = 0;
  auto list_of_translations =
      dictionary->get_specific_words(word_base_language);
  for (auto &x : list_of_translations) {
    index++;
    auto lay = std::make_unique<OnceIndexBox>(
        &main_widget, dictionary->get_word(x), QString::number(index),
        word_base_language);
    baselayout->addLayout(lay.get());
    current_words.push_back(std::move(lay));
  }
  groupbox->setLayout(baselayout.get());
  for (auto &x : current_words) {
    QObject::connect(x.get(), &IndexBox::creating_detail_view, this,
                     &WordWindow::add_detail_view);
  }
}

void WordWindow::add_detail_view(Word &word, Word::Language language) {
  emit add_detail_view_signal(dictionary, word, language);
}

void WordWindow::create_word_layout(Word::Language word_base_language,
                                    Word::Language word_translation_language) {
  clear_layout();
  int index = 0;
  auto list_of_translations = dictionary->get_specific_translations(
      word_base_language, word_translation_language);
  for (auto &x : list_of_translations) {
    index++;
    auto lay = std::make_unique<DoubleIndexBox>(
        &main_widget, dictionary->get_word(x), QString::number(index),
        word_base_language, word_translation_language);
    baselayout->addLayout(lay.get());
    current_words.push_back(std::move(lay));
  }
  groupbox->setLayout(baselayout.get());
  for (auto &x : current_words) {
    QObject::connect(x.get(), &IndexBox::update_window, this,
                     &WordWindow::update_dictionary);
  }
}

QWidget *WordWindow::get_widget() { return &main_widget; }

void WordWindow::close_button_configuration() {
  close_button.set_position(WidgetData::EXIT_POSITION_X,
                            WidgetData::EXIT_POSITION_Y);
  QObject::connect(&close_button, &QPushButton::clicked, this,
                   [this]() { emit close_signal(&main_widget); });
}

void WordWindow::configurate_swiper(Swiper *swiper) {
  auto opt = Word::Language_names;
  std::vector<Word::Language> v;
  for (auto &[lang, string] : opt) {
    v.push_back(lang);
  }

  swiper->set_options(std::move(v));
  swiper->set_font(WidgetData::FONT_SIZE_SWIPER);
}

void WordWindow::configurate_swiper(Swiper *swiper, int position_x,
                                    int position_y) {
  configurate_swiper(swiper);
  swiper->set_position(position_x, position_y);
}

void WordWindow::clear_layout() { current_words.clear(); }

void WordWindow::update_dictionary() {
  auto base_language = from_language.get_text();
  auto translated_language = to_language.get_text();
  set_layout(base_language, translated_language);
  emit update_rest_tabs(dictionary);
}

void WordWindow::reload() {
  auto base_language = from_language.get_text();
  auto translation_language = to_language.get_text();
  create_word_layout(base_language, translation_language);
}
