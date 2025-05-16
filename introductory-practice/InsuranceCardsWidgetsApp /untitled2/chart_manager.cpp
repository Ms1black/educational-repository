#include "chart_manager.h"
#include <QTableWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QFont>
#include <QMap>
#include <QColor>
#include <QStringList>
#include <QPainter>
#include <QDebug>

const int InsuranceTypeColumn = 5;

ChartManager::ChartManager(QWidget *chartContainerWidget, QObject *parent)
    : QObject(parent),
      m_chartContainerWidget(chartContainerWidget),
      m_chartView(nullptr),
      m_pieSeries(nullptr),
      m_chart(nullptr),
      m_chartFrame(nullptr),
      m_chartTitleLabel(nullptr)
{
    Q_ASSERT(m_chartContainerWidget != nullptr);
    m_pieSeries = new QtCharts::QPieSeries(this);
}

ChartManager::~ChartManager()
{
}

void ChartManager::updatePieChart(QTableWidget *tableWidget)
{
    if (!tableWidget || !m_pieSeries)
    {
        return;
    }

    QMap<QString, int> insuranceCounts;
    int totalCount = 0;
    for (int row = 0; row < tableWidget->rowCount(); ++row)
    {
        QWidget *widget = tableWidget->cellWidget(row, InsuranceTypeColumn);
        QComboBox *combo = qobject_cast<QComboBox *>(widget);
        if (combo)
        {
            insuranceCounts[combo->currentText()]++;
            totalCount++;
        }
    }

    m_pieSeries->clear();

    const QStringList insuranceTypes = {"Авто", "Здоровье", "Жизнь", "Иное"};
    const QList<QColor> colors = {
        QColor("#F0F0F0"), QColor("#C0C0C0"), QColor("#909090"), QColor("#606060")};

    if (totalCount > 0)
    {
        for (int i = 0; i < insuranceTypes.size(); ++i)
        {
            const QString &type = insuranceTypes[i];
            if (insuranceCounts.contains(type) && insuranceCounts[type] > 0)
            {
                int count = insuranceCounts[type];
                QPieSlice *slice = m_pieSeries->append(type, count);
                slice->setBrush(colors[i % colors.size()]);
                slice->setLabelVisible(true);
                slice->setLabel(QString("%1\n%2").arg(type).arg(count));
                slice->setBorderColor(Qt::white);
                slice->setBorderWidth(1);
                slice->disconnect(this);
                connect(slice, &QPieSlice::hovered, this, [slice, type, count](bool hovered)
                        {
                    if (!slice) return;
                    slice->setExploded(hovered);
                    slice->setExplodeDistanceFactor(hovered ? 0.1 : 0.0);
                    slice->setBrush(hovered ? slice->brush().color().darker(110) : slice->brush().color());
                    slice->setLabel(hovered ? QString::number(count) : QString("%1\n%2").arg(type).arg(count));
                    slice->setLabelFont(QFont("Arial", hovered ? 12 : 10, hovered ? QFont::Bold : QFont::Normal)); });
            }
        }
        if (m_chartTitleLabel && m_chartTitleLabel->text() != "Распределение видов страхования")
        {
            m_chartTitleLabel->setText("Распределение видов страхования");
        }
    }
    else
    {
        QPieSlice *emptySlice = m_pieSeries->append("Нет данных", 1);
        emptySlice->setLabelVisible(false);
        if (m_chartTitleLabel)
            m_chartTitleLabel->setText("Виды страхования (Нет данных)");
    }

    if (!m_chartView)
    {

        m_chart = new QtCharts::QChart();
        m_chart->addSeries(m_pieSeries);
        m_chart->legend()->setVisible(false);
        m_chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
        m_chart->setBackgroundVisible(false);
        m_chart->setMargins(QMargins(10, 10, 10, 10));

        m_chartView = new QtCharts::QChartView(m_chart);
        m_chartView->setRenderHint(QPainter::Antialiasing);

        m_chartFrame = new QFrame();
        m_chartFrame->setStyleSheet(
            "QFrame { border: 1px solid #E0E0E0; border-radius: 12px; "
            "background-color: white; padding: 10px; }");

        m_chartTitleLabel = new QLabel("Распределение видов страхования");
        m_chartTitleLabel->setStyleSheet(
            "font-size: 16px; font-weight: bold; margin-bottom: 5px; color: black;");
        m_chartTitleLabel->setAlignment(Qt::AlignCenter);

        QVBoxLayout *frameLayout = new QVBoxLayout(m_chartFrame);
        frameLayout->addWidget(m_chartTitleLabel);
        frameLayout->addWidget(m_chartView);
        QVBoxLayout *containerLayout = qobject_cast<QVBoxLayout *>(m_chartContainerWidget->layout());
        if (!containerLayout)
        {
            containerLayout = new QVBoxLayout(m_chartContainerWidget);
            containerLayout->setContentsMargins(0, 0, 0, 0);
            m_chartContainerWidget->setLayout(containerLayout);
        }
        containerLayout->addWidget(m_chartFrame);
    }
}
