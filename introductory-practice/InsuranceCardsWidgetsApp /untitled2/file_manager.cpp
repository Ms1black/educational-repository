#include "file_manager.h"
#include "table_manager.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

FileManager::FileManager() {}

bool FileManager::loadDataFromFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget)
{
    if (!tableManager)
        return false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(parentWidget, "Ошибка", "Не удалось открыть файл для чтения!");
        return false;
    }

    QTextStream in(&file);
    QTableWidget *table = tableManager->getTableWidget();
    table->setRowCount(0);
    int row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList fields = line.split(QRegularExpression("\\s+"), QString::SkipEmptyParts);
        if (fields.size() >= 12)
        {
            tableManager->addTableRow(row, fields, false);
            row++;
        }
    }

    file.close();
    return true;
}

bool FileManager::exportDataToFile(const QString &fileName, TableManager *tableManager, QWidget *parentWidget)
{
    if (!tableManager)
        return false;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(parentWidget, "Ошибка", "Не удалось открыть файл для записи");
        return false;
    }

    QTextStream out(&file);
    QTableWidget *table = tableManager->getTableWidget();

    for (int row = 0; row < table->rowCount(); ++row)
    {
        QStringList rowData = tableManager->getRowDataForExport(row);
        QStringList insuredFioParts;
        QStringList agentFioParts;

        for (int i = 0; i < 3 && i < rowData.size(); ++i)
            insuredFioParts << rowData[i];
        for (int i = 3; i < 6 && i < rowData.size(); ++i)
            agentFioParts << rowData[i];

        QStringList lineParts;
        lineParts << insuredFioParts.join(" ");
        lineParts << agentFioParts.join(" ");

        for (int i = 6; i < rowData.size(); ++i)
            lineParts << rowData[i];

        out << lineParts.join(" ") << "\n";
    }

    file.close();
    QMessageBox::information(parentWidget, "Экспорт", "Данные успешно экспортированы");
    return true;
}
