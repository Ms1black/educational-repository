#include "searchmanager.h"
#include <QTableWidgetItem>
#include <QBrush>
#include <QColor>
#include <QMessageBox>

SearchManager::SearchManager(QObject *parent) : QObject(parent) {}

void SearchManager::resetTableFormatting(QTableWidget *table)
{
    if (!table)
        return;
    table->setUpdatesEnabled(false);

    for (int row = 0; row < table->rowCount(); ++row)
    {
        table->setRowHidden(row, false);
        for (int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem *item = table->item(row, col);
            if (item)
            {
                item->setBackground(Qt::NoBrush);
            }
        }
    }
    table->setUpdatesEnabled(true);
    table->viewport()->update();
}

void SearchManager::search(QTableWidget *table, const QString &text,
                           const QMap<QString, int> &columnMap)
{
    if (!table)
        return;

    resetTableFormatting(table);

    QString param, value;
    QString inputText = text.trimmed();

    if (inputText.isEmpty())
    {
        return;
    }

    QStringList parts = inputText.split(':', Qt::SkipEmptyParts);
    if (parts.size() >= 2)
    {
        param = parts[0].trimmed().toLower();
        value = parts.mid(1).join(':').trimmed();
    }
    else
    {

        value = inputText;
    }

    if (value.isEmpty())
    {
        return;
    }

    int searchCol = -1;
    if (!param.isEmpty())
    {
        if (columnMap.contains(param))
        {
            searchCol = columnMap[param];
        }
        else
        {
            searchCol = -1;
        }
    }

    table->setUpdatesEnabled(false);

    for (int row = 0; row < table->rowCount(); ++row)
    {
        bool rowMatches = false;

        for (int col = 0; col < table->columnCount(); ++col)
        {
            QTableWidgetItem *item = table->item(row, col);
            if (!item)
            {
                continue;
            }

            bool itemMatches = item->text().contains(value, Qt::CaseInsensitive);

            if (searchCol != -1)
            {
                if (col == searchCol)
                {
                    if (itemMatches)
                    {
                        item->setBackground(QBrush(QColor(255, 255, 0)));
                        rowMatches = true;
                    }
                    else
                    {
                        item->setBackground(Qt::NoBrush);
                    }
                }
                else
                {
                    item->setBackground(Qt::NoBrush);
                }
            }
            else
            {
                if (itemMatches)
                {
                    item->setBackground(QBrush(QColor(255, 255, 0)));
                    rowMatches = true;
                }
                else
                {
                    item->setBackground(Qt::NoBrush);
                }
            }
        }

        table->setRowHidden(row, !rowMatches);
    }

    table->setUpdatesEnabled(true);
    table->viewport()->update();
}
