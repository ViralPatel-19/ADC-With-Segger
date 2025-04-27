
# ADC-With-Segger

## Overview
**ADC-With-Segger** is a simple embedded C project demonstrating how to interface an external ADC (Analog to Digital Converter) — specifically the **ADS8860** — with a microcontroller, while using **SEGGER RTT (Real-Time Transfer)** for efficient real-time debugging and logging.

The project focuses on reading analog values using SPI communication and displaying or analyzing them using SEGGER's lightweight and powerful RTT tool.

---

## Features
- **External ADC Interfacing:** ADS8860, a 16-bit SAR ADC with SPI interface.
- **Real-Time Debugging:** Integrated SEGGER RTT for non-intrusive debugging.
- **Efficient SPI Communication:** Simple SPI routines for quick ADC data reads.
- **Lightweight Codebase:** Minimalistic design ideal for learning and expanding.
- **Cross-Platform Ready:** Can be ported to any MCU supporting C and SPI.

---

## Project Structure

| File/Folder            | Description                                     |
|-------------------------|-------------------------------------------------|
| `ads8860.c`             | Functions to initialize and read data from ADS8860. |
| `ads8860.h`             | Header file containing prototypes and macros for ADS8860. |
| `main.c`                | Main application entry point. Calls ADC read and logs over RTT. |
| `SEGGER_RTT.c/.h`       | SEGGER RTT core files for real-time communication. |
| `SEGGER_RTT_Conf.h`     | Configuration for RTT buffer size and behavior. |
| `SEGGER_RTT_Syscalls_GCC.c` | System call implementation to support `printf` redirection. |
| `SEGGER_RTT_printf.c`   | Enhanced `printf` functionality for RTT. |

---

## Requirements

- **Microcontroller:** Any MCU with SPI peripheral and SEGGER J-Link debugger support.
- **Debugger:** SEGGER J-Link or compatible.
- **Software:**
  - SEGGER J-Link Software & Driver Package
  - Embedded development IDE (e.g., STM32CubeIDE, Keil, IAR, etc.)
  - J-Link RTT Viewer or Terminal for real-time data visualization.

---

## How It Works

1. **SPI Initialization:**  
   The MCU sets up SPI communication to connect with the ADS8860 ADC.

2. **ADC Data Acquisition:**  
   Using simple read functions, raw ADC data is continuously captured.

3. **Real-Time Output with SEGGER RTT:**  
   Captured data is logged through SEGGER RTT to the host computer, allowing real-time monitoring without halting the CPU.

4. **Application Flow:**  
   - Initialize peripherals.
   - Continuously read ADC values.
   - Output values using `SEGGER_RTT_printf`.

---

## Getting Started

1. **Clone the repository:**
   ```bash
   git clone https://github.com/ViralPatel-19/ADC-With-Segger.git
   ```

2. **Import into your IDE** and configure:
   - Set up your project settings according to your MCU.
   - Ensure the SPI peripheral and clocks are configured.
   - Make sure SEGGER RTT files are included in the build.

3. **Connect J-Link Debugger** to your target MCU.

4. **Build and Flash the Program** onto the target device.

5. **Open SEGGER RTT Viewer** or J-Link Terminal to monitor the ADC readings in real time.

---



## Credits
- **Developed by:** Viral Patel
- **Libraries Used:** SEGGER RTT for real-time data logging.

---
