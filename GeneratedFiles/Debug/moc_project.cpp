/****************************************************************************
** Meta object code from reading C++ file 'project.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../project.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'project.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlShapeWidget_t {
    QByteArrayData data[12];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlShapeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlShapeWidget_t qt_meta_stringdata_ControlShapeWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ControlShapeWidget"
QT_MOC_LITERAL(1, 19, 14), // "changeShapeArg"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 3), // "adj"
QT_MOC_LITERAL(4, 39, 5), // "value"
QT_MOC_LITERAL(5, 45, 17), // "setOnePathVisible"
QT_MOC_LITERAL(6, 63, 1), // "i"
QT_MOC_LITERAL(7, 65, 4), // "flag"
QT_MOC_LITERAL(8, 70, 19), // "spinBoxValueChanged"
QT_MOC_LITERAL(9, 90, 3), // "val"
QT_MOC_LITERAL(10, 94, 18), // "sliderValueChanged"
QT_MOC_LITERAL(11, 113, 15) // "checkBoxChanged"

    },
    "ControlShapeWidget\0changeShapeArg\0\0"
    "adj\0value\0setOnePathVisible\0i\0flag\0"
    "spinBoxValueChanged\0val\0sliderValueChanged\0"
    "checkBoxChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlShapeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       5,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   49,    2, 0x0a /* Public */,
      10,    1,   52,    2, 0x0a /* Public */,
      11,    1,   55,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Double,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void ControlShapeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlShapeWidget *_t = static_cast<ControlShapeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeShapeArg((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->setOnePathVisible((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->spinBoxValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->sliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->checkBoxChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlShapeWidget::*_t)(const QString & , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlShapeWidget::changeShapeArg)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ControlShapeWidget::*_t)(int , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlShapeWidget::setOnePathVisible)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ControlShapeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlShapeWidget.data,
      qt_meta_data_ControlShapeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ControlShapeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlShapeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ControlShapeWidget.stringdata0))
        return static_cast<void*>(const_cast< ControlShapeWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlShapeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ControlShapeWidget::changeShapeArg(const QString & _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlShapeWidget::setOnePathVisible(int _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_Project_t {
    QByteArrayData data[17];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Project_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Project_t qt_meta_stringdata_Project = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Project"
QT_MOC_LITERAL(1, 8, 12), // "fillComboBox"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "showShape"
QT_MOC_LITERAL(4, 32, 4), // "name"
QT_MOC_LITERAL(5, 37, 11), // "changeShape"
QT_MOC_LITERAL(6, 49, 3), // "adj"
QT_MOC_LITERAL(7, 53, 3), // "val"
QT_MOC_LITERAL(8, 57, 17), // "upDownTranslation"
QT_MOC_LITERAL(9, 75, 2), // "dy"
QT_MOC_LITERAL(10, 78, 20), // "leftRightTranslation"
QT_MOC_LITERAL(11, 99, 2), // "dx"
QT_MOC_LITERAL(12, 102, 23), // "shrinkExpandTranslation"
QT_MOC_LITERAL(13, 126, 5), // "times"
QT_MOC_LITERAL(14, 132, 8), // "showPath"
QT_MOC_LITERAL(15, 141, 1), // "i"
QT_MOC_LITERAL(16, 143, 4) // "flag"

    },
    "Project\0fillComboBox\0\0showShape\0name\0"
    "changeShape\0adj\0val\0upDownTranslation\0"
    "dy\0leftRightTranslation\0dx\0"
    "shrinkExpandTranslation\0times\0showPath\0"
    "i\0flag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Project[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       5,    2,   53,    2, 0x08 /* Private */,
       8,    1,   58,    2, 0x08 /* Private */,
      10,    1,   61,    2, 0x08 /* Private */,
      12,    1,   64,    2, 0x08 /* Private */,
      14,    2,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::Double,    6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   15,   16,

       0        // eod
};

void Project::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Project *_t = static_cast<Project *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fillComboBox(); break;
        case 1: _t->showShape((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->changeShape((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->upDownTranslation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->leftRightTranslation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->shrinkExpandTranslation((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->showPath((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Project::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Project.data,
      qt_meta_data_Project,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Project::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Project::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Project.stringdata0))
        return static_cast<void*>(const_cast< Project*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Project::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
