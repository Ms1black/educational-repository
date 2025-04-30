#include "ChartDialog.h"

ChartDialog::ChartDialog(QWidget *parent)
    : QDialog(parent)
{
    agentChartView = new QChartView(this);
    monthChartView = new QChartView(this);

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor("#121212"));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor("#1E1E1E"));
    darkPalette.setColor(QPalette::AlternateBase, QColor("#2A2A2A"));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor("#2D2D2D"));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor("#444444"));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    this->setPalette(darkPalette);

    // Layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(agentChartView);
    mainLayout->addWidget(monthChartView);
    setLayout(mainLayout);

    setMinimumSize(1800, 1000);
    resize(1800, 1000);
}

void ChartDialog::setData(const QMap<QString, double> &agentSums,
                          const QMap<QString, int> &monthCounts)
{
    // Оттенки серого
    const QList<QColor> grayColors = {
        QColor("#CCCCCC"), QColor("#AAAAAA"), QColor("#888888"),
        QColor("#666666"), QColor("#444444"), QColor("#222222")
    };

    // --- КРУГОВАЯ ---
    QPieSeries *agentSeries = new QPieSeries();
    double totalSum = 0;
    for (auto val : agentSums.values())
        totalSum += val;

    int colorIndex = 0;
    for (auto it = agentSums.begin(); it != agentSums.end(); ++it) {
        QPieSlice *slice = agentSeries->append(it.key(), it.value());
        slice->setColor(grayColors[colorIndex % grayColors.size()]);
        slice->setLabelVisible();
        slice->setLabelColor(Qt::white);
        slice->setLabel(QString("%1\n%2 ₽ (%3%)")
                            .arg(it.key())
                            .arg(it.value(), 0, 'f', 2)
                            .arg(100 * it.value() / totalSum, 0, 'f', 1));

        slice->setLabelFont(QFont("Arial", 9));

        colorIndex++;
    }

    QChart *agentChart = new QChart();
    agentChart->addSeries(agentSeries);
    agentChart->setTitle("Распределение сумм по агентам");
    agentChart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    agentChart->setBackgroundBrush(QBrush(QColor("#121212")));
    agentChart->setTitleBrush(QBrush(Qt::white));
    agentChart->legend()->setVisible(true);
    agentChart->legend()->setLabelColor(Qt::white);
    agentChart->legend()->setAlignment(Qt::AlignRight);
    agentChart->legend()->setFont(QFont("Arial", 10));
    agentChart->setAnimationOptions(QChart::SeriesAnimations);
    agentChartView->setChart(agentChart);

    // --- СТОЛБЧАТАЯ ---
    QBarSeries *monthSeries = new QBarSeries();
    QBarSet *set = new QBarSet("Количество сделок");
    set->setColor(QColor("#888888"));
    set->setLabelColor(Qt::white);

    QMap<QDate, int> sortedMonths;
    for (auto it = monthCounts.begin(); it != monthCounts.end(); ++it) {
        sortedMonths[QDate::fromString(it.key() + "-01", "yyyy-MM-dd")] = it.value();
    }

    QStringList categories;
    for (auto it = sortedMonths.begin(); it != sortedMonths.end(); ++it) {
        *set << it.value();
        categories << it.key().toString("MMM yyyy");
    }

    monthSeries->append(set);
    monthSeries->setLabelsVisible(true);
    monthSeries->setLabelsFormat("@value");

    QChart *monthChart = new QChart();
    monthChart->addSeries(monthSeries);
    monthChart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    monthChart->setBackgroundBrush(QBrush(QColor("#121212")));
    monthChart->setTitleBrush(QBrush(Qt::white));
    monthChart->legend()->setVisible(true);
    monthChart->legend()->setAlignment(Qt::AlignBottom);
    monthChart->legend()->setLabelColor(Qt::white);
    monthChart->legend()->setFont(QFont("Arial", 10));
    monthChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Месяц");
    axisX->setLabelsColor(Qt::white);
    axisX->setTitleBrush(Qt::white);
    monthChart->addAxis(axisX, Qt::AlignBottom);
    monthSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelFormat("%d");
    axisY->setLabelsColor(Qt::white);
    axisY->setTitleBrush(Qt::white);
    monthChart->addAxis(axisY, Qt::AlignLeft);
    monthSeries->attachAxis(axisY);

    monthChartView->setChart(monthChart);
}

