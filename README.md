# 🧥 STM32 Dry Cleaner Conveyor Retrofit

## Overview
This project retrofits an existing dry cleaner’s **clothes conveyor system** to improve efficiency and automation using an **STM32F411RE Nucleo** board.  
Instead of manually driving the conveyor with an SPDT switch, the system automatically computes the **shortest direction** to reach a selected hanger position and drives the conveyor accordingly.

The project integrates:
- **SunFounder 2-Channel 5 V Relay Module** (to replace the mechanical SPDT switch)
- **Adafruit 3×4 Keypad** (for user input)
- **2004A LCD (20×4)** (for display)
- **STM32F411RE (Bare-Metal)** microcontroller

---

## ⚙️ System Goals
- Automate hanger retrieval by selecting the shortest path (forward/reverse).
- Provide user interface for selecting hanger number.
- Replace the SPDT switch with software-controlled relays.
- Maintain safety and reliability equivalent to manual operation.

---

## 🧩 Hardware Architecture

### Core Components
| Component | Purpose | Notes |
|------------|----------|-------|
| **Nucleo STM32F411RE** | Main controller | Running bare-metal firmware |
| **SunFounder 2-Channel Relay (5 V)** | Drives conveyor forward/reverse | Controlled via transistor driver |
| **2004A LCD** | Displays hanger number and system status | Uses 4-bit parallel or I2C adapter |
| **3×4 Keypad** | User input for selecting hanger number | Polled in firmware |
| **5 V PSU** | Relay power and LCD backlight | Common ground with STM32 |

---

## 🔌 Electrical Interface

### Relay Control
The SunFounder relay board requires **5 V logic**, but STM32 GPIOs are **3.3 V**.  
Direct driving is unsafe, so transistor or driver ICs are used.

#### Recommended Interface (ULN2003A or Discrete NPN)
- **STM32 GPIO** → 4.7 kΩ resistor → **NPN base**
- **Emitter** → GND
- **Collector** → Relay INx
- **Relay VCC** → 5 V
- **Relay GND** → Common with MCU
- **Logic:**  
  - GPIO HIGH → Relay ON (active low input)  
  - GPIO LOW → Relay OFF

Each relay corresponds to:

| Relay | Direction | GPIO |
|--------|------------|------|
| IN1 | Forward | PA0 |
| IN2 | Reverse | PA1 |

> ⚠️ Add hardware **interlock** logic or firmware protection to ensure both relays can never be active simultaneously.

---

## 🔢 Control Logic

1. **User Input:**  
TBD