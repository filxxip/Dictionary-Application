#pragma once
#include "swiper.h"

class LanguageSwiper : public Swiper {
  Q_OBJECT
private:
  std::vector<Word::Language> options;
  void swipe_method() override;
  int get_options_size() override { return options.size(); }

public:
  /**
   * @brief LanguageSwiper constructor method
   * @param widget_ widget on which swiper will be placed
   * @param label_width width of swiper's main label
   * @param image_size size of arrow
   */
  LanguageSwiper(QWidget *widget_, int label_width, int image_size);

  /**
   * @brief set_text method which sets new option on swiper
   * @param option
   */
  void set_text(Word::Language language);

  /**
   * @brief set_options method which sets options which are used during swiping
   * on widget
   * @param options_ options which user can choose
   */
  void set_options(std::vector<Word::Language> options_);

  /**
   * @brief get_text method which provide current option on swiper
   * @return enum class Word::Language instance
   */
  Word::Language get_text() const;

signals:
  void swipe_signal(Word::Language language);
};
