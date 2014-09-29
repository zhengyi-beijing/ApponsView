/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GraphicsView_t {
    QByteArrayData data[8];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_GraphicsView_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_GraphicsView_t qt_meta_stringdata_GraphicsView = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 6),
QT_MOC_LITERAL(2, 20, 0),
QT_MOC_LITERAL(3, 21, 7),
QT_MOC_LITERAL(4, 29, 21),
QT_MOC_LITERAL(5, 51, 21),
QT_MOC_LITERAL(6, 73, 19),
QT_MOC_LITERAL(7, 93, 19)
    },
    "GraphicsView\0zoomIn\0\0zoomOut\0"
    "increaseContrastStart\0decreaseContrastStart\0"
    "increaseContrastEnd\0decreaseContrastEnd\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06,
       3,    0,   45,    2, 0x06,
       4,    0,   46,    2, 0x06,
       5,    0,   47,    2, 0x06,
       6,    0,   48,    2, 0x06,
       7,    0,   49,    2, 0x06,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GraphicsView *_t = static_cast<GraphicsView *>(_o);
        switch (_id) {
        case 0: _t->zoomIn(); break;
        case 1: _t->zoomOut(); break;
        case 2: _t->increaseContrastStart(); break;
        case 3: _t->decreaseContrastStart(); break;
        case 4: _t->increaseContrastEnd(); break;
        case 5: _t->decreaseContrastEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::zoomIn)) {
                *result = 0;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::zoomOut)) {
                *result = 1;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::increaseContrastStart)) {
                *result = 2;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::decreaseContrastStart)) {
                *result = 3;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::increaseContrastEnd)) {
                *result = 4;
            }
        }
        {
            typedef void (GraphicsView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GraphicsView::decreaseContrastEnd)) {
                *result = 5;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject GraphicsView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_GraphicsView.data,
      qt_meta_data_GraphicsView,  qt_static_metacall, 0, 0}
};


const QMetaObject *GraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsView.stringdata))
        return static_cast<void*>(const_cast< GraphicsView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void GraphicsView::zoomIn()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void GraphicsView::zoomOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void GraphicsView::increaseContrastStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void GraphicsView::decreaseContrastStart()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void GraphicsView::increaseContrastEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void GraphicsView::decreaseContrastEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
struct qt_meta_stringdata_View_t {
    QByteArrayData data[10];
    char stringdata[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_View_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_View_t qt_meta_stringdata_View = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 6),
QT_MOC_LITERAL(2, 12, 0),
QT_MOC_LITERAL(3, 13, 7),
QT_MOC_LITERAL(4, 21, 10),
QT_MOC_LITERAL(5, 32, 11),
QT_MOC_LITERAL(6, 44, 9),
QT_MOC_LITERAL(7, 54, 11),
QT_MOC_LITERAL(8, 66, 12),
QT_MOC_LITERAL(9, 79, 18)
    },
    "View\0zoomIn\0\0zoomOut\0rotateLeft\0"
    "rotateRight\0resetView\0setupMatrix\0"
    "toggleOpenGL\0toggleAntialiasing\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_View[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a,
       3,    0,   55,    2, 0x0a,
       4,    0,   56,    2, 0x0a,
       5,    0,   57,    2, 0x0a,
       6,    0,   58,    2, 0x0a,
       7,    0,   59,    2, 0x08,
       8,    0,   60,    2, 0x08,
       9,    0,   61,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        View *_t = static_cast<View *>(_o);
        switch (_id) {
        case 0: _t->zoomIn(); break;
        case 1: _t->zoomOut(); break;
        case 2: _t->rotateLeft(); break;
        case 3: _t->rotateRight(); break;
        case 4: _t->resetView(); break;
        case 5: _t->setupMatrix(); break;
        case 6: _t->toggleOpenGL(); break;
        case 7: _t->toggleAntialiasing(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject View::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_View.data,
      qt_meta_data_View,  qt_static_metacall, 0, 0}
};


const QMetaObject *View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *View::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_View.stringdata))
        return static_cast<void*>(const_cast< View*>(this));
    return QFrame::qt_metacast(_clname);
}

