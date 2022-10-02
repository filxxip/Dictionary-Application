#include "main_class.h"
#include "../custom_message_box/custom_message_box.h"
#include "../data/config_file.h"
#include "../detail_view/detail_view.h"

namespace {
constexpr char STYLE_PATH[] = "src/data/style.css";
constexpr char LOGOUT_QUESTION[] = "Are you sure to logout?";
constexpr char LOGOUT_TITLE[] = "LOGOUT";
constexpr char QUESTION[] = "Are you sure to remove this dictionary";
constexpr char TITLE[] = "REMOVING DICTIONARY";
constexpr char REMOVING_INFORMATION[] =
    "Are you sure to remove this dictionary tab";
constexpr char SECOND_REMOVING_INFORMATION[] =
    "Some unsaved data will be lost, save it whether you want to remain them!";
constexpr char REMOVING_INFORMATION_TITLE[] = "REMOVING TAB";

} // namespace

MainClass::MainClass(QApplication &app)
    : QObject(), base(BaseTabWidget(&app, STYLE_PATH)), login_window(list),
      register_window(list) {
  word_windows.reserve(MaxValues::MAX_OPENED_DICTS);
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
  setting_new_person_data("f.pol2@gmail.com"); // toremove
  QObject::connect(&list, &CustomList::adding_to_box, this,
                   [this](auto dict) { wordlist_window.add_groupbox(dict); });

  QObject::connect(&wordlist_window, &WordlistWindow::removing_dict_signal,
                   this, &MainClass::remove_dictionary);

  QObject::connect(&wordlist_window,
                   &WordlistWindow::changing_name_dictionary_bar, this,
                   &MainClass::change_every_dict_bar_title);

  QObject::connect(&wordlist_window, &WordlistWindow::setting_new_window, this,
                   &MainClass::add_new_dict_window);
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

void MainClass::change_every_dict_bar_title(Dictionary *dict) {
  for (auto &tab_itr : word_windows) {
    if (dict == tab_itr->get_dictionary()) {
      auto new_name = dict->get_name();
      tab_itr->change_title(new_name);
      auto widget = tab_itr->get_widget();
      base.change_name(widget, tab_itr->get_tab_title());
    }
  }
  for (auto &tab_itr : detail_tabs) {
    tab_itr->update_title();
  }
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

void MainClass::remove_dictionary(Dictionary *dictionary) {
  list.remove_dictionary(*dictionary);
  auto msg = CustomMessageBox(wordlist_window.get_widget(), TITLE, QUESTION);
  auto choice =
      msg.run(CustomMessageBox::Type::No,
              {CustomMessageBox::Type::Yes}); // zmienic na ta fajna liste
  if (choice == CustomMessageBox::Type::Yes) {
    auto person = dictionary->get_person();
    auto mail = person->get_email();
    wordlist_window.set_dict(mail, list.get_dictionary_list(mail));
    remove_dictionary_from_list(dictionary);
  }
}

void MainClass::remove_every_dict_from_list(Dictionary *dict) {
  auto index = std::remove_if(
      word_windows.begin(), word_windows.end(),
      [dict](auto &win) { return dict == win->get_dictionary(); });
  word_windows.erase(index, word_windows.end());
}
void MainClass::remove_every_dict_detail_tab_from_list(Dictionary *dict) {
  auto index2 =
      std::remove_if(detail_tabs.begin(), detail_tabs.end(), [dict](auto &win) {
        return dict == win->get_dictionary();
      });
  detail_tabs.erase(index2, detail_tabs.end());
}

void MainClass::remove_dictionary_from_list(Dictionary *dict) {
  remove_every_dict_from_list(dict);
  remove_every_dict_detail_tab_from_list(dict);
}

void MainClass::add_new_dict_window(Dictionary *dictionary) {
  auto window = std::make_unique<WordWindow>(dictionary);
  base.add_widget(window->get_widget(), window->get_tab_title());
  QObject::connect(window.get(), &WordWindow::close_signal, this,
                   &MainClass::close_widget_tab);
  QObject::connect(window.get(), &WordWindow::update_rest_tabs, this,
                   &MainClass::update_every_tab);
  QObject::connect(window.get(), &WordWindow::add_detail_view_signal, this,
                   &MainClass::add_new_detail_view);
  base.set_widget(window->get_widget());
  word_windows.push_back(std::move(window));
}

void MainClass::close_widget_tab(QWidget *widget) {
  auto msg = new CustomMessageBox(widget, REMOVING_INFORMATION_TITLE,
                                  REMOVING_INFORMATION);
  msg->create_detail_text(SECOND_REMOVING_INFORMATION);
  auto result =
      msg->run(CustomMessageBox::Type::No, {CustomMessageBox::Type::Yes});
  if (result == CustomMessageBox::Type::Yes) {
    auto index = std::find_if(word_windows.begin(), word_windows.end(),
                              [widget](auto &ptr_itr) {
                                return ptr_itr.get()->get_widget() == widget;
                              });
    delete msg;
    base.delete_widget(widget);
    word_windows.erase(index);
  }
}

void MainClass::update_every_tab(const Dictionary *dict) {
  for (auto &window : word_windows) {
    if (window->get_dictionary() == dict) {
      window->reload();
      base.change_name(window->get_widget(), window->get_tab_title());
    }
  }
  for (auto &window : detail_tabs) {
    if (window->get_dictionary() == dict) {
      window->update();
      base.change_name(window->get_widget(), window->get_tab_title());
      // zrobic jakos mozliwosc zmiany w gornym panelu tytuly przy zmianie
      // slowka i problemy ogolnie z integracja miedzy tabelkami
      //      auto widget = window->get_widget();
      //      auto word = window.get
      //      auto new_name = window->get_dictionary()->get_name();
      //      base.change_name(widget, new_name + " - detail");
    }
  }
}

void MainClass::add_new_detail_view(const Dictionary *dict, Word &word,
                                    Word::Language language) {
  auto view = std::make_unique<DetailView>(word, dict, language);
  base.add_widget(view->get_widget(), view->get_tab_title());
  QObject::connect(
      view.get(), &DetailView::close_window_signal, this, [this](auto widget) {
        base.delete_widget(widget);
        auto index = std::find_if(detail_tabs.begin(), detail_tabs.end(),
                                  [widget](auto &ptr_itr) {
                                    return ptr_itr->get_widget() == widget;
                                  });
        detail_tabs.erase(index);
      });
  QObject::connect(view.get(), &DetailView::update_rest_dicts_signal, this,
                   [this](auto dict) { update_every_tab(dict); });
  detail_tabs.push_back(std::move(view));
}
