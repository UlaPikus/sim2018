#include <QtCore/QCoreApplication>
#include <QtSql>
#include <qtextstream.h>
#include <iostream>
#include <string>
using namespace std;

void select_all(bool database_opened){

    QTextStream cout(stdout, QIODevice::WriteOnly);

    if ( database_opened ) {

        QSqlQuery query( "select * from pacjenci" );
        if ( !query.isActive() )
            cout << "Query Error" + query.lastError().text()<< endl;

        else while (query.next()) {
            int id = query.value(0).toInt();
            QString nazwisko = query.value(1).toString();
            QString imie = query.value(2).toString();
            QString adres = query.value(3).toString();
            QString miasto = query.value(4).toString();
            QString pesel = query.value(5).toString();

            cout << QString( "%1\t\t\t%2\t\t\t%3\t\t\t%4\t\t\t%5\t\t%6\n").arg(id).arg(nazwisko).arg(imie).arg(adres).arg(miasto).arg(pesel);
        }
    } else {
        cout<<"Database not opened!";
    }
}

void insert_user(QString nazwisko, QString imie, QString pesel, QString adres, QString miasto){

    QTextStream cout(stdout, QIODevice::WriteOnly);

    QSqlQuery query;

    query.prepare( "INSERT INTO pacjenci (nazwisko, imie, adres, miasto, pesel) VALUES (:nazwisko, :imie, :adres, :miasto, :pesel)");

    query.bindValue( ":nazwisko", nazwisko );
    query.bindValue( ":imie", imie );
    query.bindValue( ":adres", adres );
    query.bindValue( ":miasto", miasto );
    query.bindValue( ":pesel", pesel );

    query.exec();
}

int main(int argc, char *argv[]){

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gabinet");
    db.setUserName("root");
    db.setPassword("sim2018.");

    bool opened = db.open();

    int n;
    bool condition = true;


    while (condition){

        cout<<"Witam w gabinecie!\n";
        cout<<"Wybierz, co chcesz wykonać:\n\n";
        cout<<"1. Wyswietl pacjentow\n";
        cout<<"2. Dodaj pacjenta\n";
        cout<<"3. Usun pacjenta\n";
        cout<<"4. Koniec\n";

        cin>>n;

        switch(n){
        case 1:
        {
            select_all(opened);
            break;
        }

        case 2:
        {
            string imiet;
            string nazwiskot;
            string adrest;
            string miastot;
            string peselt;

            QString imie;
            QString nazwisko;
            QString adres;
            QString miasto;
            QString pesel;

            cout<<"Podaj nazwisko: "<<endl;
            cin>>nazwiskot;
            nazwisko = QString::fromStdString(nazwiskot);

            cout<<"Podaj imie: "<<endl;
            cin>>imiet;
            imie = QString::fromStdString(imiet);

            cout<<"Podaj pesel: "<<endl;
            cin>>peselt;
            pesel = QString::fromStdString(peselt);

            cout<<"Podaj adres zamieszkania: "<<endl;
            cin>>adrest;
            adres = QString::fromStdString(adrest);

            cout<<"Podaj miasto: "<<endl;
            cin>>miastot;
            miasto = QString::fromStdString(miastot);

            insert_user(nazwisko, imie, pesel, adres, miasto);

            cout<<"Dodano pacjenta"<<endl<<endl;
            break;
        }

        case 3:
        {
           break;
        }

        case 4:
        {
            condition = false;
            cout<<"Do widzenia wkrotce!\n";
            break;
        }
        }

    }

    db.close();

    return 0;
}
