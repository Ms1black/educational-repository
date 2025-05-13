#include "tablemanager.h"
#include "mainwindow.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStyledItemDelegate>
#include <QDebug>
#include <QColor>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QModelIndexList>


TableManager::TableManager(QTableWidget *tableWidget, MainWindow *mainWindow, QObject *parent)
    : QObject(parent),
    m_tableWidget(tableWidget),
    m_mainWindow(mainWindow),
    m_currentlyEditingRow(-1)
{
    Q_ASSERT(m_tableWidget != nullptr);
    Q_ASSERT(m_mainWindow != nullptr);

}


void TableManager::setupTableEditors()
{
    qDebug() << "Setting up table editors...";
    m_tableWidget->setItemDelegateForColumn(Column::Amount, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::Discount, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::InsuredFio, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::AgentFio, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::Phone, new QStyledItemDelegate(m_tableWidget));
}

void TableManager::initializeTable()
{
    qDebug() << "Initializing table (Combined Resize Mode)...";
    const QStringList headers = {
        "ФИО Застрахованного", "ФИО Агента", "Сумма", "Дата Страховки",
        "Дата Окончания", "Вид Страховки", "Телефон", "Скидка", "Ред."
    };

    m_tableWidget->setColumnCount(headers.size());
    m_tableWidget->setHorizontalHeaderLabels(headers);
    m_tableWidget->verticalHeader()->setDefaultSectionSize(50);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setupTableEditors();

    m_tableWidget->setStyleSheet(R"(
        QTableWidget {
            background-color: #f9f9f9; border: 1px solid #ddd;
            font-family: 'Segoe UI', sans-serif; font-size: 14px; color: #333;
        }
        QTableWidget::item { padding: 8px; border-bottom: 1px solid #ddd; background-color: #fff; }
        QTableWidget::item:selected { background-color: #c0e0ff; color: black; }
        QHeaderView::section {
            background-color: #f0f0f0; border: 1px solid #ddd; padding: 10px;
            font-weight: bold; color: #555; font-size: 14px;
        }
        QTableWidget::item:odd { background-color: #f9f9f9; }
        QTableWidget::item:even { background-color: #ffffff; }
        QComboBox, QDateEdit { font-size: 14px; padding: 6px; height: 30px; }
        QTableWidget QLineEdit { background-color: white; color: black; border: 1px solid black; padding: 1px; }
    )");

    QHeaderView *header = m_tableWidget->horizontalHeader();


    header->setSectionResizeMode(Column::InsuredFio, QHeaderView::Stretch);
    header->setSectionResizeMode(Column::AgentFio, QHeaderView::Stretch);
    header->setSectionResizeMode(Column::Amount, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::StartDate, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::EndDate, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Type, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Phone, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Discount, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::EditButton, QHeaderView::ResizeToContents);

    header->resizeSection(Column::EditButton, 45);

    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qDebug() << "Table initialization finished.";
}

QTableWidgetItem* TableManager::createNonEditableItem(const QString& text) {
    auto *item = new QTableWidgetItem(text);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    return item;
}

void TableManager::addTableRow(int row, const QStringList &fields, bool connectSignals)
{
    if (fields.size() < 12) {
        qWarning() << "addTableRow: Not enough fields provided (" << fields.size() << "), expected 12.";
        return;
    }
    qDebug() << "Adding table row" << row;
    m_tableWidget->insertRow(row);

    m_tableWidget->setItem(row, Column::InsuredFio, createNonEditableItem(QString("%1 %2 %3").arg(fields[0], fields[1], fields[2])));
    m_tableWidget->setItem(row, Column::AgentFio, createNonEditableItem(QString("%1 %2 %3").arg(fields[3], fields[4], fields[5])));
    m_tableWidget->setItem(row, Column::Amount, createNonEditableItem(fields[6]));
    m_tableWidget->setItem(row, Column::Phone, createNonEditableItem(formatPhoneNumber(fields[10])));
    m_tableWidget->setItem(row, Column::Discount, createNonEditableItem(fields[11]));

    addDateWidget(row, Column::StartDate, QDate::fromString(fields[7], "yyyy-MM-dd"));
    addDateWidget(row, Column::EndDate, QDate::fromString(fields[8], "yyyy-MM-dd"));
    addInsuranceTypeCombo(row, fields[9]);

    addEditButton(row);

    if (connectSignals) {
        if (auto *dateEdit = qobject_cast<QDateEdit*>(m_tableWidget->cellWidget(row, Column::StartDate))) {
            connect(dateEdit, &QDateEdit::dateChanged, this, &TableManager::onDateChanged);
        }
        if (auto *dateEdit = qobject_cast<QDateEdit*>(m_tableWidget->cellWidget(row, Column::EndDate))) {
            connect(dateEdit, &QDateEdit::dateChanged, this, &TableManager::onDateChanged);
        }
        if (auto *combo = qobject_cast<QComboBox*>(m_tableWidget->cellWidget(row, Column::Type))) {
            connect(combo, &QComboBox::currentTextChanged, this, &TableManager::onComboChanged);
        }
    }
}

void TableManager::addDateWidget(int row, int column, const QDate &date){
    QDateEdit *dateEdit = new QDateEdit(date);
    dateEdit->setCalendarPopup(true);
    dateEdit->setEnabled(false);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    m_tableWidget->setCellWidget(row, column, dateEdit);
}


void TableManager::addInsuranceTypeCombo(int row, const QString currentType){
    QComboBox *combo = new QComboBox();
    combo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});
    combo->setCurrentText(currentType);
    combo->setEnabled(false);
    m_tableWidget->setCellWidget(row, Column::Type, combo);
}

void TableManager::addEditButton(int row)
{
    QPushButton* button = new QPushButton("✏️");
    button->setFixedSize(30, 30);
    button->setProperty("row", row);
    connect(button, &QPushButton::clicked, this, &TableManager::onEditSaveButtonClicked);
    button->setFocusPolicy(Qt::NoFocus);
    m_tableWidget->setCellWidget(row, Column::EditButton, button);
}

void TableManager::onEditSaveButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = button->property("row").toInt();
    bool startEditing = (button->text() == "✏️");

    if (startEditing && m_currentlyEditingRow != -1 && m_currentlyEditingRow != row) {
        if(QWidget* oldButtonWidget = m_tableWidget->cellWidget(m_currentlyEditingRow, Column::EditButton)) {
            if(QPushButton* oldButton = qobject_cast<QPushButton*>(oldButtonWidget)) {
                qDebug() << "Auto-saving row" << m_currentlyEditingRow << "before editing row" << row;
                oldButton->click();
                if (oldButton->text() != "✏️") {
                    qWarning() << "Failed to auto-save row" << m_currentlyEditingRow;
                    QMessageBox::warning(m_mainWindow, "Ошибка", QString("Сначала завершите редактирование строки %1 (нажмите 💾).").arg(m_currentlyEditingRow + 1));
                    return;
                }
            }
        } else {
            qWarning() << "Could not find button for previously editing row" << m_currentlyEditingRow << ". Resetting edit state.";
            m_currentlyEditingRow = -1;
            m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        }
    }

    qDebug() << "Button clicked for row" << row << ". Start editing:" << startEditing;

    if (startEditing) {
        Qt::ItemFlags flagsToSet = (Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
        const QList<int> itemColumns = {Column::InsuredFio, Column::AgentFio, Column::Amount, Column::Phone, Column::Discount};
        for (int col : itemColumns) {
            QTableWidgetItem* item = m_tableWidget->item(row, col);
            if (!item) { item = new QTableWidgetItem(); m_tableWidget->setItem(row, col, item); }
            item->setFlags(flagsToSet);
            item->setBackground(QColor("#FFF9C4"));
        }
        const QList<int> widgetColumns = {Column::StartDate, Column::EndDate, Column::Type};
        for (int col : widgetColumns) { if (QWidget* widget = m_tableWidget->cellWidget(row, col)) { widget->setEnabled(true); } }
        m_tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        qDebug() << "Table edit triggers set to:" << m_tableWidget->editTriggers();
        m_currentlyEditingRow = row;
        button->setText("💾");
        m_tableWidget->setCurrentCell(row, Column::InsuredFio);
        m_tableWidget->edit(m_tableWidget->model()->index(row, Column::InsuredFio));
        qDebug() << "Editing started for row" << row;
    }
    else {
        qDebug() << "Finishing edit for row" << row;

        QTableWidgetItem* phoneItem = m_tableWidget->item(row, Column::Phone);
        if (phoneItem) {
            QString rawPhone = phoneItem->text();
            QString formattedPhone = formatPhoneNumber(rawPhone);
            if (rawPhone != formattedPhone) {
                phoneItem->setText(formattedPhone);
                qDebug() << "Formatted phone in cell:" << formattedPhone;
            }
        } else {
            qWarning() << "Phone item not found at row" << row << "col" << Column::Phone;
        }

        QTableWidgetItem* discountItem = m_tableWidget->item(row, Column::Discount);
        if (discountItem) {
            QString currentText = discountItem->text().trimmed();
            QString textToValidate = currentText;
            QString formattedDiscount = "0%";
            bool ok = false;
            int value = 0;

            if (textToValidate.endsWith('%')) {
                textToValidate.chop(1);
            }

            value = textToValidate.toInt(&ok);

            if (ok && value >= 0 && value <= 100) {
                formattedDiscount = QString::number(value) + "%";
            } else {
                qWarning() << "Invalid discount value entered:" << currentText << ". Resetting to 0%.";
            }

            if (currentText != formattedDiscount) {
                discountItem->setText(formattedDiscount);
                qDebug() << "Formatted discount in cell:" << formattedDiscount;
            }
        } else {
            qWarning() << "Discount item not found at row" << row << "col" << Column::Discount;
        }

        Qt::ItemFlags flagsToSet = (Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        const QList<int> itemColumns = {Column::InsuredFio, Column::AgentFio, Column::Amount, Column::Phone, Column::Discount};
        for (int col : itemColumns) {
            QTableWidgetItem* item = m_tableWidget->item(row, col);
            if (!item) { continue; }
            item->setFlags(flagsToSet);
            item->setBackground(Qt::white);
        }

        const QList<int> widgetColumns = {Column::StartDate, Column::EndDate, Column::Type};
        for (int col : widgetColumns) { if (QWidget* widget = m_tableWidget->cellWidget(row, col)) { widget->setEnabled(false); } }

        if (row == m_currentlyEditingRow || m_currentlyEditingRow == -1) {
            m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            qDebug() << "Table edit triggers set back to NoEditTriggers";
        }

        m_currentlyEditingRow = -1;
        button->setText("✏️");
        qDebug() << "Editing finished and data formatted for row" << row;

        m_mainWindow->handleCellChanged(row, -1);
    }
}

void TableManager::deleteSelectedRow()
{

    QModelIndexList selectedRows = m_tableWidget->selectionModel()->selectedRows();

    if (selectedRows.count() == 1) {
        int rowToDelete = selectedRows.first().row();
        if (rowToDelete < 0 || rowToDelete >= m_tableWidget->rowCount()) {
            qWarning() << "Invalid row index obtained from selection model:" << rowToDelete;
            QMessageBox::warning(m_mainWindow, "Ошибка", "Не удалось определить выбранную строку.");
            return;
        }

        if (rowToDelete == m_currentlyEditingRow) {
            if(QWidget* buttonWidget = m_tableWidget->cellWidget(m_currentlyEditingRow, Column::EditButton)) {
                if(QPushButton* button = qobject_cast<QPushButton*>(buttonWidget)) {
                    qDebug() << "Cancelling edit on row" << m_currentlyEditingRow << "before deletion.";
                    button->click();
                    if (m_currentlyEditingRow != -1) {
                        qWarning() << "Failed to cancel edit before deletion.";
                        QMessageBox::warning(m_mainWindow, "Ошибка", "Не удалось отменить редактирование строки перед удалением.");
                        return;
                    }
                }
            }
        }

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(m_mainWindow, "Подтверждение",
                                      QString("Вы действительно хотите удалить выделенную строку (%1)?").arg(rowToDelete + 1),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            qDebug() << "Deleting selected row" << rowToDelete;
            int deletedRowIndex = rowToDelete;

            m_tableWidget->removeRow(deletedRowIndex);

            for (int row = deletedRowIndex; row < m_tableWidget->rowCount(); ++row) {
                if (auto button = qobject_cast<QPushButton*>(m_tableWidget->cellWidget(row, Column::EditButton))) {
                    button->setProperty("row", row);
                }
            }

            if (m_currentlyEditingRow > deletedRowIndex) {
                m_currentlyEditingRow--;
            }

            m_mainWindow->handleCellChanged(-1, -1);
            qDebug() << "Row deleted. Current row count:" << m_tableWidget->rowCount();
        } else {
            qDebug() << "Deletion cancelled by user for row" << rowToDelete;
        }
    } else if (selectedRows.count() > 1) {
        QMessageBox::warning(m_mainWindow, "Ошибка", "Пожалуйста, выберите только ОДНУ строку для удаления.");
        m_tableWidget->clearSelection();
    }
    else {
        QMessageBox::warning(m_mainWindow, "Ошибка", "Пожалуйста, выберите строку для удаления, кликнув на нее.");
    }
}


QString TableManager::formatPhoneNumber(const QString &phone) {
    QString digitsOnly = phone;
    digitsOnly.remove(QRegularExpression("\\D"));

    if (digitsOnly.length() == 11 && digitsOnly.startsWith('7')) {
        return QString("+%1 (%2) %3-%4-%5")
            .arg(digitsOnly.mid(0, 1))  // '7'
            .arg(digitsOnly.mid(1, 3))  // XXX
            .arg(digitsOnly.mid(4, 3))  // XXX
            .arg(digitsOnly.mid(7, 2))  // XX
            .arg(digitsOnly.mid(9, 2));  // XX
    }

    return digitsOnly;
}

QTableWidget* TableManager::getTableWidget() const { return m_tableWidget; }

QStringList TableManager::getRowDataForExport(int row) const {
    QStringList data;
    if (row < 0 || row >= m_tableWidget->rowCount()) return data;

    QStringList insuredFioParts = m_tableWidget->item(row, Column::InsuredFio)->text().split(' ', Qt::SkipEmptyParts);
    while(insuredFioParts.size() < 3) insuredFioParts << "";
    QStringList agentFioParts = m_tableWidget->item(row, Column::AgentFio)->text().split(' ', Qt::SkipEmptyParts);
    while(agentFioParts.size() < 3) agentFioParts << "";

    data << insuredFioParts;
    data << agentFioParts;
    data << m_tableWidget->item(row, Column::Amount)->text();

    if (auto* dateEdit = qobject_cast<QDateEdit*>(m_tableWidget->cellWidget(row, Column::StartDate)))
        data << dateEdit->date().toString("yyyy-MM-dd"); else data << "";
    if (auto* dateEdit = qobject_cast<QDateEdit*>(m_tableWidget->cellWidget(row, Column::EndDate)))
        data << dateEdit->date().toString("yyyy-MM-dd"); else data << "";

    if (auto* combo = qobject_cast<QComboBox*>(m_tableWidget->cellWidget(row, Column::Type)))
        data << combo->currentText(); else data << "";

    data << m_tableWidget->item(row, Column::Phone)->text().remove(QRegularExpression("[^0-9]"));
    data << m_tableWidget->item(row, Column::Discount)->text();

    return data;
}

QMap<QString, double> TableManager::getAgentSums() const {
    QMap<QString, double> agentSums;
    for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
        if (m_tableWidget->item(row, Column::AgentFio) && m_tableWidget->item(row, Column::Amount)) {
            agentSums[m_tableWidget->item(row, Column::AgentFio)->text()] += m_tableWidget->item(row, Column::Amount)->text().toDouble();
        } else {
            qWarning() << "getAgentSums: Missing item at row" << row << "col" << Column::AgentFio << "or" << Column::Amount;
        }
    } return agentSums;
}

QMap<QString, int> TableManager::getMonthCounts() const {
    QMap<QString, int> monthCounts;
    for (int row = 0; row < m_tableWidget->rowCount(); ++row) {
        if (auto dateEdit = qobject_cast<QDateEdit*>(m_tableWidget->cellWidget(row, Column::StartDate))) {
            monthCounts[dateEdit->date().toString("yyyy-MM")]++;
        }
    } return monthCounts;
}

void TableManager::onDateChanged(const QDate &/*date*/) {

    if (m_mainWindow && m_currentlyEditingRow != -1) {
        m_mainWindow->handleCellChanged(m_currentlyEditingRow, Column::StartDate);
    }
}
void TableManager::onComboChanged(const QString &/*text*/) {

    if (m_mainWindow && m_currentlyEditingRow != -1) {
        m_mainWindow->handleCellChanged(m_currentlyEditingRow, Column::Type);
    }
}
