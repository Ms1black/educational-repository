/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
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
            MainWindow->setObjectName("MainWindow");
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
        centralwidget->setObjectName("centralwidget");
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        centralwidget->setPalette(palette1);
        insuranceTable = new QTableWidget(centralwidget);
        if (insuranceTable->columnCount() < 8)
            insuranceTable->setColumnCount(8);
        insuranceTable->setObjectName("insuranceTable");
        insuranceTable->setGeometry(QRect(30, 110, 1471, 791));
        QPalette palette2;
        QBrush brush2(QColor(0, 0, 0, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        QBrush brush4(QColor(202, 202, 202, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush4);
        QBrush brush5(QColor(159, 159, 159, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush5);
        QBrush brush6(QColor(184, 184, 184, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        QBrush brush8(QColor(118, 118, 118, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush8);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush);
        QBrush brush10(QColor(0, 0, 0, 255));
        brush10.setStyle(Qt::NoBrush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        QBrush brush11(QColor(177, 177, 177, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush11);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush9);
#endif
        insuranceTable->setPalette(palette2);
        insuranceTable->setStyleSheet(QString::fromUtf8("/* \320\227\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\275\321\213\320\265 \321\203\320\263\320\273\321\213 \320\264\320\273\321\217 \320\262\321\201\320\265\320\271 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 \321\207\320\265\321\200\320\265\320\267 QFrame */\n"
"QFrame#insuranceFrame {\n"
"    border: 2px solid #d6d6d6;\n"
"    border-radius: 12px;  /* \320\227\320\260\320\272\321\200\321\203\320\263\320\273\320\265\320\275\320\275\321\213\320\265 \321\203\320\263\320\273\321\213 */\n"
"    background-color: #f9f9f9;\n"
"}\n"
"\n"
"/* \320\235\320\260\321\201\321\202\321\200\320\260\320\270\320\262\320\260\320\265\320\274 \321\202\320\260\320\261\320\273\320\270\321\206\321\203 \320\262\320\275\321\203\321\202\321\200\320\270 */\n"
"QTableWidget {\n"
"    border: none;  /* \320\243\320\261\320\270\321\200\320\260\320\265\320\274 \321\200\320\260\320\274\320\272\321\203 \321\203 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
"    background-color: transpar"
                        "ent;\n"
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
"/* \320\241\320\272\321\200\321\203\320\263\320\273\321\217\320\265\320\274 \321\202\320\276\320\273\321\214\320\272\320\276 \321\203\320\263\320\273\321\213 \321\202\320\260\320\261\320\273\320\270\321\206\321\213 */\n"
"QTableCornerButton::section {\n"
"    border-top-left-radius: 12px;\n"
"    background-color: black;\n"
"}\n"
"\n"
"/* \320\244\320\276\320\272\321\203\321\201 \321\203\320\261\320\270\321\200\320\260\320\265\320\274 */\n"
"QTableWidget:focus {\n"
"    outline: none;\n"
"}\n"
""));
        insuranceTable->setColumnCount(8);
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(560, 40, 151, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Yandex Sans Text")});
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
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
        exportButton->setObjectName("exportButton");
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
        addButton->setObjectName("addButton");
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
        deleteButton->setObjectName("deleteButton");
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
        chartWidget_->setObjectName("chartWidget_");
        chartWidget_->setGeometry(QRect(1530, 290, 361, 391));
        openChartButton = new QPushButton(centralwidget);
        openChartButton->setObjectName("openChartButton");
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
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setGeometry(QRect(30, 40, 491, 41));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1965, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
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
