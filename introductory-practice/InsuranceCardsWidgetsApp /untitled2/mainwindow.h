#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

#include "search_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class TableManager;
class FileManager;
class ChartManager;
class ChartDialog;


/**
 * @brief Главное окно приложения, управляющее пользовательским интерфейсом и взаимодействием компонентов.
  * @extends QMainWindow <-- Родительский класс (публичное наследование)
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор главного окна.
     * @param parent Указатель на родительский виджет.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор главного окна.
     * @override QMainWindow::~QMainWindow() (неявно, так как QMainWindow имеет виртуальный деструктор)
     */
    ~MainWindow();

    /**
     * @brief Обрабатывает изменения в ячейках таблицы.
     * @param row Индекс строки.
     * @param column Индекс колонки.
     */
    void handleCellChanged(int row, int column);

private slots:

    /**
     * @brief Слот, вызываемый при нажатии кнопки загрузки данных.
     */
    void on_loadButton_clicked();

    /**
     * @brief Слот, вызываемый при нажатии кнопки добавления записи.
     */
    void on_addButton_clicked();

    /**
     * @brief Слот, вызываемый при нажатии кнопки удаления записи.
     */
    void on_deleteButton_clicked();

    /**
     * @brief Слот, вызываемый при нажатии кнопки экспорта данных.
     */
    void on_exportButton_clicked();

    /**
     * @brief Слот, вызываемый при нажатии кнопки открытия диалога с графиками.
     */
    void on_openChartsButton_clicked();

private:

    /**
     * @brief Настраивает соединения сигналов и слотов.
     */
    void setupConnections();

    /**
     * @brief Проверяет корректность данных в указанной строке таблицы.
     * @param row Индекс строки для валидации.
     * @return true, если данные корректны, иначе false.
     */
    bool validateRowData(int row);

    Ui::MainWindow *ui; // <-- Указатель на объект пользовательского интерфейса.
    TableManager *m_tableManager; // <-- Указатель на менеджер таблицы.
    FileManager *m_fileManager; // <-- Указатель на менеджер файлов.
    ChartManager *m_chartManager; // <-- Указатель на менеджер диаграмм.
    SearchManager *searchManager; // <-- Указатель на менеджер поиска.
    QMap<QString, int> columnMap; // <-- Карта для сопоставления имен колонок с их индексами.
};

#endif
