/****************************************************************************
** Meta object code from reading C++ file 'interfacetut.h'
**
** Created: Sun 12. Jan 11:41:21 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../interfacetut.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interfacetut.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Interface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      18,   10,   10,   10, 0x0a,
      32,   10,   10,   10, 0x0a,
      45,   10,   10,   10, 0x0a,
      61,   10,   10,   10, 0x0a,
      82,   10,   10,   10, 0x0a,
     100,   10,   10,   10, 0x0a,
     114,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Interface[] = {
    "Interface\0\0Aide()\0ChangerUtil()\0"
    "NouvelUtil()\0SupprimerUtil()\0"
    "FullScreen_Cahiers()\0FullScreen_Geom()\0"
    "ZoneDeTexte()\0AffichageRaccourcis()\0"
};

void Interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Interface *_t = static_cast<Interface *>(_o);
        switch (_id) {
        case 0: _t->Aide(); break;
        case 1: _t->ChangerUtil(); break;
        case 2: _t->NouvelUtil(); break;
        case 3: _t->SupprimerUtil(); break;
        case 4: _t->FullScreen_Cahiers(); break;
        case 5: _t->FullScreen_Geom(); break;
        case 6: _t->ZoneDeTexte(); break;
        case 7: _t->AffichageRaccourcis(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Interface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Interface::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Interface,
      qt_meta_data_Interface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Interface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Interface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Interface))
        return static_cast<void*>(const_cast< Interface*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
