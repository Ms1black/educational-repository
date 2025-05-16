#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QString>

class TableManager;
class QWidget;

/**
 * @brief Класс FileManager отвечает за операции загрузки данных из файла и экспорта данных в файл.
 * Он не наследуется от других классов и не реализует интерфейсы в данном контексте.
 */

class FileManager
{
public:
    /**
     * @brief Конструктор по умолчанию для FileManager.
     */
    FileManager();

    /**
     * @brief Загружает данные из указанного файла в TableManager.
     * @param fileName Имя файла для загрузки.
     * @param tableManager Указатель на TableManager для добавления данных.
     * @param parentWidget Указатель на родительский виджет для отображения сообщений.
     * @return true, если данные успешно загружены, иначе false.
     */
    bool loadDataFromFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget);
    /**
     * @brief Экспортирует данные из TableManager в указанный файл.
     * @param fileName Имя файла для экспорта.
     * @param tableManager Указатель на TableManager для получения данных.
     * @param parentWidget Указатель на родительский виджет для отображения сообщений.
     * @return true, если данные успешно экспортированы, иначе false.
     */
    bool exportDataToFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget);
};

#endif
