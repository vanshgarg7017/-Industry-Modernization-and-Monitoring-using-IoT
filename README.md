# Industry Modernization and Monitoring using IoT

## Overview
This project aims to modernize industry operations by implementing IoT (Internet of Things) technology for monitoring various parameters within chemical tanks. By utilizing sensors and IoT devices, this system ensures real-time monitoring of chemical levels, temperature, gas leakage, and unauthorized movements near the chemical tank.

## Sensors Used
1. **Ultrasonic Sensor**
   - Measures the depth of chemical present in the chemical tank.
   - Data displayed in real-time on the Blynk app.

2. **DS18B20 Temperature Sensor**
   - Measures the temperature of the chemical present in the chemical tank.
   - Data displayed in real-time on the Blynk app.

3. **MQ-2 Gas Sensor**
   - Detects fire, smoke, and gas leakage outside the chemical tank.
   - Buzzer sounds if gas is detected.

4. **PIR Motion Sensor**
   - Detects any unauthorized movement near the chemical tank.
   - Email notification sent if movement is detected.

## Functionality
- **Ultrasonic Sensor & DS18B20 Temperature Sensor:**
  - Data collected from these sensors is displayed in real-time on the Blynk app.
  - Additionally, data is stored in CSV and Excel format on ThingSpeak for further analysis.

- **MQ-2 Gas Sensor:**
  - Buzzer sounds if fire, smoke, or gas leakage is detected, ensuring immediate attention.

- **PIR Motion Sensor:**
  - Email notification is sent if any unauthorized movement is detected near the chemical tank, enhancing security measures.

## Usage
1. **Hardware Setup:**
   - Connect the sensors (ultrasonic, temperature, gas, motion) to the microcontroller (Arduino, Raspberry Pi, etc.) as per the provided schematics.

2. **Software Setup:**
   - Install necessary libraries and dependencies for sensor communication and data visualization (e.g., Blynk app).

3. **Configuration:**
   - Configure Blynk app to visualize data from ultrasonic sensor and temperature sensor.
   - Set up email notifications for PIR motion sensor alerts.

4. **Data Storage:**
   - Ensure ThingSpeak API integration for storing data from ultrasonic and temperature sensors in CSV and Excel formats.

## Dependencies
- Arduino IDE

## License
-This project is licensed under the MIT License.

## Acknowledgments
We extend our heartfelt gratitude to the following individuals for their invaluable contributions to this project:

- **Mentor and Supervisor:**
  - Dr. Sonal Rattan

- **Team Members:**
  - Ashish 
  - Vansh
  - Kanishka
  - Komal



Thank you all for your guidance, support, and dedication throughout the development of this project.
