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
    QChartView *m_chartView;
    QPieSeries *m_pieSeries;
    QChart *m_chart;
    QFrame* m_chartFrame;
    QLabel* m_chartTitleLabel;
};

#endif // CHARTMANAGER_H
