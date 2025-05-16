#include "ChartDialog.h"
#include <QHBoxLayout>
#include <QValueAxis>
#include <QBarCategoryAxis>
#include <QLineSeries>
#include <QScatterSeries>
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QToolTip>
#include <algorithm>
#include <QPen>
#include <QtMath>
#include <QPointF>
#include <QMap>
#include <QDate>

ChartDialog::ChartDialog(QWidget *parent) : QDialog(parent)
{
    agentChartView = new QChartView(this);
    monthChartView = new QChartView(this);
    agentChartView->setRenderHint(QPainter::Antialiasing);
    monthChartView->setRenderHint(QPainter::Antialiasing);

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#121212"));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor("#1E1E1E"));
    darkPalette.setColor(QPalette::AlternateBase, QColor("#2A2A2A"));
    darkPalette.setColor(QPalette::ToolTipBase, QColor("#1E1E1E"));
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor("#2D2D2D"));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor("#444444"));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    this->setPalette(darkPalette);
    this->setStyleSheet("QDialog { border: 1px solid #333; } QToolTip { padding: 4px; }");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(15);
    mainLayout->addWidget(agentChartView);
    mainLayout->addWidget(monthChartView);
    setLayout(mainLayout);

    setWindowTitle("Аналитика страховых сделок");
    setMinimumSize(1600, 800);
    resize(1800, 900);
}

