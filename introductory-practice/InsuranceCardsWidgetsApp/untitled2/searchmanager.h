#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QString>
#include <QMap>

class SearchManager : public QObject {
    Q_OBJECT

public:
    explicit SearchManager(QObject *parent = nullptr);

    // Searches the table based on the provided text.
    // If text is in "parameter: value" format, searches only in the column
    // mapped by 'parameter'. Otherwise, searches in all columns.
    // Highlights matching cells and hides non-matching rows.
    void search(QTableWidget *table, const QString &text,
                const QMap<QString, int> &columnMap); // columnMap: name -> index

private:
    // Resets the table to its original state (shows all rows, clears highlights).
    void resetTableFormatting(QTableWidget *table);
};

#endif // SEARCHMANAGER_H
