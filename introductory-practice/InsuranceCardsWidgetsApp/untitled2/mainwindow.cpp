#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "tablemanager.h"
#include "filemanager.h"
#include "chartmanager.h"
#include "ChartDialog.h"
#include "searchmanager.h"


#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QDebug>
#include <QMap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    m_tableManager = new TableManager(ui->insuranceTable, this, this);
    m_fileManager = new FileManager();
    m_chartManager = new ChartManager(ui->chartWidget_, this);
    searchManager = new SearchManager(this);

    m_tableManager->initializeTable();

    columnMap.clear();
    QTableWidget* currentTable = m_tableManager->getTableWidget();
    if (currentTable) { // Проверяем, что указатель на таблицу действителен
        // Сначала заполняем карту точными текстами заголовков (в нижнем регистре)
        for (int col = 0; col < currentTable->columnCount(); ++col) {
            QTableWidgetItem *headerItem = currentTable->horizontalHeaderItem(col);
            if (headerItem) {
                QString name = headerItem->text().trimmed().toLower();
                columnMap[name] = col; // Сохраняем соответствие имени и индекса
                qDebug() << "Mapped exact header:" << name << "to index" << col;
            }
        }

        // Теперь добавляем пользовательские псевдонимы (alias)
        // Карта: пользовательский параметр (в нижнем регистре) -> точный текст заголовка (в нижнем регистре)
        QMap<QString, QString> aliases;
        aliases["застрахованный"] = "фио застрахованного";
        aliases["агент"] = "фио агента";
        // "скидка" и "телефон" совпадают с заголовками, явные псевдонимы не нужны, если нет альтернативных написаний
        aliases["скидка"] = "скидка"; // Добавляем для уверенности, хотя может совпадать
        aliases["телефон"] = "телефон"; // Добавляем для уверенности
        aliases["дата"] = "дата страховки"; // Маппим общий "дата" на "дата страховки"
        aliases["дата окончания"] = "дата окончания"; // Добавляем псевдоним для даты окончания


        // Добавляем псевдонимы в columnMap, если соответствующий заголовок найден
        for (auto it = aliases.constBegin(); it != aliases.constEnd(); ++it) {
            const QString& alias = it.key(); // Пользовательский параметр (например, "агент")
            const QString& actualHeaderName = it.value(); // Соответствующий заголовок (например, "фио агента")

            // Проверяем, существует ли заголовок в нашей карте (он должен быть добавлен первым циклом)
            if (columnMap.contains(actualHeaderName)) {
                // Маппим пользовательский псевдоним на тот же индекс столбца, что и реальный заголовок
                columnMap[alias] = columnMap[actualHeaderName];
                qDebug() << "Mapped alias:" << alias << "to index" << columnMap[actualHeaderName] << "(" << actualHeaderName << ")";
            } else {
                qWarning() << "Alias '" << alias << "' maps to unknown header '" << actualHeaderName << "'. This alias will not work for search.";
            }
        }


    } else {
        qWarning() << "TableWidget is null in MainWindow constructor!";
    }

    ui->searchLineEdit->setPlaceholderText("🔍 параметр: текст");

    ui->searchLineEdit->setStyleSheet(R"(
        QLineEdit#searchLineEdit {
            border: 2px solid black; /* Светло-серая рамка */
            border-radius: 10px; /* Скругленные углы. Подберите значение по вкусу. */
            padding: 0 10px; /* Простой внутренний отступ (сверху, справа, снизу, слева - по 10px) */
            background-color: #ffffff; /* Белый фон */
            selection-background-color: #c0e0ff; /* Цвет выделенного текста */
        }
        /* Удалены стили для QToolButton, так как значка нет */
    )");



    setupConnections();

    m_chartManager->updatePieChart(m_tableManager->getTableWidget());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_fileManager;

}

void MainWindow::setupConnections()
{
    connect(ui->openChartButton, &QPushButton::clicked, this, &MainWindow::on_openChartsButton_clicked);
    // Подключаем сигнал изменения текста в searchLineEdit к слоту поиска
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, [=](const QString &text) {
        // Вызываем метод search у searchManager, передавая ему QTableWidget, текст и карту столбцов
        // ИСПОЛЬЗУЕМ m_tableManager->getTableWidget() ВМЕСТО НЕОБЪЯВЛЕННОЙ 'table'
        searchManager->search(m_tableManager->getTableWidget(), text, columnMap);
    });


}


void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выбрать файл для загрузки",
                                                    "", "Text Files (*.txt);;All Files (*)");
    if (!fileName.isEmpty()) {
        bool success = m_fileManager->loadDataFromFile(fileName, m_tableManager, this);
        if (success) {
            m_chartManager->updatePieChart(m_tableManager->getTableWidget());
        }
    }
}

