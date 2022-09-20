#include "change_color.h"

#include "../data/config_file.h"
#include "../delay/delay.h"

void change_color(std::vector<EntryLine *> il, const QString &change_color,
                  int miliseconds_sleep) {
  std::map<EntryLine *, QString> previous_styles;
  for (auto entry : il) {
    auto style = entry->styleSheet();
    previous_styles.insert({entry, style});
    entry->setStyleSheet("background-color: " + change_color);
  }
  if (miliseconds_sleep != 0) {
    delay(miliseconds_sleep);
    for (auto entry : il) {
      entry->setStyleSheet(previous_styles.at(entry));
    }
  }
}
