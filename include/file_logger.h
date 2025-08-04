#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "logger.h"
#include <fstream>
#include <iostream>

/**
 * @class FileLogger
 * @brief Реализация логгера для записи сообщений в файл
 * @details Наследует интерфейс Logger и предоставляет функциональность
 * для записи логов в текстовый файл с учетом уровня важности.
 */
class FileLogger : public Logger {
private:
    std::ofstream m_logFile;  ///< Поток для записи в файл
    std::string m_filename;   ///< Имя файла журнала

public:
    /**
     * @brief Конструктор по умолчанию
     */
    FileLogger();
    
    /**
     * @brief Деструктор, закрывает файл при уничтожении объекта
     */
    ~FileLogger() override;
    
    /**
     * @brief Инициализация файлового логгера
     * @param filename Имя файла для записи логов
     * @param defaultLevel Уровень логирования по умолчанию
     * @return true если инициализация прошла успешно, false в случае ошибки
     */
    bool initialize(const std::string& filename, LogLevel defaultLevel) override;
    
    /**
     * @brief Установка уровня логирования
     * @param level Новый уровень логирования
     */
    void setLogLevel(LogLevel level) override;
    
    /**
     * @brief Запись сообщения в лог с указанным уровнем важности
     * @param message Текст сообщения
     * @param level Уровень важности сообщения
     */
    void log(const std::string& message, LogLevel level) override;
    
    /**
     * @brief Запись сообщения в лог с уровнем по умолчанию
     * @param message Текст сообщения
     */
    void log(const std::string& message) override;
};

#endif // FILE_LOGGER_H