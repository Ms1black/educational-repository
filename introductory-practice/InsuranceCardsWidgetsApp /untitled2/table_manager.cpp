#include "table_manager.h"
#include "mainwindow.h"

#include <QTableWidget>
#include <QHeaderView>
#include <QDateEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QRegularExpression>
#include <QStyledItemDelegate>
#include <QColor>
#include <QAbstractItemView>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QSortFilterProxyModel>
#include <QPainter>
#include <QApplication>

TableManager::TableManager(QTableWidget *tableWidget, MainWindow *mainWindow, QObject *parent)
    : QObject(parent),
      m_tableWidget(tableWidget),
      m_mainWindow(mainWindow),
      m_currentlyEditingRow(-1),
      m_sortedColumn(-1),
      m_sortOrder(Qt::AscendingOrder)
{
    Q_ASSERT(m_tableWidget != nullptr);
    Q_ASSERT(m_mainWindow != nullptr);
}

void TableManager::initializeTable()
{
    const QStringList headers = {
        "ФИО Застрахованного", "ФИО Агента", "Сумма", "Дата Страховки",
        "Дата Окончания", "Вид Страховки", "Телефон", "Скидка", "Ред."};

    m_tableWidget->setColumnCount(headers.size());
    m_tableWidget->setHorizontalHeaderLabels(headers);
    m_tableWidget->verticalHeader()->setDefaultSectionSize(50);
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_tableWidget->setSortingEnabled(true);
    connect(m_tableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &TableManager::onHeaderClicked);

    setupTableEditors();
    QHeaderView *header = m_tableWidget->horizontalHeader();
    header->setSectionsClickable(true);
    header->setHighlightSections(true);
    header->setStretchLastSection(false);

    header->setSectionResizeMode(Column::InsuredFio, QHeaderView::Stretch);
    header->setSectionResizeMode(Column::AgentFio, QHeaderView::Stretch);

    header->setSectionResizeMode(Column::Amount, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::StartDate, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::EndDate, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Type, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Phone, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::Discount, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(Column::EditButton, QHeaderView::Fixed);
    header->resizeSection(Column::EditButton, 45);

    header->setMinimumSectionSize(60);
    header->resizeSection(Column::Amount, 100);
    header->resizeSection(Column::Discount, 80);

    m_tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TableManager::onHeaderClicked(int logicalIndex)
{
    if (logicalIndex == Column::EditButton)
        return;

    if (m_currentlyEditingRow != -1)
    {
        QMessageBox::warning(m_mainWindow, "Ошибка", "Завершите редактирование перед сортировкой.");
        return;
    }

    m_tableWidget->setUpdatesEnabled(false);

    if (m_sortedColumn == logicalIndex)
    {
        m_sortOrder = (m_sortOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    }
    else
    {
        m_sortedColumn = logicalIndex;
        m_sortOrder = Qt::AscendingOrder;
    }

    m_tableWidget->sortItems(m_sortedColumn, m_sortOrder);
    m_tableWidget->horizontalHeader()->setSortIndicator(m_sortedColumn, m_sortOrder);
    m_tableWidget->setUpdatesEnabled(true);
    m_tableWidget->resizeColumnsToContents();
}

void TableManager::sortTable(int column, Qt::SortOrder order)
{
    m_tableWidget->sortItems(column, order);
}

void TableManager::updateSortIndicator(int column, Qt::SortOrder order)
{
    QHeaderView *header = m_tableWidget->horizontalHeader();
    header->setSortIndicatorShown(true);
    header->setSortIndicator(column, order);
}

void TableManager::setupTableEditors()
{
    m_tableWidget->setItemDelegateForColumn(Column::Amount, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::Discount, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::InsuredFio, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::AgentFio, new QStyledItemDelegate(m_tableWidget));
    m_tableWidget->setItemDelegateForColumn(Column::Phone, new QStyledItemDelegate(m_tableWidget));
}

QTableWidgetItem *TableManager::createNonEditableItem(const QString &text)
{
    auto *item = new QTableWidgetItem(text);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    return item;
}

void TableManager::addTableRow(int row, const QStringList &fields, bool connectSignals)
{
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

    if (connectSignals)
    {
        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::StartDate)))
        {
            connect(dateEdit, &QDateEdit::dateChanged, this, &TableManager::onDateChanged);
        }
        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::EndDate)))
        {
            connect(dateEdit, &QDateEdit::dateChanged, this, &TableManager::onDateChanged);
        }
        if (auto *combo = qobject_cast<QComboBox *>(m_tableWidget->cellWidget(row, Column::Type)))
        {
            connect(combo, &QComboBox::currentTextChanged, this, &TableManager::onComboChanged);
        }
    }
}

