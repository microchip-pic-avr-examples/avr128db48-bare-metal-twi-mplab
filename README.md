<!-- Please do not change this logo with link -->

[![MCHP](images/microchip.png)](https://www.microchip.com)

# Bare Metal TWI Driver for the AVR&reg; DB Family of MCUs

This code example provides a simple bare-metal TWI driver for the AVR&reg; DB family of microcontrollers. TWI (Two-Wire Interface) is a peripheral to enables the microcontroller to easily communicate on an I<sup>2</sup>C bus.

## Related Examples

- [Bare Metal TWI for the ATtiny1627 Family of MCUs](https://github.com/microchip-pic-avr-examples/attiny1627-bare-metal-twi-mplab)
- [Bare Metal I<sup>2</sup>C driver for PIC16F15244](https://github.com/microchip-pic-avr-examples/pic16f15244-bare-metal-i2c-mplab)
- [Advanced I/O Expander using the PIC16F15244](https://github.com/microchip-pic-avr-examples/pic16f15244-family-advanced-i2c-io-expander)

## Software Used

- [MPLAB&reg; X IDE v6.0.0 or newer](#)
- [MPLAB XC8 v2.35.0 or newer](#)

## Hardware Used

- AVR128DB48 Curiosity Nano
- Curiosity Nano Adapter Board

**Important: The Curiosity Nano, MCP2221A, and I/O Expander have been configured for 3.3V operation. 5V Operation is also possible, but all demo parts must be set for 5V operation (e.g.: no mixing voltage levels). Permanent damage may occur if mixed.**

### Host Mode Testing

 - [Advanced I/O Expander Demo Board](https://github.com/microchip-pic-avr-examples/pic16f15244-family-advanced-i2c-io-expander)

### Client Mode Testing

- [MCP2221A USB-I<sup>2</sup>C Bridge](#)

## Pin Usage

| Pin | Function
| --- | -------
| PA2 | SDA
| PA3 | SCL

## Host Mode

Host mode operation allows the microcontroller to control the I<sup>2</sup>C bus and establish communication with client devices, such as sensors and EEPROMs. *This driver only supports polling based communication in Host mode.*

**Important: This driver has not been evaluated for multi-host busses.**

### Overview of the TWI Host API

| Function Name | Description
| ------------  | -----------
| void TWI_initHost(void) | Initializes the TWI Peripheral
| void TWI_initPins(void) | Configures the I/O pins for the TWI peripheral.
| bool TWI_sendByte(uint8_t addr, uint8_t data) | Sends a single byte to a client device at the specified address.
| bool TWI_sendBytes(uint8_t addr, uint8_t* data, uint8_t len) | Sends LEN bytes to a client device at the specified address.
| bool TWI_readByte(uint8_t addr, uint8_t* data) | Reads a single byte from a client device at the specified address.
| bool TWI_readBytes(uint8_t addr, uint8_t* data, uint8_t len) | Reads LEN bytes from a client device at the specified address.
| bool TWI_sendAndReadBytes(uint8_t addr, uint8_t regAddress, uint8_t* data, uint8_t len) | Sends a single byte to a client device at the specified address, then restarts the bus and reads LEN bytes back.

**Note: For all bool functions (ex: TWI_sendByte), returning true indicates the operation was successful, while returning false indicates an error has occurred.**

#### TWI Host - API Description

##### Initialization Functions

```
void TWI_initHost(void)
void TWI_initPins(void)
```

To initialize the peripheral and the I/O, two functions are provided. The first `TWI_initHost()` initializes the peripheral settings for the TWI. The second function `TWI_initPins()` is used to setup the I/O pins for the peripheral. If different I/O pins are used (via PORTMUX or a different TWI instance), then this function will need to modified accordingly.

##### Writing to Clients

```
bool TWI_sendByte(uint8_t addr, uint8_t data)
bool TWI_sendBytes(uint8_t addr, uint8_t* data, uint8_t len)
```

To write data from the host to the client device at ADDR, two functions are provided. Either call `TWI_sendByte(uint8_t addr, uint8_t data)` or `TWI_sendBytes(uint8_t addr, uint8_t* data, uint8_t len)`. Both functions operate similarly, however `TWI_sendByte` is designed to send only a single byte of data, whereas `TWI_sendBytes` is designed to send LEN bytes to the client.

If the client NACKs during addressing or data transmission, these functions return false.

##### Reading from Clients

```
bool TWI_readByte(uint8_t addr, uint8_t* data)
bool TWI_readBytes(uint8_t addr, uint8_t* data, uint8_t len)
```

To get data from the client to the host, two functions are provided. The first `TWI_readByte(uint8_t addr, uint8_t* data)` reads a single byte from the client device at ADDR, whereas the second function `bool TWI_readBytes(uint8_t addr, uint8_t* data, uint8_t len)` will attempt to read LEN bytes from the client.

If the client NACKs during addressing, these functions return false.

##### Write - Restart - Read Operations

```
bool TWI_sendAndReadBytes(uint8_t addr, uint8_t regAddress, uint8_t* data, uint8_t len)
```

To perform a write-restart-read operation in I<sup>2</sup>C, a special function must be called `TWI_sendAndReadBytes(uint8_t addr, uint8_t regAddress, uint8_t* data, uint8_t len)`. This function addresses the client at ADDR in write mode, writes a single byte (regAddress), then restarts the bus. Then, the client is re-addressed in read mode and LEN bytes are read back.

If the client NACKs during addressing or transmission, then this function will return false.

### Advanced I/O Expander API (for Demo)

| Function Name | Description
| ------------  | -----------
| void advancedIO_init(void) | Initializes the Advanced I/O Expander and the TWI peripheral
| void advancedIO_setRegister(ADVANCED_IO_REGISTER reg, uint8_t value) | Sets a register inside of the Advanced I/O Expander to the value specified.
| uint8_t advancedIO_getRegister(ADVANCED_IO_REGISTER reg) | Returns the value inside of the Advanced I/O Expander.
| void advancedIO_toggleBitsInRegister(ADVANCED_IO_REGISTER reg, uint8_t mask) | Inverts the bits defined by the mask in the register specified.
| uint8_t advancedIO_getPinState(void) | Returns the digital levels on the I/O Expander pins.
| void advancedIO_setOutputsHigh(uint8_t mask) | Sets the output value of the pins defined by the mask to be '1'. **Does not set the pin as an output.**
| void advancedIO_setOutputsLow(uint8_t mask) | Sets the output value of the pins defined by the mask to be '0'. **Does not set the pin as an output.**
| void advancedIO_setPinsAsInputs(uint8_t mask) | Sets the pins defined by the mask to be outputs. **Does not set the output level of the pin.**
| void advancedIO_setPinsAsOutputs(uint8_t mask) | Sets the pins defined by the mask to be inputs.
| void advancedIO_resetToDefault(void) | Resets the Advanced I/O Expander to compile time defaults. **The INT line must be monitored to properly use this function. Consult the Advanced I/O Expander API for more information.**
| void advancedIO_performMemoryOP(ADVANCED_IO_MEMORY_OP op) | Performs a memory operation (reset/save/load/save+load) on the Advanced I/O Expander. **The INT line must be monitored to properly use this function. Consult the Advanced I/O Expander API for more information.**

[Advanced I/O Expander README](https://github.com/microchip-pic-avr-examples/pic16f15244-family-advanced-i2c-io-expander)

### TWI Host Demo

The demo program uses the TWI, Real-Time Clock (RTC) and Sleep Controller (SLPCTRL) to blink the LEDs on the I/O Expander at 2 Hz. After initializing the I/O Expander, the microcontroller enters sleep. When the Periodic Interrupt Timer (PIT) in the RTC triggers, the microcontroller wakes up, inverts the states of the LEDs on the I/O Expander and returns to sleep.

## Client Mode


### API Summary


## Operation

<!-- Explain how to operate the example. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->

## Summary

<!-- Summarize what the example has shown -->
