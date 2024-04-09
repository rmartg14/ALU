#include "operaciones.h"
#include <QString>
#include <bitset>
#include <stdio.h>
#include "conversor.h"
#include <math.h>
#include <iostream>
#include <cmath>
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
    //PASO 1
    int P =0;
    int g=0, r=0, st=0;
    int n=24;
    bool Operandos_intercambiados=false;
    bool denormal=false;
    bool Complementado_P=false;
    QString signoString1 = num1.mid(0, 1);
    QString expString1 = num1.mid(1, 8);
    QString signoString2 = num2.mid(0, 1);
    QString expString2 = num2.mid(1, 8);
    std::bitset<8> expbitset2(expString2.toStdString());
    std::bitset<8> expbitset1(expString1.toStdString());
    unsigned int exp1=expbitset1.to_ulong();
    unsigned int exp2=expbitset2.to_ulong();
    QString mantString1="";
    QString mantString2="";
    if(exp1>254||exp2>254){
        QString infinito="Inf";
        return infinito;
    }
    if(expString1.toStdString()=="00000000"||expString1.toStdString()=="11111111"){
        expString1="00000001";
        mantString1 = "0"+num1.mid(9, 23);
        denormal=true;
    }else{
        mantString1 = "1"+num1.mid(9, 23);
    }

    if(expString2.toStdString()=="00000000"||expString2.toStdString()=="11111111"){
        expString2="00000001";
        mantString2 = "0"+num2.mid(9, 23);
        denormal=true;
    }else{
        mantString2 = "1"+num2.mid(9, 23);
    }

    std::bitset<1> signobitset1(signoString1.toStdString());
    std::bitset<24> mantbitset1(mantString1.toStdString());
    std::bitset<1> signobitset2(signoString2.toStdString());

    std::bitset<24> mantbitset2(mantString2.toStdString());
    unsigned int signo1;
    unsigned int mant1;
    unsigned int signo2;
    unsigned int mant2;
    //PASO 2
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
    //PASO 3
    unsigned int expS=exp1;
    unsigned int d=exp1-exp2;


    P=mant2;
    std::bitset<24> binaryValue(P);
    QString binaryPString = QString::fromStdString(binaryValue.to_string());
    //PASO 4 Y 5
    if(signo1!=signo2){
        QString biti="";
        QString temporal="";
        for(int i=0;i<24;i++){
            biti=binaryPString.at(i);
            if(biti.toStdString()=="1"){
                temporal=temporal+"0";

            }else{
               temporal=temporal+"1";
            }

        }
        binaryPString="";
        int acarreotemp=1;
        for(int i=23;i>=0;i--){
            biti=temporal.at(i);
            if(biti.toStdString()=="0"){
                if(acarreotemp==0){
                    binaryPString="0"+binaryPString;
                }else{
                    binaryPString="1"+binaryPString;
                    acarreotemp=0;
                }
            }else{
                if(acarreotemp==0){
                    binaryPString="1"+binaryPString;
                }else{
                    binaryPString="0"+binaryPString;
                }
            }
        }

    }


    QString bitG="";
    QString bitR="";
    QString bitST="";
    //PASO 6
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
    }else if(d>=3&&d<27){
        if(24-d>=0){
            bitG=binaryPString.at(24-d);
        }
        if(24-d+1>=0){
            bitR=binaryPString.at(24-d+1);
        }

        int i=24-d+2;
        bitST=binaryPString.at(24-d+2);
        while(i>=0&&bitST.toStdString()=="0"){
            bitST=binaryPString.at(i);
            i--;
        }

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
    }else{
        if(d>0){
            int i=23;
            bitST=binaryPString.at(23);
            while(i>=0&&bitST.toStdString()=="0"){
                bitST=binaryPString.at(i);
                i--;
            }
        }
    }

    //PASO 7
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
    //PASO 8
    QString binaryPStringSuma="";
    QString bit1="";
    QString bit2="";
    int acarreo=0;
    std::bitset<24> binaryValueMant1(mant1);
    QString binaryMant1String = QString::fromStdString(binaryValueMant1.to_string());
    for(int i=23;i>=0;i--){
        bit1=binaryMant1String.at(i);
        bit2=binaryPString2.at(i);
        if(bit1.toStdString()=="1"&&bit2.toStdString()=="1"){
            if(acarreo==1){
                binaryPStringSuma="1"+binaryPStringSuma;
            }else{
                binaryPStringSuma="0"+binaryPStringSuma;
                acarreo=1;
            }
        }else if(bit1.toStdString()=="0"&&bit2.toStdString()=="0"){
            if(acarreo==1){
                binaryPStringSuma="1"+binaryPStringSuma;
                acarreo=0;
            }else{
                binaryPStringSuma="0"+binaryPStringSuma;
            }
        }else{
            if(acarreo==1){
                binaryPStringSuma="0"+binaryPStringSuma;
            }else{
                binaryPStringSuma="1"+binaryPStringSuma;
            }
        }

    }
    //PASO 9
    bit1=binaryPStringSuma.at(0);
    if(signo1!=signo2&&bit1.toStdString()=="1"&&acarreo==0){
        QString biti2="";
        QString temporal2="";
        for(int i=0;i<24;i++){
            biti2=binaryPStringSuma.at(i);
            if(biti2.toStdString()=="1"){
                temporal2=temporal2+"0";

            }else{
                temporal2=temporal2+"1";
            }

        }
        binaryPStringSuma="";
        int acarreotemp2=1;
        for(int i=23;i>=0;i--){
            biti2=temporal2.at(i);
            if(biti2.toStdString()=="0"){
                if(acarreotemp2==0){
                    binaryPStringSuma="0"+binaryPStringSuma;
                }else{
                    binaryPStringSuma="1"+binaryPStringSuma;
                    acarreotemp2=0;
                }
            }else{
                if(acarreotemp2==0){
                    binaryPStringSuma="1"+binaryPStringSuma;
                }else{
                    binaryPStringSuma="0"+binaryPStringSuma;
                }
            }
        }


        Complementado_P=true;
    }
    //PASO 10
    if(signo1==signo2&&acarreo==1){
        if(g==1||r==1||st==1){
            st=1;
        }
        bit1=binaryPStringSuma.at(0);
        r=std::stoi(bit1.toStdString());
        binaryPStringSuma="1"+binaryPStringSuma.mid(0,24-1);
        expS=expS+1;
        //suma usando expFinal
    }else{
        bit1=binaryPStringSuma.at(0);
        int k=0;
        while(bit1.toStdString()=="0"&&k<23){
            bit1=binaryPStringSuma.at(k+1);
            k++;
        }
        if(bit1.toStdString()=="0"){
            k++;
        }


        if(k==0){
            if(r==1||st==1){
                st=1;
            }
            r=g;
        }else{
            r=0;
            st=0;
        }
        QString strG="";
        if(g==1){
            for(int i=0;i<k;i++){
                strG=strG+"1";
            }
        }else{
            for(int i=0;i<k;i++){
                strG=strG+"0";
            }
        }
        binaryPStringSuma=binaryPStringSuma.mid(k,24-k)+strG;
        expS=expS-k;
    }
    //PASO 11
     bit1=binaryPStringSuma.at(n-1);
    if((r==1&&st==1)||(r==1&&st==0&&bit1.toStdString()=="1")){
        QString binaryPFinal="";
        int acarreo2=1;
        for(int i=23;i>=0;i--){
            bit1=binaryPStringSuma.at(i);
            if(bit1.toStdString()=="0"){
                if(acarreo2==0){
                    binaryPFinal="0"+binaryPFinal;
                }else{
                    binaryPFinal="1"+binaryPFinal;
                    acarreo2=0;
                }
            }else{
                if(acarreo2==0){
                    binaryPFinal="1"+binaryPFinal;
                }else{
                    binaryPFinal="0"+binaryPFinal;
                }
            }

        }
        if(acarreo2==1){
            binaryPFinal="1"+binaryPFinal.mid(1,24-1);
            expS=expS+1;

        }
        binaryPStringSuma=binaryPFinal;

    }
    //PASO 12
    QString mantisaFinal=binaryPStringSuma;
    QString signoF="";
    if(Operandos_intercambiados==false&&Complementado_P==true){
        if(signo2==0){
            signoF="0"+signoF;
        }else{
           signoF="1"+signoF;
        }

    }else{
        if(signo1==0){
            signoF="0"+signoF;
        }else{
            signoF="1"+signoF;
        }

    }

    QString expFinal="";
    if(exp1==exp2&&signo1!=signo2&&mant1==mant2){
        expFinal="00000000";
    }else{
        std::bitset<8> binaryExp(expS);
        expFinal = QString::fromStdString(binaryExp.to_string());

    }
    if(denormal==true){
        expFinal="00000001";
    }


    //PASO 13
    return signoF+expFinal+mantisaFinal.mid(1,23);
}

