#pragma once

#include "../image_button/image_button.h"
#include "../translation/translation.h"

#include <QHBoxLayout>
#include <QStringLiteral>
#include <QWidget>

class CustomizeImageButton : public ImageButton {
  Q_OBJECT
public:
  CustomizeImageButton(QWidget *widget, const QString &image_source);
};

namespace {
const QString IMAGE_FILE QStringLiteral("images/%1");
constexpr int IMAGE_HEIGHT = 40;
}; // namespace

class ConfigDetailViewPanel : public QHBoxLayout {
  Q_OBJECT

private:
  QWidget *main_widget;
  CustomizeImageButton trash_all_button;
  CustomizeImageButton add_button;
  CustomizeImageButton edit_button;
  CustomizeImageButton cancel_button;
  CustomizeImageButton confirm_button;
  Word &word;

  void connect_button();

public:
  enum class Status { NORMAL, EDIT };
  ConfigDetailViewPanel(QWidget *widget, Word &word_);
  void set_status(Status status);

public slots:
  void delete_word_slot();
  void add_new_word_slot();
  void edit_word_slot();
  void confirm_changes_slot();
  void cancel_changes_slot();

signals:
  void delete_word_signal(Word &word);
  void add_new_word();
  void edit_word_signal(Word &word);
  void confirm_changes_singal(Word &word);
};