void TableManager::addDateWidget(int row, int column, const QDate &date)
{
    QDateEdit *dateEdit = new QDateEdit(date);
    dateEdit->setCalendarPopup(true);
    dateEdit->setEnabled(false);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    m_tableWidget->setCellWidget(row, column, dateEdit);
}

void TableManager::addInsuranceTypeCombo(int row, const QString currentType)
{
    QComboBox *combo = new QComboBox();
    combo->addItems({"Авто", "Здоровье", "Жизнь", "Иное"});
    combo->setCurrentText(currentType);
    combo->setEnabled(false);
    m_tableWidget->setCellWidget(row, Column::Type, combo);
}

void TableManager::addEditButton(int row)
{
    QPushButton *button = new QPushButton("✏️");
    button->setFixedSize(30, 30);
    button->setProperty("row", row);
    button->setStyleSheet("QPushButton { border: none; background: transparent; }");
    connect(button, &QPushButton::clicked, this, &TableManager::onEditSaveButtonClicked);
    button->setFocusPolicy(Qt::NoFocus);
    m_tableWidget->setCellWidget(row, Column::EditButton, button);
}

void TableManager::onEditSaveButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    int row = button->property("row").toInt();
    bool isEditMode = (button->text() == "✏️");

    if (isEditMode)
    {
        if (m_currentlyEditingRow != -1 && m_currentlyEditingRow != row)
        {
            QMessageBox::warning(m_mainWindow, "Ошибка", "Завершите редактирование текущей строки перед редактированием другой.");
            return;
        }

        button->setText("💾");
        m_currentlyEditingRow = row;

        QList<int> editableColumns = {
            Column::InsuredFio,
            Column::AgentFio,
            Column::Amount,
            Column::Phone,
            Column::Discount};

        for (int col : editableColumns)
        {
            if (QTableWidgetItem *item = m_tableWidget->item(row, col))
            {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
                item->setBackground(QColor("#FFF9C4"));
            }
        }

        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::StartDate)))
        {
            dateEdit->setEnabled(true);
        }
        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::EndDate)))
        {
            dateEdit->setEnabled(true);
        }
        if (auto *combo = qobject_cast<QComboBox *>(m_tableWidget->cellWidget(row, Column::Type)))
        {
            combo->setEnabled(true);
        }

        m_tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
        m_tableWidget->setCurrentCell(row, Column::InsuredFio);
    }
    else
    {
        button->setText("✏️");
        m_currentlyEditingRow = -1;

        for (int col = 0; col < m_tableWidget->columnCount(); ++col)
        {
            if (QTableWidgetItem *item = m_tableWidget->item(row, col))
            {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                item->setBackground(Qt::white);
            }
        }

        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::StartDate)))
        {
            dateEdit->setEnabled(false);
        }
        if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::EndDate)))
        {
            dateEdit->setEnabled(false);
        }
        if (auto *combo = qobject_cast<QComboBox *>(m_tableWidget->cellWidget(row, Column::Type)))
        {
            combo->setEnabled(false);
        }

        formatRowData(row);
        m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

        if (m_mainWindow)
        {
            m_mainWindow->handleCellChanged(row, -1);
        }
    }
}

void TableManager::formatRowData(int row)
{
    if (QTableWidgetItem *phoneItem = m_tableWidget->item(row, Column::Phone))
    {
        QString formatted = formatPhoneNumber(phoneItem->text());
        if (phoneItem->text() != formatted)
        {
            phoneItem->setText(formatted);
        }
    }

    if (QTableWidgetItem *discountItem = m_tableWidget->item(row, Column::Discount))
    {
        QString text = discountItem->text().replace("%", "").trimmed();
        bool ok;
        int value = text.toInt(&ok);
        if (ok && value >= 0 && value <= 100)
        {
            discountItem->setText(QString::number(value) + "%");
        }
        else
        {
            discountItem->setText("0%");
        }
    }
}

