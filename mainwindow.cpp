#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QTableView"//добавлено для вывода БД в таблице
#include "QStandardItemModel"//добавлено для вывода БД в таблице
#include "QStandardItem"//добавлено для вывода БД в таблице


#include "QCheckBox"//добавлено для вывода QCheckBox в таблице
#include "QRadioButton"//добавлено для вывода QRadioButton в таблице
#include "QHBoxLayout"//добавлено для создания элемента, в котором динамически будут созданы другие элементы



/*для исправления ошибки QSqlDatabasePrivate::addDatabase: duplicate connection name 'qt_sql_default_connection', old connection removed
подключать драйвер для БД (обычно доступно несколько драйверов, их список содержится в стандартном методе QSqlDatabase::drivers();)
следует в глобальной переменной static (видно везде в одном файле) или extern (видно везде во всех файлах) */
static QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");// db - это статическая глобальная переменная, которую можно использовать только в этом файле

// Создаём элемент, который будет выполнять роль чекбокса,делаем его static
//static QTableWidgetItem *item = new QTableWidgetItem();

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
tablewidgetfunction();//основная функция, выводящая таблицу в tableWidget


connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(forworktablevidget()));//получение значений всех ячеек в tablevidget через выбранные checkbox и radiobutton

}
MainWindow::~MainWindow()
{
delete ui;
}

void MainWindow::tablewidgetfunction(){//основная функция, выводящая таблицу в tableWidget
    ui->tableWidget->setColumnCount(5); // указываем количество столбцов в таблице

            //подключить БД по ее адресу на компьютере
            db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            //открывает базу данных, указанную в db.setDatabaseName("/home/mishanyya/fordbwork/examplebdfordbwork");
            db.open();

            //создает объект для запросов SQL
            QSqlQuery query( db );
            query.exec("SELECT * FROM basetable");

            // вставляем еще одну колонку в таблицу
            ui->tableWidget->insertColumn(1);

            for(int i = 0; query.next(); i++)
            {
                // вставляем еще одну строку в таблицу
                ui->tableWidget->insertRow(i);

                  //Работающий способ 1,только для checkbox!
                 // Создаём элемент, который будет выполнять роль чекбокса способ 1
               /* QTableWidgetItem *item = new QTableWidgetItem();
                item->data(Qt::CheckStateRole);
                item->setCheckState(Qt::Unchecked);
                        // Устанавливаем чекбокс в первую колонку
                        ui->tableWidget->setItem(i,0, item);*/


               //Работающий способ 2
                // Создаём элемент, который будет выполнять роль чекбокса способ 2
                //пробуем установить чекбоксы другим способом непосредственно в ячейку через setCellWidget
                //QCheckBox *checkbox = new QCheckBox();//для QCheckBox
                QRadioButton *checkbox = new QRadioButton();//для QRadioButton
                ui->tableWidget->setCellWidget(i, 0, checkbox);

            //вставить ячейку со значением в каждый элемент двумерного массива
                ui->tableWidget->setItem(i,1, new QTableWidgetItem(query.value(0).toString()));//value(2)-элемент 0 массива вывода
                ui->tableWidget->setItem(i,2, new QTableWidgetItem(query.value(1).toString()));//value(2)-элемент 1 массива вывода
                ui->tableWidget->setItem(i,3, new QTableWidgetItem(query.value(2).toString()));//value(2)-элемент 2 массива вывода
                ui->tableWidget->setItem(i,4, new QTableWidgetItem(query.value(3).toString()));//value(3)-элемент 3 массива вывода
                ui->tableWidget->setItem(i,5, new QTableWidgetItem(query.value(4).toString()));//value(4)-элемент 4 массива вывода
            }
            ui->tableWidget->hideColumn(1);//скрыть колонку 1, при этом все функции останутся работать
   }

void MainWindow::forworktablevidget(){
    //Работающий способ 1,только для checkbox!

    /*int qqq=ui->tableWidget->rowCount();//подсчет количества строк в таблице в виджете
    int w;//номер строки
        QString text;//переменная для содержимого ячейки
        for(w=0;w<qqq;w++){
           // if(ui->tableWidget->item(w,1)->isSelected())//если выделена ячейка в этом столбце
              if(ui->tableWidget->item(w,0)->checkState()) //если отмечен checkbox
            {
                text=ui->tableWidget->item(w,2)->text();//получение значений столбца 1
                 qDebug() << QString("Выбраны строки с номерами: ") << text;//вывод значений столбца 1
            }
        }*/


    //Работающий способ 2
    //В комментариях ВСЕ функции - РАБОТАЮЩИЕ!

//QVariant myData=ui->tableWidget->currentRow(); //рабочая функция!получение номера текущей строки
    //ui->label_2->setText(myData.toString());//рабочая функция!получение номера текущей строки

//int qqq=ui->tableWidget->rowCount();//рабочая функция подсчета и вывода количества строк в таблице в виджете
//ui->label_2->setText(QString::number(qqq));//рабочая функция подсчета и вывода количества строк в таблице в виджете

//рабочая функция подсчета нажатых checkbox
   /* int qqq=ui->tableWidget->rowCount();//подсчет количества строк в таблице в виджете
int w=0;//кол-во нажатых checkbox
    for(int i = 0; i<qqq; i++)
    {
          QCheckBox *checkbox = qobject_cast<QCheckBox*>(ui->tableWidget->cellWidget(i, 0));
            ui->tableWidget->setCellWidget(i, 0, checkbox);
            if (checkbox->isChecked())
            {
                w++;
            }
        }
    ui->label_2->setText(QString::number(w));*/

//ui->label_2->setText(ui->tableWidget->currentItem()->text());//рабочий пример получения значения выделенной ячейки

//рабочая функция получения значений поля в строках с выбранным checkbox
    int qqq=ui->tableWidget->rowCount();//подсчет количества строк в таблице в виджете
    QString a[qqq];//объявление массива из количества элементов = qqq
static QString check;
    for(int i = 0; i<qqq; i++)
    {
          //QCheckBox *checkbox = qobject_cast<QCheckBox*>(ui->tableWidget->cellWidget(i, 0));//для QCheckBox
        QRadioButton *checkbox = qobject_cast<QRadioButton*>(ui->tableWidget->cellWidget(i, 0));//для QRadioButton
            ui->tableWidget->setCellWidget(i, 0, checkbox);
            if (checkbox->isChecked())
            {
//надо немного доработать
              check=ui->tableWidget->item(i,1)->text();//получаем значение в ячейке колонки №0 (ID) в таблице
a[i]=check;
//рабочий пример динамического создания и вывода графических элементов
//требуется виджет в котором будут динамически создаваться объекты layout class="QVBoxLayout" name="verticalLayout"
   QLabel *label = new QLabel(a[i]);
   ui->verticalLayout->addWidget(label);
               }
        }
}



