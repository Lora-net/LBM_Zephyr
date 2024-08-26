# HW MODEM

This example shows an implementation of a all integrated modem that can be addressed using UART RX/TX and 3 gpios for commands handling (command and busy) and events notification (event)
All functions included in lora basics modem api can be called using commands.

## Board support

The sample is tested on the `nrf52840dk/nrf52840` board and a DTS overlay is provided for this board.
If any other board is used, a new DTS overlay should be created for it.

### UART configuration

As configured, uart0 is used as the debug console (routed to the USB cable), and uart1 is used for the modem communication.
The uart1 pins are configured in the `uart1_default_alt` and `uart1_sleep_alt` groups in the overlay.
They are set so that they are routed through the LR112x shield to free pins that are not used by the shield.

### Other Pins

Other pins as configured in `src/modem_pinout.h`. They are set so that they are routed through the LR112x shield to free pins that are not used by the shield.

### Sending commands

Send commands to the device by connecting the configured command pin (in [modem_pinout.h](src/modem_pinout.h) - HW_MODEM_COMMAND_PIN) to the transmission line of your UART Serial Port Module (example CP2102).

>[!NOTE]
>A list of all available commands can be found here: [cmd_parser.c](src/hw_modem/cmd_parser.c)

Commands should be passed to the modem following the format:

```shell
<command id> <command size> <command data (optional)> <crc>
```

Command example:

```text
<0x5d> <0x00> <0x5d>
```

Example using python serial to send commands:

```python
python3
import serial
ser = serial.Serial('/dev/ttyUSB0',115200,timeout = 0.5)
ser.write("\x5d".encode()); ser.write("\x00".encode()); ser.write("\x5d".encode())
```
