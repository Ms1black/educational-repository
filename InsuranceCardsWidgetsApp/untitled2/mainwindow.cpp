#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QComboBox>
#include <QDateEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QRegularExpression>
#include <QtCharts>
#include "ChartDialog.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_chartView(nullptr)
    , m_pieSeries(new QPieSeries())
{
    ui->setupUi(this);
    initializeTable();
    setupConnections();
    setupStyles();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTable()
{
    const QStringList headers = {
        "ФИО Застрахованного", "ФИО Агента", "Сумма", "Дата Страховки",
        "Дата Окончания", "Вид Страховки", "Телефон", "Скидка", "Ред."
    };


    ui->insuranceTable->setColumnCount(headers.size());
    ui->insuranceTable->setHorizontalHeaderLabels(headers);
    ui->insuranceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->insuranceTable->verticalHeader()->setDefaultSectionSize(50);
    ui->insuranceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::setupConnections()
{
    disconnect(ui->insuranceTable, &QTableWidget::cellChanged,
               this, &MainWindow::handleCellChanged);
    connect(ui->insuranceTable, &QTableWidget::cellChanged,
            this, &MainWindow::handleCellChanged);

    disconnect(ui->openChartButton, &QPushButton::clicked,
               this, &MainWindow::on_openChartsButton_clicked);
    connect(ui->openChartButton, &QPushButton::clicked,
            this, &MainWindow::on_openChartsButton_clicked);

    disconnect(ui->loadButton, &QPushButton::clicked,
               this, &MainWindow::on_loadButton_clicked);
    connect(ui->loadButton, &QPushButton::clicked,
            this, &MainWindow::on_loadButton_clicked);

    disconnect(ui->addButton, &QPushButton::clicked,
               this, &MainWindow::on_addButton_clicked);
    connect(ui->addButton, &QPushButton::clicked,
            this, &MainWindow::on_addButton_clicked);

    disconnect(ui->deleteButton, &QPushButton::clicked,
               this, &MainWindow::on_deleteButton_clicked);
    connect(ui->deleteButton, &QPushButton::clicked,
            this, &MainWindow::on_deleteButton_clicked);

    disconnect(ui->exportButton, &QPushButton::clicked,
               this, &MainWindow::on_exportButton_clicked);
    connect(ui->exportButton, &QPushButton::clicked,
            this, &MainWindow::on_exportButton_clicked);
}


void MainWindow::setupStyles()
{
    ui->insuranceTable->setStyleSheet(R"(
        QTableWidget {
            background-color: #f9f9f9;
            border: 1px solid #ddd;
            font-family: 'Segoe UI', sans-serif;
            font-size: 14px;
            color: #333;
        }
        QTableWidget::item {
            padding: 8px;
            border-bottom: 1px solid #ddd;
            background-color: #fff;
        }
        QTableWidget::item:selected {
            background-color: #c0e0ff;
        }
        QHeaderView::section {
            background-color: #f0f0f0;
            border: 1px solid #ddd;
            padding: 10px;
            font-weight: bold;
            color: #555;
            font-size: 14px;
        }
        QTableWidget::item:odd { background-color: #f9f9f9; }
        QTableWidget::item:even { background-color: #ffffff; }
        QComboBox, QDateEdit {
            font-size: 14px;
            padding: 6px;
            height: 30px;
        }
    )");

    ui->insuranceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->insuranceTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для загрузки",
                                                    "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        loadDataFromFile(fileName);
    }
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
        if (line.isEmpty()) continue;

        QStringList fields = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (fields.size() >= 12) {
            addTableRow(row, fields);
            row++;
        }
    }

    file.close();
    updateCharts();
}

void MainWindow::addTableRow(int row, const QStringList &fields)
{
    ui->insuranceTable->insertRow(row);

    ui->insuranceTable->setItem(row, 0, new QTableWidgetItem(
                                            QString("%1 %2 %3").arg(fields[0], fields[1], fields[2])));
    ui->insuranceTable->setItem(row, 1, new QTableWidgetItem(
                                            QString("%1 %2 %3").arg(fields[3], fields[4], fields[5])));
    ui->insuranceTable->setItem(row, 2, new QTableWidgetItem(fields[6]));

    addDateWidget(row, 3, QDate::fromString(fields[7], "yyyy-MM-dd"));
    addDateWidget(row, 4, QDate::fromString(fields[8], "yyyy-MM-dd"));

    addInsuranceTypeCombo(row, fields[9]);

    ui->insuranceTable->setItem(row, 6, new QTableWidgetItem(formatPhoneNumber(fields[10])));
    ui->insuranceTable->setItem(row, 7, new QTableWidgetItem(fields[11]));

    addEditButton(row);
}

void MainWindow::addDateWidget(int row, int column, const QDate &date)
{
    QDateEdit *dateEdit = new QDateEdit(date);
    dateEdit->setCalendarPopup(true);
    dateEdit->setEnabled(false);
    ui->insuranceTable->setCellWidget(row, column, dateEdit);
}

void MainWindow::addInsuranceTypeCombo(int row, const QString &currentType)
{
    QComboBox *combo = new QComboBox();
    combo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});
    combo->setCurrentText(currentType);
    combo->setEnabled(false);
    connect(combo, &QComboBox::currentTextChanged, this, &MainWindow::updateCharts);
    ui->insuranceTable->setCellWidget(row, 5, combo);
}

