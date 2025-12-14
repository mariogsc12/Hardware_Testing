import requests
import time
import pandas as pd
import matplotlib.pyplot as plt
import os
from pathlib import Path

# --- Configuration parameters ---
WIFI_IP = "http://192.168.1.39/data"
OUTPUT_NAME = "data"
OUTPUT_PATH = Path("C:/Users/mario/Desktop/Mario/Repositorios/ROBOT_AUTOBALANCEADO/Tools/Results") 
TEST_NAME = "Test_1"

# Data
DATA_LENGTH = 11
names = ["time", "input_yaw", "input_throttle", "input_switch", "control_action_left", "control_action_right", "speed_left", "speed_right", "voltage", "imu_pitch", "imu_yaw"]
data = []

# Plot 

# Main loop
try:
    while True:
        answer = requests.get(WIFI_IP)
        if answer.status_code == 200:
            message = answer.text.strip()  
            received_values = message.split(",")
            print(received_values)
            
            float_values = [float(val) for val in received_values]
            data.append({f"{names[i]}":float_values[i] for i in range(0,DATA_LENGTH)})
except KeyboardInterrupt:
    print("\nStopping to save data")

df = pd.DataFrame(columns=names)
df = pd.DataFrame(data)

test_folder = OUTPUT_PATH / TEST_NAME
test_folder.mkdir(parents=True, exist_ok=True)

# Plotting
for col in names[1:]:  
    plt.figure(figsize=(14, 8))
    plt.plot(df["time"], df[col], label=col)

    plt.xlabel("Time (ms)")
    plt.ylabel("Values")
    plt.title("Sensor Data vs Time")
    plt.legend()
    plt.grid(True)
    # plt.show()
    output_path = f"{OUTPUT_PATH}/{TEST_NAME}/{col}.png"
    plt.savefig(output_path)
    plt.close()
