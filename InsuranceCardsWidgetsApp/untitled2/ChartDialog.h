#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QMap>

namespace Ui {
class ChartDialog;
}

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(QWidget *parent = nullptr);
    ~ChartDialog();

    void setAgentData(const QMap<QString, double> &agentSums);  
    void setMonthData(const QMap<QString, int> &monthCounts);    

private:
    Ui::ChartDialog *ui;

    void createLineChart(const QMap<QString, double> &agentSums);  
    void createBarChart(const QMap<QString, int> &monthCounts);    
};

#endif // CHARTDIALOG_H
