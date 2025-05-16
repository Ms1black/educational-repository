#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QString>
#include <QMap>

class SearchManager : public QObject
{
    Q_OBJECT

public:
    explicit SearchManager(QObject *parent = nullptr);

    void search(QTableWidget *table, const QString &text,
                const QMap<QString, int> &columnMap);

private:
    void resetTableFormatting(QTableWidget *table);
};

#endif
