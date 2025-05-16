#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <QtCharts/QChartView>
/**
* @brief Класс ChartDialog представляет диалоговое окно для отображения аналитических графиков.
* @extends QDialog <-- Родительский класс (публичное наследование)
*/
class ChartDialog : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор диалогового окна с графиками.
     * @param parent Указатель на родительский виджет.
     */
    explicit ChartDialog(QWidget *parent = nullptr);

    /**
     * @brief Устанавливает данные для отображения на графиках.
     * @param agentSums Карта сумм по агентам (Агент -> Сумма).
     * @param monthCounts Карта количества сделок по месяцам (Месяц -> Количество).
     */
    void setData(const QMap<QString, double> &agentSums,
                 const QMap<QString, int> &monthCounts);

private:
    QtCharts::QChartView *agentChartView; // <-- Виджет для отображения графика по агентам.
    QtCharts::QChartView *monthChartView; // <-- Виджет для отображения графика по месяцам.
};

#endif