void ChartDialog::setData(const QMap<QString, double> &agentSums,
                          const QMap<QString, int> &monthCounts)
{

    const QColor agentLineColor = QColor("#CCCCCC");
    const QColor monthBarColor = QColor("#888888");

    QList<QPair<QString, double>> sortedAgents;
    for (auto it = agentSums.constBegin(); it != agentSums.constEnd(); ++it)
    {
        if (it.value() > 0)
            sortedAgents.append({it.key(), it.value()});
    }
    std::sort(sortedAgents.begin(), sortedAgents.end(),
              [](const QPair<QString, double> &a, const QPair<QString, double> &b)
              {
                  return a.first < b.first;
              });

    QLineSeries *agentSeries = new QLineSeries();
    agentSeries->setName("Сумма по агентам");

    QStringList agentCategories;
    double maxAgentSum = 0;
    for (int i = 0; i < sortedAgents.size(); ++i)
    {
        const auto &pair = sortedAgents[i];

        agentSeries->append(i, pair.second);
        agentCategories << pair.first;
        if (pair.second > maxAgentSum)
            maxAgentSum = pair.second;
    }
    QPen agentPen(agentLineColor);
    agentPen.setWidth(2);
    agentSeries->setPen(agentPen);
    agentSeries->setPointsVisible(true);

    QChart *agentChart = new QChart();
    agentChart->addSeries(agentSeries);
    agentChart->setTitle("Общие суммы по агентам");
    agentChart->setTheme(QChart::ChartThemeLight);
    agentChart->setBackgroundBrush(QBrush(QColor("#121212")));
    agentChart->setTitleFont(QFont("Arial", 16, QFont::Bold));
    agentChart->setTitleBrush(QBrush(Qt::white));
    agentChart->legend()->setVisible(true);
    agentChart->legend()->setAlignment(Qt::AlignTop);
    agentChart->legend()->setFont(QFont("Arial", 11));
    agentChart->legend()->setBrush(QBrush(QColor("#1E1E1E")));
    agentChart->legend()->setLabelColor(Qt::white);
    agentChart->setAnimationOptions(QChart::SeriesAnimations);
    agentChart->setAnimationDuration(500);
    agentChart->setAnimationEasingCurve(QEasingCurve::Linear);
    agentChart->setMargins(QMargins(10, 10, 10, 20));

    QBarCategoryAxis *axisXAgents = new QBarCategoryAxis();
    if (!agentCategories.isEmpty())
        axisXAgents->append(agentCategories);
    axisXAgents->setTitleText("Агент");
    axisXAgents->setTitleBrush(QBrush(Qt::white));
    axisXAgents->setTitleFont(QFont("Arial", 11));
    axisXAgents->setLabelsColor(Qt::white);
    axisXAgents->setLabelsFont(QFont("Arial", 10));
    if (agentCategories.count() > 15)
        axisXAgents->setLabelsAngle(-60);
    else
        axisXAgents->setLabelsAngle(0);
    axisXAgents->setGridLineVisible(false);
    agentChart->addAxis(axisXAgents, Qt::AlignBottom);
    agentSeries->attachAxis(axisXAgents);

    QValueAxis *axisYAgents = new QValueAxis();
    axisYAgents->setLabelFormat("%.0f P");
    axisYAgents->setTitleText("Сумма");
    axisYAgents->setTitleBrush(QBrush(Qt::white));
    axisYAgents->setTitleFont(QFont("Arial", 11));
    axisYAgents->setLabelsColor(Qt::white);
    axisYAgents->setLabelsFont(QFont("Arial", 10));
    axisYAgents->setGridLineVisible(true);
    axisYAgents->setGridLineColor(QColor("#444444"));
    axisYAgents->setMin(0);
    int tickCountYAgent = 5;
    double niceMaxYAgent = 1000;
    if (maxAgentSum > 0)
    {
        double step = qPow(10.0, qFloor(qLn(maxAgentSum) / qLn(10.0)));
        if (maxAgentSum / step < 2)
            step /= 5.0;
        else if (maxAgentSum / step < 5)
            step /= 2.0;
        if (step <= 0)
            step = 100;
        niceMaxYAgent = qCeil(maxAgentSum / step) * step;
        tickCountYAgent = qMax(2, static_cast<int>(niceMaxYAgent / step) + 1);
        tickCountYAgent = qBound(3, tickCountYAgent, 8);
    }
    axisYAgents->setMax(niceMaxYAgent);
    axisYAgents->setTickCount(tickCountYAgent);
    agentChart->addAxis(axisYAgents, Qt::AlignLeft);
    agentSeries->attachAxis(axisYAgents);

    connect(agentSeries, &QLineSeries::hovered, this,
            [agentCategories](const QPointF &point, bool state)
            {
                int index = static_cast<int>(point.x());
                if (index >= 0 && index < agentCategories.size())
                {
                    QString agentName = agentCategories[index];
                    double value = point.y();
                    if (state)
                    {
                        QToolTip::showText(QCursor::pos(), QString("%1\nСумма: %L2 P").arg(agentName).arg(value, 0, 'f', 0), nullptr);
                    }
                    else
                    {
                        QToolTip::hideText();
                    }
                }
                else
                {
                    QToolTip::hideText();
                }
            });

    agentChartView->setChart(agentChart);

    QMap<QDate, int> sortedMonths;
    for (auto it = monthCounts.constBegin(); it != monthCounts.constEnd(); ++it)
    {
        if (it.value() > 0)
            sortedMonths[QDate::fromString(it.key() + "-01", "yyyy-MM-dd")] = it.value();
    }

    QBarSeries *monthSeries = new QBarSeries();
    QBarSet *monthSet = new QBarSet("Количество сделок");
    monthSet->setColor(monthBarColor);
    monthSet->setBorderColor(QColor("#111111"));
    monthSet->setLabelColor(Qt::white);
    monthSet->setLabelFont(QFont("Arial", 9));

    QStringList monthCategories;
    double maxMonthValue = 0;
    for (auto it = sortedMonths.constBegin(); it != sortedMonths.constEnd(); ++it)
    {
        int value = it.value();
        *monthSet << value;
        monthCategories << it.key().toString("MMM yyyy");
        if (value > maxMonthValue)
            maxMonthValue = value;
    }

    monthSeries->append(monthSet);
    monthSeries->setLabelsVisible(true);
    monthSeries->setLabelsFormat("@value");
    monthSeries->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    monthSeries->setBarWidth(0.7);

    QChart *monthChart = new QChart();
    monthChart->addSeries(monthSeries);
    monthChart->setTitle("Количество сделок по месяцам");
    monthChart->setTheme(QChart::ChartThemeLight);
    monthChart->setBackgroundBrush(QBrush(QColor("#121212")));
    monthChart->setTitleFont(QFont("Arial", 16, QFont::Bold));
    monthChart->setTitleBrush(QBrush(Qt::white));
    monthChart->legend()->setVisible(true);
    monthChart->legend()->setAlignment(Qt::AlignTop);
    monthChart->legend()->setFont(QFont("Arial", 11));
    monthChart->legend()->setBrush(QBrush(QColor("#1E1E1E")));
    monthChart->legend()->setLabelColor(Qt::white);
    monthChart->setAnimationOptions(QChart::SeriesAnimations);
    monthChart->setAnimationDuration(750);
    monthChart->setAnimationEasingCurve(QEasingCurve::OutCubic);
    monthChart->setMargins(QMargins(5, 10, 5, 10));

    QBarCategoryAxis *axisXMonths = new QBarCategoryAxis();
    if (!monthCategories.isEmpty())
        axisXMonths->append(monthCategories);
    axisXMonths->setTitleText("Месяц");
    axisXMonths->setTitleBrush(QBrush(Qt::white));
    axisXMonths->setTitleFont(QFont("Arial", 11));
    axisXMonths->setLabelsColor(Qt::white);
    axisXMonths->setLabelsFont(QFont("Arial", 10));
    if (monthCategories.count() > 12)
    {
        axisXMonths->setLabelsAngle(-45);
    }
    else
    {
        axisXMonths->setLabelsAngle(0);
    }
    axisXMonths->setGridLineVisible(false);
    monthChart->addAxis(axisXMonths, Qt::AlignBottom);
    monthSeries->attachAxis(axisXMonths);

    QValueAxis *axisYMonths = new QValueAxis();
    axisYMonths->setLabelFormat("%d");
    axisYMonths->setTitleBrush(QBrush(Qt::white));
    axisYMonths->setTitleFont(QFont("Arial", 11));
    axisYMonths->setLabelsColor(Qt::white);
    axisYMonths->setLabelsFont(QFont("Arial", 10));
    axisYMonths->setGridLineVisible(true);
    axisYMonths->setGridLineColor(QColor("#444444"));
    axisYMonths->setMin(0);

    int tickCountY = 5;
    double niceMaxY = 10;
    if (maxMonthValue > 0)
    {
        double step = qPow(10.0, qFloor(qLn(maxMonthValue) / qLn(10.0)));
        if (maxMonthValue / step < 2)
            step /= 5.0;
        else if (maxMonthValue / step < 5)
            step /= 2.0;
        if (step <= 0)
            step = 1;
        niceMaxY = qCeil(maxMonthValue / step) * step;
        tickCountY = qMax(2, static_cast<int>(niceMaxY / step) + 1);
        tickCountY = qBound(3, tickCountY, 10);
    }
    axisYMonths->setMax(niceMaxY);
    axisYMonths->setTickCount(tickCountY);
    monthChart->addAxis(axisYMonths, Qt::AlignLeft);
    monthSeries->attachAxis(axisYMonths);

    QColor monthOriginalColor = monthBarColor;

    connect(monthSeries, &QBarSeries::hovered, this,
            [monthSet, monthOriginalColor](bool status, int index, QBarSet *barset)
            {
                if (!barset || barset != monthSet)
                    return;
                if (status)
                {
                    QToolTip::showText(QCursor::pos(), QString("%1: %L2").arg(barset->label()).arg(barset->at(index)), nullptr);
                    monthSet->setColor(monthOriginalColor.lighter(150));
                }
                else
                {
                    monthSet->setColor(monthOriginalColor);
                    QToolTip::hideText();
                }
            });

    monthChartView->setChart(monthChart);
}
