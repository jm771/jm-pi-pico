#!/usr/bin/env bash
set -e -u -o pipefail

if (usbipd.exe list | grep -q "USB Serial Device"); then
 COM_LINE=$(usbipd.exe list | grep "USB Serial Device")
 echo "found COM device:\n$COM_LINE"
 DEVICE_ID=$(echo $COM_LINE | cut -d ' ' -f 1)
 if (echo $COM_LINE | grep -q "Shared"); then
  echo "Mounting com device"
  usbipd.exe attach --wsl --busid=$DEVICE_ID
  sleep 1
 fi
fi

if [ -e /dev/ttyACM0 ]; then
  echo "I see tty file - attempting reset"
  echo r >> /dev/ttyACM0
  sleep 1

  # DEVICE_LINE=$()
  # DEVICE_ID=$(echo $DEVICE_LINE | cut -d ' ' -f 1)
  # echo $DEVICE_LINE | grep -q "Attached" || 
  #sleep 1
else
 echo "couldn't open tty session - assuming device already in BOOTSEL"
fi

sudo /usr/bin/mount -t drvfs D\: /mnt/d
cp ./build/midi_controller.uf2 /mnt/d/