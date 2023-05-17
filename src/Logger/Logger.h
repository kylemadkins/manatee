#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

enum class LogType {
  Error,
  Info,
  Warning
};

struct LogEntry {
  LogType type;
  std::string message;
};

class Logger {
  public:
    static std::vector<LogEntry> messages;
    static void Err(const std::string& message);
    static void Log(const std::string& message);
    static void Warn(const std::string& message);
};

#endif
