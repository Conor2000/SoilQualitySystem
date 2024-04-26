import http.client
import urllib
import time
import serial
import json

#Assign serial communication to serial variable
serial = serial.Serial('/dev/ttyACM0', 9600, 8, 'N', 1, timeout=5)

# Firebase URL and Auth Key
FIREBASE_URL = "soil-data-6f4b6-default-rtdb.firebaseio.com" 
FIREBASE_AUTH_KEY = "21RV2AkZdsWV1x7Mjfi3hYGexHdRT6RYaqLVDO8M"

#The main function that runs the rest of the program
def startMainProgram():
    readSensors()
    uploadToFirebase()

#Read the Arduino serial console for the sensor results and use
#these results to determine the soil quality
def readSensors():
    for countdown in range(90,0,-1):
        print("Reading Sensors...")
    try:
        readings = serial.readline(20).decode('utf-8').rstrip().split(',')
        readings = [float(i) for i in readings]
        
        global moisture, pH, nitrogen, phosphorus, potassium
        
        moisture = int(readings[0])
        pH = readings[1]
        nitrogen = float(readings[2])
        phosphorus = float(readings[3])
        potassium = float(readings[4])
        print(readings)
        
    except:
        print("Error with reading sensors")

# Function to upload sensor data to Firebase
def uploadToFirebase():
    timestamp = int(time.time())
    data = {
        "moistureLevel": moisture,
        "pHValue": pH,
        "nitrogenValue": nitrogen,
        "phosphorusValue": phosphorus,
        "potassiumValue": potassium,
        "timestamp": timestamp
    }
    
    conn = http.client.HTTPSConnection(FIREBASE_URL)
    # Adjusted URL to include the Database Secret as a query parameter for authentication
    conn.request("PUT", f"/sensor_readings/{timestamp}.json?auth={FIREBASE_AUTH_KEY}", json.dumps(data))
    response = conn.getresponse()
    print(response.read().decode())


        
startMainProgram()