int View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_PanelButton_t {
    QByteArrayData data[1];
    char stringdata[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PanelButton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PanelButton_t qt_meta_stringdata_PanelButton = {
    {
QT_MOC_LITERAL(0, 0, 11)
    },
    "PanelButton\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void PanelButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject PanelButton::staticMetaObject = {
    { &QToolButton::staticMetaObject, qt_meta_stringdata_PanelButton.data,
      qt_meta_data_PanelButton,  qt_static_metacall, 0, 0}
};


const QMetaObject *PanelButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelButton::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanelButton.stringdata))
        return static_cast<void*>(const_cast< PanelButton*>(this));
    return QToolButton::qt_metacast(_clname);
}

int PanelButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Panel_t {
    QByteArrayData data[31];
    char stringdata[548];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Panel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Panel_t qt_meta_stringdata_Panel = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 16),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 14),
QT_MOC_LITERAL(4, 39, 6),
QT_MOC_LITERAL(5, 46, 17),
QT_MOC_LITERAL(6, 64, 14),
QT_MOC_LITERAL(7, 79, 24),
QT_MOC_LITERAL(8, 104, 10),
QT_MOC_LITERAL(9, 115, 10),
QT_MOC_LITERAL(10, 126, 16),
QT_MOC_LITERAL(11, 143, 14),
QT_MOC_LITERAL(12, 158, 18),
QT_MOC_LITERAL(13, 177, 18),
QT_MOC_LITERAL(14, 196, 19),
QT_MOC_LITERAL(15, 216, 23),
QT_MOC_LITERAL(16, 240, 16),
QT_MOC_LITERAL(17, 257, 18),
QT_MOC_LITERAL(18, 276, 17),
QT_MOC_LITERAL(19, 294, 20),
QT_MOC_LITERAL(20, 315, 18),
QT_MOC_LITERAL(21, 334, 21),
QT_MOC_LITERAL(22, 356, 25),
QT_MOC_LITERAL(23, 382, 17),
QT_MOC_LITERAL(24, 400, 17),
QT_MOC_LITERAL(25, 418, 23),
QT_MOC_LITERAL(26, 442, 21),
QT_MOC_LITERAL(27, 464, 19),
QT_MOC_LITERAL(28, 484, 19),
QT_MOC_LITERAL(29, 504, 24),
QT_MOC_LITERAL(30, 529, 17)
    },
    "Panel\0openButton_click\0\0autoSaveEnable\0"
    "enable\0powerButton_click\0contrastEnable\0"
    "autoContrastButton_click\0zoomEnable\0"
    "moveEnable\0singleScanEnable\0dualScanEnable\0"
    "invertButton_click\0rotateButton_click\0"
    "settingButton_click\0calibrationButton_click\0"
    "plotButton_click\0aboutButton_handle\0"
    "openButton_handle\0settingButton_handle\0"
    "powerButton_handle\0contrastButton_handle\0"
    "autoContrastButton_handle\0zoomButton_handle\0"
    "moveButton_handle\0singleScanButton_handle\0"
    "dualScanButton_handle\0invertButton_handle\0"
    "rotateButton_handle\0calibrationButton_handle\0"
    "plotButton_handle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Panel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      14,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  154,    2, 0x06,
       3,    1,  155,    2, 0x06,
       5,    0,  158,    2, 0x06,
       6,    1,  159,    2, 0x06,
       7,    0,  162,    2, 0x06,
       8,    1,  163,    2, 0x06,
       9,    1,  166,    2, 0x06,
      10,    1,  169,    2, 0x06,
      11,    1,  172,    2, 0x06,
      12,    0,  175,    2, 0x06,
      13,    0,  176,    2, 0x06,
      14,    0,  177,    2, 0x06,
      15,    0,  178,    2, 0x06,
      16,    0,  179,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
      17,    0,  180,    2, 0x0a,
      18,    0,  181,    2, 0x0a,
      19,    0,  182,    2, 0x0a,
      20,    0,  183,    2, 0x0a,
      21,    0,  184,    2, 0x0a,
      22,    0,  185,    2, 0x0a,
      23,    0,  186,    2, 0x0a,
      24,    0,  187,    2, 0x0a,
      25,    0,  188,    2, 0x0a,
      26,    0,  189,    2, 0x0a,
      27,    0,  190,    2, 0x0a,
      28,    0,  191,    2, 0x0a,
      29,    0,  192,    2, 0x0a,
      30,    0,  193,    2, 0x0a,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Panel *_t = static_cast<Panel *>(_o);
        switch (_id) {
        case 0: _t->openButton_click(); break;
        case 1: _t->autoSaveEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->powerButton_click(); break;
        case 3: _t->contrastEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->autoContrastButton_click(); break;
        case 5: _t->zoomEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->moveEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->singleScanEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->dualScanEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->invertButton_click(); break;
        case 10: _t->rotateButton_click(); break;
        case 11: _t->settingButton_click(); break;
        case 12: _t->calibrationButton_click(); break;
        case 13: _t->plotButton_click(); break;
        case 14: _t->aboutButton_handle(); break;
        case 15: _t->openButton_handle(); break;
        case 16: _t->settingButton_handle(); break;
        case 17: _t->powerButton_handle(); break;
        case 18: _t->contrastButton_handle(); break;
        case 19: _t->autoContrastButton_handle(); break;
        case 20: _t->zoomButton_handle(); break;
        case 21: _t->moveButton_handle(); break;
        case 22: _t->singleScanButton_handle(); break;
        case 23: _t->dualScanButton_handle(); break;
        case 24: _t->invertButton_handle(); break;
        case 25: _t->rotateButton_handle(); break;
        case 26: _t->calibrationButton_handle(); break;
        case 27: _t->plotButton_handle(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::openButton_click)) {
                *result = 0;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::autoSaveEnable)) {
                *result = 1;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::powerButton_click)) {
                *result = 2;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::contrastEnable)) {
                *result = 3;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::autoContrastButton_click)) {
                *result = 4;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::zoomEnable)) {
                *result = 5;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::moveEnable)) {
                *result = 6;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::singleScanEnable)) {
                *result = 7;
            }
        }
        {
            typedef void (Panel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::dualScanEnable)) {
                *result = 8;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::invertButton_click)) {
                *result = 9;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::rotateButton_click)) {
                *result = 10;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::settingButton_click)) {
                *result = 11;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::calibrationButton_click)) {
                *result = 12;
            }
        }
        {
            typedef void (Panel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Panel::plotButton_click)) {
                *result = 13;
            }
        }
    }
}

const QMetaObject Panel::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_Panel.data,
      qt_meta_data_Panel,  qt_static_metacall, 0, 0}
};


const QMetaObject *Panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Panel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Panel.stringdata))
        return static_cast<void*>(const_cast< Panel*>(this));
    return QFrame::qt_metacast(_clname);
}

int Panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void Panel::openButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Panel::autoSaveEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Panel::powerButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void Panel::contrastEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Panel::autoContrastButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void Panel::zoomEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Panel::moveEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Panel::singleScanEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Panel::dualScanEnable(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Panel::invertButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}

// SIGNAL 10
void Panel::rotateButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 10, 0);
}

// SIGNAL 11
void Panel::settingButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 11, 0);
}

// SIGNAL 12
void Panel::calibrationButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 12, 0);
}

// SIGNAL 13
void Panel::plotButton_click()
{
    QMetaObject::activate(this, &staticMetaObject, 13, 0);
}
QT_END_MOC_NAMESPACE
