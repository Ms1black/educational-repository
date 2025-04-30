#ifndef CHARTMANAGER_H
#define CHARTMANAGER_H

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>


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
    QFrame* m_chartFrame;
    QLabel* m_chartTitleLabel;
};

#endif // CHARTMANAGER_H
