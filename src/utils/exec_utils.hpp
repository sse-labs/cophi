#ifndef DELPHICPP_EXECUTILS_HPP_
#define DELPHICPP_EXECUTILS_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <chrono>
#include <iostream>
#include <memory>

namespace Utils {

// Error Helper
static void errAndExit(std::string errMessage) {
  spdlog::error(errMessage);
  std::cerr << "exiting..." << std::endl;
  exit(1);
}

}

#endif  // DELPHICPP_EXECUTILS_HPP_