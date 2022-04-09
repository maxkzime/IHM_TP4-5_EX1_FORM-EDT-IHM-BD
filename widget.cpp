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

    //itsProxyModel->setSourceModel(itsModel);


    connect(ui->deleteButton, SIGNAL(clicked(bool)),this,
            SLOT(remove()));
    connect(ui->addButton, SIGNAL(clicked(bool)),this,
            SLOT(addNew()));
    connect(ui->submitButton, SIGNAL(clicked(bool)),this,
            SLOT(save()));

    connect(ui->dsb_duration, SIGNAL(valueChanged(double)),
            itsProxyModel, SLOT(setValue(double)));
}


void Widget::initDatabase()
{
    itsDB = QSqlDatabase::addDatabase("QSQLITE");
    itsDB.setDatabaseName("C:\\Users\\Maxime\\Documents\\session.bd");

    if (!itsDB.open())
        qDebug() << "Error: connection with database failed";
    else
        qDebug() << "Database: connection ok";
}


void Widget::populateDataItem()
{
    itsModel = new QSqlTableModel(0, itsDB);
    itsModel->setTable("session");
    itsModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    itsModel->select();
    itsModel->setHeaderData(0, Qt::Horizontal, tr("Subject"));
    itsModel->setHeaderData(1, Qt::Horizontal, tr("Type"));
    itsModel->setHeaderData(2, Qt::Horizontal, tr("DateTime"));
    itsModel->setHeaderData(3, Qt::Horizontal, tr("Duration"));
    itsModel->setHeaderData(4, Qt::Horizontal, tr("Classroom"));

    ui->tvTable->setModel(itsModel);
    //    ui->tvTable->sortByColumn(3, Qt::AscendingOrder);
    //    ui->tvTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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


void Widget::addNew()
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
        itsModel->insertRows(row,1);
        itsModel->setData(itsModel->index(row,0),ui->le_subject->text());
        itsModel->setData(itsModel->index(row,1),ui->le_type->text());
        itsModel->setData(itsModel->index(row,2),ui->le_date->text());
        itsModel->setData(itsModel->index(row,3),ui->le_duration->text());
        itsModel->setData(itsModel->index(row,4),ui->le_classroom->text());
    }
    else
        QMessageBox::information(this,
                                 "Invalid insert",
                                 "Invalid Insert :\n Subject : AP,BD,CDIN,SI \n Type : CM,TD,TP \n Classroom : D204 \n Duration : in minutes ");
}


void Widget::remove(){
    int row=ui->tvTable->currentIndex().row();
    if(QMessageBox::question(0,"Delete", "Record no. "
                             +QString::number(row+1)
                             +" will be deleted. Are you sure?",
                             QMessageBox::No,QMessageBox::Yes)==
            QMessageBox::Yes){
        itsModel->removeRow(row);
    }
}


void Widget::save(){
    bool flag=itsModel->submitAll();
    if(flag==false)
        QMessageBox::critical(this,"Failed", "cannot save changes.");
    else
        QMessageBox::information(this,"Success",
                                 "Changes saved successfully.");
}


void Widget::closeDatabase()
{itsDB.close();}


Widget::~Widget()
{
    closeDatabase();
    delete itsModel;
    delete ui;
    delete itsProxyModel;
}