void MainWindow::addEditButton(int row)
{
    QPushButton* button = new QPushButton("✏️");
    button->setFixedSize(30, 30);
    button->setProperty("row", row);
    connect(button, &QPushButton::clicked, this, &MainWindow::on_editButtonClicked);
    ui->insuranceTable->setCellWidget(row, 8, button);
}

void MainWindow::on_editButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    bool nowEditable = !m_editableRows.contains(row);

    const QList<int> editableColumns = {0, 1, 2, 6, 7};

    for (int col : editableColumns) {
        if (QTableWidgetItem* item = ui->insuranceTable->item(row, col)) {
            item->setFlags(nowEditable ? (item->flags() | Qt::ItemIsEditable)
                                       : (item->flags() & ~Qt::ItemIsEditable));
            item->setBackground(nowEditable ? QColor("#FFF9C4") : Qt::white);
        }
    }

    const QList<int> widgetColumns = {3, 4, 5};
    for (int col : widgetColumns) {
        if (QWidget* widget = ui->insuranceTable->cellWidget(row, col)) {
            widget->setEnabled(nowEditable);
        }
    }

    if (nowEditable) {
        m_editableRows.insert(row);
    } else {
        m_editableRows.remove(row);
    }
}




QString MainWindow::formatPhoneNumber(const QString &phone)
{
    QString formatted = phone.trimmed();
    QRegularExpression re("^(\\d{1})(\\d{3})(\\d{3})(\\d{2})(\\d{2})$");

    if (auto match = re.match(formatted); match.hasMatch()) {
        return QString("+%1 (%2) %3-%4-%5")
            .arg(match.captured(1), match.captured(2),
                 match.captured(3), match.captured(4), match.captured(5));
    }
    return phone;
}


void MainWindow::updateCharts()
{
    updatePieChart();
}

