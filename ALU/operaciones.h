#include <QString>

#ifndef OPERACIONES_H
#define OPERACIONES_H

class Operaciones
{
public:
    static QString realizarOperacion(QString num1, QString num2, char operacion);

private:
    static QString sumar(QString num1, QString num2);
    static QString multiplicar(QString num1, QString num2);
    static QString dividir(QString num1, QString num2);
};

#endif // OPERACIONES_H
