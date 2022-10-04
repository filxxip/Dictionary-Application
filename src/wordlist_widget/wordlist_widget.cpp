#include "wordlist_widget.h"
#include "../content_layout/content_layout.h"
#include "../custom_entry_line/entry_line.h"
#include "../data/config_file.h"
#include "../text_button/text_button.h"

#include <QDebug>
#include <QLabel>
#include <QObject>
#include <QScrollBar>
#include <QTimer>

#include <map>
#include <utility>

namespace {
constexpr char EXIT_IMAGE[] = "images/exit.png";
constexpr char TITLE_IMAGE[] = "images/dict.png";

} // namespace

void WordlistWindow::setting_scroll_options() {
  scrollarea.setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  scrollarea.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scrollarea.setWidgetResizable(true);
  groupbox->setEnabled(true);
}

WordlistWindow::WordlistWindow()
    : QObject(), exit_button(&main_widget, EXIT_IMAGE,
                             Displays::DisplayStyle::SCALED_WIDTH,
                             WidgetData::EXIT_HEIGHT),
      main_label(&main_widget, TITLE_IMAGE,
                 Displays::DisplayStyle::CHANGED_WIDTH,
                 WidgetData::WORDLIST_VIEW_IMG_HEIGHT),
      groupbox(std::make_unique<QGroupBox>()),
      baselayout(std::make_unique<QVBoxLayout>()) {
  mainlayout.addWidget(&main_label);
  exit_button.set_position(WidgetData::EXIT_POSITION_X,
                           WidgetData::EXIT_POSITION_Y);

  setting_scroll_options();

  scrollarea.setWidget(groupbox.get());
  mainlayout.addWidget(&scrollarea);

  main_widget.setLayout(&mainlayout);
  mainlayout.setContentsMargins(WidgetData::WORDLIST_VIEW_IMG_MARGINS);
}

QWidget *WordlistWindow::get_widget() { return &main_widget; };

ImageButton &WordlistWindow::get_exit_button() { return exit_button; }

void WordlistWindow::set_dict(const QString &person_mail,
                              std::vector<Dictionary *> dictionary) {
  owner = person_mail;
  dict = dictionary;
  groupbox_dict.clear();
  baselayout = std::make_unique<QVBoxLayout>();
  groupbox = std::make_unique<QGroupBox>();

  scrollarea.setWidget(groupbox.get());
  auto dict_size = dict.size();
  if (dict_size > 0) {
    for (unsigned long i = 0; i <= dict_size; i++) {
      if (i < dict_size - 1) {
        auto grpbox = std::make_unique<DoubleGrpBox>(main_widget, dict.at(i),
                                                     dict.at(i + 1));
        i++;
        baselayout->addLayout(grpbox.get());
        groupbox_dict.push_back(std::move(grpbox));

        continue;
      }
      if (i == dict_size - 1) {
        auto grpbox = std::make_unique<DoubleGrpBox>(main_widget, dict.at(i));
        baselayout->addLayout(grpbox.get());
        groupbox_dict.push_back(std::move(grpbox));
        break;
      }
      if (i == dict_size) {
        auto grpbox = std::make_unique<DoubleGrpBox>(main_widget);
        baselayout->addLayout(grpbox.get());
        groupbox_dict.push_back(std::move(grpbox));
        break;
      }
    }
    QObject::connect(
        (groupbox_dict.end() - 1)->get()->get_dict_layout(),
        &NewDictLayout::new_box_signal, this,
        [this](const QString &name) { emit new_dict_signal(name, owner); });
  }

  groupbox->setLayout(baselayout.get());
  for (auto &box : groupbox_dict) {
    connect_doublebox(box.get());
    connect_setting_doublebox(box.get());
  }
}

void WordlistWindow::add_groupbox(Dictionary *dict) {
  std::unique_ptr<DoubleGrpBox> ptr = nullptr;
  std::unique_ptr<DoubleGrpBox> ptr2 = nullptr;
  auto size = groupbox_dict.size();
  if (size > 0) {
    auto last_pair = std::move(groupbox_dict.at(size - 1));
    groupbox_dict.erase(groupbox_dict.end() - 1);
    if (last_pair->get_right_item() == nullptr) {
      ptr = std::make_unique<DoubleGrpBox>(main_widget, dict);
    } else {
      auto dict1 = last_pair->get_left_dictionary();
      ptr2 = std::make_unique<DoubleGrpBox>(main_widget, dict1, dict);
      ptr = std::make_unique<DoubleGrpBox>(main_widget);
    }
    if (ptr2) {
      baselayout->addLayout(ptr2.get());
      connect_doublebox(ptr2.get());
      connect_setting_doublebox(ptr2.get());
      groupbox_dict.push_back(std::move(ptr2));
    }
    baselayout->addLayout(ptr.get());
    connect_doublebox(ptr.get());
    connect_setting_doublebox(ptr.get());
    groupbox_dict.push_back(std::move(ptr));
  }
  QObject::connect(
      (groupbox_dict.end() - 1)->get()->get_dict_layout(),
      &NewDictLayout::new_box_signal, this,
      [this](const QString &name) { emit new_dict_signal(name, owner); });
}

void WordlistWindow::connect_doublebox(DoubleGrpBox *box) {
  if (box->get_left_item() != nullptr) {
    if (dynamic_cast<ContentLayout *>(box->get_left_item().get())) {
      auto item = static_cast<ContentLayout *>(box->get_left_item().get());

      QObject::connect(item, &ContentLayout::trash_dict, this,
                       [this](auto dict) { emit removing_dict_signal(dict); });
      QObject::connect(
          item, &ContentLayout::window_titles_changed_signal, this,
          [this](auto dict) { emit changing_name_dictionary_bar(dict); });
    }
  }
  if (box->get_right_item() != nullptr) {
    if (dynamic_cast<ContentLayout *>(box->get_right_item().get())) {
      auto item = static_cast<ContentLayout *>(box->get_right_item().get());

      QObject::connect(item, &ContentLayout::trash_dict, this,
                       [this](auto dict) { emit removing_dict_signal(dict); });
      QObject::connect(
          item, &ContentLayout::window_titles_changed_signal, this,
          [this](auto dict) { emit changing_name_dictionary_bar(dict); });
    }
  }
}

void WordlistWindow::connect_setting_doublebox(DoubleGrpBox *box) {
  if (box->get_left_item() != nullptr) {
    if (dynamic_cast<ContentLayout *>(box->get_left_item().get())) {
      auto item = static_cast<ContentLayout *>(box->get_left_item().get());

      QObject::connect(item, &ContentLayout::set_signal, this,
                       [this](auto dict) { emit setting_new_window(dict); });
    }
  }
  if (box->get_right_item() != nullptr) {
    if (dynamic_cast<ContentLayout *>(box->get_right_item().get())) {
      auto item = static_cast<ContentLayout *>(box->get_right_item().get());

      QObject::connect(item, &ContentLayout::set_signal, this,
                       [this](auto dict) { emit setting_new_window(dict); });
    }
  }
}

void WordlistWindow::clear() {}

void WordlistWindow::update(Dictionary *dictionary) {
  clear();
  auto index = std::find_if(groupbox_dict.begin(), groupbox_dict.end(),
                            [dictionary](auto &doublebox) {
                              return doublebox->has_dictionary(dictionary);
                            });
  index->get()->update_dictionary(dictionary);
  //  set_dict(owner, dict);
}
