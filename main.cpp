#include "src/base_tab_widget/base_tab_widget.h"
#include "src/custom_list/custom_list.h"
#include "src/dictionary/dictionary.h"
#include "src/login_view/login_view.h"
#include "src/regex_check/regex_check.h"
#include "src/register_window/register_window.h"

#include <QApplication>
#include <QDebug>
#include <memory>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  CustomList list;
  list.create_from_json();
  //  Dictionary n = Dictionary(&list.get_person("f.polt2oraczyk@gmail.com"));
  //  n.add_word(Word(Word::Language::POLISH, "mleko"));
  //  list.add_dictionary(n);
  qDebug() << is_password_valid("fpolgSSSmail.com");
  auto base = std::make_shared<BaseTabWidget>(&app, "src/data/style.css");
  auto log = LoginView(list.get_logs_data());
  auto reg = RegisterWindow(list);
  base->add_widget(log.get_widget(), "log in");
  base->add_widget(reg.get_widget(), "register");
  qDebug() << &list;
  //  list.update_json();
  const int retval = app.exec();
  list.update_json(); // naprawic ze usunelo plik gdy dodalem osobe
  return retval;
}
