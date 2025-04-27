#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QMap>
#include <QStringList>
#include <QDate>
#include <QColor>
#include <QPieSeries>
#include <QtCharts>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();
    void on_editButtonClicked();
    void on_openChartsButton_clicked();
    void handleCellChanged(int row, int column);
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_exportButton_clicked();

private:
    void initializeTable();
    void setupConnections();
    void setupStyles();
    void loadDataFromFile(const QString &fileName);
    void addTableRow(int row, const QStringList &fields);
    void addDateWidget(int row, int column, const QDate &date);
    void addInsuranceTypeCombo(int row, const QString &currentType);
    void addEditButton(int row);
    void updateCharts();
    void updatePieChart();
    QString formatPhoneNumber(const QString &phone);
    void addNewRow();
    void deleteRow(int row);
    void exportToFile();

private:
    Ui::MainWindow *ui;

    QSet<int> m_editableRows;

    QChartView *m_chartView;
    QPieSeries *m_pieSeries;
};

#endif // MAINWINDOW_H
