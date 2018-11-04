import sqlite3
import datetime
import matplotlib.pyplot as plt
from sqlite3 import Error

def createTable(db_file, tableName, conn):
    try:
     #   conn = sqlite3.connect(db_file)
        c = conn.cursor()
        values = (tableName)
        c.execute('CREATE TABLE IF NOT EXISTS plantplants(time TEXT PRIMARY KEY, temperature REAL, light INTEGER, soil INTEGER);')
    except Error as e:
        print(e)
    #finally:
     #   conn.close()

def makeGraph(db_file, dependentVariable, conn):
    try:
     #   conn = sqlite3.connect(db_file)
        c = conn.cursor()
        values = [dependentVariable]
        c.execute('SELECT * FROM plantplants;')
        result = c.fetchall()
        print('length' + str(len(result)))
        for row in result:
            print(row)
    except Error as e:
        print(e)
    #finally:
     #   conn.close()

def getListValues(dependentVariable, conn):
    try:
     #   conn = sqlite3.connect(db_file)
        c = conn.cursor()
        values = [dependentVariable]
        c.execute('SELECT ' + dependentVariable + ' FROM plantplants;')
        result = c.fetchall()
        print('length' + str(len(result)))
        return result
    except Error as e:
        print(e)


conn = sqlite3.connect('plant.db')
for count, data in enumerate(['soil', 'temperature', 'light']):
    result = getListValues(data, conn)
    print(result)
    count_set = []
    for c, i in enumerate(result):
        count_set.append(c)

    plt.subplot(3, 1, count + 1)
    plt.title(data)
    plt.xlabel("index")
    plt.ylabel(data)
    if data == 'temperature':
        plt.ylabel("temperature (C)")

    plt.plot(count_set, result)

plt.tight_layout()
plt.show()
plt.close()