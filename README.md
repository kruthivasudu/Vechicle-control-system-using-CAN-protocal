# Vehicle control system using CAN Protocol

## 📌 Project Objective

The main aim of this project is to:

* Display engine temperature
* Generate alert messages when temperature exceeds limits
* Provide reverse obstacle alerts
* Control vehicle indicators
  using the **CAN (Controller Area Network) protocol**

---

## 🧩 System Overview

The system consists of **three nodes** that communicate with each other via CAN:

1. **Main Node**
2. **Indicator Node**
3. **Reverse Alert Node**

Each node performs a specific task and exchanges data over the CAN bus.

---

## 🔗 Node Architecture

### 🔹 1. Main Node

**Responsibilities:**

* Continuously read engine temperature
* Display temperature on LCD
* Set a predefined temperature threshold
* Compare real-time temperature with the threshold

**Actions:**

* If temperature exceeds limit:

  * Turn ON LED(s) as an alert
* Handle interrupt signals
* Send indicator control signals to Indicator Node via CAN
* Receive reverse alert data from Reverse Node
* Control LED/Buzzer based on reverse alert status

---

### 🔹 2. Indicator Node

**Responsibilities:**

* Continuously listen for CAN messages from Main Node

**Actions:**

* On receiving data:

  * Control indicator LEDs connected to the microcontroller
  * Perform actions based on received signal (e.g., turn ON/OFF indicators)

---

### 🔹 3. Reverse Alert Node

**Responsibilities:**

* Continuously read distance using **GP2D12 sensor**
* Use on-chip ADC for sensor data acquisition

**Actions:**

* Set a threshold distance value
* If object is **closer than limit**:

  * Send logic `1` to Main Node via CAN
* If object is **farther than limit**:

  * Send logic `0` to Main Node via CAN

---

## 🔄 Communication Flow

```text
[Reverse Node] ---> (CAN) ---> [Main Node] ---> (CAN) ---> [Indicator Node]
                         |
                         v
                   LCD Display + LED/Buzzer
```

---

## ⚙️ Key Features

* Real-time engine temperature monitoring
* Over-temperature alert system
* Reverse obstacle detection
* Distributed communication using CAN protocol
* Interrupt-based signal handling
* Modular node-based architecture

---

## 🛠️ Technologies Used

* Embedded C
* Microcontrollers (e.g., ARM / PIC / AVR / STM32)
* CAN Protocol
* ADC (Analog to Digital Converter)
* GP2D12 Distance Sensor
* LCD Display
* LEDs & Buzzer

---

## 📊 Advantages

* Reliable communication using CAN
* Scalable multi-node architecture
* Real-time monitoring and alerts
* Efficient fault detection system

