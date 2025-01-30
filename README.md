# Car-Black-Box
 
## 📌 Project Overview  
The **Car Black Box** is an event data recorder (EDR) designed to capture critical driving events.  
It logs information such as speed, engine temperature, fuel consumption, and trip distance.  
The system enhances vehicle monitoring, promotes safe driving, and can be extended into an IoT-based solution.  

## 🚀 Features  
- **Event Logging** – Records gear shifts, speed, fuel usage, and trip distance.  
- **Secure Access** – Password-protected data access for transport managers.  
- **Real-Time Monitoring** – Captures events even while logs are being viewed.  
- **Dashboard Display** – Shows current time, speed, and latest events.  
- **Cloud Extension** – Potential for IoT-based centralized monitoring.  

## 🖼️ Project Images  

### 📌 Main Interface  
This is the primary screen users interact with.  
![Image](https://github.com/user-attachments/assets/715ada83-cd86-475d-9a25-52dfec99eaef)

### 📌 Additional Main Screens  
Different screens showing options and data.  
![Image](https://github.com/user-attachments/assets/bd2c2c4d-e038-4aae-9f4b-a0b1f9b53a12)
![Image](https://github.com/user-attachments/assets/d6d5dadb-6445-4679-9531-626c0f694153) 

### 📌 Dashboard View  
Displays the real-time driving statistics and logs.  
![Image](https://github.com/user-attachments/assets/62ebf5c3-a204-4122-a51b-db6c2b10e86d) 

### 📌 Log Management  
- **Viewing Logs** – Users can check previously recorded data.  
  ![Image](https://github.com/user-attachments/assets/63999f91-062d-410d-85fd-6fb6c34e0b5c) 
- **Clearing Logs** – Old data can be removed to free up space.  
  ![Image](https://github.com/user-attachments/assets/2594e5ae-5db1-489e-9d34-c5a4019a5c7b)  

### 📌 Setting the System Time  
Allows users to manually configure or sync the system time.  
![Image](https://github.com/user-attachments/assets/ecc63df7-aa61-40b8-87ef-713928da11b3) 

## 📂 Files Included  

### 📜 Source Code Files  
- `adc.c`, `adc.h` – Handles Analog-to-Digital Conversion (ADC).  
- `black_box.h` – Core definitions for the system.  
- `clcd.c`, `clcd.h` – Controls the character LCD display.  
- `clear_log.c` – Handles log clearing operations.  
- `digital_keypad.c`, `digital_keypad.h` – Manages the digital keypad.  
- `display_main_menu.c` – Displays the main menu options.  
- `download_log.c` – Allows logs to be downloaded for analysis.  
- `DS1307.c`, `DS1307.h` – Manages real-time clock (RTC) operations.  
- `eeprom.c`, `eeprom.h` – Handles internal EEPROM storage.  
- `External_EEPROM.c`, `External_EEPROM.h` – Manages external EEPROM storage.  
- `external_eeprom_store.c` – Handles external EEPROM data logging.  
- `I2C.c`, `I2C.h` – Manages I2C communication with peripherals.  
- `main.c` – The main program execution file.  
- `matrix_keypad.c`, `matrix_keypad.h` – Handles matrix keypad input.  
- `set_time.c` – Allows setting system time.  
- `UART.c`, `UART.h` – Manages UART communication.  
- `view_dashboard.c` – Displays real-time dashboard information.  
- `view_log.c` – Enables viewing of stored logs.  

## 🛠️ Requirements  

### 🏎️ Hardware  
- **Microcontroller**: PIC18F4580  
- **Storage**: EEPROM (AT24C02)  
- **Communication**: CAN Transceiver (MCP2551)  
- **Time Management**: RTC (DS1307)  
- **Display**: CLCD screen  
- **User Input**: Tactile buttons  

### 💻 Software  
- **Programming Language**: Embedded C  
- **Protocols Used**: I2C, CAN  

