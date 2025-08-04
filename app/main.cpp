#include "../include/logger_factory.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <atomic>
#include <condition_variable>

class LoggingApp {
private:
    std::unique_ptr<Logger> logger;
    std::queue<std::pair<std::string, LogLevel>> logQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    std::atomic<bool> running{false};
    std::thread workerThread;

    void processLogs() {
        while (running || !logQueue.empty()) {
            std::unique_lock<std::mutex> lock(queueMutex);
            queueCV.wait(lock, [this]() {
                return !logQueue.empty() || !running;
            });

            if (!logQueue.empty()) {
                auto entry = logQueue.front();
                logQueue.pop();
                lock.unlock();

                logger->log(entry.first, entry.second);
            }
        }
    }

public:
    LoggingApp(const std::string& logPath, LogLevel defaultLevel) {
        logger = LoggerFactory::createLogger(LoggerType::FILE);
        if (!logger->initialize(logPath, defaultLevel)) {
            std::cerr << "Failed to initialize logger" << std::endl;
            std::exit(1);
        }

        running = true;
        workerThread = std::thread(&LoggingApp::processLogs, this);
    }

    ~LoggingApp() {
        running = false;
        queueCV.notify_all();
        if (workerThread.joinable()) {
            workerThread.join();
        }
    }

    void addLog(const std::string& message, LogLevel level) {
        std::lock_guard<std::mutex> lock(queueMutex);
        logQueue.emplace(message, level);
        queueCV.notify_one();
    }
};

void printUsage() {
    std::cout << "Usage: logger_app <log_file> <default_level>\n"
              << "Available levels: DEBUG, INFO, WARNING, ERROR\n"
              << "Example: logger_app app.log INFO\n";
}

LogLevel parseLogLevel(const std::string& levelStr) {
    if (levelStr == "DEBUG") return LogLevel::DEBUG;
    if (levelStr == "INFO") return LogLevel::INFO;
    if (levelStr == "WARNING") return LogLevel::WARNING;
    if (levelStr == "ERROR") return LogLevel::ERROR;
    return LogLevel::INFO; // default
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage();
        return 1;
    }

    std::string logFile = argv[1];
    LogLevel defaultLevel = parseLogLevel(argv[2]);

    LoggingApp app(logFile, defaultLevel);

    std::cout << "Logging application started. Enter messages in format: <LEVEL>:<message>\n"
              << "where <LEVEL> is one of these: ERROR, WARNING, INFO, DEBUG.\n"
              << "Before the first ':' must be <LEVEL>!\n"
              << "Type 'exit' to quit\n";

    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        size_t colonPos = input.find(':');
        if (colonPos != std::string::npos) {
            std::string levelStr = input.substr(0, colonPos);
            LogLevel level = parseLogLevel(levelStr);
            std::string message = input.substr(colonPos + 1);
            app.addLog(message, level);
        } else {
            app.addLog(input, defaultLevel);
        }
    }

    return 0;
}