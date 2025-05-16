#ifndef TABLE_MANAGER_H
#define TABLE_MANAGER_H

#include <QObject>
#include <QtCharts>

class QWidget;
class QFrame;
class QTableWidget;
class QLabel;
class QTableWidgetItem;
class QDate;
class MainWindow;
class QPushButton;
class QStyledItemDelegate;
class QChartView;
class QPieSeries;
class QChart;

namespace Column
{

    /**
     * @brief Перечисление для индексов колонок таблицы.
     */
    enum Enum
    {
        InsuredFio = 0,
        AgentFio = 1,
        Amount = 2,
        StartDate = 3,
        EndDate = 4,
        Type = 5,
        Phone = 6,
        Discount = 7,
        EditButton = 8
    };
}

/**
 * @brief Класс TableManager управляет операциями с QTableWidget.
 * @extends QObject <-- Родительский класс (публичное наследование)
 */
class TableManager : public QObject
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор TableManager.
     * @param tableWidget Указатель на QTableWidget для управления.
     * @param mainWindow Указатель на главное окно приложения.
     * @param parent Указатель на родительский QObject.
     */
    explicit TableManager(QTableWidget *tableWidget, MainWindow *mainWindow, QObject *parent = nullptr);

    /**
     * @brief Деструктор по умолчанию.
     * @override QObject::~QObject() (неявно, так как QObject имеет виртуальный деструктор)
     */
    ~TableManager() = default;

    /**
     * @brief Инициализирует таблицу (заголовки, настройки).
     */
    void initializeTable();

    /**
     * @brief Настраивает редакторы для ячеек таблицы.
     */
    void setupTableEditors();

    /**
     * @brief Добавляет строку в таблицу.
     * @param row Индекс новой строки.
     * @param fields Список данных для ячеек строки.
     * @param connectSignals Флаг, указывающий, нужно ли подключать сигналы для виджетов в строке.
     */
    void addTableRow(int row, const QStringList &fields, bool connectSignals = true);

    /**
     * @brief Удаляет выбранную строку из таблицы.
     */
    void deleteSelectedRow();

    /**
     * @brief Возвращает указатель на управляемый QTableWidget.
     * @return QTableWidget* Указатель на таблицу.
     */
    QTableWidget *getTableWidget() const;

    /**
     * @brief Получает данные строки для экспорта.
     * @param row Индекс строки.
     * @return QStringList Список данных строки.
     */
    QStringList getRowDataForExport(int row) const;

    /**
     * @brief Рассчитывает суммы по агентам.
     * @return QMap<QString, double> Карта (Агент -> Сумма).
     */
    QMap<QString, double> getAgentSums() const;

    /**
     * @brief Рассчитывает количество сделок по месяцам.
     * @return QMap<QString, int> Карта (Месяц -> Количество).
     */
    QMap<QString, int> getMonthCounts() const;

    /**
     * @brief Статический метод для форматирования телефонного номера.
     * @param phone Исходная строка с телефонным номером.
     * @return QString Отформатированный телефонный номер.
     */
    static QString formatPhoneNumber(const QString &phone);

private slots:

    /**
     * @brief Слот, вызываемый при нажатии кнопки редактирования/сохранения в строке.
     */
    void onEditSaveButtonClicked();

    /**
     * @brief Слот, вызываемый при изменении даты в QDateEdit.
     * @param date Новая дата.
     */
    void onDateChanged(const QDate &date);

    /**
     * @brief Слот, вызываемый при изменении значения в QComboBox.
     * @param text Новый выбранный текст.
     */
    void onComboChanged(const QString &text);

    /**
     * @brief Слот, вызываемый при клике по заголовку колонки для сортировки.
     * @param logicalIndex Логический индекс колонки.
     */
    void onHeaderClicked(int logicalIndex);

private:
    void addDateWidget(int row, int column, const QDate &date);
    void addInsuranceTypeCombo(int row, const QString currentType);
    void addEditButton(int row);
    void updateSortIndicator(int column, Qt::SortOrder order);
    void sortTable(int column, Qt::SortOrder order);
    void formatRowData(int row);

    QTableWidgetItem *createNonEditableItem(const QString &text);
    QTableWidget *m_tableWidget; // <-- Указатель на управляемый виджет таблицы.
    MainWindow *m_mainWindow; // <-- Указатель на главное окно.

    int m_currentlyEditingRow; // <-- Индекс строки, находящейся в режиме редактирования.
    int m_sortedColumn; //< Индекс колонки, по которой выполнена сортировка.
    Qt::SortOrder m_sortOrder; // <-- Текущий порядок сортировки.
};

#endif
