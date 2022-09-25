#include "src/custom_list/custom_list.h"
#include "src/main_class/main_class.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainClass main(app);
  auto &list = main.get_list();
  const int retval = app.exec();
  list.update_json();
  return retval;
}