void MainWindow::handleCellChanged(int row, int column)
{
    qDebug() << "MainWindow::handleCellChanged received signal for row" << row << "col" << column;

    bool needsChartUpdate = false;

    if (row >= 0 && column == -1) {
        qDebug() << "Row" << row << "editing finished. Validating data...";

        if (validateRowData(row)) {
            qDebug() << "Row" << row << "data is valid.";
            needsChartUpdate = true;
        } else {
            qDebug() << "Row" << row << "data is invalid (message shown by validator).";

        }
    }

    else if (column == Column::Type || column == Column::StartDate || column == Column::EndDate || (row == -1 && column == -1)) {
        needsChartUpdate = true;
    }

    if (needsChartUpdate) {
        qDebug() << "Updating pie chart triggered by row" << row << "col" << column;
        m_chartManager->updatePieChart(m_tableManager->getTableWidget());
    }
}

void MainWindow::on_addButton_clicked()
{
    qDebug() << "Add button clicked.";

    QDialog dialog(this);
    dialog.setWindowTitle("Добавление новой записи");

    QFormLayout form(&dialog);

    QLineEdit *insuredFioEdit = new QLineEdit(&dialog);
    insuredFioEdit->setPlaceholderText("Фамилия Имя Отчество (или Фамилия Имя -)");

    QLineEdit *agentFioEdit = new QLineEdit(&dialog);
    agentFioEdit->setPlaceholderText("Фамилия Имя Отчество (или Фамилия Имя -)");

    QLineEdit *amountEdit = new QLineEdit(&dialog);
    amountEdit->setValidator(new QDoubleValidator(0, 1e9, 2, &dialog));
    amountEdit->setPlaceholderText("Например, 15000.50");

    QDateEdit *startDateEdit = new QDateEdit(QDate::currentDate(), &dialog);
    startDateEdit->setCalendarPopup(true);
    startDateEdit->setDisplayFormat("yyyy-MM-dd");

    QDateEdit *endDateEdit = new QDateEdit(QDate::currentDate().addYears(1), &dialog);
    endDateEdit->setCalendarPopup(true);
    endDateEdit->setDisplayFormat("yyyy-MM-dd");

    QComboBox *typeCombo = new QComboBox(&dialog);
    typeCombo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});
    QLineEdit *phoneEdit = new QLineEdit(&dialog);
    phoneEdit->setPlaceholderText("+7(XXX)XXX-XX-XX или 7XXXXXXXXXX");

    QLineEdit *discountEdit = new QLineEdit("0", &dialog);

    discountEdit->setValidator(new QIntValidator(0, 100, &dialog));
    discountEdit->setPlaceholderText("0-100");

    form.addRow("ФИО Застрах.*:", insuredFioEdit);
    form.addRow("ФИО Агента*:", agentFioEdit);
    form.addRow("Сумма*:", amountEdit);
    form.addRow("Дата Страховки:", startDateEdit);
    form.addRow("Дата Окончания:", endDateEdit);
    form.addRow("Вид Страховки:", typeCombo);
    form.addRow("Телефон*:", phoneEdit);
    form.addRow("Скидка (%):", discountEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "Add dialog accepted. Validating input...";
        QString errorMsg;

        QString insuredFioRaw = insuredFioEdit->text().trimmed();
        QStringList insuredParts = insuredFioRaw.split(' ', Qt::SkipEmptyParts);
        if (insuredFioRaw.isEmpty()) {
            errorMsg += "Не указано ФИО Застрахованного.\n";
        } else if (insuredParts.count() != 3) {
            errorMsg += "ФИО Застрахованного: Укажите Фамилию, Имя и Отчество (или Фамилию, Имя и прочерк '-' вместо отчества).\n";
        }

        QString agentFioRaw = agentFioEdit->text().trimmed();
        QStringList agentParts = agentFioRaw.split(' ', Qt::SkipEmptyParts);
        if (agentFioRaw.isEmpty()) {
            errorMsg += "Не указано ФИО Агента.\n";
        } else if (agentParts.count() != 3) {
            errorMsg += "ФИО Агента: Укажите Фамилию, Имя и Отчество (или Фамилию, Имя и прочерк '-' вместо отчества).\n";
        }

        if (amountEdit->text().trimmed().isEmpty()) {
            errorMsg += "Не указана Сумма.\n";
        } else {
            bool amountOk;
            amountEdit->text().toDouble(&amountOk);
            if (!amountOk) {
                errorMsg += "Сумма указана некорректно (ожидается число).\n";
            }
        }

        bool discountOk;
        int discountVal = discountEdit->text().toInt(&discountOk);
        if (!discountOk || discountVal < 0 || discountVal > 100) {

            errorMsg += "Скидка указана некорректно (ожидается целое число от 0 до 100).\n";
        }

        if (startDateEdit->date() > endDateEdit->date()) {
            errorMsg += "Дата окончания не может быть раньше даты начала страховки.\n";
        }

        QString phoneRaw = phoneEdit->text().trimmed();
        if (phoneRaw.isEmpty()) {
            errorMsg += "Не указан Телефон.\n";
        } else {
            QString digitsOnly = phoneRaw;
            digitsOnly.remove(QRegularExpression("\\D"));
            if (digitsOnly.length() != 11) {
                errorMsg += "Телефон: Должно быть 11 цифр (например, 79991234567).\n";
            } else if (digitsOnly.at(0) != QChar('7')) {
                errorMsg += "Телефон: Должен начинаться с 7 (или +7).\n";
            }
        }

        if (!errorMsg.isEmpty()) {
            qDebug() << "Validation failed:" << errorMsg;
            QMessageBox::warning(this, "Ошибка ввода", errorMsg);
            return;
        }

        qDebug() << "Input validated successfully. Adding row...";

        QStringList fields;
        fields << insuredParts;
        fields << agentParts;
        fields << amountEdit->text().trimmed();
        fields << startDateEdit->date().toString("yyyy-MM-dd");
        fields << endDateEdit->date().toString("yyyy-MM-dd");
        fields << typeCombo->currentText();
        fields << phoneRaw;
        fields << discountEdit->text().trimmed() + "%";

        int newRow = ui->insuranceTable->rowCount();
        m_tableManager->addTableRow(newRow, fields, true);


        m_chartManager->updatePieChart(m_tableManager->getTableWidget());
        qDebug() << "Row added and chart updated.";

    } else {
        qDebug() << "Add dialog rejected.";
    }
}

