import pandas as pd
import matplotlib.pyplot as plt
import re
import requests
from io import StringIO

# Function to parse the time correctly
def parse_time(t):
    parts = t.split(':')
    if len(parts[0]) == 1:  # Handle times like "8:44:10"
        parts[0] = '0' + parts[0]
    return ':'.join(parts)

# Function to extract float values from the string
def extract_float(s):
    match = re.search(r'\d+\.?\d*', s)
    if match:
        return float(match.group())
    return None

# Initialize an empty list to store data from multiple files
all_data = []

# Loop through files 8 to 22
for i in range(8, 23):
    github_url = f'https://raw.githubusercontent.com/VenomusGraphics/GeigerCounterArd/main/LOGS/LOGS{i:03d}.TXT'
    response = requests.get(github_url)

    if response.status_code == 200:
        data_content = response.text
        
        # Read the data into a list of dictionaries
        data = []
        for line in StringIO(data_content):
            line = line.strip()
            if line:
                time, cpm, nsvh, usvh, pressure = line.split(',')
                time = parse_time(time)
                cpm = extract_float(cpm)
                nsvh = extract_float(nsvh)
                usvh = extract_float(usvh)
                pressure = extract_float(pressure)
                data.append({'Time': time, 'CPM': cpm, 'nSv/h': nsvh, 'uSv/h': usvh, 'Pressure': pressure})
        
        # Append the data from this file to the list
        all_data.extend(data)
    else:
        print(f"Failed to fetch data from {github_url}. Status code: {response.status_code}")

# Convert the list of dictionaries to a DataFrame
df = pd.DataFrame(all_data)

# Convert the 'Time' column to datetime
df['Time'] = pd.to_datetime(df['Time'], format='%H:%M:%S')

# Plotting the data
plt.figure(figsize=(12, 10))

# Plot CPM
plt.subplot(4, 1, 1)
plt.plot(df['Time'], df['CPM'], label='CPM', color='b')
plt.xlabel('Time')
plt.ylabel('CPM')
plt.legend(loc='upper left')

# Plot nSv/h
plt.subplot(4, 1, 2)
plt.plot(df['Time'], df['nSv/h'], label='nSv/h', color='g')
plt.xlabel('Time')
plt.ylabel('nSv/h')
plt.legend(loc='upper left')

# Plot uSv/h
plt.subplot(4, 1, 3)
plt.plot(df['Time'], df['uSv/h'], label='uSv/h', color='r')
plt.xlabel('Time')
plt.ylabel('uSv/h')
plt.legend(loc='upper left')

# Plot Pressure
plt.subplot(4, 1, 4)
plt.plot(df['Time'], df['Pressure'], label='Pressure', color='purple')
plt.xlabel('Time')
plt.ylabel('Pressure')
plt.legend(loc='upper left')

# Adjust layout to prevent overlap
plt.tight_layout()

# Show the plot
plt.suptitle('Data Visualization', y=1.02)
plt.show()
