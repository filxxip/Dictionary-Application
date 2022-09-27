#include "main_class.h"
#include "../custom_message_box/custom_message_box.h"
#include "../data/config_file.h"

namespace {
constexpr char STYLE_PATH[] = "src/data/style.css";
constexpr char LOGOUT_QUESTION[] = "Are you sure to logout?";
constexpr char LOGOUT_TITLE[] = "LOGOUT";
constexpr char QUESTION[] = "Are you sure to remove this dictionary";
constexpr char TITLE[] = "REMOVING DICTIONARY";

} // namespace

MainClass::MainClass(QApplication &app)
    : QObject(), base(BaseTabWidget(&app, STYLE_PATH)), login_window(list),
      register_window(list) {
  auto login_widget = login_window.get_widget();
  auto register_widget = register_window.get_widget();
  auto wordlist_widget = wordlist_window.get_widget();
  base.add_widget(login_widget, Titles::LOGIN);
  base.add_widget(register_widget, Titles::REGISTER);
  base.add_widget(wordlist_widget, Titles::WORDLIST);
  QObject::connect(&login_window, &LoginView::data_window_create, this,
                   &MainClass::setting_new_person_data);
  auto &exit_button1 = data_window.get_exit_button();
  QObject::connect(&exit_button1, &QPushButton::clicked, this,
                   &MainClass::logout);
  auto &exit_button2 = wordlist_window.get_exit_button();
  QObject::connect(&exit_button2, &QPushButton::clicked, this,
                   &MainClass::logout);
  QObject::connect(&wordlist_window, &WordlistWindow::new_dict_signal, this,
                   &MainClass::add_new_dictionary);
  setting_new_person_data("f.polt2oraczyk@gmail.com"); // toremove
  QObject::connect(&list, &CustomList::adding_to_box, this,
                   [this](auto dict) { wordlist_window.add_groupbox(dict); });

  QObject::connect(&wordlist_window, &WordlistWindow::removing_dict_signal,
                   this, &MainClass::remove_dictionary);
}

void MainClass::setting_new_person_data(const QString &email) {
  auto &person = list.get_person(email);
  data_window.set_person(&person);

  auto dict_list = list.get_dictionary_list(email);
  wordlist_window.set_dict(email, dict_list);

  auto data_widget = data_window.get_widget();
  base.add_widget(data_widget, Titles::DATA);
  auto wordlist_widget = wordlist_window.get_widget();
  base.add_widget(wordlist_widget, Titles::WORDLIST);
  auto login_widget = login_window.get_widget();
  auto register_widget = register_window.get_widget();
  base.delete_widget(login_widget);
  base.delete_widget(register_widget);
}

void MainClass::logout() {
  CustomMessageBox msg(data_window.get_widget(), LOGOUT_TITLE, LOGOUT_QUESTION);
  auto choice =
      msg.run(CustomMessageBox::Type::No, {CustomMessageBox::Type::Yes});
  if (choice == CustomMessageBox::Type::Yes) {
    auto data_widget = data_window.get_widget();
    auto wordlist_widget = wordlist_window.get_widget();
    base.delete_widget(data_widget);
    base.delete_widget(wordlist_widget);
    auto login_widget = login_window.get_widget();
    auto register_widget = register_window.get_widget();
    base.add_widget(login_widget, Titles::LOGIN);
    base.add_widget(register_widget, Titles::REGISTER);
  }
}

CustomList &MainClass::get_list() { return list; }

void MainClass::add_new_dictionary(const QString &name, const QString &owner) {
  auto &person = list.get_person(owner);
  Dictionary dict(&person, name);
  list.add_dictionary(std::move(dict));
  list.add_last_dictionary_to_box();
}

void MainClass::remove_dictionary(Dictionary *dictionary,
                                  const QString &person_mail) {
  list.remove_dictionary(*dictionary);
  auto msg = CustomMessageBox(wordlist_window.get_widget(), TITLE, QUESTION);
  auto choice =
      msg.run(CustomMessageBox::Type::Yes,
              {CustomMessageBox::Type::No}); // zmienic na ta fajna liste
  if (choice == CustomMessageBox::Type::Yes) {
    wordlist_window.set_dict(person_mail,
                             list.get_dictionary_list(person_mail));
  }
}
