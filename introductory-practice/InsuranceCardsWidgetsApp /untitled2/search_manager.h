#ifndef SEARCH_MANAGER_H
#define SEARCH_MANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QString>
#include <QMap>

/**
 * @brief Класс SearchManager управляет поиском и фильтрацией данных в QTableWidget.
 * @extends QObject <-- Родительский класс (публичное наследование)
 */
class SearchManager : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор SearchManager.
     * @param parent Указатель на родительский QObject.
     */
    explicit SearchManager(QObject *parent = nullptr);

    /**
     * @brief Выполняет поиск в таблице на основе предоставленного текста и карты колонок.
     * @param table Указатель на QTableWidget, в котором выполняется поиск.
     * @param text Текст поискового запроса.
     * @param columnMap Карта сопоставления имен колонок с их индексами.
     */
    void search(QTableWidget *table, const QString &text, const QMap<QString, int> &columnMap);

private:

    /**
     * @brief Сбрасывает форматирование таблицы (подсветку, скрытые строки) к исходному состоянию.
     * @param table Указатель на QTableWidget для сброса форматирования.
     */
    void resetTableFormatting(QTableWidget *table);
};

#endif
