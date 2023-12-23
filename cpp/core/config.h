#ifndef CONFIG_H
#define CONFIG_H

#define PROJECT_ROOT_PATH                       "/home/matio/Workspace/Projects/software/eternity2/"
#define PUZZLE_DATA_FILE_DIRECTORY_PATH         PROJECT_ROOT_PATH "puzzle_data/"
#define PUZZLE_LOGS_FILE_DIRECTORY_PATH         PROJECT_ROOT_PATH "logs/"

#define PUZZLE_ETERNITY_2_DATA_FILE_NAME        "eternity2_pieces.json"
#define PUZZLE_DUMMY_DATA_FILE_NAME             "dummy_puzzle_pieces.json"
#define PUZZLE_VERY_EASY_DATA_FILE_NAME         "very_easy_puzzle_pieces.json"
#define PUZZLE_EASY_DATA_FILE_NAME              "easy_puzzle_pieces.json"

#define PUZZLE_ETERNITY_2_DATA_FILE_PATH        PUZZLE_DATA_FILE_DIRECTORY_PATH PUZZLE_ETERNITY_2_DATA_FILE_NAME
#define PUZZLE_DUMMY_DATA_FILE_PATH             PUZZLE_DATA_FILE_DIRECTORY_PATH PUZZLE_DUMMY_DATA_FILE_NAME
#define PUZZLE_VERY_EASY_DATA_FILE_PATH         PUZZLE_DATA_FILE_DIRECTORY_PATH PUZZLE_VERY_EASY_DATA_FILE_NAME
#define PUZZLE_EASY_DATA_FILE_PATH              PUZZLE_DATA_FILE_DIRECTORY_PATH PUZZLE_EASY_DATA_FILE_NAME

#define PUZZLE_INFOS_LOG_FILE_PATH              PUZZLE_LOGS_FILE_DIRECTORY_PATH "infos_logs.log"
#define PUZZLE_RAW_LOG_FILE_PATH                PUZZLE_LOGS_FILE_DIRECTORY_PATH "raw_logs.log"

#define PIECES_QUANTITY                         256
#define PUZZLE_X_DIMENSION                      16
#define PUZZLE_Y_DIMENSION                      16

#define UNIT_TEST_ADDITIONNAL_LOGS              0

#endif // CONFIG_H
