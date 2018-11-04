import serial

reader = serial.Serial('COM3')

light_set = []
soil_set = []
temp_set = []


#Convert input to byte stream
#Soil threshold
reader.write(input().encode())
#Frequency
reader.write(input().encode())

while True:
    code = str(reader.readline())
    if 'Soil' in code:
        value = int(code[5:])
        print(value)
    elif 'Light' in code:
        value = int(code[7:])
    elif 'Temperature' in code:
        value = int(code[12:])
    else:
        value = ""
    print(value)