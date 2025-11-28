cmake_minimum_required(VERSION 3.16)
project(untitled3)  # اسم المشروع زي ما انت عايزه

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ملفات الهيدر
set(HEADERS
        boardgame_classes.h
        sus_classes.h
        game3h.h
        game10h.h
)

# ملفات المصدر
set(SOURCES
        main.cpp
        sus_classes.cpp
        game3h.cpp
        game10h.cpp
)

# إنشاء التطبيق التنفيذي
add_executable(untitled3 ${SOURCES} ${HEADERS})
