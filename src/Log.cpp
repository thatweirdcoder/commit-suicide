//
// Created by Muhamed Hassan on 2019-06-06.
//
#include "Log.h"


std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_Logger = spdlog::stdout_color_mt("Logger");
    s_Logger->set_level(spdlog::level::trace);
}

