/****************************************************************************
** Meta object code from reading C++ file 'qtclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qtclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtClient_t {
    QByteArrayData data[11];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtClient_t qt_meta_stringdata_QtClient = {
    {
QT_MOC_LITERAL(0, 0, 8), // "QtClient"
QT_MOC_LITERAL(1, 9, 13), // "ConnectServer"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 16), // "DisconnectServer"
QT_MOC_LITERAL(4, 41, 14), // "ReceiveMessage"
QT_MOC_LITERAL(5, 56, 11), // "SendMessage"
QT_MOC_LITERAL(6, 68, 17), // "ConnectFileServer"
QT_MOC_LITERAL(7, 86, 20), // "DisconnectFileServer"
QT_MOC_LITERAL(8, 107, 10), // "SelectFile"
QT_MOC_LITERAL(9, 118, 8), // "SendFile"
QT_MOC_LITERAL(10, 127, 18) // "UpdateFileProgress"

    },
    "QtClient\0ConnectServer\0\0DisconnectServer\0"
    "ReceiveMessage\0SendMessage\0ConnectFileServer\0"
    "DisconnectFileServer\0SelectFile\0"
    "SendFile\0UpdateFileProgress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void,

       0        // eod
};

void QtClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ConnectServer(); break;
        case 1: _t->DisconnectServer(); break;
        case 2: _t->ReceiveMessage(); break;
        case 3: _t->SendMessage(); break;
        case 4: _t->ConnectFileServer(); break;
        case 5: _t->DisconnectFileServer(); break;
        case 6: _t->SelectFile(); break;
        case 7: _t->SendFile(); break;
        case 8: _t->UpdateFileProgress((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 9: _t->UpdateFileProgress(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_QtClient.data,
    qt_meta_data_QtClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtClient.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QtClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
