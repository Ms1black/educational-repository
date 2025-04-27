#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->taskList, &QListWidget::itemChanged, this, &MainWindow::on_taskChecked);
    connect(ui->sortButton, &QPushButton::clicked, this, &MainWindow::sortTasks);
}

MainWindow::~MainWindow()
{
    // delete ui;
}

void MainWindow::on_addButton_clicked()
{
    QString taskText = ui->taskInput->text().trimmed();

    if (!taskText.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem(taskText, ui->taskList);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        item->setCheckState(Qt::Unchecked);
        ui->taskInput->clear();
    }
}

void MainWindow::on_deleteButton_clicked()
{

    for (int i = ui->taskList->count() - 1; i >= 0; --i) {
        QListWidgetItem *item = ui->taskList->item(i);

        if (item->checkState() == Qt::Checked) {

            delete ui->taskList->takeItem(i);
        }
    }
}

void MainWindow::on_taskChecked(QListWidgetItem *item)
{
    if (item->checkState() == Qt::Checked) {
        item->setForeground(Qt::gray);
        item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Bold));
    } else {
        item->setForeground(Qt::black);
        item->setFont(QFont(item->font().family(), item->font().pointSize(), QFont::Normal));
    }
}

void MainWindow::sortTasks()
{
    QListWidgetItem *item;
    QList<QString> taskTexts;

    for (int i = 0; i < ui->taskList->count(); ++i) {
        item = ui->taskList->item(i);
        taskTexts.append(item->text());
    }

    std::sort(taskTexts.begin(), taskTexts.end());

    ui->taskList->clear();
    for (const QString &taskText : taskTexts) {
        QListWidgetItem *newItem = new QListWidgetItem(taskText, ui->taskList);
        newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        newItem->setCheckState(Qt::Unchecked);
    }
}
