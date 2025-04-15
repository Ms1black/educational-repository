#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class ChartDialog; }
QT_END_NAMESPACE

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(QWidget *parent = nullptr);
    void setData(const QMap<QString, double> &agentSums,
                 const QMap<QString, int> &monthCounts);

private:
    QChartView *agentChartView;
    QChartView *monthChartView;
};

#endif // CHARTDIALOG_H
