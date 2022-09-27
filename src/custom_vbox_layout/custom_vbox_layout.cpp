#include "custom_vbox_layout.h"
#include "../data/config_file.h"

namespace {
constexpr char GROUPBOX_NAME[] = "smallgroupbox";
} // namespace

CustomVBoxLayout::CustomVBoxLayout(QWidget &widget_)
    : QObject(), widget(widget_), layout(std::make_unique<QVBoxLayout>()) {
  groupbox = create_groupbox();
  groupbox->setLayout(layout.get());
}

const std::unique_ptr<QVBoxLayout> &CustomVBoxLayout::get_layout() {
  return layout;
};

const std::unique_ptr<QGroupBox> &CustomVBoxLayout::get_groupbox() {
  return groupbox;
};

std::unique_ptr<QGroupBox> CustomVBoxLayout::create_groupbox() { // done
  auto box = std::make_unique<QGroupBox>();
  box->setEnabled(true);
  box->setObjectName(GROUPBOX_NAME);
  box->setFixedWidth(WidgetData::ELEMENT_WIDTH);
  return box;
}
