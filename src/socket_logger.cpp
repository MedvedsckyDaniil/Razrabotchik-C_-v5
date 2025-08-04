#include "../include/socket_logger.h"

bool SocketLogger::initialize(const std::string& serverAddress, LogLevel defaultLevel) {
    m_serverAddress = serverAddress;
    m_defaultLevel = defaultLevel;
    
    std::cout << "SocketLogger initialized (simulated mode) with server: " 
              << serverAddress << std::endl;
    return true;
}

void SocketLogger::setLogLevel(LogLevel level) {
    m_defaultLevel = level;
}

void SocketLogger::log(const std::string& message, LogLevel level) {
    if (level < m_defaultLevel) return;
    
    std::cout << "[SocketLogger] [" << getCurrentTime() << "] "
              << "[" << levelToString(level) << "] "
              << message << " (simulated send to " << m_serverAddress << ")" 
              << std::endl;
}

void SocketLogger::log(const std::string& message) {
    log(message, m_defaultLevel);
}