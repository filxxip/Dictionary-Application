#pragma once

#include <QCompleter>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <vector>

class CustomCompleter : public QCompleter {

private:
  QStringList create_stringlist(std::vector<QString> elements);

public:
  enum class Status { HAS_RESULTS, NO_RESULTS };
  CustomCompleter(QWidget *widget, std::vector<QString> elements);
  Status get_status() const;
};
