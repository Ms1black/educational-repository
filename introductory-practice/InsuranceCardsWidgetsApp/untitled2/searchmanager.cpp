#include "searchmanager.h"
#include <QTableWidgetItem>
#include <QBrush>
#include <QColor>
#include <QDebug> // Добавил для отладочных сообщений
#include <QMessageBox> // Опционально для уведомления о неверном параметре

SearchManager::SearchManager(QObject *parent) : QObject(parent) {}

void SearchManager::resetTableFormatting(QTableWidget *table) {
    if (!table) return;
    table->setUpdatesEnabled(false); // Отключаем обновления для лучшей производительности

    for (int row = 0; row < table->rowCount(); ++row) {
        table->setRowHidden(row, false); // Показываем все строки
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (item) {
                item->setBackground(Qt::NoBrush); // Убираем подсветку
            }
        }
    }
    table->setUpdatesEnabled(true); // Включаем обновления
    table->viewport()->update(); // Запрашиваем перерисовку
}

void SearchManager::search(QTableWidget *table, const QString &text,
                           const QMap<QString, int> &columnMap) {
    if (!table) return;

    resetTableFormatting(table); // Сбрасываем предыдущие результаты поиска

    QString param, value;
    QString inputText = text.trimmed();

    if (inputText.isEmpty()) {
        // Если строка поиска пуста, просто сбрасываем форматирование и выходим.
        return;
    }

    QStringList parts = inputText.split(':', Qt::SkipEmptyParts);
    if (parts.size() >= 2) {
        param = parts[0].trimmed().toLower();
        // Объединяем все части после первого двоеточия в значение,
        // чтобы обрабатывать случаи, когда значение само содержит двоеточие.
        value = parts.mid(1).join(':').trimmed();
    } else {
        // Если двоеточия нет, весь текст считается значением для поиска по всем столбцам.
        value = inputText;
    }

    if (value.isEmpty()) {
        // Если после парсинга значение оказалось пустым (например, ввели только "параметр:"),
        // сбрасываем форматирование и выходим.
        return;
    }

    int searchCol = -1;
    if (!param.isEmpty()) {
        if (columnMap.contains(param)) {
            searchCol = columnMap[param];
            qDebug() << "Searching for value" << value << "in column" << param << "(" << searchCol << ")";
        } else {
            // Если параметр указан, но не найден в карте столбцов.
            qDebug() << "Column parameter" << param << "not found. Searching in all columns.";
            // Можно вывести сообщение пользователю опционально:
            // QMessageBox::information(nullptr, "Поиск", QString("Столбец '%1' не найден. Выполняется поиск по всем столбцам.").arg(param));
            searchCol = -1; // Продолжаем поиск по всем столбцам как при отсутствии параметра
        }
    } else {
        qDebug() << "No parameter specified. Searching for value" << value << "in all columns.";
    }


    table->setUpdatesEnabled(false); // Отключаем обновления на время поиска

    for (int row = 0; row < table->rowCount(); ++row) {
        bool rowMatches = false;

        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem *item = table->item(row, col);
            if (!item) {
                // Если ячейка пустая, просто очищаем её фон и переходим к следующей.
                // resetTableFormatting уже сделал это, но для надежности можно повторить.
                continue;
            }

            // Проверяем, содержит ли текст ячейки искомое значение (без учета регистра).
            bool itemMatches = item->text().contains(value, Qt::CaseInsensitive);

            if (searchCol != -1) { // Если задан конкретный столбец для поиска
                if (col == searchCol) { // Проверяем только этот столбец
                    if (itemMatches) {
                        item->setBackground(QBrush(QColor(255, 255, 0))); // Подсвечиваем совпадение желтым
                        rowMatches = true; // Строка считается соответствующей, если есть совпадение в искомом столбце
                    } else {
                        item->setBackground(Qt::NoBrush); // Убираем подсветку, если нет совпадения в этом столбце
                    }
                } else {
                    item->setBackground(Qt::NoBrush); // Убираем подсветку для столбцов, которые не ищем
                }
            } else { // Если поиск по всем столбцам
                if (itemMatches) {
                    item->setBackground(QBrush(QColor(255, 255, 0))); // Подсвечиваем любое совпадение в строке
                    rowMatches = true; // Строка считается соответствующей, если есть совпадение в любом столбце
                } else {
                    item->setBackground(Qt::NoBrush); // Убираем подсветку, если нет совпадения
                }
            }
        }

        // Скрываем строку, если в ней не найдено совпадений в соответствующих столбцах.
        table->setRowHidden(row, !rowMatches);
    }

    table->setUpdatesEnabled(true); // Включаем обновления таблицы
    table->viewport()->update(); // Запрашиваем перерисовку для отображения изменений
}
