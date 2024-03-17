#include "conversor.h"
#include <QTextStream>
#include <bitset>
#include <QString>
union Code {

    struct {
        unsigned int partFrac : 23;
        unsigned int expo : 8;
        unsigned int sign : 1;
    } bitfield;

    float numero;
    unsigned int numerox;
};

QString Conversor::convertir(float num){
    union Code a;
    a.numero = num;
    QString result=QString::fromStdString(std::bitset<1>(a.bitfield.sign).to_string());
    result+=QString::fromStdString(std::bitset<8>(a.bitfield.expo).to_string());
    result+=QString::fromStdString(std::bitset<23>(a.bitfield.partFrac).to_string());
    return result;

}

float Conversor::convertir2(QString num) {
    QString subString1 = num.mid(0, 1);
    QString subString2 = num.mid(1, 8);
    QString subString3 = num.mid(9, 23);
    std::bitset<1> bitset(subString1.toStdString());
    std::bitset<8> bitset2(subString2.toStdString());
    std::bitset<23> bitset3(subString3.toStdString());
    union Code a;
    a.bitfield.sign =bitset.to_ulong();
    a.bitfield.expo = bitset2.to_ulong();;
    a.bitfield.partFrac = bitset3.to_ulong();;;

    return a.numero;
}
