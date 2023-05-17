#include <vector>
#include <chrono>
#include <ctime>
#include <string>
#include <iostream>

#include "Logger.h"

std::vector<LogEntry> Logger::messages;

std::string GetTime() {
  std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string buffer(30, '\0');
  std::strftime(&buffer[0], buffer.size(), "%a %b %d %H:%M:%S %Y", std::localtime(&now));
  return buffer;
}

void RecordMessage(LogType type, std::string message) {
  std::string typestrs[3] = { "31mERR", "32mINFO", "33mWARN" };
  std::string typestr = typestrs[static_cast<int>(type)];
  LogEntry l;
  l.type = type;
  l.message = "\033[" + typestr + ": [" + GetTime() + "] - " + message + "\033[0m";
  std::cerr << l.message << std::endl;
  Logger::messages.push_back(l);
}

void Logger::Err(const std::string& message) {
  RecordMessage(LogType::Error, message);
}

void Logger::Log(const std::string& message) {
  RecordMessage(LogType::Info, message);
}

void Logger::Warn(const std::string& message) {
  RecordMessage(LogType::Warning, message);
}
