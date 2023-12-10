TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lgtest -lpthread -lboost_system -lboost_filesystem

DEFINES += UNIT_TEST_MODE=1

SOURCES += \
        core/main.cpp \
        core/PuzzleLogger.cpp \
        core/PuzzleSolver.cpp \
        core/PuzzleManager.cpp

HEADERS += \
        core/PuzzleLogger.h \
        core/Puzzle.h \
        core/PuzzleSolver.h \
        core/PuzzleManager.h \
        core/config.h

SOURCES += \
        unit_tests/tdd_unit_test.cpp

HEADERS += \
        unit_tests/tdd_unit_test.h
