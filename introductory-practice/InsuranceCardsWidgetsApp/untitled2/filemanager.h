#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>

class TableManager;
class QWidget;

class FileManager
{
public:
    FileManager();

    bool loadDataFromFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget);
    bool exportDataToFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget);
};

#endif // FILEMANAGER_H