QString Operaciones::multiplicar(QString num1, QString num2) {
    if(num1.toStdString()=="00000000000000000000000000000000"){
        return num1;
    }
    if(num2.toStdString()=="00000000000000000000000000000000"){
        return num2;
    }
    int g=0, r=0, st=0;
    int n=24;
    bool denormal;
    QString signoString1 = num1.mid(0, 1);
    QString signoString2 = num2.mid(0, 1);
    QString expString1 = num1.mid(1, 8);
    QString expString2 = num2.mid(1, 8);
    QString mantString1="1"+num1.mid(9, 23);;
    QString mantString2="1"+num2.mid(9, 23);;
    std::bitset<1> signobitset1(signoString1.toStdString());
    std::bitset<8> expbitset1(expString1.toStdString());
    std::bitset<24> mantbitset1(mantString1.toStdString());
    std::bitset<1> signobitset2(signoString2.toStdString());
    std::bitset<8> expbitset2(expString2.toStdString());
    std::bitset<24> mantbitset2(mantString2.toStdString());
    unsigned int exp1=expbitset1.to_ulong();
    unsigned int exp2=expbitset2.to_ulong();
    unsigned int signo1=signobitset1.to_ulong();
    unsigned int mant1=mantbitset1.to_ulong();
    unsigned int signo2=signobitset2.to_ulong();
    unsigned int mant2=mantbitset2.to_ulong();


    if(expString1.toStdString()=="00000000"||expString1.toStdString()=="11111111"||expString2.toStdString()=="00000000"||expString2.toStdString()=="11111111"){
        denormal=true;
    }
    // PASO 1
    QString signoF="";

    if (signo1==signo2){
        signoF="0"+signoF;
    }else{
        signoF="1"+signoF;
    }


    //PASO 2
    int expR;
    expR= 127+(exp1-127) + (exp2 - 127);

    //PASO 3
    //PASO I
    QString P="000000000000000000000000";
    QString A=mantString1;
    QString B=mantString2;
    QString bita0="";
    QString bit1="";
    QString bit2="";
    int acarreo=0;
    for(int j = 0; j < n; j++) {
        bita0=A.at(23);
        if(bita0.toStdString()=="1") {
            QString sumaP="";
            for(int i=23;i>=0;i--){
                bit1=P.at(i);
                bit2=B.at(i);
                if(bit1.toStdString()=="1"&&bit2.toStdString()=="1"){
                    if(acarreo==1){
                        sumaP="1"+sumaP;
                    }else{
                        sumaP="0"+sumaP;
                        acarreo=1;
                    }
                }else if(bit1.toStdString()=="0"&&bit2.toStdString()=="0"){
                    if(acarreo==1){
                        sumaP="1"+sumaP;
                        acarreo=0;
                    }else{
                        sumaP="0"+sumaP;
                    }
                }else{
                    if(acarreo==1){
                        sumaP="0"+sumaP;
                    }else{
                        sumaP="1"+sumaP;
                    }
                }

            }
            P=sumaP;
        }else{
            acarreo=0;
        }
        bita0=P.at(23);
        A=bita0+A.mid(0,23);
        if(acarreo==0){
            P="0"+P.mid(0,23);
        }else{
            P="1"+P.mid(0,23);
        }



    }
    //PASO II
    bita0=P.at(0);
    if(bita0.toStdString()=="0"){
        bit1=A.at(23);
        P=P.mid(1,23)+bit1;
        A=A.mid(1,23)+"0";

    }else{
        expR=expR+1;
    }
    //PASO III

    bit1=A.at(0);
    if(bit1.toStdString()=="1"){
        r=1;
    }else{
        r=0;
    }
    //PASO IV
    for(int i=1;i<24;i++){
        bit2=A.at(i);
        if(bit2=="1"){
            st=1;
        }
    }

    //PASO V
    bita0=P.at(23);
    if ((r == 1 && st == 1) || (r == 1 && st == 0 && bita0.toStdString()=="1")) {
        QString binaryPFinal="";
        int acarreo2=1;
        for(int i=23;i>=0;i--){
            bit1=P.at(i);
            if(bit1.toStdString()=="0"){
                if(acarreo2==0){
                    binaryPFinal="0"+binaryPFinal;
                }else{
                    binaryPFinal="1"+binaryPFinal;
                    acarreo2=0;
                }
            }else{
                if(acarreo2==0){
                    binaryPFinal="1"+binaryPFinal;
                }else{
                    binaryPFinal="0"+binaryPFinal;
                }
            }

        }
        P=binaryPFinal;
    }



    //COMPROBACIONES OVERFLOW UNDERFLOW Y DENORMAL

    if (expR>254) {
        QString expMax="11111111";
        return signoF+expMax+P;
    }


    if(expR<1) {
        int t = 1-expR;
        if (t >= 24){
            QString expMax="11111111";
            return " "+signoF+expMax+P;
        }else{
            QString aux1="";
            QString aux2="";
            for (int i = 23; i>23-t; i++) {
                aux1=aux1+"0";
                aux2=P.at(i)+aux2;

            }
            P=aux1+P.mid(0,24-t);
            A=aux2+A.mid(0,24-t);
            expR = 1;
        }
    }

    if(denormal==true){
        if(expR>1){
            int t1, t2, t;
            t1=expR-1;
            QString bit0="";
            bit0=P.at(0);
            t2=0;
            while(bit0.toStdString()=="0"&&t2<23){
                bit0=P.at(t2+1);
                t2++;
            }
            if(bit0.toStdString()=="0"){
                t2++;
                int t3=0;
                bit0=A.at(0);
                while(bit0.toStdString()=="0"&&t3<23){
                    bit0=A.at(t3+1);
                    t3++;
                }
                if(bit0.toStdString()=="0"){
                    t3++;
                }
                t2=t2+t3;

            }
            if(t1>t2){
                t=t2;
            }else{
                t=t1;
            }
            expR=expR-t;
            QString PA=P+A;
            QString ceros="";
            for(int i=0;i<t;i++){
                ceros=ceros+"0";
            }
            PA=PA.mid(0,48-t)+ceros;
            P=PA.mid(0,24);


        }
    }



    QString binaryPString = P;
    QString mantisaFinal=binaryPString;
    QString expFinal="";

    std::bitset<8> binaryExp(expR);
    expFinal = QString::fromStdString(binaryExp.to_string());


    return signoF+expFinal+mantisaFinal.mid(1,23);
}

