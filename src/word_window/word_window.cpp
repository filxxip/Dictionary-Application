#include "word_window.h"
#include "../add_new_word/add_new_word.h"
#include "../data/config_file.h"
#include "../detail_view/detail_view.h"
#include "../index_boxes/once_index_box.h"
#include "../swiper/swiper.h"
#include "../translation/translation.h"

#include <QFontMetrics>
#include <QPainter>
#include <QScrollBar>

namespace {
constexpr char IMAGE_EXIT[] = "images/exit2.png";
constexpr char NEW_WORD_IMAGE[] = "images/add.png";
} // namespace

WordWindow::WordWindow(Dictionary &dictionary_)
    : QObject(), dictionary(dictionary_),
      close_button(&main_widget, IMAGE_EXIT,
                   Displays::DisplayStyle::SCALED_WIDTH,
                   WidgetData::EXIT_HEIGHT),
      title(&main_widget, dictionary.get_name()),
      from_language(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                    WidgetData::ARROW_SIZE),
      to_language(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                  WidgetData::ARROW_SIZE),
      sort_swiper(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                  WidgetData::ARROW_SIZE),
      direction_swiper(&main_widget, WidgetData::LABEL_WIDTH_SWIPER,
                       WidgetData::ARROW_SIZE),
      scrollarea(&main_widget), groupbox(std::make_unique<QGroupBox>()),
      baselayout(std::make_unique<QVBoxLayout>()),
      new_word_button(&main_widget, NEW_WORD_IMAGE,
                      Displays::DisplayStyle::SCALED_WIDTH,
                      WidgetData::NEW_WORD_HEIGHT) {
  new_word_button.set_position(WidgetData::NEW_WORD_X, WidgetData::NEW_WORD_Y);
  QObject::connect(&new_word_button, &QPushButton::clicked, this,
                   &WordWindow::add_new_word);
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
  configurate_swiper(&sort_swiper);
  configurate_swiper(&direction_swiper);

  down_layout_swiper.setContentsMargins(100, 0, 0, 0);
  mainlayout.addLayout(&down_layout_swiper);

  //  mainlayout.addLayout(sort_swiper.create_layout());

  close_button_configuration();
  swiper_connect();
}

Dictionary &WordWindow::get_dictionary() { return dictionary; }

void WordWindow::swiper_connect() {
  QObject::connect(&from_language, &LanguageSwiper::swipe_signal, this,
                   [this](Word::Language language) {
                     auto translation_language = to_language.get_text();
                     set_layout(language, translation_language);
                   });
  QObject::connect(&to_language, &LanguageSwiper::swipe_signal, this,
                   [this](Word::Language language) {
                     auto base_language = from_language.get_text();
                     set_layout(base_language, language);
                   });
  QObject::connect(&sort_swiper, &SortSwiper::swipe_signal, this,
                   [this](auto option) {
                     sort_layout(option, direction_swiper.get_text());
                   });
  QObject::connect(
      &direction_swiper, &DirectionSwiper::swipe_signal, this,
      [this](auto option) { sort_layout(sort_swiper.get_text(), option); });
}

void WordWindow::set_layout(Word::Language word_base_language,
                            Word::Language word_translation_language) {
  clear_layout();
  try {
    Word::is_language_valid(word_base_language);
  } catch (std::invalid_argument &) {
    return;
  }

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
  sort_layout(sort_swiper.get_text(), direction_swiper.get_text());
}

void WordWindow::change_title(const QString &new_title) {
  title.setText(new_title);
}

