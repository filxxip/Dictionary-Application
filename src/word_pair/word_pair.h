//#pragma once

//#include "../text_label/text_label.h"
//#include "../translation/translation.h"

//#include <QHBoxLayout>

// class CustomWordWindowObject : public QHBoxLayout {
// protected:
//  QWidget *widget; ///< main widget on which labels will be placed
//  Word &word;
//  TextLabel from_word_label; ///< label which contains first word

// public:
//  /**
//   * @brief CustomWordWindowObject constuctor method
//   * @param widget_ widget on which labels will be placed
//   * @param word reference to word whose translations should be shown on
//   widget
//   * @param from_language base language for word
//   * @param to_language translation language of word
//   */
//  CustomWordWindowObject(QWidget *widget_, Word &word_,
//                         Word::Language from_language);
//};

///** WordPair class which contain two text label compressed in one
///QHBoxLayout*/
// class WordPair : public CustomWordWindowObject {
// private:
//  TextLabel to_word_label; ///< label which contains second word

// public:
//  /**
//   * @brief WordPair constuctor method
//   * @param widget_ widget on which labels will be placed
//   * @param word reference to word whose translations should be shown on
//   widget
//   * @param from_language base language for word
//   * @param to_language translation language of word
//   */
//  WordPair(QWidget *widget_, Word &word_, Word::Language from_language,
//           Word::Language to_language);
//};

// class WordOnce : public CustomWordWindowObject {
// public:
//  WordOnce(QWidget *widget_, Word &word, Word::Language from_language);
//};
