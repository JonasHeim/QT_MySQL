/*
Example application interfacing a remote MySQL Database using QT Framework.
Copyright (C) 2019  Jonas Heim

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QCoreApplication>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>

#define DB_HOSTNAME                     "192.168.178.100"
#define DB_USERNAME                     "test"
#define DB_DATABASE                     "test"
#define DB_PASSWORD                     "test12345MM#"

#define FORMAT_DATETIME                 "yyyy-MM-dd hh:mm:ss"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);     //QTCore App
    bool is_database_open = false;      //Indicator: The database is opened
    QStringList db_list_tables;         //List of all available tables in the chosen database
    QSqlDatabase mysql_db;              //Object to access the remote MySQL database
    QSqlQuery sql_query;                //Object to execute queries against the database
    int column_id;                      //Used to store a value of the first column "id"
    QString column_timestamp;       //Used to store a value of the second column "timestamp" as a string
    QString column_user;                //Used to store a value of the third column "user"
    int query_result_size;              //Number of queried results
    QString query_insertion;     //Used for assembly of insertion query

    /* Begin of MySQL example */

    /* Select database type */
    mysql_db = QSqlDatabase::addDatabase("QMYSQL");

    /* Set connection parameter and credentials */
    mysql_db.setHostName(DB_HOSTNAME);
    mysql_db.setPort(3306);             //default port
    mysql_db.setDatabaseName(DB_DATABASE);
    mysql_db.setUserName(DB_USERNAME);
    mysql_db.setPassword(DB_PASSWORD);

    /* Connect to the remote database */
    is_database_open = mysql_db.open();

    if(true == is_database_open)
    {
        qDebug() << "Database test opened successfully!" << endl;

        /* Get a list of available tables in current database */
        db_list_tables = mysql_db.tables(QSql::Tables);

        if(db_list_tables.size() != 0)
        {
            qDebug() << "Available tables: " << db_list_tables << endl;

            /* try to get the table 'test_table' with columns
             * ***************************************************
             * |Id (INT)|Timestamp (DATETIME)|user (vharchar(50))|
             * ***************************************************
             */

            /* Create Query access */
            sql_query = QSqlQuery(mysql_db);

            /* query to get a first view at the current table datasets */
            qDebug() << "SELECT * FROM test_table;" << endl;
            sql_query.exec("SELECT * FROM test_table;");

            /* did we get any results? */
            query_result_size = sql_query.size();

            if(0 < query_result_size)
            {
                /* Print out the query results */

                /* according to http://doc.qt.io/qt-5/sql-sqlstatements.html
                 * To acces the first result of the result set after calling exec for the query,
                 * call query.next() to move the data pointer to the first result */

                while(sql_query.next())
                {
                    /* get Id (int, primary key of table) */
                    column_id = sql_query.value(0).toInt();

                    /* get Timestamp (datetime, YYYY-MM-DD HH:MM:SS ) */
                    column_timestamp = sql_query.value(1).toString();

                    QDateTime::fromString(column_timestamp, FORMAT_DATETIME);

                    /* get User (varchar(50))*/
                    column_user = sql_query.value(2).toString();

                    /* dump one entry */
                    qDebug() << "|\t" << column_id << "\t|\t" << column_timestamp << "\t|\t" << column_user << "\t|" << endl;
                }
            }

            /* Add an entry to the table */
            qDebug() << "Adding new entry" << endl;

            /* first column: "id" is auto-incremented on the server side */

            /* second column: generate current "timestamp" */
            column_timestamp = QDateTime::currentDateTime().toString(FORMAT_DATETIME);

            /* third column: get username */
            column_user = qgetenv("USER");sql_query.exec("SELECT * FROM test_table");sql_query.exec("SELECT * FROM test_table");

            qDebug() << "|\t" << "++\t|\t" << column_timestamp << "\t|\t" << column_user << "\t|" << endl;

            /* assemble execute insert query */
            query_insertion = "INSERT INTO test_table(timestamp, user) values(\"";
            query_insertion.append(column_timestamp);
            query_insertion.append("\", \"");
            query_insertion.append(column_user);
            query_insertion.append("\");");

            qDebug() << query_insertion << endl;

            /* finally insert data to table */
            sql_query.exec(query_insertion);

        }

        /* Finally close the database */
        mysql_db.close();
    }
    else {
        printf("Could not open database!\r\n");
    }

    return a.exec();
}


