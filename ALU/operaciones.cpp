#include "operaciones.h"
#include <QString>
#include <bitset>
#include <stdio.h>
#include <math.h>
#include <iostream>
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
    QString mantString1 = "1"+num1.mid(9, 23);
    QString signoString2 = num2.mid(0, 1);
    QString expString2 = num2.mid(1, 8);
    QString mantString2 = "1"+num2.mid(9, 23);
    std::bitset<1> signobitset1(signoString1.toStdString());
    std::bitset<8> expbitset1(expString1.toStdString());
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
    std::bitset<24> binaryValue(P);
    QString binaryPString = QString::fromStdString(binaryValue.to_string());
    QString bitG="";
    QString bitR="";
    QString bitST="";
    if(d==1){
        bitG=binaryPString.at(24-d);
        if(bitG.toStdString()=="0"){
            g=0;
        }else{
            g=1;
        }
    }else if(d==2){
        bitG=binaryPString.at(24-d);
        bitR=binaryPString.at(24-d+1);
        if(bitG.toStdString()=="0"){
            g=0;
        }else{
            g=1;
        }
        if(bitR.toStdString()=="0"){
            r=0;
        }else{
            r=1;
        }
    }else if(d>=3){
        bitG=binaryPString.at(24-d);
        bitR=binaryPString.at(24-d+1);
        bitST=binaryPString.at(24-d+2);
        if(bitG.toStdString()=="0"){
            g=0;
        }else{
            g=1;
        }
        if(bitR.toStdString()=="0"){
            r=0;
        }else{
            r=1;
        }
        if(bitST.toStdString()=="0"){
            st=0;
        }else{
            st=1;
        }
    }

    QString binaryPString2="";
    QString subPbinary="";
    if(signo1!=signo2){
        QString stringUnos="";
        for(int i=d;i>0;i--){
            stringUnos=stringUnos+"1";
        }
        subPbinary=binaryPString.mid(0,24-d);
        binaryPString2=stringUnos+subPbinary;
    }else{
        QString stringCeros="";
        for(int i=d;i>0;i--){
            stringCeros=stringCeros+"0";
        }
        subPbinary=binaryPString.mid(0,24-d);
        binaryPString2=stringCeros+subPbinary;

    }
    printf("Unsigned int value: %u\n", exp1);
    printf("Unsigned int value: %u\n", exp2);
    printf("Unsigned int value: %u\n", P);
    printf("Unsigned int value: %u\n", d);
    std::cout << bitG.toStdString() << std::endl;
    std::cout << binaryPString2.toStdString() << std::endl;


    return binaryPString;
}

QString Operaciones::multiplicar(QString num1, QString num2) {
    int P =0;
    int g=0, r=0, st=0;
    int n=24;
    QString signoString1 = num1.mid(0, 1);
    QString expString1 = num1.mid(1, 8);
    QString mantString1 = "1"+num1.mid(9, 23);
    QString signoString2 = num2.mid(0, 1);
    QString expString2 = num2.mid(1, 8);
    QString mantString2 = "1"+num2.mid(9, 23);
    std::bitset<1> signobitset1(signoString1.toStdString());
    std::bitset<8> expbitset1(expString1.toStdString());
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

    std::bitset<24> binaryBValue(P);
    QString binaryBString = QString::fromStdString(binaryBValue.to_string());

    unsigned int signoR;
    signoR=signo1 * signo2;

    unsigned int expR= 127+(exp1-127) + (exp2 - 127);
    expR= 127+(exp1-127) + (exp2 - 127);

    unsigned int mantR;
    mant1 = mant1|8388608;
    mant2 = mant2|8388608;

    //paso a producto sin signo
    unsigned int a=0;
    unsigned int b=0;

    a = mant1;
    b = 0;

    for(int i = 0; i < n; i++) {
        if(a>>(0)&1) {
            b = b + mant2;
        }

        b = b >> 1;
        a = a >> 1;
    }

    if (!((b>>23)&1)) {
        b = b << 1;

    } else {
        expR = expR + 1;
    }

    r = ((a>>23)&1);
    st = 0;

    for (int i = 22; i >= 0; i--) {
        st = st|((a>>i)&1);
    }

    if ((r == 1 && st == 1) || (r == 1 && st == 0 && (b>>0)&1 == 1)) {
        b = b + 1;
    }

    //overflow
    if (expR>254) {


    //underflow
    if(expR < 1) {
    }

    //operandos denormales


    b=mantR;

    return binaryBString;
}

QString Operaciones::dividir(QString num1, QString num2) {
    return num1;
}
