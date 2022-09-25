#pragma once

#include <QMargins>
#include <QRect>
#include <unordered_map>

namespace Json {
constexpr char NAME[] = "name";
constexpr char SURNAME[] = "surname";
constexpr char AGE[] = "age";
constexpr char COUNTRY[] = "country";
constexpr char SCHOOL[] = "school";
constexpr char PASSWORD[] = "password";
constexpr char EMAIL[] = "email";
constexpr char REPEAT_PASSWORD[] = "repeat pass";
constexpr char NAME_JSON[] = "name";
constexpr char WORDLIST_JSON[] = "dict_wordlist";

} // namespace Json

namespace Date_Values {
constexpr int DAY_HOURS = 24;
constexpr int DAY_YEAR = 365;
constexpr int MINUTE_HOUR = 60;
constexpr int SECOND_MINUTE = 60;
} // namespace Date_Values

namespace Placeholders {
constexpr char LOGIN_PLACEHOLDER[] = "your_login@adres.com";
constexpr char PASSWORD_PLAHOLDER[] = "password";
constexpr char NAME[] = "write your name...";
constexpr char SURNAME[] = "write your surname...";
constexpr char AGE[] = "write your age...";
constexpr char COUNTRY[] = "write your country...";
constexpr char SCHOOL[] = "write your school...";
constexpr char PASSWORD[] = "write your password...";
constexpr char EMAIL[] = "wrtie your email...";
constexpr char REPEAT_PASSWORD[] = "repeat your password...";
constexpr char NEW_DICT_PLACEHOLDER[] = "write dictionary name";
} // namespace Placeholders

namespace MaxValues {
constexpr int MAX_PERSON_NUM = 100;

}

namespace Colors {
constexpr char RED[] = "red";
constexpr char GREEN[] = "green";
constexpr char DEFAULT[] = "";
constexpr char DARK_RED[] = "rgb(51, 18, 18)";
} // namespace Colors

namespace WidgetData {
constexpr QMargins NEW_GRPBOX_MARGINS = {10, 20, 10, 5};
constexpr int NEW_DICT_BUTTON = 55;
constexpr int MSGBOX_IMAGE_SIZE = 50;
constexpr int LOGIN_BOX_HEIGHT = 40;
constexpr int SEE_BUTTON_HEIGHT = 50;
constexpr QRect TAB_WIDGET_POSITION = {100, 100, 700, 700};
constexpr QMargins DEFAULT_TEXT_MARGINS = {10, 5, 5, 5};
constexpr int LOGIN_LABEL_WIDTH =
    130; ///< width of label which is placed next to login entryline
constexpr int PASSWORD_LABEL_WIDTH =
    130; ///< width of label which is placed next to password entryline
constexpr int IMAGE_HEIGHT = 150; ///< height of main title image
constexpr int BUTTONS_SPACING =
    100; ///< spacing beetween clear and submit button
constexpr int LOGS_SPACING =
    20; ///< spacing beetween entry and label in logs panel
constexpr int REGISTER_SPACING =
    10; ///< spacing beetween entry and label in register panel
constexpr int EXIT_HEIGHT = 45;
constexpr int EXIT_POSITION_X = 630;
constexpr int EXIT_POSITION_Y = 600;
constexpr int WORDLIST_VIEW_IMG_HEIGHT = 100;
constexpr int ELEMENT_HEIGHT = 30;
constexpr int ELEMENT_WIDTH = 200;
constexpr char SET_BUTTON_TEXT[] = "SET";
constexpr QMargins WORDLIST_VIEW_IMG_MARGINS = {70, 50, 70, 50};
constexpr QMargins REGISTER_BOX_MARGINS = {30, 0, 30, 0};
constexpr QMargins BUTTONS_MARGINS = {100, 0, 100,
                                      0}; ///< margins of buttons layout
constexpr QMargins MAIN_LAYOUT_MARGINS = {40, 0, 40,
                                          40}; ///< margins of main layout
constexpr char NEW_DICT_LABEL_TEXT[] = "new dictionary";
constexpr int NEW_DICT_SPACING = 20;
constexpr char LOGIN_LABEL_TEXT[] =
    "LOGIN"; ///< text which will be placed on login label
constexpr char PASSWORD_LABEL_TEXT[] =
    "PASSWORD"; ///< text which will be placed on password label
constexpr char SUBMIT_BUTTON_TEXT[] =
    "SUBMIT"; ///< text which will be placed on submit button
constexpr char CLEAR_BUTTON_TEXT[] =
    "CLEAR"; ///< text which will be placed on clear button
constexpr char REGISTER_BUTTON_TEXT[] = "REGISTER";
constexpr QMargins DEFAULT_MARGINS = {
    60, 0, 60, 0}; ///< Default values of margins of main layout
constexpr int DEFAULT_FONT_SIZE = 14;
constexpr int DEFAULT_WIDTH = 150;
constexpr char DISCARD_NAME[] = "DISCARD";
constexpr char SAVE_NAME[] = "SAVE";
constexpr char CHANGE_NAME[] = "CHANGE";
} // namespace WidgetData

namespace Regex {
constexpr char EMAIL_CHECK[] = ".*@.*\\.(com|pl|eu)";
} // namespace Regex

namespace Titles {
constexpr char LOGIN[] = "log in";
constexpr char REGISTER[] = "register";
constexpr char DATA[] = "data";
constexpr char WORDLIST[] = "wordlist";

} // namespace Titles