void MainWindow::updatePieChart()
{
    QMap<QString, int> insuranceCounts;
    for (int row = 0; row < ui->insuranceTable->rowCount(); ++row) {
        if (auto combo = qobject_cast<QComboBox*>(ui->insuranceTable->cellWidget(row, 5))) {
            insuranceCounts[combo->currentText()]++;
        }
    }

    m_pieSeries->clear();

    const QStringList insuranceTypes = {"Авто", "Здоровье", "Жизнь", "Иное"};
    const QList<QColor> colors = {
        QColor("#F0F0F0"), QColor("#C0C0C0"), QColor("#909090"), QColor("#606060")
    };

    for (int i = 0; i < insuranceTypes.size(); ++i) {
        const QString &type = insuranceTypes[i];
        if (insuranceCounts.contains(type)) {
            QPieSlice *slice = m_pieSeries->append(type, insuranceCounts[type]);
            slice->setBrush(colors[i]);
            slice->setLabelVisible(true);
            slice->setLabel(QString("%1\n%2").arg(type).arg(insuranceCounts[type]));
            slice->setBorderColor(Qt::white);
            slice->setBorderWidth(1);

            connect(slice, &QPieSlice::hovered, [slice, type](bool hovered) {
                slice->setExploded(hovered);
                slice->setExplodeDistanceFactor(hovered ? 0.1 : 0.0);
                slice->setBrush(hovered ? slice->brush().color().darker(110) : slice->brush().color());
                slice->setLabel(hovered ? QString::number(slice->value()) : QString("%1\n%2").arg(type).arg(slice->value()));
                slice->setLabelFont(QFont("Arial", hovered ? 25 : 12, hovered ? QFont::Bold : QFont::Normal));
            });
        }
    }

    if (!m_chartView) {
        QChart *chart = new QChart();
        chart->addSeries(m_pieSeries);
        chart->legend()->setVisible(false);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setBackgroundVisible(false);
        chart->setMargins(QMargins(10, 10, 10, 10));

        m_chartView = new QChartView(chart);
        m_chartView->setRenderHint(QPainter::Antialiasing);

        QFrame* chartFrame = new QFrame();
        chartFrame->setStyleSheet(
            "QFrame { border: 1px solid #E0E0E0; border-radius: 12px; "
            "background-color: white; padding: 10px; }");

        QLabel* chartTitle = new QLabel("Распределение видов страхования");
        chartTitle->setStyleSheet(
            "font-size: 16px; font-weight: bold; margin-bottom: 5px; color: black;");
        chartTitle->setAlignment(Qt::AlignCenter);

        QVBoxLayout* chartLayout = new QVBoxLayout(chartFrame);
        chartLayout->addWidget(chartTitle);
        chartLayout->addWidget(m_chartView);

        if (!ui->chartWidget_->layout()) {
            ui->chartWidget_->setLayout(new QVBoxLayout());
        }
        ui->chartWidget_->layout()->addWidget(chartFrame);
    }
}

void MainWindow::on_openChartsButton_clicked()
{
    QMap<QString, double> agentSums;
    QMap<QString, int> monthCounts;

    for (int row = 0; row < ui->insuranceTable->rowCount(); ++row) {
        // Agent sums
        if (auto agentItem = ui->insuranceTable->item(row, 1)) {
            if (auto amountItem = ui->insuranceTable->item(row, 2)) {
                agentSums[agentItem->text()] += amountItem->text().toDouble();
            }
        }

        // Month counts
        if (auto dateEdit = qobject_cast<QDateEdit*>(ui->insuranceTable->cellWidget(row, 3))) {
            monthCounts[dateEdit->date().toString("yyyy-MM")]++;
        }
    }

    ChartDialog *dialog = new ChartDialog(this);
    dialog->setData(agentSums, monthCounts);
    dialog->setWindowTitle("Аналитика страховых сделок");
    dialog->exec();
    delete dialog;
}

void MainWindow::handleCellChanged(int row, int column)
{
    if (column == 3 || column == 4 || column == 5) {
        updateCharts();
    }
}

