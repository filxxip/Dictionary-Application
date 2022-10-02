#include "vertical_label.h"

namespace {
constexpr int WORD_SIZE = 20;
constexpr int ROTATE_DEGREES = 270;
constexpr int LABEL_MARGINS = 30;
constexpr char FONT_TYPE[] = "Helvetica";
} // namespace

VerticalLabel::VerticalLabel(QWidget *widget_, const QString &text_)
    : TextLabel(widget_, text_) {
  setAlignment(Qt::AlignRight);
}
void VerticalLabel::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setPen(Qt::white);
  painter.rotate(ROTATE_DEGREES);
  painter.setFont(QFont(FONT_TYPE, WORD_SIZE));
  QFontMetrics fm = painter.fontMetrics();
  auto width = fm.horizontalAdvance(text());
  painter.drawText(-width - LABEL_MARGINS, LABEL_MARGINS, text());
  setFixedHeight(width + LABEL_MARGINS * 2);
}
