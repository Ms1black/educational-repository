/****************************************************************************
** Meta object code from reading C++ file 'tablemanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../untitled2/tablemanager.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qabstractbarseries.h>
#include <QtCharts/qvbarmodelmapper.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCharts/qcandlestickseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qboxplotseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qpieseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCharts/qxyseries.h>
#include <QtCore/qabstractitemmodel.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tablemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_TableManager_t {
    uint offsetsAndSizes[18];
    char stringdata0[13];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[5];
    char stringdata5[15];
    char stringdata6[5];
    char stringdata7[16];
    char stringdata8[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_TableManager_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_TableManager_t qt_meta_stringdata_TableManager = {
    {
        QT_MOC_LITERAL(0, 12),  // "TableManager"
        QT_MOC_LITERAL(13, 23),  // "onEditSaveButtonClicked"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 13),  // "onDateChanged"
        QT_MOC_LITERAL(52, 4),  // "date"
        QT_MOC_LITERAL(57, 14),  // "onComboChanged"
        QT_MOC_LITERAL(72, 4),  // "text"
        QT_MOC_LITERAL(77, 15),  // "onHeaderClicked"
        QT_MOC_LITERAL(93, 12)   // "logicalIndex"
    },
    "TableManager",
    "onEditSaveButtonClicked",
    "",
    "onDateChanged",
    "date",
    "onComboChanged",
    "text",
    "onHeaderClicked",
    "logicalIndex"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_TableManager[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    1,   39,    2, 0x08,    2 /* Private */,
       5,    1,   42,    2, 0x08,    4 /* Private */,
       7,    1,   45,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

Q_CONSTINIT const QMetaObject TableManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_TableManager.offsetsAndSizes,
    qt_meta_data_TableManager,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_TableManager_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TableManager, std::true_type>,
        // method 'onEditSaveButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'onComboChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onHeaderClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void TableManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TableManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEditSaveButtonClicked(); break;
        case 1: _t->onDateChanged((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 2: _t->onComboChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onHeaderClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *TableManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TableManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
