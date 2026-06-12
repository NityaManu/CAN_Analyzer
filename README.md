# QNX-Based Automotive CAN Bus Analyzer

A multi-process Automotive CAN Bus Analyzer Simulator developed on QNX Neutrino RTOS using native message-passing IPC, timer-driven ECU simulation, CAN frame decoding, traffic monitoring, statistics collection, and fault detection.

## Project Overview

This project simulates an automotive CAN network consisting of multiple Electronic Control Units (ECUs) communicating with a central CAN Bus Analyzer. The system demonstrates real-time inter-process communication using QNX Neutrino's native message-passing architecture.

The analyzer receives CAN frames from multiple ECUs, decodes message payloads, monitors network traffic, maintains statistics, and detects protocol faults.

## Features

1. Multi-process architecture using QNX Neutrino RTOS
2. Native message-passing IPC
  - ChannelCreate()
  - ConnectAttach()
  - MsgSend()
  - MsgReceive()
  - MsgReply()
3. Timer-driven ECU simulation using:
  - POSIX Timers
  - SIGEV_PULSE
  - QNX Pulses
4. Engine ECU simulation (RPM data)
5. Speed ECU simulation (Vehicle Speed data)
6. Brake ECU simulation (Brake Status data)
7. CAN frame creation and decoding
8. Timestamped CAN traffic monitoring
9. Real-time CAN traffic statistics
10. Fault injection and detection:
  - Invalid CAN ID detection
  - Invalid DLC detection
  - Abnormal RPM detection
  - Abnormal Speed detection

## System Architecture

```
Engine ECU
     \
      \
       ---> CAN Bus Analyzer
      /
     /
Speed ECU

Brake ECU
```

Each ECU generates CAN frames periodically and transmits them to the CAN Bus Analyzer using QNX message-passing IPC.

## Technologies Used

1. C Programming
2. QNX Neutrino RTOS
3. QNX Native IPC
4. POSIX Timers
5. QNX Pulses
6. VMware Workstation
7. QNX Momentics IDE

## Learning Outcomes

Through this project, I gained hands-on experience with:

1. Real-time operating system concepts
2. Inter-process communication
3. Event-driven software design
4. Timer-based task scheduling
5. Automotive CAN message handling
6. Fault monitoring and diagnostics
