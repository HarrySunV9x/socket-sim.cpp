//
// Created by WorkHarry on 2024/8/14.
//
#include "include/logger.h"

std::shared_ptr<spdlog::logger> fLogger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");
