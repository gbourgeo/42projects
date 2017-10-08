/****************************************************************************
** Meta object code from reading C++ file 'benWindow.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Ben/benWindow.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'benWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BenWindow_t {
    QByteArrayData data[13];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BenWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BenWindow_t qt_meta_stringdata_BenWindow = {
    {
QT_MOC_LITERAL(0, 0, 9), // "BenWindow"
QT_MOC_LITERAL(1, 10, 13), // "connectClient"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 10), // "quitClient"
QT_MOC_LITERAL(4, 36, 13), // "sockConnected"
QT_MOC_LITERAL(5, 50, 16), // "sockDisconnected"
QT_MOC_LITERAL(6, 67, 9), // "sockError"
QT_MOC_LITERAL(7, 77, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(8, 106, 6), // "erreur"
QT_MOC_LITERAL(9, 113, 8), // "sendText"
QT_MOC_LITERAL(10, 122, 8), // "sockRead"
QT_MOC_LITERAL(11, 131, 9), // "clearText"
QT_MOC_LITERAL(12, 141, 8) // "clearLog"

    },
    "BenWindow\0connectClient\0\0quitClient\0"
    "sockConnected\0sockDisconnected\0sockError\0"
    "QAbstractSocket::SocketError\0erreur\0"
    "sendText\0sockRead\0clearText\0clearLog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BenWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BenWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BenWindow *_t = static_cast<BenWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectClient(); break;
        case 1: _t->quitClient(); break;
        case 2: _t->sockConnected(); break;
        case 3: _t->sockDisconnected(); break;
        case 4: _t->sockError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->sendText(); break;
        case 6: _t->sockRead(); break;
        case 7: _t->clearText(); break;
        case 8: _t->clearLog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject BenWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BenWindow.data,
      qt_meta_data_BenWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BenWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BenWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BenWindow.stringdata0))
        return static_cast<void*>(const_cast< BenWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BenWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
