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
