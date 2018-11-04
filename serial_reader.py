import serial
import sqlite3
import datetime
from sqlite3 import Error

def addToDatabase(db_file, tableName, time, temp, light, soil, conn):
    try:
    #   conn = sqlite3.connect(db_file)
        c=conn.cursor()
        values = [time, temp, light, soil]
        print(values)
        c.execute('''INSERT INTO plantplants VALUES(?,?,?,?);''', values)
        print('insert')
    except Error as e:
        print(e)
    # finally:
        #conn.close()

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




conn = sqlite3.connect('plant.db')

light_set = []
soil_set = []
temp_set = []

moment_set = []

makeGraph('plant.db', 'soil', conn)

createTable("plant.db", "plantplants", conn)


#Prompt for number of runs:
loops = int(input('Enter the number of data tests to run:\n'))
print(loops)

reader = serial.Serial('COM3')
if not reader.in_waiting:
    print()
    try:
        #Convert input to byte stream
        #Soil threshold
        reader.write(input('Enter the soil moisture threshold - an alert is made if moisture is below this value: ').encode())
        #Frequency
        reader.write(input('Enter the interval between serial outputs in seconds: ').encode())
    except Error as e:
        print(e)

counter = 0
print("To the loop!")
while counter < loops:
    try:
        #Read from serial output
        code = str(reader.readline())
        #Remove byte prefix, and control characters
        code = code[2:-5]
        print(code)
        if 'Soil' in code:
            value = int(code[5:])
            soil_set.append(value)
            moment_set.append(value)
        elif 'Light' in code:
            value = int(code[7:])
            light_set.append(value)
            moment_set.append(value)
        elif 'Temperature' in code:
            value = float(code[13:])
            temp_set.append(value)
            moment_set.append(value)
            #print(moment_set)
            addToDatabase('plant.db', 'plantplants', str(datetime.datetime.now()) , moment_set[2], moment_set[1], moment_set[0], conn)
            moment_set = []
            #Temperature is the last value per set, so increment counter when temperature is obtained
            counter += 1
        else:
            value = ""
        print(value)
    except Error as e:
        print(e)

#Save to database
conn.commit()
conn.close()