void WordWindow::create_word_layout(Word::Language word_base_language) {
  int index = 0;
  auto list_of_translations = dictionary.get_specific_words(word_base_language);
  for (auto &x : list_of_translations) {
    index++;
    auto lay = std::make_unique<OnceIndexBox>(
        &main_widget, dictionary.get_word(x), QString::number(index),
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

void WordWindow::sort_layout(SortSwiper::SortOptions option,
                             DirectionSwiper::DirectionsOptions direction) {
  for (auto &lay : current_words) {
    //    baselayout->deleteLater();
    baselayout->removeItem(lay.get());
  }
  switch (option) {
  case SortSwiper::SortOptions::ALPHABETIC: {
    std::sort(current_words.begin(), current_words.end(),
              [this](auto &layout, auto &second_layout) {
                return second_layout->get_word().get_translation(
                           this->from_language.get_text()) >
                       layout->get_word().get_translation(
                           this->from_language.get_text());
              });
    break;
  }
  case SortSwiper::SortOptions::NUMERIC: {
    std::sort(current_words.begin(), current_words.end(),
              [](auto &layout, auto &second_layout) {
                return second_layout->get_index() > layout->get_index();
              });
    break;
  }
  case SortSwiper::SortOptions::DATE: {
    std::sort(current_words.begin(), current_words.end(),
              [this](auto &layout, auto &second_layout) {
                return second_layout->get_word().get_date(
                           this->from_language.get_text()) >
                       layout->get_word().get_date(
                           this->from_language.get_text());
              });
    break;
  }
  case SortSwiper::SortOptions::WORD_LENGHT: {
    std::sort(current_words.begin(), current_words.end(),
              [this](auto &layout, auto &second_layout) {
                return second_layout->get_word()
                           .get_translation(this->from_language.get_text())
                           .size() >
                       layout->get_word()
                           .get_translation(this->from_language.get_text())
                           .size();
              });
    break;
  }
  }

  if (direction == DirectionSwiper::DirectionsOptions::DOWN) {
    std::reverse(current_words.begin(), current_words.end());
  }
  for (auto &lay : current_words) {
    baselayout->addLayout(lay.get());
  }
}

void WordWindow::create_word_layout(Word::Language word_base_language,
                                    Word::Language word_translation_language) {
  clear_layout();
  int index = 0;
  auto list_of_translations = dictionary.get_specific_translations(
      word_base_language, word_translation_language);
  for (auto &x : list_of_translations) {
    index++;
    auto lay = std::make_unique<DoubleIndexBox>(
        &main_widget, dictionary.get_word(x), QString::number(index),
        word_base_language, word_translation_language);
    baselayout->addLayout(lay.get());
    current_words.push_back(std::move(lay));
  }
  groupbox->setLayout(baselayout.get());
  for (auto &x : current_words) {
    QObject::connect(x.get(), &IndexBox::update_window, this,
                     &WordWindow::update_whole_dictionary);
  }
}

QWidget *WordWindow::get_widget() { return &main_widget; }

void WordWindow::close_button_configuration() {
  close_button.set_position(WidgetData::EXIT_POSITION_X,
                            WidgetData::EXIT_POSITION_Y);
  QObject::connect(&close_button, &QPushButton::clicked, this,
                   [this]() { emit close_signal(&main_widget); });
}

void WordWindow::configurate_swiper(LanguageSwiper *swiper) {
  auto opt = Word::Language_names;
  std::vector<Word::Language> v;
  v.reserve(opt.size());
  for (const auto &[lang, string] : opt) {
    v.push_back(lang);
  }

  swiper->set_options(std::move(v));
}

void WordWindow::configurate_swiper(LanguageSwiper *swiper, int position_x,
                                    int position_y) {
  configurate_swiper(swiper);
  swiper->set_font(WidgetData::FONT_SIZE_SWIPER);
  swiper->set_position(position_x, position_y);
}

void WordWindow::configurate_swiper(SortSwiper *swiper) {
  std::vector<SortSwiper::SortOptions> v;

  for (int i = 0;
       static_cast<SortSwiper::SortOptions>(i) <= SortSwiper::SortOptions::DATE;
       i++) {
    v.push_back(static_cast<SortSwiper::SortOptions>(i));
  }
  swiper->set_options(std::move(v));
  swiper->set_font(WidgetData::FONT_SIZE_SWIPER);
  down_layout_swiper.addLayout(swiper->create_layout());
  //  swiper->set_position(position_x, position_y);
}
void WordWindow::configurate_swiper(DirectionSwiper *swiper) {
  std::vector<DirectionSwiper::DirectionsOptions> v;

  for (int i = 0; static_cast<DirectionSwiper::DirectionsOptions>(i) <=
                  DirectionSwiper::DirectionsOptions::DOWN;
       i++) {
    v.push_back(static_cast<DirectionSwiper::DirectionsOptions>(i));
  }
  swiper->set_options(std::move(v));
  swiper->set_font(WidgetData::FONT_SIZE_SWIPER);
  down_layout_swiper.addLayout(swiper->create_layout());
  //  swiper->set_position(position_x, position_y);
}

void WordWindow::clear_layout() {
  //  baselayout->deleteLater();
  current_words.clear();
}

void WordWindow::update_whole_dictionary() {
  reload();
  emit update_rest_tabs(dictionary);
}

void WordWindow::reload() {
  auto base_language = from_language.get_text();
  auto translated_language = to_language.get_text();
  set_layout(base_language, translated_language);
}

QString WordWindow::get_tab_title() const {
  return dictionary.get_name() + " - dict";
}

void WordWindow::add_new_word() {
  emit add_new_word_signal(this->from_language.get_text(), dictionary);
}