void MainWindow::on_deleteButton_clicked()
{
    m_tableManager->deleteSelectedRow();
    m_chartManager->updatePieChart(m_tableManager->getTableWidget());
}

void MainWindow::on_exportButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Экспорт данных",
                                                    "", "Текстовые файлы (*.txt);;Все файлы (*)");
    if (!fileName.isEmpty()) {
        m_fileManager->exportDataToFile(fileName, m_tableManager, this);
    }
}


void MainWindow::on_openChartsButton_clicked()
{
    QMap<QString, double> agentSums = m_tableManager->getAgentSums();
    QMap<QString, int> monthCounts = m_tableManager->getMonthCounts();

    ChartDialog *dialog = new ChartDialog(this);
    dialog->setData(agentSums, monthCounts);
    dialog->setWindowTitle("Аналитика страховых сделок");
    dialog->exec();
    delete dialog;
}

bool MainWindow::validateRowData(int row)
{
    if (!m_tableManager || !m_tableManager->getTableWidget()) return false;
    QTableWidget *table = m_tableManager->getTableWidget();
    if (row < 0 || row >= table->rowCount()) return false;

    QString errorMsg;
    bool isValid = true;


    QString insuredFioStr = table->item(row, Column::InsuredFio) ? table->item(row, Column::InsuredFio)->text().trimmed() : "";
    QString agentFioStr = table->item(row, Column::AgentFio) ? table->item(row, Column::AgentFio)->text().trimmed() : "";
    QString amountStr = table->item(row, Column::Amount) ? table->item(row, Column::Amount)->text().trimmed() : "";
    QString phoneStr = table->item(row, Column::Phone) ? table->item(row, Column::Phone)->text().trimmed() : "";
    QString discountStr = table->item(row, Column::Discount) ? table->item(row, Column::Discount)->text().trimmed() : "0%";
    QDate startDate = QDate(); if (auto* de = qobject_cast<QDateEdit*>(table->cellWidget(row, Column::StartDate))) startDate = de->date();
    QDate endDate = QDate();   if (auto* de = qobject_cast<QDateEdit*>(table->cellWidget(row, Column::EndDate)))   endDate = de->date();

    QStringList insuredParts = insuredFioStr.split(' ', Qt::SkipEmptyParts);
    if (insuredFioStr.isEmpty()) {
        errorMsg += "ФИО Застрахованного: не заполнено.\n"; isValid = false;
    } else if (insuredParts.count() != 3) {
        errorMsg += "ФИО Застрахованного: Укажите Фамилию, Имя и Отчество (или прочерк '-' вместо отчества).\n"; isValid = false;
    }

    QStringList agentParts = agentFioStr.split(' ', Qt::SkipEmptyParts);
    if (agentFioStr.isEmpty()) {
        errorMsg += "ФИО Агента: не заполнено.\n"; isValid = false;
    } else if (agentParts.count() != 3) {
        errorMsg += "ФИО Агента: Укажите Фамилию, Имя и Отчество (или прочерк '-' вместо отчества).\n"; isValid = false;
    }

    if (amountStr.isEmpty()) { errorMsg += "Не указана Сумма.\n"; isValid = false; }
    else { bool amountOk; double amount = amountStr.toDouble(&amountOk); if (!amountOk || amount < 0) { errorMsg += "Сумма должна быть положительным числом.\n"; isValid = false; }}

    if (phoneStr.isEmpty()) {
        errorMsg += "Не указан Телефон.\n"; isValid = false;
    } else {
        QString digitsOnly = phoneStr;
        digitsOnly.remove(QRegularExpression("\\D"));
        if (digitsOnly.length() != 11) {
            errorMsg += "Телефон: Ожидается 11 цифр (например, +7(999)123-45-67).\n"; isValid = false;
        } else if (!digitsOnly.startsWith('7')) {
            errorMsg += "Телефон: Должен начинаться с 7 (или +7).\n"; isValid = false;
        }
    }

    if (!isValid) {
        QMessageBox::warning(this, "Ошибка данных в строке " + QString::number(row + 1), errorMsg);
    }

    return isValid;
}

