#include "../include/file_logger.h"

FileLogger::FileLogger() : m_logFile(), m_filename() {}

FileLogger::~FileLogger() {
    if (m_logFile.is_open()) {
        m_logFile.close();
    }
}

bool FileLogger::initialize(const std::string& filename, LogLevel defaultLevel) {
    m_filename = filename;
    m_defaultLevel = defaultLevel;
    
    m_logFile.open(filename, std::ios::out | std::ios::app);
    if (!m_logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
        return false;
    }
    
    return true;
}

void FileLogger::setLogLevel(LogLevel level) {
    m_defaultLevel = level;
}

void FileLogger::log(const std::string& message, LogLevel level) {
    if (level < m_defaultLevel) return;
    
    if (!m_logFile.is_open()) {
        std::cerr << "Log file is not open" << std::endl;
        return;
    }
    
    m_logFile << "[" << getCurrentTime() << "] "
              << "[" << levelToString(level) << "] "
              << message << std::endl;
}

void FileLogger::log(const std::string& message) {
    log(message, m_defaultLevel);
}