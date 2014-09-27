/****************************************************************************
** Meta object code from reading C++ file 'digitalclock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../digitalclock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'digitalclock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PixelInfoLabel_t {
    QByteArrayData data[6];
    char stringdata[31];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PixelInfoLabel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PixelInfoLabel_t qt_meta_stringdata_PixelInfoLabel = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 7),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 1),
QT_MOC_LITERAL(4, 26, 1),
QT_MOC_LITERAL(5, 28, 1)
    },
    "PixelInfoLabel\0setInfo\0\0a\0b\0v\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PixelInfoLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,

       0        // eod
};

void PixelInfoLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PixelInfoLabel *_t = static_cast<PixelInfoLabel *>(_o);
        switch (_id) {
        case 0: _t->setInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObject PixelInfoLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_PixelInfoLabel.data,
      qt_meta_data_PixelInfoLabel,  qt_static_metacall, 0, 0}
};


const QMetaObject *PixelInfoLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PixelInfoLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PixelInfoLabel.stringdata))
        return static_cast<void*>(const_cast< PixelInfoLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int PixelInfoLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_FrameCountLabel_t {
    QByteArrayData data[6];
    char stringdata[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_FrameCountLabel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_FrameCountLabel_t qt_meta_stringdata_FrameCountLabel = {
    {
QT_MOC_LITERAL(0, 0, 15),
QT_MOC_LITERAL(1, 16, 11),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 1),
QT_MOC_LITERAL(4, 31, 13),
QT_MOC_LITERAL(5, 45, 1)
    },
    "FrameCountLabel\0setDataLost\0\0n\0"
    "setFrameCount\0c\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameCountLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a,
       4,    1,   27,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void FrameCountLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FrameCountLabel *_t = static_cast<FrameCountLabel *>(_o);
        switch (_id) {
        case 0: _t->setDataLost((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setFrameCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject FrameCountLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_FrameCountLabel.data,
      qt_meta_data_FrameCountLabel,  qt_static_metacall, 0, 0}
};


const QMetaObject *FrameCountLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameCountLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameCountLabel.stringdata))
        return static_cast<void*>(const_cast< FrameCountLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int FrameCountLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_DigitalClock_t {
    QByteArrayData data[3];
    char stringdata[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DigitalClock_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DigitalClock_t qt_meta_stringdata_DigitalClock = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 8),
QT_MOC_LITERAL(2, 22, 0)
    },
    "DigitalClock\0showtime\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DigitalClock[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x08,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void DigitalClock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DigitalClock *_t = static_cast<DigitalClock *>(_o);
        switch (_id) {
        case 0: _t->showtime(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DigitalClock::staticMetaObject = {
    { &QLCDNumber::staticMetaObject, qt_meta_stringdata_DigitalClock.data,
      qt_meta_data_DigitalClock,  qt_static_metacall, 0, 0}
};


const QMetaObject *DigitalClock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DigitalClock::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DigitalClock.stringdata))
        return static_cast<void*>(const_cast< DigitalClock*>(this));
    return QLCDNumber::qt_metacast(_clname);
}

int DigitalClock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLCDNumber::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
