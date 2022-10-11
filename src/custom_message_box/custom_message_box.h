#pragma once

#include <QMessageBox>
#include <QString>

#include <vector>

/** Custom Message Box class which shared interation with user*/
class CustomMessageBox : public QMessageBox {

public:
  enum class Type {
    Yes,
    No,
    Ok,
    Great,
    Accept,
    Cancel
  }; ///< enum class which specifes types of user choices

private:
  /**
   * @brief setting_image method which sets image on messagebox label
   * @param name path to the image
   */
  void setting_image(const QString &name);

public:
  /**
   * @brief CustomMessageBox constructor method
   * @param widget main widget on which messagebox will be placed
   * @param title title of messagebox
   * @param content main content of messagebox
   */
  CustomMessageBox(QWidget *widget, const QString &content,
                   const QString &question);
  ~CustomMessageBox() { qDebug("delete"); }

  /**
   * @brief run method which causes appearing msgbox on screen
   * @param default_name type of main button, when user avoid clicking any
   * button, it will be automatically clicked
   * @param rest_names rest types of button in vector structure
   * @return custom type of button
   */
  Type run(Type default_name, const std::vector<Type> rest_names = {});

  /**
   * @brief create_detail_text method which create detail text of messagebox
   * @param text QString instance with some text
   */
  void create_detail_text(const QString &text);
};
