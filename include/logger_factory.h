#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H

#include "logger.h"
#include <memory>

/**
 * @enum LoggerType
 * @brief Типы доступных логгеров
 */
enum class LoggerType {
    FILE,    ///< Логгирование в файл
    SOCKET   ///< Логгирование через сокет
};

/**
 * @class LoggerFactory
 * @brief Фабрика для создания объектов логгеров
 */
class LoggerFactory {
public:
    /**
     * @brief Создает логгер указанного типа
     * @param type Тип создаваемого логгера
     * @return Указатель на созданный логгер или nullptr при ошибке
     */
    static std::unique_ptr<Logger> createLogger(LoggerType type);
};

#endif // LOGGER_FACTORY_H