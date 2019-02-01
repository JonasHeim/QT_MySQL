# QT MySQL 

## Example QT application that interfaces a remote MySQL server and adds a new entry

The MySQL server is running in a private network and has the IP 192.168.178.100 assigned and listens on port 3306.


A user named "test" that has (remote) access to the database was created.

A new table named "test_table" with columns:
```
* ***************************************************
* |Id (INT)|Timestamp (DATETIME)|user (vharchar(50))|
* ***************************************************
```

The example application adds a new data set to the database.


