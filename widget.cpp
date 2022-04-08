// TP4-5/EX1/widget.cpp
// Exercice 1 : Formulaire emploi du temps
// BODIN Maxime C2
// 08/04/2022

#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    initDatabase();

    populateDataItem();


    connect(ui->deleteButton, SIGNAL(clicked(bool)),this,
            SLOT(remove()));
    connect(ui->addButton, SIGNAL(clicked(bool)),this,
            SLOT(addnew()));
    connect(ui->submitButton, SIGNAL(clicked(bool)),this,
            SLOT(save()));
}


void Widget::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\Maxime\\Documents\\session.bd");

    if (!db.open())
        qDebug() << "Error: connection with database failed";
    else
        qDebug() << "Database: connection ok";
}


void Widget::populateDataItem(){
    model = new QSqlTableModel(0, db);

    model->setTable("session");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Subject"));
    model->setHeaderData(1, Qt::Horizontal, tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, tr("DateTime"));
    model->setHeaderData(3, Qt::Horizontal, tr("Duration"));
    model->setHeaderData(4, Qt::Horizontal, tr("Classroom"));

    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->setAlternatingRowColors(true);
}


bool Widget::validClassroom()
{
    bool validation = true;
    string temp = ui->le_classroom->text().toStdString();
    if((temp[0] >= 65 && temp[0] <= 90) && temp.length() == 4){
        for(int i = 1; i < 4; i++)
            if(temp[i] < 48 || temp[i] > 57)
                validation = false;
    }else
        validation = false;

    return validation;
}


bool Widget::validDuration()
{
    bool validation = true;
    for(char c : ui->le_duration->text().toStdString())
        if(c < 48 || c > 57)
            validation = false;
    return validation;
}


void Widget::addnew()
{
    if(
            (ui->le_subject->text() == "AP" ||
             ui->le_subject->text() == "BD" ||
             ui->le_subject->text() == "CDIN" ||
             ui->le_subject->text() == "SI")
            &&
            (ui->le_type->text() == "CM" ||
             ui->le_type->text() == "TP" ||
             ui->le_type->text() == "TD")
            &&
            validClassroom()
            &&
            validDuration()
            )
    {
        int row=0;
        model->insertRows(row,1);
        model->setData(model->index(row,0),ui->le_subject->text());
        model->setData(model->index(row,1),ui->le_type->text());
        model->setData(model->index(row,2),ui->le_date->text());
        model->setData(model->index(row,3),ui->le_duration->text());
        model->setData(model->index(row,4),ui->le_classroom->text());
    }
    else
        QMessageBox::information(this,
                                 "Invalid insert",
                                 "Invalid Insert :\n Subject : AP,BD,CDIN,SI \n Type : CM,TD,TP \n Classroom : D204 \n Duration : in minutes ");
}


void Widget::remove(){
    int row=ui->tableView->currentIndex().row();
    if(QMessageBox::question(0,"Delete", "Record no. "
                             +QString::number(row+1)
                             +" will be deleted. Are you sure?",
                             QMessageBox::No,QMessageBox::Yes)==
            QMessageBox::Yes){
        model->removeRow(row);
    }
}


void Widget::save(){
    bool flag=model->submitAll();
    if(flag==false)
        QMessageBox::critical(this,"Failed", "cannot save changes.");
    else
        QMessageBox::information(this,"Success",
                                 "Changes saved successfully.");
}


void Widget::closeDatabase()
{db.close();}


Widget::~Widget()
{
    closeDatabase();
    delete model;
    delete ui;
}
