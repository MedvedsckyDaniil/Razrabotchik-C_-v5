#include "../include/logger_factory.h"
#include "../include/file_logger.h"
#include "../include/socket_logger.h"

std::unique_ptr<Logger> LoggerFactory::createLogger(LoggerType type) {
    switch (type) {
        case LoggerType::FILE:
            return std::make_unique<FileLogger>();
        case LoggerType::SOCKET:
            return std::make_unique<SocketLogger>();
        default:
            return nullptr;
    }
}