#ifndef DELPHICPP_LOGGING_HPP_
#define DELPHICPP_LOGGING_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <iostream>
#include <memory>

namespace Utils {

void initializeLogger() {
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);
    console_sink->set_pattern("[delphi_cpp] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/delphi_cpp.log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = { file_sink, console_sink };

    spdlog::set_default_logger(std::make_shared<spdlog::logger>("delphi_cpp_logger", sink_list));
    spdlog::flush_on(spdlog::level::trace);

  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log Initialization Failed: " << ex.what() << std::endl;
    exit(1);
  }
}

}

#endif  // DELPHICPP_LOGGING_HPP_