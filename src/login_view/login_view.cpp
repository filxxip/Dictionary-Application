#include "login_view.h"
#include "../change_color/change_color.h"
#include "../data/config_file.h"
#include "../delay/delay.h"
#include "../image_button/image_button.h"
#include "../person_data_window/person_data_window.h"

#include <QDebug>
#include <QObject>
#include <QStyle>
#include <QTime>
#include <QTimer>

namespace {
constexpr char HIDDEN_PASS_ICON[] = "images/eye.png";
constexpr char VISIBLE_PASS_ICON[] = "images/eye2.png";
constexpr char MAIN_IMAGE[] = "images/dict.png";
} // namespace

LoginView::LoginView(const CustomList &list)
    : QObject(), user_list(list),
      main_image_label(ImageLabel(&main_widget, MAIN_IMAGE,
                                  Displays::DisplayStyle::CHANGED_WIDTH,
                                  WidgetData::IMAGE_HEIGHT)),
      entry_line_box_login(&main_widget, WidgetData::LOGIN_LABEL_TEXT,
                           Placeholders::LOGIN_PLACEHOLDER,
                           EntryLine::Status::NORMAL),
      entry_line_box_password(&main_widget, WidgetData::PASSWORD_LABEL_TEXT,
                              Placeholders::PASSWORD_PLAHOLDER,
                              EntryLine::Status::PASSWORD),
      image_button(&main_widget, HIDDEN_PASS_ICON,
                   Displays::DisplayStyle::CHANGED_WIDTH,
                   WidgetData::SEE_BUTTON_HEIGHT),
      submit_button(&main_widget, WidgetData::SUBMIT_BUTTON_TEXT),
      clear_button(&main_widget, WidgetData::CLEAR_BUTTON_TEXT) {
  create_main_vboxlayout();
  auto buttons_layout =
      creating_buttons_layout(user_list, WidgetData::BUTTONS_MARGINS);
  main_layout.addLayout(buttons_layout);
  main_layout.setContentsMargins(WidgetData::MAIN_LAYOUT_MARGINS);
  main_widget.setLayout(&main_layout);
}

QWidget *LoginView::get_widget() { return &main_widget; }

QHBoxLayout *LoginView::creating_buttons_layout(const CustomList &list,
                                                const QMargins &margin) {
  auto layout = new QHBoxLayout;
  layout->addWidget(&submit_button);
  layout->addWidget(&clear_button);
  //  auto email = list.get_logs_data();
  QObject::connect(
      &submit_button, &QPushButton::pressed, this,
      [&list, this]() { // dlaczego dziala przez kopie a przez referencje nie,
                        // poniewaz byl to obiekt tymczasowy i zapomnial o nim
        this->submit_function(list.get_logs_data());
      });
  QObject::connect(&clear_button, &QPushButton::pressed, this,
                   &LoginView::clear_function);
  QObject::connect(entry_line_box_password.get_entryline(),
                   &QLineEdit::returnPressed, this,
                   [this]() { submit_button.pressed(); });
  layout->setSpacing(WidgetData::BUTTONS_SPACING);
  layout->setContentsMargins(margin);
  return layout;
}

void LoginView::clear_function() {
  entry_line_box_login.clear();
  entry_line_box_password.clear();
}

void LoginView::submit_function(const std::map<QString, QString> &logs_map) {
  auto email = entry_line_box_login.get_text();
  auto password = entry_line_box_password.get_text();
  auto index = std::find_if(
      logs_map.begin(), logs_map.end(),
      [&email](const auto &pair) { // nie dziala mi structure bindings
        return pair.first == email;
      });
  if (index == logs_map.end()) {

    change_color({entry_line_box_login.get_entryline(),
                  entry_line_box_password.get_entryline()},
                 Colors::RED, 1500);

  } else {
    auto index_pass = std::find_if(
        logs_map.begin(), logs_map.end(),
        [&password](const auto &pair) { // nie dziala mi structure bindings
          return pair.second == password;
        });
    if (index_pass == logs_map.end()) {
      change_color({entry_line_box_password.get_entryline()}, Colors::RED,
                   1500);
    } else {
      change_color({entry_line_box_login.get_entryline(),
                    entry_line_box_password.get_entryline()},
                   Colors::GREEN, 1500);
      emit data_window_create(entry_line_box_login.get_text());
    }
  }
}

void LoginView::set_to_visible() {
  entry_line_box_password.get_entryline()->set_text_status(
      EntryLine::Status::NORMAL);
  image_button.change_image(VISIBLE_PASS_ICON);
}
void LoginView::set_to_hidden() {
  entry_line_box_password.get_entryline()->set_text_status(
      EntryLine::Status::PASSWORD);
  image_button.change_image(HIDDEN_PASS_ICON);
}
void LoginView::create_main_vboxlayout() {
  entry_line_box_login.set_label_width(WidgetData::LOGIN_LABEL_WIDTH);
  entry_line_box_password.set_label_width(WidgetData::PASSWORD_LABEL_WIDTH);
  main_layout.addWidget(&main_image_label);
  auto login_box =
      entry_line_box_login.create_layout(WidgetData::LOGIN_BOX_HEIGHT);
  main_layout.addLayout(login_box);
  auto password_box =
      entry_line_box_password.create_layout(WidgetData::LOGIN_BOX_HEIGHT);
  password_box->addWidget(&image_button);
  QObject::connect(&image_button, &QPushButton::pressed, this,
                   &LoginView::set_to_visible);
  QObject::connect(&image_button, &QPushButton::released, this,
                   &LoginView::set_to_hidden); // wpieprzyc w jedna fcje
  main_layout.addLayout(password_box);
}
