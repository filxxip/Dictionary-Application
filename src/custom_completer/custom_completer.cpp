#include "custom_completer.h"

#include <QAbstractItemView>
#include <QStringListModel>

#include <memory>
#include <utility>

namespace {
constexpr int ELEMENTS_NUMBER = 3;
}

QStringList CustomCompleter::create_stringlist(std::vector<QString> elements) {
  QStringList elements_list;
  for (auto &item : elements) {
    elements_list.append(item);
  }
  return elements_list;
}

CustomCompleter::CustomCompleter(QWidget *widget, std::vector<QString> elements)
    : QCompleter(widget) {
  auto lista = create_stringlist(elements);
  auto model = new QStringListModel(std::move(lista), this);
  setModel(model);
  setCaseSensitivity(Qt::CaseInsensitive);
  setMaxVisibleItems(ELEMENTS_NUMBER);
  //  setObjectName("completer");
}

CustomCompleter::Status CustomCompleter::get_status() const {
  if (this->currentRow() == -1) {
    return CustomCompleter::Status::NO_RESULTS;
  }
  return CustomCompleter::Status::HAS_RESULTS;
}
