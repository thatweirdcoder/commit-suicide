//
// Created by Muhamed Hassan on 8/26/19.
//

#pragma once

#ifdef DEBUG
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"



std::shared_ptr<spdlog::logger> Logger;

void initLogger(void) {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    Logger = spdlog::stdout_color_mt("Logger");
    Logger->set_level(spdlog::level::trace);

}

#define LOG_TRACE(...) Logger->trace(__VA_ARGS__)
#define LOG_INFO(...) Logger->info(__VA_ARGS__)
#define LOG_WARN(...) Logger->warn(__VA_ARGS__)
#define LOG_ERROR(...) Logger->error(__VA_ARGS__)
#define LOG_FATAL(...) Logger->fatal(__VA_ARGS__)
#else
void initLogger(void) {}
#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#endif

