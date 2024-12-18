// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , firstNum(0.0)
    , userIsTypingSecondNum(false)
{
    ui->setupUi(this);

    // Connect digit buttons
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));

    // Connect operator buttons
    connect(ui->pushButton_add, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_subtract, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(operator_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(operator_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    QString newLabel;

    if ((ui->label->text() == "0") || (userIsTypingSecondNum))
    {
        newLabel = button->text();
        userIsTypingSecondNum = false;
    }
    else
    {
        newLabel = ui->label->text() + button->text();
    }

    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_clear_clicked()
{
    ui->label->setText("0");
    firstNum = 0.0;
    userIsTypingSecondNum = false;
    operatorSymbol.clear();  // Limpar a operação quando o botão de limpar for pressionado
}

void MainWindow::operator_pressed()
{
    QPushButton *button = (QPushButton*)sender();
    firstNum = ui->label->text().toDouble(); // Armazena o primeiro número
    operatorSymbol = button->text(); // Armazena o operador
    ui->label->setText("0"); // Zera o display para o próximo número
    userIsTypingSecondNum = true;
}

void MainWindow::on_pushButton_equals_clicked()
{
    double secondNum = ui->label->text().toDouble();
    double result = 0.0;

    // Realiza a operação com base no operador
    if (operatorSymbol == "+")
    {
        result = firstNum + secondNum;
    }
    else if (operatorSymbol == "-")
    {
        result = firstNum - secondNum;
    }
    else if (operatorSymbol == "*")
    {
        result = firstNum * secondNum;
    }
    else if (operatorSymbol == "/")
    {
        if (secondNum != 0)
        {
            result = firstNum / secondNum;
        }
        else
        {
            ui->label->setText("Error");
            return; // Retorna sem fazer mais nada
        }
    }

    // Exibe o resultado
    ui->label->setText(QString::number(result, 'g', 15));
    userIsTypingSecondNum = false;
}
