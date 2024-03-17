#include "operaciones.h"
#include <QString>
#include <bitset>
#include <stdio.h>
#include <math.h>
QString Operaciones::realizarOperacion(QString num1, QString num2, char operacion) {
    switch (operacion) {
    case '+':
        return sumar(num1, num2);
    case '*':
        return multiplicar(num1, num2);
    case '/':
        return dividir(num1, num2);
    }
}

QString Operaciones::sumar(QString num1, QString num2) {
    int P =0;
    int g=0, r=0, st=0;
    int n=24;
    bool Operandos_intercambiados=false;
    bool Completado_P=false;
    QString signoString1 = num1.mid(0, 1);
    QString expString1 = num1.mid(1, 8);
    QString mantString1 = "0"+num1.mid(9, 23);
    QString signoString2 = num2.mid(0, 1);
    QString expString2 = num2.mid(1, 8);
    QString mantString2 = "0"+num2.mid(9, 23);
    std::bitset<1> signobitset1(signoString1.toStdString());
    std::bitset<8> expbitset1(expString2.toStdString());
    std::bitset<24> mantbitset1(mantString1.toStdString());
    std::bitset<1> signobitset2(signoString2.toStdString());
    std::bitset<8> expbitset2(expString2.toStdString());
    std::bitset<24> mantbitset2(mantString2.toStdString());
    unsigned int exp1=expbitset1.to_ulong();
    unsigned int exp2=expbitset2.to_ulong();
    unsigned int signo1;
    unsigned int mant1;
    unsigned int signo2;
    unsigned int mant2;
    if(exp2>exp1){
        exp1=expbitset2.to_ulong();
        exp2=expbitset1.to_ulong();
        signo2=signobitset1.to_ulong();
        mant2=mantbitset1.to_ulong();
        signo1=signobitset2.to_ulong();
        mant1=mantbitset2.to_ulong();
        Operandos_intercambiados=true;
    }else{
        signo1=signobitset1.to_ulong();
        mant1=mantbitset1.to_ulong();
        signo2=signobitset2.to_ulong();
        mant2=mantbitset2.to_ulong();
    }
    unsigned int expS=exp1;
    unsigned int d=exp1-exp2;
    if(signo1!=signo2){
        mant2=~mant2;
        mant2=mant2+1;
    }
    P=mant2;

    printf("Unsigned int value: %u\n", mant2);


    return mantString1;
}

QString Operaciones::multiplicar(QString num1, QString num2) {
    return num2;
}

QString Operaciones::dividir(QString num1, QString num2) {
    return num1;
}
