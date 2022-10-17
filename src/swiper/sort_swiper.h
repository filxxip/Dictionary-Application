#pragma once
#include "swiper.h"

/** SortSwiper class which allows user to choose type of sorting data*/
class SortSwiper : public Swiper {
  Q_OBJECT
public:
  enum class SortOptions { NUMERIC, ALPHABETIC, WORD_LENGHT, DATE };
  std::map<SortOptions, QString> sort_names = {
      {SortOptions::NUMERIC, "numeric"},
      {SortOptions::ALPHABETIC, "alphabetic"},
      {SortOptions::WORD_LENGHT, "word_lenght"},
      {SortOptions::DATE, "date"},
  };

private:
  std::vector<SortOptions> options; ///< options used in swiper

  /**
   * @brief swipe_method used during swiping
   */
  void swipe_method() override;
  int get_options_size() override { return options.size(); }

public:
  /**
   * @brief SortSwiper constructor method
   * @param widget_ widget on which swiper will be placed
   * @param label_width width of swiper's main label
   * @param image_size size of arrow
   */
  SortSwiper(QWidget *widget_, int label_width, int image_size);

  /**
   * @brief set_text method which sets new option on swiper
   * @param option
   */
  void set_text(SortOptions option);

  /**
   * @brief set_options method which sets options which are used during swiping
   * on widget
   * @param options_ options which user can choose
   */
  void set_options(std::vector<SortOptions> options_);

  /**
   * @brief get_text method which provide current option on swiper
   * @return enum class SortOptions instance
   */
  SortOptions get_text() const;

signals:
  void swipe_signal(SortOptions language);
};
