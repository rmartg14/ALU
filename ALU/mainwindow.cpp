#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "conversor.h"
#include "QString"
#include "operaciones.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnSuma,SIGNAL(clicked()),this, SLOT(convertiraIEE()));
    connect(ui->btnSuma,SIGNAL(clicked()),this, SLOT(realizarSuma()));
    connect(ui->btnSuma,SIGNAL(clicked()),this, SLOT(convertiraDec()));
    connect(ui->btnMult,SIGNAL(clicked()),this, SLOT(convertiraIEE()));
    connect(ui->btnMult,SIGNAL(clicked()),this, SLOT(realizarMultiplicacion()));
    connect(ui->btnMult,SIGNAL(clicked()),this, SLOT(convertiraDec()));
    connect(ui->btnDivision,SIGNAL(clicked()),this, SLOT(convertiraIEE()));
    connect(ui->btnDivision,SIGNAL(clicked()),this, SLOT(realizarDivision()));
    connect(ui->btnDivision,SIGNAL(clicked()),this, SLOT(convertiraDec()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convertiraIEE(){
    float num1=ui->decimal1->text().toFloat();
    float num2=ui->decimal2->text().toFloat();
    QString result1=Conversor::convertir(num1);
    QString result2=Conversor::convertir(num2);
    ui->IEE1->setText(result1);
    ui->IEE2->setText(result2);
}


void MainWindow::convertiraDec(){
    QString num=ui->IEERes->text();
    if(num=="Inf"){
        ui->decimalRes->setText(num);
    }else{
        float result=Conversor::convertir2(num);
        ui->decimalRes->setText(QString::number(result));
    }

}


void MainWindow::realizarSuma()
{
    // Obtener los valores de los QLineEdit y convertirlos a números
    QString num1 = ui->IEE1->text();
    QString num2 = ui->IEE2->text();
    char operacion='+';
    // Realizar la operación de suma
    QString resultado = Operaciones::realizarOperacion(num1, num2, operacion);;

    // Mostrar el resultado en el QLineEdit correspondiente
    ui->IEERes->setText(resultado);
}

void MainWindow::realizarMultiplicacion()
{
    QString num1 = ui->IEE1->text();
    QString num2 = ui->IEE2->text();
    char operacion='*';
    QString resultado = Operaciones::realizarOperacion(num1, num2, operacion);;
    ui->IEERes->setText(resultado);
}

void MainWindow::realizarDivision()
{
    QString num1 = ui->IEE1->text();
    QString num2 = ui->IEE2->text();
    char operacion='/';
    QString resultado = Operaciones::realizarOperacion(num1, num2, operacion);;
    ui->IEERes->setText(resultado);


}
