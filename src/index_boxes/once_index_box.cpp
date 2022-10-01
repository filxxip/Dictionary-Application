#include "once_index_box.h"
#include "../detail_view/detail_view.h"

namespace {
constexpr char DETAIL_IMAGE[] = "images/glass.png";
}

OnceIndexBox::OnceIndexBox(QWidget *widget_, Word &word_, const QString &index,
                           Word::Language l1)
    : IndexBox(widget_, word_, index, l1),
      details_button(widget_, DETAIL_IMAGE,
                     Displays::DisplayStyle::SCALED_WIDTH, 30) {
  set_status(Status::READ_ONLY);
  details_button.setObjectName("bluecolor");
  index_entry_layout->addWidget(&details_button);

  QObject::connect(&details_button, &QPushButton::clicked, this, [this]() {
    emit creating_detail_view(word, base_language);
  });
}

void OnceIndexBox::set_status(Status status) {
  switch (status) {
  case IndexBox::Status::EDIT: {
    from_word_entry.setReadOnly(false);
    break;
  }
  case IndexBox::Status::READ_ONLY: {
    from_word_entry.setReadOnly(true);
    break;
  }
  }
}
