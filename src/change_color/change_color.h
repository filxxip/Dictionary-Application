#pragma once

#include <vector>

#include <QString>

#include "../custom_entry_line/entry_line.h"

/**
 * @brief change_color method which changes color of entrylines
 * @param il vector with pointers to entryline
 * @param miliseconds_sleep number of time when entry's color will be changed
 * @param change_color color which will be applied to entry
 */
void change_color(std::vector<EntryLine *> il, const QString &change_color,
                  int miliseconds_sleep = 0);
