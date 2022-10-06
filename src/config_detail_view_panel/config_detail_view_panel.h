#pragma once

#include "../image_button/image_button.h"
#include "../translation/translation.h"

#include <QHBoxLayout>
#include <QStringLiteral>
#include <QWidget>

/** CustomizeImageButton class is a class inherited from ImageButton class which
 * some extra specified features*/
class CustomizeImageButton : public ImageButton {
  Q_OBJECT
public:
  /**
   * @brief CustomizeImageButton costructor method
   * @param widget widget on which imagebutton will be shown
   * @param image_source qstring instance which is a source to image data
   */
  CustomizeImageButton(QWidget *widget, const QString &image_source);
};

/** ConfigDetailViewPanel is a class used for performing activities on specified
 * word */
class ConfigDetailViewPanel : public QHBoxLayout {
  Q_OBJECT

private:
  QWidget *main_widget; ///*main widget on which buttons will be placed
  CustomizeImageButton
      trash_all_button;            ///< imagebutton used for removing whole word
  CustomizeImageButton add_button; ///< button used for adding new word
  CustomizeImageButton edit_button; ///< button used for editing data
  CustomizeImageButton
      cancel_button; ///< button used for removing changes made by user
  CustomizeImageButton
      confirm_button; ///< button used for confirming changes made by user
  Word &word;         ///< main word on which operation will be done

  void connect_button();

public:
  enum class Status { NORMAL, EDIT };

  /**
   * @brief ConfigDetailViewPanel constructor method
   * @param widget widget on which buttons are placed
   * @param word_ reference to word
   */
  ConfigDetailViewPanel(QWidget *widget, Word &word_);

  /**
   * @brief set_status method which sets new status of buttons
   * @param status new status of buttons
   */
  void set_status(Status status);

public slots:

  /**
   * @brief delete_word_slot method used for removing word
   */
  void delete_word_slot();

  /**
   * @brief add_new_word_slot method used for adding new word
   */
  void add_new_word_slot();

  /**
   * @brief edit_word_slot used for edding current word
   */
  void edit_word_slot();

  /**
   * @brief confirm_changes_slot used for confirming changes made by user
   */
  void confirm_changes_slot();

  /**
   * @brief cancel_changes_slot used for canceling changes made by user
   */
  void cancel_changes_slot();

signals:
  void delete_word_signal(Word &word);
  void add_new_word();
  void edit_word_signal(Word &word);
  void confirm_changes_singal(Word &word);
};
