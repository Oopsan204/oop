/****************************************************************************
** Meta object code from reading C++ file 'viewer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../viewer.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN6ViewerE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN6ViewerE = QtMocHelpers::stringData(
    "Viewer",
    "startGame_slot",
    "",
    "restartGame_slot",
    "f",
    "loadFile_slot",
    "surrender_slot",
    "saveGame_slot",
    "timeout_slot",
    "startWithAI_slot"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN6ViewerE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x0a,    1 /* Public */,
       3,    1,   69,    2, 0x0a,    2 /* Public */,
       3,    0,   72,    2, 0x2a,    4 /* Public | MethodCloned */,
       5,    0,   73,    2, 0x0a,    5 /* Public */,
       6,    0,   74,    2, 0x0a,    6 /* Public */,
       7,    1,   75,    2, 0x0a,    7 /* Public */,
       7,    0,   78,    2, 0x2a,    9 /* Public | MethodCloned */,
       8,    0,   79,    2, 0x0a,   10 /* Public */,
       9,    0,   80,    2, 0x0a,   11 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Viewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ZN6ViewerE.offsetsAndSizes,
    qt_meta_data_ZN6ViewerE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN6ViewerE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Viewer, std::true_type>,
        // method 'startGame_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restartGame_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'restartGame_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadFile_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'surrender_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveGame_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveGame_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'timeout_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startWithAI_slot'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Viewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Viewer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->startGame_slot(); break;
        case 1: _t->restartGame_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->restartGame_slot(); break;
        case 3: _t->loadFile_slot(); break;
        case 4: _t->surrender_slot(); break;
        case 5: _t->saveGame_slot((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->saveGame_slot(); break;
        case 7: _t->timeout_slot(); break;
        case 8: _t->startWithAI_slot(); break;
        default: ;
        }
    }
}

const QMetaObject *Viewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Viewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN6ViewerE.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Viewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
