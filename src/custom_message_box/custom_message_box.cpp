#include "custom_message_box.h"

#include "../data/config_file.h"
#include "../image_button/image_button.h"
#include "../text_label/text_label.h"

#include <QPixmap>

#include <map>

namespace {
constexpr char LETTER_IMAGE[] = "../images/letter.png";
const std::map<CustomMessageBox::Type, QString> names = {
    {CustomMessageBox::Type::Ok, "OK"},
    {CustomMessageBox::Type::No, "No"},
    {CustomMessageBox::Type::Yes, "Yes"},
    {CustomMessageBox::Type::Great, "Great"},
    {CustomMessageBox::Type::Accept, "Accept"},
    {CustomMessageBox::Type::Cancel, "Cancel"}};
} // namespace

CustomMessageBox::CustomMessageBox(QWidget *widget, const QString &title,
                                   const QString &content)
    : QMessageBox(widget) {
  setWindowTitle(title);
  setText(content);
  setObjectName("messagebox");
  setting_image(LETTER_IMAGE);
}

void CustomMessageBox::setting_image(const QString &name) {
  auto iconx = QPixmap(name);
  iconx = iconx.scaledToWidth(WidgetData::MSGBOX_IMAGE_SIZE);
  setIconPixmap(iconx);
}

CustomMessageBox::Type
CustomMessageBox::run(Type default_name, const std::vector<Type> rest_names) {
  std::map<int, Type> indexes;
  indexes.insert({0, default_name});
  auto default_text = names.at(default_name);
  auto main = addButton(default_text, ButtonRole::NoRole);
  setEscapeButton(main);
  auto index = 1;
  for (auto name : rest_names) {
    indexes.insert({index, name});
    index++;
    auto text = names.at(name);
    addButton(text, ButtonRole::NoRole);
  }
  show();
  auto value = exec();
  return indexes.at(value);
}

void CustomMessageBox::create_detail_text(const QString &text) {
  setDetailedText(text);
}
