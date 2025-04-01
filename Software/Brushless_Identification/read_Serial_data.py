import serial
import serial.tools.list_ports
import sys
import os
import scipy.io
import signal

def checkSerialPort(selected_port):
    """ Checks if the selected serial port is available.\n
    If not, kill the program """
    portList = []
    availablePorts = serial.tools.list_ports.comports()
    
    for port in availablePorts:
        portList.append(str(port))
        print(str(port))

    for port in portList:
        if selected_port in port:
            print(f"Selected port: {selected_port}")
            return selected_port
        
    sys.exit(f"Error - The selected port is not available") 

def splitMessage(message):
    """ Split the message in 3 values """
    message = message.strip()
    data = message.split(',') 

    if len(data) == 3:
        try:
            value1 = int(data[0])   # time  
            value2 = float(data[1]) # control_action  
            value3 = float(data[2]) # speed
            return value1, value2, value3
        except ValueError:
            sys.exit(f"Error - Unable to convert message to numbers")
    else:
        sys.exit(f"Error - The received message does not match the expected one") 

def saveData(name):
    """ Save the data to a .mat file when the program is interrupted """
    data = {
        'time': time_data,
        'control_action': control_action_data,
        'speed': speed_data
    }
    
    file_name = f"{name}.mat"
    mat_file_path = os.path.join(output_path, file_name)
    
    scipy.io.savemat(mat_file_path, data)
    print(f"Data saved to: {mat_file_path}")
    
    sys.exit(0)  

# Signal handler to call saveData when the program is interrupted
signal.signal(signal.SIGINT, lambda signal, frame: saveData(output_file_name))


# ---- ToBeModified by the user ----
# Serial Configuration 
port = "COM4"
baudrate = 115200
# Path Configuration
output_folder_name = "serialData"
output_file_name = "serialData_8"
# Time to store [seconds]
start_time = 0
end_time = 40
# ----  ----

# Get the directory where the script is located
script_directory = os.path.dirname(os.path.abspath(__file__))

# Construct the output path
output_path = os.path.join(script_directory, output_folder_name)
print(f"Output path: {output_path}")

# Ensure the path exists, create the folder if it doesn't exist
if not os.path.exists(output_path):
    os.makedirs(output_path)
    print(f"Created the directory: {output_path}")
else:
    print(f"The directory already exists: {output_path}")

# Define the file path to save the data
mat_file_path = os.path.join(output_path, f"{output_file_name}.mat")

# Check that the selected port is available
port = checkSerialPort(port)

# Create the serial object with the selected configuration
serial_device = serial.Serial()
serial_device.port = port
serial_device.baudrate = baudrate
serial_device.open()

# Variables to store the data
control_action_data = []  
speed_data = []  
time_data = []  

# Start the loop to read the message
while True:
    if serial_device.in_waiting:
        received_message = serial_device.readline().decode('utf-8')  # Decoding the received bytes
        time, control_action, speed = splitMessage(received_message)

        print(f"time: {time} control_action: {control_action}, speed: {speed}")
        
        if time / 1000 >= start_time:
            if time / 1000 == start_time:
                print("Starting to store data...")

            time_data.append(time / 1000)
            control_action_data.append(control_action)
            speed_data.append(speed)
            
            data = {
                'time': time_data,
                'control_action': control_action_data,
                'speed': speed_data
            }
            
            scipy.io.savemat(mat_file_path, data)
            
            if time / 1000 == end_time:
                print("Data storage complete...")
                saveData(output_file_name)
            elif time / 1000 > end_time:
                print("Data storage is overloaded...")
                saveData(output_file_name)