# WPSD MQTT Topic Subscrption Tool

This is a small C program for subscribing to the various MQTT topics provided
by `G4KLX`'s MMDVMHost and other related gateway programs.

It runs as a daemon in the background, and as new MQTT messages arrive, writes
the messages to json files.

## Build:

This program requires the following dev headers and libs in order to build:
1. Mosquitto
2. cJSON
3. libini(h)

Once these deps. are satisfied, simply build by running:
```text
gcc wpsd-mqtt-subscriber.c -o wpsd-mqtt-subscriber -lmosquitto -lcjson -linih
```

## Syntax:

```text
wpsd-mqtt-subscriber <path-to-config-file>
```

## Config File:

Format is a simple INI-style. There is an example included in the source.

## Systemd setup:

1. Copy `wpsd-mqtt-subscriber.service`  to `/etc/systemd/system/wpsd-mqtt-subscriber.service`
2. Run:
     ```text
    sudo systemctl daemon-reload
    sudo systemctl enable wpsd-mqtt-subscriber.service
    sudo systemctl start wpsd-mqtt-subscriber.service
    ```

