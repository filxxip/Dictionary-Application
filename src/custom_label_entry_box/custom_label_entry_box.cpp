#include "custom_label_entry_box.h"
#include <QDebug>
#include <QStyle>

LabelEntryBox::LabelEntryBox(QWidget *widget, const QString &label_text,
                             const QString &entry_placeholder,
                             EntryLine::Status entry_type)
    : label(new TextLabel(widget, label_text)),
      entry(new EntryLine(widget, entry_type)) {
  entry->setPlaceholderText(entry_placeholder);
}

QString LabelEntryBox::get_text() { return entry->text(); }

void LabelEntryBox::set_text(const QString &text) { entry->setText(text); }

QHBoxLayout *LabelEntryBox::create_layout(int height, int spacing,
                                          const QMargins &margin) {
  QHBoxLayout *layout = new QHBoxLayout;
  label->setFixedHeight(height);
  entry->setFixedHeight(height);
  layout->addWidget(label.get());
  layout->addWidget(entry.get());
  layout->setSpacing(spacing);
  layout->setContentsMargins(margin);
  return layout;
}

void LabelEntryBox::set_label_width(int width) { label->setFixedWidth(width); }

void LabelEntryBox::set_entry_width(int width) { entry->setFixedWidth(width); }

void LabelEntryBox::clear() { entry->clear(); }

QString LabelEntryBox::get_style_sheet() { return entry->styleSheet(); }

EntryLine *LabelEntryBox::get_entryline() { return entry.get(); }

void LabelEntryBox::set_read_only(bool status) { entry->setReadOnly(status); }

void LabelEntryBox::change_entry_line_object_name(
    const QString &new_object_name) {
  entry->set_object_name_stylesheet(new_object_name);
}