void MainWindow::on_addButton_clicked()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Добавление новой записи");

    QFormLayout form(&dialog);

    QLineEdit *insuredFioEdit = new QLineEdit(&dialog);
    QLineEdit *agentFioEdit = new QLineEdit(&dialog);
    QLineEdit *amountEdit = new QLineEdit(&dialog);
    QDateEdit *startDateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    QDateEdit *endDateEdit = new QDateEdit(QDate::currentDate().addYears(1), &dialog);
    QComboBox *typeCombo = new QComboBox(&dialog);
    QLineEdit *phoneEdit = new QLineEdit(&dialog);
    QLineEdit *discountEdit = new QLineEdit("0", &dialog);

    startDateEdit->setCalendarPopup(true);
    endDateEdit->setCalendarPopup(true);
    typeCombo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});

    form.addRow("ФИО Застрахованного:", insuredFioEdit);
    form.addRow("ФИО Агента:", agentFioEdit);
    form.addRow("Сумма:", amountEdit);
    form.addRow("Дата Страховки:", startDateEdit);
    form.addRow("Дата Окончания:", endDateEdit);
    form.addRow("Вид Страховки:", typeCombo);
    form.addRow("Телефон:", phoneEdit);
    form.addRow("Скидка:", discountEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {

        if (insuredFioEdit->text().isEmpty() || agentFioEdit->text().isEmpty() ||
            amountEdit->text().isEmpty() || phoneEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Заполните все обязательные поля!");
            return;
        }

        QStringList fields;
        fields << insuredFioEdit->text().split(" ") << agentFioEdit->text().split(" ");
        while (fields.size() < 6) fields << "";

        fields << amountEdit->text()
               << startDateEdit->date().toString("yyyy-MM-dd")
               << endDateEdit->date().toString("yyyy-MM-dd")
               << typeCombo->currentText()
               << phoneEdit->text()
               << discountEdit->text();

        int row = ui->insuranceTable->rowCount();
        ui->insuranceTable->insertRow(row);
        addTableRow(row, fields);

        updateCharts();
    }
}

void MainWindow::on_deleteButton_clicked()
{
    int currentRow = ui->insuranceTable->currentRow();
    if (currentRow >= 0 && currentRow < ui->insuranceTable->rowCount()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение",
                                      "Вы действительно хотите удалить выбранную запись?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            ui->insuranceTable->removeRow(currentRow);

            for (int row = currentRow; row < ui->insuranceTable->rowCount(); ++row) {
                if (auto button = qobject_cast<QPushButton*>(ui->insuranceTable->cellWidget(row, 8))) {
                    button->setProperty("row", row);
                }
            }

            m_editableRows.remove(currentRow);

            updateCharts();
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите строку для удаления");
    }
}

void MainWindow::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт данных",
                                                    "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи");
        return;
    }

    QTextStream out(&file);

    for (int row = 0; row < ui->insuranceTable->rowCount(); ++row) {

        QString insuredFio = ui->insuranceTable->item(row, 0)->text();
        QStringList insuredParts = insuredFio.split(" ");
        while (insuredParts.size() < 3) insuredParts << "";

        QString agentFio = ui->insuranceTable->item(row, 1)->text();
        QStringList agentParts = agentFio.split(" ");
        while (agentParts.size() < 3) agentParts << "";

        QString amount = ui->insuranceTable->item(row, 2)->text();
        QString startDate = qobject_cast<QDateEdit*>(ui->insuranceTable->cellWidget(row, 3))->date().toString("yyyy-MM-dd");
        QString endDate = qobject_cast<QDateEdit*>(ui->insuranceTable->cellWidget(row, 4))->date().toString("yyyy-MM-dd");
        QString type = qobject_cast<QComboBox*>(ui->insuranceTable->cellWidget(row, 5))->currentText();
        QString phone = ui->insuranceTable->item(row, 6)->text().remove(QRegularExpression("[^0-9]"));
        QString discount = ui->insuranceTable->item(row, 7)->text();

        out << insuredParts.join(" ") << " "
            << agentParts.join(" ") << " "
            << amount << " "
            << startDate << " "
            << endDate << " "
            << type << " "
            << phone << " "
            << discount << "\n";
    }

    file.close();
    QMessageBox::information(this, "Экспорт", "Данные успешно экспортированы");
}


