#pragma once

#include <QCompleter>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <vector>

/** CustomCompleter class which creates list of strings fitted to some data*/
class CustomCompleter : public QCompleter {

public:
  /**
   * @brief create_stringlist method which create QStringList from vector
   * @param elements vector instance with strings to analyse
   * @return
   */
  QStringList create_stringlist(std::vector<QString> elements);

  enum class Status { HAS_RESULTS, NO_RESULTS };

  /**
   * @brief CustomCompleter constructor method
   * @param widget widget where it should be shown
   * @param elements vector of strings to analyse
   */
  CustomCompleter(QWidget *widget, std::vector<QString> elements);

  /**
   * @brief get_status method which provides status of results
   * @return HAS_RESULTS if completer found some fitted elements, otherwise
   * NO_RESULTS
   */
  Status get_status() const;
};
