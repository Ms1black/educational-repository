#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QRegularExpression>
#include <QChartView>
#include <QPieSeries>
// Или просто:
#include <QtCharts>
#include "ChartDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createPieChart();
private slots:
    void on_loadButton_clicked();
    void on_openChartsButton_clicked();
private:
    Ui::MainWindow *ui;
    QChartView *chartView = nullptr;

    void loadDataFromFile(const QString &fileName);
    QString formatPhoneNumber(const QString &phone);

};

#endif 
