%load_ext autoreload
%autoreload 2
import serial, time, io, datetime
from serial import Serial
# import sys
import time
import pdb
import csv
from IPython.core.debugger import set_trace
import gspread
from oauth2client.service_account import ServiceAccountCredentials
import time

# Function to segregate data
def sensor_group(datastring):
    if datastring[0] == 'A':
        Humidity.append(datastring[1:len(datastring)][:-2])
    else:
        if datastring[0] == 'B':
            DHT_Temp.append(datastring[1:len(datastring)][:-2])
        else:
            if datastring[0] == 'C':
                Soil.append(datastring[1:len(datastring)][:-2])     
            else:
                if datastring[0] == 'D':
                    Thermo.append(datastring[1:len(datastring)][:-2])
    return Humidity, DHT_Temp, Soil, Thermo

# Google Sheet API
scope = ['https://spreadsheets.google.com/feeds','https://www.googleapis.com/auth/drive']
credentials = ServiceAccountCredentials.from_json_keyfile_name('Trail-a7cf89fbdcf3.json', scope)
# Import credentials
client = gspread.authorize(credentials)
# Open sheet
sheet = client.open("IOT").worksheets()
#----------------------------------------------------------
# Start Serial Communication
ser = serial.Serial('COM4', 9600)
sio = io.TextIOWrapper(
   io.BufferedRWPair(ser, ser, 1), 
   encoding= 'ascii', newline='\r')
Humidity=[]
DHT_Temp=[]
Soil=[]
Thermo=[]

while ser.isOpen():
#     try:
        datastring = ser.readline().decode()
        # Call function
        Humidity, DHT_Temp, Soil, Thermo = sensor_group(datastring) 
        for i in sheet:
            curr_time = time.localtime()
            time_str = time.strftime("%m/%d/%Y %H:%M:%S",curr_time)
            # Clean empty array
            if DHT_Temp == []:
                DHT_Temp.append('0')
            if Soil == []:
                Soil.append('0')
            if Thermo == []:
                Thermo.append('0')
            # Send data 
            i.append_row([time_str, Humidity[len(Humidity)-1], DHT_Temp[len(DHT_Temp)-1], Soil[len(Soil)-1], Thermo[len(Thermo)-1]])
#     except:
#         print("Something is wrong")
#         break        