#set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
#cmake_minimum_required(VERSION 3.16)

project(dic_project)

find_package(Qt5 5.12.8 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    src/base_tab_widget/base_tab_widget.cpp
    src/translation/translation.cpp
    src/date/date.cpp
    src/date/time_delta.cpp
    src/dictionary/dictionary.cpp
    src/person/person.cpp
    src/regex_check/regex_check.cpp
    src/custom_list/custom_list.cpp
    src/data/setting_person_list.cpp
    src/date/current_date.cpp
    src/main_class/main_class.cpp
    src/custom_entry_line/entry_line.cpp
    src/custom_widget/custom_widget.cpp
    src/text_label/text_label.cpp
    src/image_label/image_label.cpp
    src/login_view/login_view.cpp
    src/text_button/text_button.cpp
    src/delay/delay.cpp
    src/register_window/register_window.cpp
    src/person/person_errors.cpp
    src/image_button/image_button.cpp
    src/person_data_window/person_data_window.cpp
    src/custom_label_entry_box/custom_label_entry_box.cpp
    src/change_color/change_color.cpp
    src/custom_message_box/custom_message_box.cpp
    src/custom_completer/custom_completer.cpp
    src/wordlist_widget/wordlist_widget.cpp
    src/double_grp_box/double_grp_box.cpp
    src/custom_vbox_layout/custom_vbox_layout.cpp
    src/content_layout/content_layout.cpp
    src/newdict_layout/newdict_layout.cpp
    src/word_window/word_window.cpp
    src/swiper/swiper.cpp
    src/vertical_label/vertical_label.cpp
    src/index_boxes/index_box.cpp
    src/index_boxes/double_index_box.cpp
    src/index_boxes/once_index_box.cpp
    src/detail_view/detail_view.cpp
    src/detail_view_one_language_layout/detail_view_one_language_layout.cpp
    src/config_detail_view_panel/config_detail_view_panel.cpp
    src/add_new_word/add_new_word.cpp
    src/swiper/direction_swiper.cpp
    src/swiper/sort_swiper.cpp
    src/swiper/language_swiper.cpp
    main.cpp
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow")

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON)

target_link_libraries(${PROJECT_NAME}
    # Qt5::Quick
    Qt5::Widgets
)
