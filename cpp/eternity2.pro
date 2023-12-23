TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest -lpthread -lboost_system -lboost_filesystem

DEFINES += UNIT_TEST_MODE=1

# Core
SOURCES += \
        core/main.cpp \
        core/puzzle_logger.cpp \
        core/puzzle_solver.cpp \
        core/puzzle_manager.cpp

HEADERS += \
        core/puzzle.h \
        core/puzzle_logger.h \
        core/puzzle_solver.h \
        core/puzzle_manager.h \
        core/config.h

# Unit tests
SOURCES += \
        unit_tests/puzzle_manager_unit_test.cpp

