#include "register_window.h"
#include "../change_color/change_color.h"
#include "../custom_entry_line/entry_line.h"
#include "../data/config_file.h"
#include "../delay/delay.h"
#include "../person/person.h"
#include "../person/person_errors.h"
#include "../regex_check/regex_check.h"

#include <QString>

#include <algorithm>
#include <utility>
#include <vector>

namespace {
constexpr char MAIN_IMAGE[] = "images/dict.png";

const std::map<RegisterWindow::Entries, std::pair<QString, QString>>
    entries_boxes_values = {
        {RegisterWindow::Entries::NAME, {Json::NAME, Placeholders::NAME}},
        {RegisterWindow::Entries::SURNAME,
         {Json::SURNAME, Placeholders::SURNAME}},
        {RegisterWindow::Entries::AGE, {Json::AGE, Placeholders::AGE}},
        {RegisterWindow::Entries::COUNTRY,
         {Json::COUNTRY, Placeholders::COUNTRY}},
        {RegisterWindow::Entries::SCHOOL, {Json::SCHOOL, Placeholders::SCHOOL}},
        {RegisterWindow::Entries::EMAIL, {Json::EMAIL, Placeholders::EMAIL}},
        {RegisterWindow::Entries::PASSWORD,
         {Json::PASSWORD, Placeholders::PASSWORD}},
        {RegisterWindow::Entries::REPEAT_PASSWORD,
         {Json::REPEAT_PASSWORD, Placeholders::REPEAT_PASSWORD}},
}; ///< map with entries sign as key and its components
   ///< as value (pair)
} // namespace

RegisterWindow::RegisterWindow(CustomList &main_list)
    : QObject(), title_label(ImageLabel(&main_widget, MAIN_IMAGE,
                                        Displays::DisplayStyle::CHANGED_WIDTH,
                                        WidgetData::IMAGE_HEIGHT)),
      clear_button(TextButton(&main_widget, WidgetData::CLEAR_BUTTON_TEXT)),
      register_button(
          TextButton(&main_widget, WidgetData::REGISTER_BUTTON_TEXT)),
      list(main_list) {
  main_layout.addWidget(&title_label);
  QHBoxLayout *buttons_lay = creating_buttons_layout();
  QVBoxLayout *entries_lay = creating_entries_layout();
  main_layout.addLayout(entries_lay);
  main_layout.addLayout(buttons_lay);
  main_widget.setLayout(&main_layout);
  main_layout.setContentsMargins(WidgetData::MAIN_LAYOUT_MARGINS);
}

QWidget *RegisterWindow::get_widget() { return &main_widget; }

QHBoxLayout *RegisterWindow::creating_buttons_layout(const QMargins &margin) {
  QHBoxLayout *layout(new QHBoxLayout);
  layout->addWidget(&clear_button);
  QObject::connect(&clear_button, &TextButton::clicked, this,
                   &RegisterWindow::clear_method);
  layout->addWidget(&register_button);
  QObject::connect(&register_button, &TextButton::clicked, this,
                   &RegisterWindow::user_register);
  layout->setContentsMargins(margin);
  return layout;
}

QVBoxLayout *RegisterWindow::creating_entries_layout() {
  auto layout = new QVBoxLayout;
  QHBoxLayout *h_lay;
  for (int i = 0; i <= 5; i++) {
    auto entry_name = static_cast<Entries>(i);
    h_lay = create_custom_entry_box(entry_name);
    layout->addLayout(h_lay);
  }
  for (int i = 6; i <= 7; i++) {
    auto entry_name = static_cast<Entries>(i);
    h_lay = create_custom_entry_box(entry_name, EntryLine::Status::PASSWORD);
    layout->addLayout(h_lay);
  }
  layout->setContentsMargins(WidgetData::REGISTER_BOX_MARGINS);
  return layout;
}

QHBoxLayout *RegisterWindow::create_custom_entry_box(Entries entry_name,
                                                     EntryLine::Status style) {
  QHBoxLayout *h_lay;
  auto &[label_text, placeholder] = entries_boxes_values.at(entry_name);
  auto ptr = std::make_unique<LabelEntryBox>(&main_widget, label_text,
                                             placeholder, style);
  ptr->set_label_width(WidgetData::LOGIN_LABEL_WIDTH);

  items.insert({entry_name, std::move(ptr)});
  h_lay = items.at(entry_name)
              ->create_layout(WidgetData::LOGIN_BOX_HEIGHT,
                              WidgetData::REGISTER_SPACING,
                              WidgetData::DEFAULT_MARGINS);
  return h_lay;
}

void RegisterWindow::clear_method() {
  for (auto &box : items) {
    box.second->clear();
  }
}

void RegisterWindow::user_register() {
  std::vector<Entries> potential_errors;
  Person person;
  auto name_string = get_line_edit(Entries::NAME)->text();
  auto surname_string = get_line_edit(Entries::SURNAME)->text();
  auto age_string = get_line_edit(Entries::AGE)->text();
  auto country_string = get_line_edit(Entries::COUNTRY)->text();
  auto email_string = get_line_edit(Entries::EMAIL)->text();
  auto password_string = get_line_edit(Entries::PASSWORD)->text();
  auto repeated_password = get_line_edit(Entries::REPEAT_PASSWORD)->text();
  auto school_string = get_line_edit(Entries::SCHOOL)->text();
  if (!person.set_email(email_string)) {
    potential_errors.push_back(Entries::EMAIL);
  } else {
    try {
      list.get_person(email_string);
      potential_errors.push_back(Entries::EMAIL);
    } catch (std::invalid_argument) {
    }
  }
  if (!person.set_password(password_string)) {
    potential_errors.push_back(Entries::PASSWORD);
  }
  if (password_string != repeated_password) {
    potential_errors.push_back(Entries::REPEAT_PASSWORD);
  }
  if (!person.set_age(age_string)) {
    potential_errors.push_back(Entries::AGE);
  }
  if (!person.set_name(name_string)) {
    potential_errors.push_back(Entries::NAME);
  }
  if (!person.set_surname(surname_string)) {
    potential_errors.push_back(Entries::SURNAME);
  }
  if (!person.set_country(country_string)) {
    potential_errors.push_back(Entries::COUNTRY);
  }
  if (!person.set_school(school_string)) {
    potential_errors.push_back(Entries::SCHOOL);
  }
  if (potential_errors.empty()) {
    list.add_person(person);
    auto v = make_vector<Entries>(
        {Entries::NAME, Entries::SCHOOL, Entries::SURNAME, Entries::EMAIL,
         Entries::REPEAT_PASSWORD, Entries::REPEAT_PASSWORD, Entries::AGE});
    change_color(v, Colors::GREEN, 100);
    clear_method();
  }
  change_color(make_vector<Entries>(potential_errors), Colors::RED, 1000);
}

EntryLine *RegisterWindow::get_line_edit(Entries entry_enum) {

  auto entry = items.at(entry_enum)->get_entryline();
  return entry;
}

template <typename T>
std::vector<EntryLine *> RegisterWindow::make_vector(std::vector<T> list) {
  std::vector<EntryLine *> entrylines;
  for (auto i : list) {
    auto lineedt = get_line_edit(i);
    entrylines.push_back(lineedt);
  }
  return entrylines;
}
