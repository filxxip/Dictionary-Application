#include "person_data_window.h"
#include "../change_color/change_color.h"
#include "../regex_check/regex_check.h"

#include <QDebug>
#include <QStyle>
namespace {
const std::map<Person::Data, QString> entries_boxes_values = {
    {Person::Data::NAME, Json::NAME},
    {Person::Data::SURNAME, Json::SURNAME},
    {Person::Data::AGE, Json::AGE},
    {Person::Data::COUNTRY, Json::COUNTRY},
    {Person::Data::SCHOOL, Json::SCHOOL},
    {Person::Data::EMAIL, Json::EMAIL},
    {Person::Data::PASSWORD, Json::PASSWORD}}; ///< map with entries sign as key
                                               ///< and its components as value
                                               ///< (pair)
}
PersonDataWindow::PersonDataWindow(Person &user)
    : QObject(), title_label(ImageLabel(&main_widget, "images/dict.png",
                                        Displays::DisplayStyle::CHANGED_WIDTH,
                                        WidgetData::IMAGE_HEIGHT)),
      person(user), changes_button(&main_widget, WidgetData::CHANGE_NAME),
      savebutton(&main_widget, WidgetData::SAVE_NAME) {
  main_layout.addWidget(&title_label);
  QHBoxLayout *buttons_lay = creating_buttons_layout();
  QVBoxLayout *entries_lay = creating_entries_layout();
  main_layout.addLayout(entries_lay);
  main_layout.addLayout(buttons_lay);
  main_widget.setLayout(&main_layout);
  main_layout.setContentsMargins(WidgetData::MAIN_LAYOUT_MARGINS);
}

QWidget *PersonDataWindow::get_widget() { return &main_widget; }

QVBoxLayout *PersonDataWindow::creating_entries_layout() {
  auto layout = new QVBoxLayout;
  QHBoxLayout *h_lay;
  for (int i = 0; i <= 6; i++) {
    h_lay = create_entry_box(static_cast<Person::Data>(i));
    layout->addLayout(h_lay);
  }
  return layout;
}

QHBoxLayout *PersonDataWindow::creating_buttons_layout(const QMargins &margin) {
  QHBoxLayout *layout = new QHBoxLayout;
  layout->addWidget(&savebutton);
  savebutton.setDisabled(true);
  layout->addWidget(&changes_button);
  QObject::connect(&changes_button, &QPushButton::clicked, this,
                   &PersonDataWindow::change_button_function);
  QObject::connect(&savebutton, &QPushButton::clicked, this,
                   &PersonDataWindow::save_function);
  layout->setContentsMargins(margin);
  return layout;
}

QHBoxLayout *PersonDataWindow::create_entry_box(Person::Data entry_name) {
  auto label_text = entries_boxes_values.at(entry_name);
  auto ptr = std::make_unique<LabelEntryBox>(&main_widget, label_text, "",
                                             EntryLine::Status::NORMAL);
  QObject::connect(
      ptr->get_entryline(), &QLineEdit::textChanged, this,
      [this, entry_name]() { this->every_change_event(entry_name); });
  auto layout = ptr->create_layout(WidgetData::LOGIN_BOX_HEIGHT);
  ptr->set_read_only(true);
  ptr->set_label_width(WidgetData::DEFAULT_WIDTH);
  items_map.insert({entry_name, std::move(ptr)});
  set_person_data(entry_name);
  return layout;
}

void PersonDataWindow::change_button_function() {
  savebutton.setEnabled(true);
  for (auto &[name, entry_box] : items_map) {
    entry_box->set_read_only(false);
  }
  changes_button.setText(WidgetData::DISCARD_NAME);
  QObject::disconnect(&changes_button, &QPushButton::clicked, this,
                      &PersonDataWindow::change_button_function);
  QObject::connect(&changes_button, &QPushButton::clicked, this,
                   &PersonDataWindow::discard_changes);
}

void PersonDataWindow::discard_changes() {
  savebutton.setDisabled(true);
  for (auto &[name, entry_box] : items_map) {
    entry_box->set_read_only(true);
    set_person_data(name);
  }
  changes_button.setText(WidgetData::CHANGE_NAME);
  QObject::disconnect(&changes_button, &QPushButton::clicked, this,
                      &PersonDataWindow::discard_changes);
  QObject::connect(&changes_button, &QPushButton::clicked, this,
                   &PersonDataWindow::change_button_function);
}

void PersonDataWindow::set_person_data(Person::Data entry_name) {
  auto entry = get_line_edit(entry_name);
  auto content = person.get_data(entry_name);
  entry->setText(content);
}

EntryLine *PersonDataWindow::get_line_edit(Person::Data entry_enum) {
  auto entry = items_map.at(entry_enum)->get_entryline();
  return entry;
}

void PersonDataWindow::save_function() {
  std::vector<Person::Data> potential_errors;

  for (int i = 0; i <= 6; i++) {
    auto name = static_cast<Person::Data>(i);
    auto text = get_line_edit(name)->text();
    if (!person.is_valid_data(text, name)) {
      potential_errors.push_back(name);
    }
  }
  if (potential_errors.empty()) {
    for (int i = 0; i <= 6; i++) {
      auto name = static_cast<Person::Data>(i);
      auto text = get_line_edit(name)->text();
      person.set_data(text, name);
    }
    discard_changes();
  } else {
    std::vector<EntryLine *> errors;
    for (auto name : potential_errors) {
      errors.push_back(get_line_edit(name));
    }
    change_color(errors, Colors::DARK_RED, 1000);
  }
  for (int i = 0; i <= 6; i++) {
    auto name = static_cast<Person::Data>(i);
    every_change_event(name);
    get_line_edit(name)->clearFocus();
  }
}

void PersonDataWindow::every_change_event(Person::Data entry_enum) {
  auto entry = items_map.at(entry_enum)->get_entryline();
  auto text = entry->text();
  if (text != person.get_data(entry_enum)) {
    if (person.is_valid_data(text, entry_enum)) {
      change_color({entry}, Colors::GREEN);
    } else {
      change_color({entry}, Colors::RED);
    }
  } else {
    change_color({entry}, Colors::DEFAULT);
  }
}
