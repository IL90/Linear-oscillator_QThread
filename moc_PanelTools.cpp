/****************************************************************************
** Meta object code from reading C++ file 'PanelTools.h'
**
** Created: Fri Nov 8 12:42:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sources/PanelTools.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PanelTools.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PanelTools[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   23,   28,   28, 0x05,
      29,   28,   28,   28, 0x05,
      39,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      49,   60,   28,   28, 0x08,
      62,   28,   28,   28, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PanelTools[] = {
    "PanelTools\0sgnCmd(int)\0flag\0\0sgnPlay()\0"
    "sgnHelp()\0click(int)\0i\0slotPlay()\0"
};

void PanelTools::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PanelTools *_t = static_cast<PanelTools *>(_o);
        switch (_id) {
        case 0: _t->sgnCmd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sgnPlay(); break;
        case 2: _t->sgnHelp(); break;
        case 3: _t->click((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->slotPlay(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PanelTools::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PanelTools::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PanelTools,
      qt_meta_data_PanelTools, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PanelTools::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PanelTools::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PanelTools::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PanelTools))
        return static_cast<void*>(const_cast< PanelTools*>(this));
    return QFrame::qt_metacast(_clname);
}

int PanelTools::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PanelTools::sgnCmd(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PanelTools::sgnPlay()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void PanelTools::sgnHelp()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
