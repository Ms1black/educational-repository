#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>

#include "searchmanager.h"

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void handleCellChanged(int row, int column);

private slots:
    void on_loadButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_exportButton_clicked();
    void on_openChartsButton_clicked();

private:
    void setupConnections();
    bool validateRowData(int row);
    Ui::MainWindow *ui;
    TableManager *m_tableManager;
    FileManager *m_fileManager;
    ChartManager *m_chartManager;
    SearchManager *searchManager;
    QMap<QString, int> columnMap;
};
#endif
