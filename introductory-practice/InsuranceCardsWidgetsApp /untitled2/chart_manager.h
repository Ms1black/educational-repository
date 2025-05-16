#ifndef CHART_MANAGER_H
#define CHART_MANAGER_H

#include <QObject>
#include <QtCharts>

class QWidget;
class QFrame;
class QTableWidget;
class QLabel;
class QChartView;
class QPieSeries;
class QChart;

/**
 * @brief Класс ChartManager управляет созданием и обновлением круговой диаграммы видов страхования.
 * @extends QObject <-- Родительский класс (публичное наследование)
 */
class ChartManager : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор ChartManager.
     * @param chartContainerWidget Указатель на виджет-контейнер, в котором будет отображаться диаграмма.
     * @param parent Указатель на родительский QObject.
     */
    explicit ChartManager(QWidget *chartContainerWidget, QObject *parent = nullptr);

    /**
     * @brief Деструктор ChartManager.
     * @override QObject::~QObject() (неявно, так как QObject имеет виртуальный деструктор)
     */
    ~ChartManager();

    /**
     * @brief Обновляет круговую диаграмму на основе данных из QTableWidget.
     * @param tableWidget Указатель на QTableWidget, из которого берутся данные.
     */
    void updatePieChart(QTableWidget *tableWidget);

private:
    QWidget *m_chartContainerWidget; // <-- Виджет-контейнер для диаграммы.
    QtCharts::QChartView *m_chartView; // <-- Виджет для отображения диаграммы.
    QtCharts::QPieSeries *m_pieSeries; // <-- Серия данных для круговой диаграммы.
    QtCharts::QChart *m_chart; // <-- Объект диаграммы.
    QFrame *m_chartFrame; // <-- Рамка для визуального оформления диаграммы.
    QLabel *m_chartTitleLabel; // <-- Метка для заголовка диаграммы.
};

#endif
