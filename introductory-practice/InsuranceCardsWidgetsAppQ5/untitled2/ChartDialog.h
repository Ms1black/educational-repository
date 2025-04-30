#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QtCharts/QChartView>

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(QWidget *parent = nullptr);
    void setData(const QMap<QString, double> &agentSums,
                 const QMap<QString, int> &monthCounts);

private:
    QtCharts::QChartView *agentChartView;
    QtCharts::QChartView *monthChartView;
};

#endif // CHARTDIALOG_H
