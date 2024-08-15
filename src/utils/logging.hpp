#ifndef DELPHICPP_LOGGING_HPP_
#define DELPHICPP_LOGGING_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <chrono>
#include <iostream>
#include <memory>

namespace Utils {

// this returns the logger, but if you want to use the logger 
// in other translation units (cpp files), call ``
void initializeLogger() {
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::trace);
    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l]  %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/delphi_cpp.log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = { file_sink, console_sink };

    auto logger = std::make_shared<spdlog::logger>("delphi_cpp", sink_list);

    // IMPORTANT SETTINGS (they might actually not do anything, i dunno)
    logger->flush_on(spdlog::level::trace);
    logger->should_log(spdlog::level::trace);
    logger->set_level(spdlog::level::trace);
    //spdlog::set_level(spdlog::level::trace);

    // set as default logger
    spdlog::set_default_logger(logger);

  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log Initialization Failed: " << ex.what() << std::endl;
    exit(1);
  }
}

}

#endif  // DELPHICPP_LOGGING_HPP_