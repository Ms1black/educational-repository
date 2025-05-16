#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QObject>
#include <QtCharts>

class QWidget;
class QFrame;
class QTableWidget;
class QLabel;
class QTableWidgetItem;
class QDate;
class MainWindow;
class QPushButton;
class QStyledItemDelegate;
class QChartView;
class QPieSeries;
class QChart;

namespace Column
{
    enum Enum
    {
        InsuredFio = 0,
        AgentFio = 1,
        Amount = 2,
        StartDate = 3,
        EndDate = 4,
        Type = 5,
        Phone = 6,
        Discount = 7,
        EditButton = 8
    };
}

class TableManager : public QObject
{
    Q_OBJECT

public:
    explicit TableManager(QTableWidget *tableWidget, MainWindow *mainWindow, QObject *parent = nullptr);
    ~TableManager() = default;

    void initializeTable();
    void setupTableEditors();
    void addTableRow(int row, const QStringList &fields, bool connectSignals = true);
    void deleteSelectedRow();
    QTableWidget *getTableWidget() const;
    QStringList getRowDataForExport(int row) const;
    QMap<QString, double> getAgentSums() const;
    QMap<QString, int> getMonthCounts() const;
    static QString formatPhoneNumber(const QString &phone);

private slots:
    void onEditSaveButtonClicked();
    void onDateChanged(const QDate &date);
    void onComboChanged(const QString &text);
    void onHeaderClicked(int logicalIndex);

private:
    void addDateWidget(int row, int column, const QDate &date);
    void addInsuranceTypeCombo(int row, const QString currentType);
    void addEditButton(int row);
    void updateSortIndicator(int column, Qt::SortOrder order);
    void sortTable(int column, Qt::SortOrder order);
    void formatRowData(int row);

    QTableWidgetItem *createNonEditableItem(const QString &text);
    QTableWidget *m_tableWidget;
    MainWindow *m_mainWindow;

    int m_currentlyEditingRow;
    int m_sortedColumn;
    Qt::SortOrder m_sortOrder;
};

#endif
