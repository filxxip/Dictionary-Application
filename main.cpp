#include "src/base_tab_widget/base_tab_widget.h"
#include "src/custom_list/custom_list.h"
#include "src/dictionary/dictionary.h"
#include "src/login_view/login_view.h"
#include "src/person_data_window/person_data_window.h"
#include "src/regex_check/regex_check.h"
#include "src/register_window/register_window.h"

#include <QApplication>
#include <QDebug>
#include <memory>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  CustomList list;
  list.create_from_json();
  auto base = std::make_shared<BaseTabWidget>(&app, "src/data/style.css");
  auto log = LoginView(list.get_logs_data());
  auto reg = RegisterWindow(list);
  auto dat = PersonDataWindow(list.get_person("f.pol@gmail.com"));
  base->add_widget(log.get_widget(), "log in");
  base->add_widget(reg.get_widget(), "register");
  base->add_widget(dat.get_widget(), "data");
  const int retval = app.exec();
  list.update_json();
  return retval;
}
