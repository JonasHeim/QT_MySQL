# QT MySQL 

## Example QT application that interfaces a remote MySQL server and adds a new entry

The MySQL server is running in a private network and has the IP 192.168.178.100 assigned and listens on port 3306.

A database "test" was created.

```
CREATE DATABASE test;
USE test;
```

A user "test" was created, that has (remote) privileged access to all databases.
```
CREATE USER 'test'@'%' IDENTIFIED BY 'test12345MM#';
GRANT ALL PRIVILEGES ON *.* TO 'test'@'%';
FLUSH PRIVILEGES;
```

A new table "test_table" was created, defined by the columns below:
```
* ***************************************************
* |Id (INT)|Timestamp (DATETIME)|user (vharchar(50))|
* ***************************************************

CREATE TABLE test_table(id integer PRIMARY KEY AUTO_INCREMENT, timestamp datetime, user varchar(50));
```


The example application adds a new data set to the database.


