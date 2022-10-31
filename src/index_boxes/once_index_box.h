#pragma once

#include "index_box.h"

class OnceIndexBox : public IndexBox {
  Q_OBJECT
private:
  ImageButton details_button; ///< button which show details about given word
public:
  OnceIndexBox(QWidget *widget_, Word &word_, const QString &index,
               Word::Language l1);

  /**
   * @brief set_status method which change status of entry
   * @param status status enum type, ReadOnly or Edit
   */
  void set_status(Status status);
  void set_visible(bool status) override;
};