QString Operaciones::dividir(QString num1, QString num2) {
    if(num2.toStdString()=="00000000000000000000000000000000"){
        QString Nan="NaN";
        return Nan;
    }
    if(num1.toStdString()=="00000000000000000000000000000000"){
        QString cero ="00000000000000000000000000000000";
        return cero;
    }
    QString signoString1 = num1.mid(0, 1);
    QString signoString2 = num2.mid(0, 1);
    QString num1prueba = "0"+num1.mid(1, 31);
    QString num2prueba = "0"+num2.mid(1, 31);
    QString expnum1String=num1.mid(1,8);
    QString expnum2String=num2.mid(1,8);
    std::bitset<8> expbitsetN2(expnum1String.toStdString());
    std::bitset<8> expbitsetN1(expnum2String.toStdString());
    unsigned int expN1=expbitsetN1.to_ulong();
    unsigned int expN2=expbitsetN2.to_ulong();
    if(expN1>254||expN2>254){
        QString infinito="Inf";
        return infinito;
    }
    //PASO 1
    QString mantString1="1"+num1.mid(9, 23);;
    QString mantString2="1"+num2.mid(9, 23);;
    float bprim=0.0;
    float adec=0.0;
    float bdec=0.0;
    QString bitMant="";
    for(int i=1;i<24;i++){
        bitMant=mantString1.at(i);
        if(bitMant.toStdString()=="1"){
            adec=adec+1/pow(2,i);
        }
    }
    adec=1+adec;
    for(int i=1;i<24;i++){
        bitMant=mantString2.at(i);
        if(bitMant.toStdString()=="1"){
            bdec=bdec+1/pow(2,i);
        }
    }
    bdec=1+bdec;
    //PASO 2
    if(bdec>=1.25){
        bprim=0.80;
    }else{
        bprim=1.0;
    }
    //PASO 3
    float lim=0.0001;
    QString aString= Conversor::convertir(adec);
    QString bString=Conversor::convertir(bdec);
    QString bprimString=Conversor::convertir(bprim);
    QString r2=Conversor::convertir(2.0);
    QString xInic= Operaciones::multiplicar(aString,bprimString);
    QString yInic= Operaciones::multiplicar(bString,bprimString);
    QString restaString="";
    float resta=1.0;
    QString r="";
    QString yFin="";
    QString xFin="";
    //PASO 4
    while(resta>=lim){
        r=Operaciones::sumar(r2,"1"+yInic.mid(1,31));
        xFin=Operaciones::multiplicar(xInic,r);
        yFin=Operaciones::multiplicar(yInic,r);
        restaString=Operaciones::sumar(xFin,"1"+xInic.mid(1,31));
        resta=Conversor::convertir2(restaString);
        if(resta<0){
            resta=resta*(-1);
        }
        xInic=xFin;
        yInic=yFin;

    }
    //RESULTADOS
    QString signoA=num1.mid(0,1);
    QString signoB=num2.mid(0,1);
    QString signoF="";
    if(signoA.toStdString()==signoB.toStdString()){
        signoF=signoF+"0";
    }else{
        signoF=signoF+"1";
    }
    QString mantF=xInic.mid(9,23);
    QString expString1 = num1.mid(1, 8);
    QString expString2 = num2.mid(1, 8);
    QString expString3 = xInic.mid(1, 8);
    std::bitset<8> expbitset1(expString1.toStdString());
    std::bitset<8> expbitset2(expString2.toStdString());
    std::bitset<8> expbitset3(expString3.toStdString());
    unsigned int exp1=expbitset1.to_ulong();
    unsigned int exp2=expbitset2.to_ulong();
    unsigned int exp3=expbitset3.to_ulong();
    int expFinal=exp1-exp2+exp3;
    std::bitset<8> binaryExp(expFinal);
    QString expF = QString::fromStdString(binaryExp.to_string());
    if(expFinal>254){
        if(signoString1.toStdString()==signoString2.toStdString()){
            QString expInf="11111111";
            return signoF+ expInf +mantF;
        }else{
            QString expInf="11111111";
            return signoF+ expInf +mantF;
        }

    }



    return signoF+ expF +mantF;
}

