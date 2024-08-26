# LoRa Basics Modem on Zephyr

This repository aims to make LoRa Basics Modem available in Zephyr. It wraps the existing
SWL2001 repository from Semtech.

At term, this repository might be merged into the upstream Zephyr project.

This is an experimental release of demo projects of LBM on Zephyr, tested on LR11xxMB1LxKS shields

## Zephyr module

You can use this module either as your "west manifest project", or include it in 
another project. In that case you need to add `import: true` to the caller configuration, as this:

```yaml
  projects:
    - name: lora_lbm
      path: modules/lora_lbm
      remote: lora-net
      repo-path: lora_lbm_zephyr
      revision: zephyr
      import: true
```

## Requirements

You need a recent Linux distribution (Python >= 3.10, CMake >= 3.20.5).

### Install west and Zephyr SDK

You need to install the Zephyr SDK (compiler and flashing tools) and west (the build system tool).

Please follow instructions at <https://docs.zephyrproject.org/latest/develop/getting_started/index.html>.
You will only need to follow this step only once for all your Zephyr projects.

### Activate the Zephyr virtual environment (if not already activated)

If it's not installed in your system, you need to load the Zephyr SDK environment each time you open a new terminal:

```bash
source ~/zephyrproject/.venv/bin/activate
```

## Download code

This repository only contains specific LBM port code and the samples. We also need to download Zephyr itself, LBM, and associated HAL modules.

You need to create an empty directory, let's name it `lbm_zephyr_workspace`, and clone the current repository inside it.

```bash
mkdir lbm_zephyr_workspace
cd lbm_zephyr_workspace
git clone git@github.com:lora-net-private/SWL2001_Zephyr.git lora_lbm
```

The `SWL2001_Manifest` repository will be automatically downloaded, you don't need to clone it yourself.

### Configure the SSH command (only needed if external to lora-net-private)

If you need Git to use a custom SSH key to access the private repositories, you can either
configure it in your `~/.ssh/config` file or specify it in your terminal's environment:

```bash
export GIT_SSH_COMMAND="/usr/bin/ssh -i <path>/60093279.SWL2001SSHKEYMFAS.key"
```

### Download Zephyr and its modules

Then, initialize West (the build tool):
Multiple repositories will be automatically downloaded inside the workspace directory.

```bash
west init -l lora_lbm
west update
```

It will take 3-10 minutes to run depending on your network connection.

You will need to run this step for every project you download.

If major updates to `lora_lbm` are provided, you might need to run `west update` again.

## The samples

Samples are in the `lora_lbm/samples` directory, split in two classes:

* lora_drivers: Samples only using the low level LoRa drivers 
  * ping_pong : Flash this sample to two boards to see them talk.
  * ping_shell : Same as ping_pong, but manually, using the Zephyr shell ! run `lorademo ping` in one board to ping the other flashed board.
* lora_basics_modem: Samples leveraging the LBM stack to communicate with LoRaWAN networks.
  * app_demo_periodical_uplink: This sample joins a network and periodically sends packets.
    You can also send a packet manually by pressing the button (on nRF52840dk it's BUTTON 1).
    Please configure your device EUIs/App keys in `src/example_options.h`
  * app_lbm_hw_modem: used for continuous integration tests. It expects serial communication on an UART port.
    Read `src/hw_modem/cmd_parser.c` for explanations.


## Build the code

You need to inform Zephyr which board and shield you want to use. Shields are in the `lora_lbm/boards/shields/*` directories as `.overlay` files.
They describe which transceiver model you are using. For example, `semtech_lr1110mb1xxs`.

Go into a sample's directory, then run:

```bash
west build --board nrf52840dk/nrf52840 -- -DSHIELD=semtech_lr1110mb1xxs
# or 
west build --board nucleo_l476rg --build-dir build_nucleo -- -DSHIELD=semtech_lr1110mb1xxs
```

It will build your project in the `build` subdirectory (can be configured by `--build-dir`).
You can pass `--pristine` to ensure the build directory is clean.

The boards are expected to have a `lora0` node label. The shield `semtech_lr1110mb1xxs` provides it.

You might want to customize the LoRa transceiver configuration by adding a file in the `boards` subdirectory or via `app.overlay`.
For example, to set a TCXO instead of the default XTAL:

```dts
&lora_semtech_lr11xxmb1xis {
    tcxo-wakeup-time = <7>;
};
```

## Flash the board

```bash
west flash
# or
west flash --build-dir build_nucleo
```

For the nRF52840-DK board, you don't need to close open serial ports during flash.

## Open the serial port

You can use minicom, picocom, tio,…

```bash
tio /dev/serial/by-id/usb-SEGGER_J-Link_*-if00
```
