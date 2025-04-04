#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QComboBox>
#include <QDateEdit>
#include <QDate>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    
    connect(ui->loadButton, &QPushButton::clicked, this, &MainWindow::on_loadButton_clicked);

    QStringList headers = {
        "ФИО Застрахованного", "ФИО Агента", "Сумма", "Дата Страховки",
        "Дата Окончания", "Вид Страховки", "Телефон", "Скидка"
    };
    ui->insuranceTable->setColumnCount(8); 
    ui->insuranceTable->setHorizontalHeaderLabels(headers);

    ui->insuranceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    ui->insuranceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->insuranceTable->setColumnWidth(0, 220); 
    ui->insuranceTable->setColumnWidth(1, 220); 
    ui->insuranceTable->setColumnWidth(2, 100); 
    ui->insuranceTable->setColumnWidth(3, 150); 
    ui->insuranceTable->setColumnWidth(4, 150); 
    ui->insuranceTable->setColumnWidth(5, 150); 
    ui->insuranceTable->setColumnWidth(6, 150); 
    ui->insuranceTable->setColumnWidth(7, 100);  
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для загрузки", "", "Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) {
        return;
    }

    loadDataFromFile(fileName);
}


void MainWindow::loadDataFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл!");
        return;
    }

    QTextStream in(&file);
    ui->insuranceTable->setRowCount(0);

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (fields.size() >= 12) {
            ui->insuranceTable->insertRow(row);

          
            QString insuredFullName = fields[0] + " " + fields[1] + " " + fields[2];
        
            QString agentFullName = fields[3] + " " + fields[4] + " " + fields[5];

            QString amount = fields[6];

            QDate insuranceDate = QDate::fromString(fields[7], "yyyy-MM-dd");
            QDate expiryDate = QDate::fromString(fields[8], "yyyy-MM-dd");

            QString insuranceType = fields[9];

            QString phone = formatPhoneNumber(fields[10]); 

            QString discount = fields[11];

            ui->insuranceTable->setItem(row, 0, new QTableWidgetItem(insuredFullName));  
            ui->insuranceTable->setItem(row, 1, new QTableWidgetItem(agentFullName));   
            ui->insuranceTable->setItem(row, 2, new QTableWidgetItem(amount));         

            QDateEdit *insuranceDateEdit = new QDateEdit(insuranceDate);
            insuranceDateEdit->setCalendarPopup(true); 
            ui->insuranceTable->setCellWidget(row, 3, insuranceDateEdit); 

            QDateEdit *expiryDateEdit = new QDateEdit(expiryDate);
            expiryDateEdit->setCalendarPopup(true);  
            ui->insuranceTable->setCellWidget(row, 4, expiryDateEdit);   

            QComboBox *insuranceTypeCombo = new QComboBox();
            insuranceTypeCombo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});
            insuranceTypeCombo->setCurrentText(insuranceType);
            ui->insuranceTable->setCellWidget(row, 5, insuranceTypeCombo); 


            ui->insuranceTable->setItem(row, 6, new QTableWidgetItem(phone)); 
            ui->insuranceTable->setItem(row, 7, new QTableWidgetItem(discount)); 

            row++;
        }
    }

    file.close();
}

QString MainWindow::formatPhoneNumber(const QString &phone)
{
    QString formattedPhone = phone.trimmed();

    QRegularExpression re("^\\d{10}$");
    if (re.match(formattedPhone).hasMatch()) {

        return QString("+7 (%1) %2-%3-%4")
            .arg(formattedPhone.mid(0, 3))  
            .arg(formattedPhone.mid(3, 3))  
            .arg(formattedPhone.mid(6, 2))  
            .arg(formattedPhone.mid(8, 2)); 
    }

    return phone;
}