void TableManager::deleteSelectedRow()
{

    QModelIndexList selectedRows = m_tableWidget->selectionModel()->selectedRows();

    if (selectedRows.count() == 1)
    {
        int rowToDelete = selectedRows.first().row();
        if (rowToDelete < 0 || rowToDelete >= m_tableWidget->rowCount())
        {
            QMessageBox::warning(m_mainWindow, "Ошибка", "Не удалось определить выбранную строку.");
            return;
        }

        if (rowToDelete == m_currentlyEditingRow)
        {
            if (QWidget *buttonWidget = m_tableWidget->cellWidget(m_currentlyEditingRow, Column::EditButton))
            {
                if (QPushButton *button = qobject_cast<QPushButton *>(buttonWidget))
                {
                    button->click();
                    if (m_currentlyEditingRow != -1)
                    {
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

        if (reply == QMessageBox::Yes)
        {
            int deletedRowIndex = rowToDelete;

            m_tableWidget->removeRow(deletedRowIndex);

            for (int row = deletedRowIndex; row < m_tableWidget->rowCount(); ++row)
            {
                if (auto button = qobject_cast<QPushButton *>(m_tableWidget->cellWidget(row, Column::EditButton)))
                {
                    button->setProperty("row", row);
                }
            }

            if (m_currentlyEditingRow > deletedRowIndex)
            {
                m_currentlyEditingRow--;
            }

            m_mainWindow->handleCellChanged(-1, -1);
        }
    }
    else if (selectedRows.count() > 1)
    {
        QMessageBox::warning(m_mainWindow, "Ошибка", "Пожалуйста, выберите только ОДНУ строку для удаления.");
        m_tableWidget->clearSelection();
    }
    else
    {
        QMessageBox::warning(m_mainWindow, "Ошибка", "Пожалуйста, выберите строку для удаления, кликнув на нее.");
    }
}

QString TableManager::formatPhoneNumber(const QString &phone)
{
    QString digitsOnly = phone;
    digitsOnly.remove(QRegularExpression("\\D"));

    if (digitsOnly.length() == 11 && digitsOnly.startsWith('7'))
    {
        return QString("+%1 (%2) %3-%4-%5")
            .arg(digitsOnly.mid(0, 1))
            .arg(digitsOnly.mid(1, 3))
            .arg(digitsOnly.mid(4, 3))
            .arg(digitsOnly.mid(7, 2))
            .arg(digitsOnly.mid(9, 2));
    }

    return digitsOnly;
}

QTableWidget *TableManager::getTableWidget() const { return m_tableWidget; }

QStringList TableManager::getRowDataForExport(int row) const
{
    QStringList data;
    if (row < 0 || row >= m_tableWidget->rowCount())
        return data;

    QStringList insuredFioParts = m_tableWidget->item(row, Column::InsuredFio)->text().split(' ', QString::SkipEmptyParts);
    while (insuredFioParts.size() < 3)
        insuredFioParts << "";
    QStringList agentFioParts = m_tableWidget->item(row, Column::AgentFio)->text().split(' ', QString::SkipEmptyParts);
    while (agentFioParts.size() < 3)
        agentFioParts << "";

    data << insuredFioParts;
    data << agentFioParts;
    data << m_tableWidget->item(row, Column::Amount)->text();

    if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::StartDate)))
        data << dateEdit->date().toString("yyyy-MM-dd");
    else
        data << "";
    if (auto *dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::EndDate)))
        data << dateEdit->date().toString("yyyy-MM-dd");
    else
        data << "";

    if (auto *combo = qobject_cast<QComboBox *>(m_tableWidget->cellWidget(row, Column::Type)))
        data << combo->currentText();
    else
        data << "";

    data << m_tableWidget->item(row, Column::Phone)->text().remove(QRegularExpression("[^0-9]"));
    data << m_tableWidget->item(row, Column::Discount)->text();

    return data;
}

QMap<QString, double> TableManager::getAgentSums() const
{
    QMap<QString, double> agentSums;
    for (int row = 0; row < m_tableWidget->rowCount(); ++row)
    {
        if (m_tableWidget->item(row, Column::AgentFio) && m_tableWidget->item(row, Column::Amount))
        {
            agentSums[m_tableWidget->item(row, Column::AgentFio)->text()] += m_tableWidget->item(row, Column::Amount)->text().toDouble();
        }
    }
    return agentSums;
}

QMap<QString, int> TableManager::getMonthCounts() const
{
    QMap<QString, int> monthCounts;
    for (int row = 0; row < m_tableWidget->rowCount(); ++row)
    {
        if (auto dateEdit = qobject_cast<QDateEdit *>(m_tableWidget->cellWidget(row, Column::StartDate)))
        {
            monthCounts[dateEdit->date().toString("yyyy-MM")]++;
        }
    }
    return monthCounts;
}

void TableManager::onDateChanged(const QDate & /*date*/)
{

    if (m_mainWindow && m_currentlyEditingRow != -1)
    {
        m_mainWindow->handleCellChanged(m_currentlyEditingRow, Column::StartDate);
    }
}
void TableManager::onComboChanged(const QString & /*text*/)
{

    if (m_mainWindow && m_currentlyEditingRow != -1)
    {
        m_mainWindow->handleCellChanged(m_currentlyEditingRow, Column::Type);
    }
}
