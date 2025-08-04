#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>

/**
 * @enum LogLevel
 * @brief Уровни важности для фильтрации лог-сообщений
 * @details Сообщения с уровнем ниже установленного порога 
 * не будут записываться в лог.
 */
enum class LogLevel {
    DEBUG,   ///< Отладочная информация
    INFO,    ///< Информационные сообщения (стандартный уровень)
    WARNING, ///< Предупреждения
    ERROR    ///< Ошибки (наивысший уровень)
};

/**
 * @class Logger
 * @brief Абстрактный базовый класс для системы логирования
 * @details Определяет единый интерфейс для всех реализаций логгеров.
 * Поддерживает уровни важности сообщений и временные метки.
 */
class Logger {
protected:
    LogLevel m_defaultLevel; ///< Текущий минимальный уровень логирования

    /**
     * @brief Генерирует строку с текущим временем
     * @return Строка в формате "YYYY-MM-DD HH:MM:SS"
     */
    virtual std::string getCurrentTime() const;

    /**
     * @brief Преобразует уровень логирования в строку
     * @param level Уровень логирования
     * @return Строковое представление уровня ("DEBUG", "INFO" и т.д.)
     */
    virtual std::string levelToString(LogLevel level) const;

public:
    virtual ~Logger() = default;
        
    /**
     * @brief Инициализирует логгер
     * @param initParam Параметр инициализации (зависит от реализации)
     * @param defaultLevel Уровень логирования по умолчанию
     * @return true если инициализация прошла успешно
     */
    virtual bool initialize(const std::string& initParam, LogLevel defaultLevel) = 0;
    
    /**
     * @brief Устанавливает минимальный уровень логирования
     * @param level Новый уровень логирования
     */
    virtual void setLogLevel(LogLevel level) = 0;
    
    /**
     * @brief Записывает сообщение в лог с указанным уровнем
     * @param message Текст сообщения
     * @param level Уровень важности сообщения
     */
    virtual void log(const std::string& message, LogLevel level) = 0;
    
    /**
     * @brief Записывает сообщение с уровнем по умолчанию
     * @param message Текст сообщения
     */
    virtual void log(const std::string& message) = 0;
};

#endif // LOGGER_H