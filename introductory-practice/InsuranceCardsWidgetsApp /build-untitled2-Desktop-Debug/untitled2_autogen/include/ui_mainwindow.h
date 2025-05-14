/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *insuranceTable;
    QPushButton *loadButton;
    QPushButton *exportButton;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QWidget *chartWidget_;
    QPushButton *openChartButton;
    QLineEdit *searchLineEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1965, 839);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush1(QColor(239, 239, 239, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        MainWindow->setPalette(palette);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        centralwidget->setPalette(palette1);
        insuranceTable = new QTableWidget(centralwidget);
        if (insuranceTable->columnCount() < 8)
            insuranceTable->setColumnCount(8);
        insuranceTable->setObjectName(QString::fromUtf8("insuranceTable"));
        insuranceTable->setGeometry(QRect(30, 110, 1471, 791));
        QPalette palette2;
        QBrush brush2(QColor(51, 51, 51, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush3(QColor(51, 51, 51, 128));
        brush3.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush3);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush);
        QBrush brush4(QColor(202, 202, 202, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush4);
        QBrush brush5(QColor(159, 159, 159, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush5);
        QBrush brush6(QColor(184, 184, 184, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush);
        QBrush brush7(QColor(118, 118, 118, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush);
        QBrush brush8(QColor(177, 177, 177, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush8);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        insuranceTable->setPalette(palette2);
        insuranceTable->setStyleSheet(QString::fromUtf8("\n"
"\n"
"/* \320\235\320\260\321\201\321\202\321\200\320\260\320\270\320\262\320\260\320\265\320\274 \321\202\320\260\320\261\320\273\320\270\321\206\321\203 \320\262\320\275\321\203\321\202\321\200\320\270 */\n"
"QTableWidget {\n"
"    border: none;  /* \320\243\320\261\320\270\321\200\320\260\320\265\320\274 \321\200\320\260\320\274\320\272\321\203 \321\203 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
"    background-color: transparent;\n"
"    gridline-color: #e0e0e0;\n"
"}\n"
"\n"
"/* \320\227\320\260\320\263\320\276\320\273\320\276\320\262\320\272\320\270 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
"QHeaderView::section {\n"
"    background-color: black;\n"
"    color: white;\n"
"    padding: 8px;\n"
"    font-size: 12pt;\n"
"    border: 1px solid #4d4d4d;\n"
"}\n"
"\n"
"/* \320\241\320\272\321\200\321\203\320\263\320\273\321\217\320\265\320\274 \321\202\320\276\320\273\321\214\320\272\320\276 \321\203\320\263\320\273\321\213 \321\202\320\260\320\261\320\273\320\270\321"
                        "\206\321\213 */\n"
"QTableCornerButton::section {\n"
"    border-top-left-radius: 12px;\n"
"    background-color: black;\n"
"}\n"
"\n"
"/* \320\244\320\276\320\272\321\203\321\201 \321\203\320\261\320\270\321\200\320\260\320\265\320\274 */\n"
"QTableWidget:focus {\n"
"    outline: none;\n"
"}\n"
"\n"
"QTableWidget {\n"
"            background-color: white; border: none;\n"
"            font-family: 'Segoe UI', sans-serif; font-size: 14px; color: #333;\n"
"        }\n"
"        QTableWidget::item { padding: 6px;  background-color: #fff; } 3px solid #ddd;\n"
"        QTableWidget::item:selected { background-color: #c0e0ff; color: black; };\n"
"        QHeaderView::section {\n"
"            background-color: #f0f0f0; border: 1px solid #ddd; padding: 10px;\n"
"            font-weight: bold; color: #555; font-size: 14px;\n"
"        }\n"
"        QTableWidget::item:odd { background-color: #f9f9f9; }\n"
"        QTableWidget::item:even { background-color: #ffffff; }\n"
"        QComboBox, QDateEdit { font-size: 14px"
                        "; padding: 6px; height: 30px; }\n"
"        QTableWidget QLineEdit { background-color: white; color: black; border: 1px solid black; padding: 1px; }"));
        insuranceTable->setColumnCount(8);
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setGeometry(QRect(560, 40, 151, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Yandex Sans Text"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        loadButton->setFont(font);
        loadButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"    color: black;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-size: 12pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e6e6e6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d4d4d4;\n"
"}\n"
""));
        exportButton = new QPushButton(centralwidget);
        exportButton->setObjectName(QString::fromUtf8("exportButton"));
        exportButton->setGeometry(QRect(730, 40, 151, 41));
        exportButton->setFont(font);
        exportButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"    color: black;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-size: 12pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e6e6e6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d4d4d4;\n"
"}\n"
""));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setGeometry(QRect(1100, 40, 191, 41));
        addButton->setFont(font);
        addButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"    color: black;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-size: 12pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e6e6e6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d4d4d4;\n"
"}\n"
""));
        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(1310, 40, 191, 41));
        deleteButton->setFont(font);
        deleteButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"    color: black;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-size: 12pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e6e6e6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d4d4d4;\n"
"}\n"
""));
        chartWidget_ = new QWidget(centralwidget);
        chartWidget_->setObjectName(QString::fromUtf8("chartWidget_"));
        chartWidget_->setGeometry(QRect(1530, 290, 361, 391));
        openChartButton = new QPushButton(centralwidget);
        openChartButton->setObjectName(QString::fromUtf8("openChartButton"));
        openChartButton->setGeometry(QRect(1600, 700, 231, 41));
        openChartButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    border: 2px solid black;\n"
"    color: black;\n"
"    border-radius: 8px;\n"
"    padding: 8px 16px;\n"
"    font-size: 12pt;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e6e6e6;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #d4d4d4;\n"
"}"));
        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setGeometry(QRect(30, 40, 491, 41));
        searchLineEdit->setStyleSheet(QString::fromUtf8("QLineEdit#searchLineEdit {\n"
"            border: 2px solid black; /* \320\241\320\262\320\265\321\202\320\273\320\276-\321\201\320\265\321\200\320\260\321\217 \321\200\320\260\320\274\320\272\320\260 */\n"
"            border-radius: 10px; /* \320\241\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\275\321\213\320\265 \321\203\320\263\320\273\321\213. \320\237\320\276\320\264\320\261\320\265\321\200\320\270\321\202\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265 \320\277\320\276 \320\262\320\272\321\203\321\201\321\203. */\n"
"            padding: 0 10px; /* \320\237\321\200\320\276\321\201\321\202\320\276\320\271 \320\262\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\320\271 \320\276\321\202\321\201\321\202\321\203\320\277 (\321\201\320\262\320\265\321\200\321\205\321\203, \321\201\320\277\321\200\320\260\320\262\320\260, \321\201\320\275\320\270\320\267\321\203, \321\201\320\273\320\265\320\262\320\260 - \320\277\320\276 10px) */\n"
"            backgr"
                        "ound-color: #ffffff; /* \320\221\320\265\320\273\321\213\320\271 \321\204\320\276\320\275 */\n"
"            selection-background-color: #c0e0ff; /* \320\246\320\262\320\265\321\202 \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\275\320\276\320\263\320\276 \321\202\320\265\320\272\321\201\321\202\320\260 */\n"
"        }"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1965, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\200\320\260\321\205\320\276\320\262\320\276\320\265 \320\260\320\263\320\265\320\275\321\201\321\202\320\262\320\276", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\320\277\320\276\321\200\321\202", nullptr));
        exportButton->setText(QCoreApplication::translate("MainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202", nullptr));
        addButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
        openChartButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\260\320\275\320\260\320\273\320\270\321\202\320\270\320\272\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
