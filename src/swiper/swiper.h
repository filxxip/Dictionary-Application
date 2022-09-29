#pragma once
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"
#include "../translation/translation.h"

#include <memory>
#include <vector>

#include <QHBoxLayout>
#include <QPoint>
#include <QString>

class Swiper : public QObject {
  Q_OBJECT
public:
  QWidget *widget;
  ImageButton left_arrow;
  ImageButton right_arrow;
  TextLabel main_label;
  std::vector<Word::Language> options;
  QPoint position;
  Word::Language current_language;
  int current_index = 0;

  void set_text(Word::Language language);

public:
  Swiper(QWidget *widget_, int label_width, int image_size);
  void set_position(int position_x, int position_y);
  void set_options(std::vector<Word::Language> options_);
  void set_font(int value);
  Word::Language get_text() const;
  Word::Language get_option(int index);
  QHBoxLayout *create_layout();

public slots:
  void swiper_left();
  void swipe_right();
signals:
  void swipe_signal(Word::Language language);
  void swipe_left_end_of();
};
