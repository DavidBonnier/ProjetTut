/****************************************************************************
** Meta object code from reading C++ file 'projetgeometrie.h'
**
** Created: Sun 12. Jan 17:52:25 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../projetgeometrie.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'projetgeometrie.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProjetGeometrie[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      30,   16,   16,   16, 0x0a,
      39,   16,   16,   16, 0x0a,
      49,   16,   16,   16, 0x0a,
      57,   16,   16,   16, 0x0a,
      66,   16,   16,   16, 0x0a,
      74,   16,   16,   16, 0x0a,
      82,   16,   16,   16, 0x0a,
      94,   16,   16,   16, 0x0a,
     103,   16,   16,   16, 0x0a,
     110,   16,   16,   16, 0x0a,
     117,   16,   16,   16, 0x0a,
     124,   16,   16,   16, 0x0a,
     132,   16,   16,   16, 0x0a,
     142,  140,   16,   16, 0x0a,
     168,  166,   16,   16, 0x0a,
     192,   16,   16,   16, 0x0a,
     225,  213,   16,   16, 0x0a,
     248,  140,   16,   16, 0x0a,
     271,  166,   16,   16, 0x0a,
     294,   16,   16,   16, 0x0a,
     314,  213,   16,   16, 0x0a,
     336,   16,   16,   16, 0x0a,
     350,  140,   16,   16, 0x0a,
     375,  166,   16,   16, 0x0a,
     400,   16,   16,   16, 0x0a,
     422,  213,   16,   16, 0x0a,
     446,   16,   16,   16, 0x0a,
     462,  140,   16,   16, 0x0a,
     486,  166,   16,   16, 0x0a,
     510,   16,   16,   16, 0x0a,
     542,  531,   16,   16, 0x0a,
     564,  213,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProjetGeometrie[] = {
    "ProjetGeometrie\0\0PleinEcran()\0Crayon()\0"
    "Equerre()\0Regle()\0Compas()\0Point()\0"
    "Texte()\0Epaisseur()\0Grille()\0Noir()\0"
    "Bleu()\0Vert()\0Rouge()\0Jaune()\0x\0"
    "CrayonPositionX(double)\0y\0"
    "CrayonPositionY(double)\0CrayonTransparence()\0"
    "orientation\0CrayonOrientation(int)\0"
    "ReglePositionX(double)\0ReglePositionY(double)\0"
    "RegleTransparence()\0RegleOrientation(int)\0"
    "RegleTracer()\0EquerrePositionX(double)\0"
    "EquerrePositionY(double)\0EquerreTransparence()\0"
    "EquerreOrientation(int)\0EquerreTracer()\0"
    "CompasPositionX(double)\0CompasPositionY(double)\0"
    "CompasTransparence()\0ecartement\0"
    "CompasEcartement(int)\0CompasOrientation(int)\0"
};

void ProjetGeometrie::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProjetGeometrie *_t = static_cast<ProjetGeometrie *>(_o);
        switch (_id) {
        case 0: _t->PleinEcran(); break;
        case 1: _t->Crayon(); break;
        case 2: _t->Equerre(); break;
        case 3: _t->Regle(); break;
        case 4: _t->Compas(); break;
        case 5: _t->Point(); break;
        case 6: _t->Texte(); break;
        case 7: _t->Epaisseur(); break;
        case 8: _t->Grille(); break;
        case 9: _t->Noir(); break;
        case 10: _t->Bleu(); break;
        case 11: _t->Vert(); break;
        case 12: _t->Rouge(); break;
        case 13: _t->Jaune(); break;
        case 14: _t->CrayonPositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->CrayonPositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 16: _t->CrayonTransparence(); break;
        case 17: _t->CrayonOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->ReglePositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 19: _t->ReglePositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->RegleTransparence(); break;
        case 21: _t->RegleOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->RegleTracer(); break;
        case 23: _t->EquerrePositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 24: _t->EquerrePositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 25: _t->EquerreTransparence(); break;
        case 26: _t->EquerreOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->EquerreTracer(); break;
        case 28: _t->CompasPositionX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->CompasPositionY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 30: _t->CompasTransparence(); break;
        case 31: _t->CompasEcartement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->CompasOrientation((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProjetGeometrie::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProjetGeometrie::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProjetGeometrie,
      qt_meta_data_ProjetGeometrie, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProjetGeometrie::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProjetGeometrie::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProjetGeometrie::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProjetGeometrie))
        return static_cast<void*>(const_cast< ProjetGeometrie*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProjetGeometrie::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
