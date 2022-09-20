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
    main.cpp
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wpedantic -Wshadow")

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON)

target_link_libraries(${PROJECT_NAME}
    # Qt5::Quick
    Qt5::Widgets
)
