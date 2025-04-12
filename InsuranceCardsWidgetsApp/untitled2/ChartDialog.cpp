#include "ChartDialog.h"
#include "ui_ChartDialog.h"

ChartDialog::ChartDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChartDialog)
{
    ui->setupUi(this);
}

ChartDialog::~ChartDialog()
{
    delete ui;
}

void ChartDialog::setAgentData(const QMap<QString, double> &agentSums)
{
    createLineChart(agentSums);
}

void ChartDialog::setMonthData(const QMap<QString, int> &monthCounts)
{
    createBarChart(monthCounts);
}

void ChartDialog::createLineChart(const QMap<QString, double> &agentSums)
{
    QLineSeries *series = new QLineSeries();

    for (auto it = agentSums.begin(); it != agentSums.end(); ++it) {
        series->append(series->count(), it.value());
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Суммы сделок по агентам");
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}

void ChartDialog::createBarChart(const QMap<QString, int> &monthCounts)
{
    QBarSeries *series = new QBarSeries();

    QBarSet *set = new QBarSet("Сделки");
    for (auto it = monthCounts.begin(); it != monthCounts.end(); ++it) {
        *set << it.value();
    }

    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Количество сделок по месяцам");
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);
}
