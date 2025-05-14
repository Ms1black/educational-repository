#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <QObject>
#include <QtCharts>

class QWidget;
class QFrame;
class QTableWidget;
class QLabel;
class QChartView;
class QPieSeries;
class QChart;

class ChartManager : public QObject
{
    Q_OBJECT

public:
    explicit ChartManager(QWidget *chartContainerWidget, QObject *parent = nullptr);
    ~ChartManager();
    void updatePieChart(QTableWidget *tableWidget);

private:
    QWidget *m_chartContainerWidget;
    QtCharts::QChartView *m_chartView;
    QtCharts::QPieSeries *m_pieSeries;
    QtCharts::QChart *m_chart;
    QFrame *m_chartFrame;
    QLabel *m_chartTitleLabel;
};

#endif
