//#ifndef WIDGET_H
//#define WIDGET_H

//#include <QWidget>

//QT_BEGIN_NAMESPACE
//namespace Ui { class Widget; }
//QT_END_NAMESPACE

//class Widget : public QWidget
//{
//    Q_OBJECT

//public:
//    Widget(QWidget *parent = nullptr);
//    ~Widget();

//private:
//    Ui::Widget *ui;
//};
//#endif // WIDGET_H


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QtGui>

namespace Ui {
   class Widget;
}

class Widget : public QWidget
{
   Q_OBJECT

   public:
      explicit Widget(QWidget *parent = 0);
      ~Widget();
      void populateDataItem();

   public slots:
      void addnew();
      void remove();
      void save();

   private:
      Ui::Widget *ui;
      QSqlTableModel *model;
      QSqlDatabase db;

      bool initDatabase();
      void closeDatabase();
};
#endif   // WIDGET_H
