#ifndef EDU_SERVICE_MESH_LOG_H
#define EDU_SERVICE_MESH_LOG_H

#include <memory>
#include <string>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace edu {

enum class LOG_LEVEL {
    TRACE    = 0,
    DEBUG    = 1,
    INFO     = 2,
    WARN     = 3,
    ERROR    = 4,
    CRITICAL = 5,
    OFF      = 6
};

class Log final {
  public:
    Log(const std::string& name);
    ~Log();

  public:
    //需要在初始化之前调用
    void LogOnConsole(bool v);
    void SetOutputDir(const std::string& dir);
    void SetFormat(const std::string& format);
    void SetLogLevel(LOG_LEVEL level);

    int Initialize();

    template <typename... ARGS> void Trace(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->trace(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->trace(fmt, std::forward<ARGS>(args)...);
    }
    template <typename... ARGS> void Debug(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->debug(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->debug(fmt, std::forward<ARGS>(args)...);
    }
    template <typename... ARGS> void Info(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->info(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->info(fmt, std::forward<ARGS>(args)...);
    }
    template <typename... ARGS> void Warn(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->warn(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->warn(fmt, std::forward<ARGS>(args)...);
    }
    template <typename... ARGS> void Error(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->error(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->error(fmt, std::forward<ARGS>(args)...);
    }
    template <typename... ARGS>
    void Critical(const std::string& fmt, ARGS... args)
    {
        if (console_logger_)
            console_logger_->critical(fmt, std::forward<ARGS>(args)...);
        if (file_logger_)
            file_logger_->critical(fmt, std::forward<ARGS>(args)...);
    }

    std::shared_ptr<spdlog::logger> GetConsoleLogger()
    {
        return console_logger_;
    }

  private:
    std::shared_ptr<spdlog::logger> file_logger_;
    std::shared_ptr<spdlog::logger> console_logger_;
    bool                            log_on_console_;
    LOG_LEVEL                       log_level_;
    std::string                     format_;
    std::string                     dir_;
    std::string                     logger_name_;
};

extern std::shared_ptr<Log> _sdk_logger;
extern std::shared_ptr<Log> _grpc_logger;

#if SMS_DEBUG
#    define log_e(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Error("[{}:{}][{}]: " + std::string(msg),         \
                                   __FILE__, __LINE__, __FUNCTION__,           \
                                   ##__VA_ARGS__);                             \
            }                                                                  \
        } while (0)
#    define log_t(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Trace("[{}:{}][{}]: " + std::string(msg),         \
                                   __FILE__, __LINE__, __FUNCTION__,           \
                                   ##__VA_ARGS__);                             \
            }                                                                  \
        } while (0)
#    define log_i(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Info("[{}:{}][{}]: " + std::string(msg),          \
                                  __FILE__, __LINE__, __FUNCTION__,            \
                                  ##__VA_ARGS__);                              \
            }                                                                  \
        } while (0)
#    define log_w(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Warn("[{}:{}][{}]: " + std::string(msg),          \
                                  __FILE__, __LINE__, __FUNCTION__,            \
                                  ##__VA_ARGS__);                              \
            }                                                                  \
        } while (0)
#    define log_c(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Critical("[{}:{}][{}]: " + std::string(msg),      \
                                      __FILE__, __LINE__, __FUNCTION__,        \
                                      ##__VA_ARGS__);                          \
            }                                                                  \
        } while (0)
#    define log_d(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Debug("[{}:{}][{}]: " + std::string(msg),         \
                                   __FILE__, __LINE__, __FUNCTION__,           \
                                   ##__VA_ARGS__);                             \
            }                                                                  \
        } while (0)
#else
#    define log_e(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Error(": " + std::string(msg), ##__VA_ARGS__);    \
            }                                                                  \
        } while (0)
#    define log_t(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Trace(": " + std::string(msg), ##__VA_ARGS__);    \
            }                                                                  \
        } while (0)
#    define log_i(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Info(": " + std::string(msg), ##__VA_ARGS__);     \
            }                                                                  \
        } while (0)
#    define log_w(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Warn(": " + std::string(msg), ##__VA_ARGS__);     \
            }                                                                  \
        } while (0)
#    define log_c(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Critical(": " + std::string(msg), ##__VA_ARGS__); \
            }                                                                  \
        } while (0)
#    define log_d(msg, ...)                                                    \
        do {                                                                   \
            if (_sdk_logger) {                                                 \
                _sdk_logger->Debug(": " + std::string(msg), ##__VA_ARGS__);    \
            }                                                                  \
        } while (0)
#endif
}  // namespace edu
#endif