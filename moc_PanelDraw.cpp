/****************************************************************************
** Meta object code from reading C++ file 'PanelDraw.h'
**
** Created: Fri Nov 8 12:42:57 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sources/PanelDraw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PanelDraw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyThread[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_MyThread[] = {
    "MyThread\0"
};

void MyThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MyThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MyThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_MyThread,
      qt_meta_data_MyThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyThread))
        return static_cast<void*>(const_cast< MyThread*>(this));
    return QThread::qt_metacast(_clname);
}

int MyThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_PanelDraw[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   48,   28,   28, 0x0a,
      50,   28,   28,   28, 0x0a,
      63,   28,   28,   28, 0x0a,
      78,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PanelDraw[] = {
    "PanelDraw\0sgnChangePCount()\0\0"
    "slotFlagTools(int)\0i\0slotPlayPD()\0"
    "slotNextStep()\0slotChangePCount()\0"
};

void PanelDraw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PanelDraw *_t = static_cast<PanelDraw *>(_o);
        switch (_id) {
        case 0: _t->sgnChangePCount(); break;
        case 1: _t->slotFlagTools((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->slotPlayPD(); break;
        case 3: _t->slotNextStep(); break;
        case 4: _t->slotChangePCount(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PanelDraw::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PanelDraw::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PanelDraw,
      qt_meta_data_PanelDraw, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PanelDraw::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PanelDraw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PanelDraw::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanelDraw))
        return static_cast<void*>(const_cast< PanelDraw*>(this));
    return QFrame::qt_metacast(_clname);
}

int PanelDraw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void PanelDraw::sgnChangePCount()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
