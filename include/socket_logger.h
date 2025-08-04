#ifndef SOCKET_LOGGER_H
#define SOCKET_LOGGER_H

#include "logger.h"
#include <string>
#include <iostream>

/**
 * @class SocketLogger
 * @brief Имитация логгера для записи в сетевой сокет
 * @details Реализует интерфейс Logger, симулируя запись логов в сетевой сокет.
 * В текущей реализации все сообщения выводятся в стандартный поток вывода
 * с пометкой о том, что они были бы отправлены по сети.
 */
class SocketLogger : public Logger {
public:
    /**
     * @brief Конструктор по умолчанию
     */
    SocketLogger() = default;
    
    /**
     * @brief Деструктор по умолчанию
     */
    ~SocketLogger() override = default;
    
    /**
     * @brief Инициализация сокет-логгера (режим симуляции)
     * @param serverAddress Адрес сервера в формате "host:port" (для имитации)
     * @param defaultLevel Уровень логирования по умолчанию
     * @return Всегда возвращает true (в режиме симуляции)
     * 
     * @note В реальной реализации должна возвращать false при невозможности
     *       установить соединение с указанным сервером
     */
    bool initialize(const std::string& serverAddress, LogLevel defaultLevel) override;
    
    /**
     * @brief Установка минимального уровня логируемых сообщений
     * @param level Новый уровень логирования
     */
    void setLogLevel(LogLevel level) override;
    
    /**
     * @brief Логирование сообщения с указанным уровнем важности
     * @param message Текст сообщения
     * @param level Уровень важности сообщения
     * 
     * @note В режиме симуляции выводит сообщение в stdout с пометкой [SocketLogger]
     */
    void log(const std::string& message, LogLevel level) override;
    
    /**
     * @brief Логирование сообщения с уровнем по умолчанию = m_defaultLevel
     * @param message Текст сообщения
     */
    void log(const std::string& message) override;

private:
    std::string m_serverAddress; ///< Адрес сервера для имитации (формат "host:port")
};

#endif // SOCKET_LOGGER_H