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
#include <QRegularExpression>
#include <QtCharts>
#include "ChartDialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->openChartButton, &QPushButton::clicked, this, &MainWindow::on_openChartsButton_clicked);


    
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
    createPieChart();
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

void MainWindow::createPieChart()
{
    if (chartView) {
        ui->chartWidget_->layout()->removeWidget(chartView);
        delete chartView;
        chartView = nullptr;
    }

    auto *series = new QPieSeries();

    QMap<QString, int> insuranceCounts;
    for (int row = 0; row < ui->insuranceTable->rowCount(); ++row) {
        if (auto *combo = qobject_cast<QComboBox*>(ui->insuranceTable->cellWidget(row, 5))) {
            QString type = combo->currentText();
            insuranceCounts[type]++;
        }
    }

    const QStringList insuranceTypes = {"Авто", "Здоровье", "Жизнь", "Иное"};
    for (const QString &type : insuranceTypes) {
        if (insuranceCounts.contains(type)) {
            series->append(type, insuranceCounts[type]);
        }
    }

    const QList<QColor> bwColors = {
        QColor("#F0F0F0"),
        QColor("#C0C0C0"),
        QColor("#909090"),
        QColor("#606060")
    };

    for (int i = 0; i < series->count(); ++i) {
        QPieSlice* slice = series->slices().at(i);
        slice->setBrush(bwColors[i % bwColors.size()]);
        slice->setLabelVisible(true);
        slice->setLabelFont(QFont("Arial", 10));
        slice->setBorderColor(Qt::white);
        slice->setBorderWidth(1);
        slice->setLabel(QString("%1\n%2").arg(slice->label()).arg(slice->value()));
    }

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setVisible(false);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundVisible(false);
    chart->setMargins(QMargins(10, 10, 10, 10));

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QFrame* chartFrame = new QFrame();
    chartFrame->setStyleSheet(
        "QFrame {"
        "  border: 1px solid #E0E0E0;"
        "  border-radius: 12px;"
        "  background-color: white;"
        "  padding: 10px;"
        "}"
        );

    QLabel* chartTitle = new QLabel("Распределение видов страхования");
    chartTitle->setStyleSheet(
        "font-size: 16px;"
        "font-weight: bold;"
        "margin-bottom: 5px;"
        "color: black;"
        );
    chartTitle->setAlignment(Qt::AlignCenter);

    QVBoxLayout* chartLayout = new QVBoxLayout(chartFrame);
    chartLayout->addWidget(chartTitle);
    chartLayout->addWidget(chartView);

    if (!ui->chartWidget_->layout()) {
        ui->chartWidget_->setLayout(new QVBoxLayout());
    }
    ui->chartWidget_->layout()->addWidget(chartFrame);

    for (auto *slice : series->slices()) {
        QString originalLabel = slice->label();

        connect(slice, &QPieSlice::hovered, [slice, originalLabel](bool hovered) {
            slice->setExploded(hovered);
            slice->setExplodeDistanceFactor(hovered ? 0.1 : 0.0);

            QColor baseColor = slice->brush().color();
            slice->setBrush(hovered ? baseColor.darker(110) : baseColor);

            if (hovered) {
                slice->setLabel(QString::number(slice->value()));
                QFont bigFont("Arial", 25, QFont::Bold);
                slice->setLabelFont(bigFont);
            } else {
                slice->setLabel(originalLabel);
                QFont normalFont("Arial", 12);
                slice->setLabelFont(normalFont);
            }
        });
    }
}


void MainWindow::on_openChartsButton_clicked()
{
    QMap<QString, double> agentSums;  
    QMap<QString, int> monthCounts;   


    for (int row = 0; row < ui->insuranceTable->rowCount(); ++row) {

        if (auto *agentItem = ui->insuranceTable->item(row, 1)) {
            QString agent = agentItem->text();  

            if (auto *amountItem = ui->insuranceTable->item(row, 2)) {
                double amount = amountItem->text().toDouble();  

                if (auto *monthItem = ui->insuranceTable->item(row, 3)) {
                    QString month = monthItem->text(); 

                    agentSums[agent] += amount;
                    monthCounts[month] += 1;
                }
            }
        }
    }

    ChartDialog *dialog = new ChartDialog(this);
    dialog->setAgentData(agentSums);
    dialog->setMonthData(monthCounts); 
    dialog->exec();
}




