import serial

reader = serial.Serial('COM3')

light_set = []
soil_set = []
temp_set = []



while True:
    code = reader.readline()
    print(code)
    code = code[2:]
