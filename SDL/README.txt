************************************************************************
*STEPS TO SETUP PROPER CAMERA STREAMING ENVIRONMENT ON A FRESH SD CARD *
************************************************************************

1) Run MainInstaller.sh as root (found in the installer directory).

2) Run AutobootSetup.sh as root (found in the installer directory).

3) Run "tvservice -d edid" from the terminal followed by "edidparser edid".

4) Find the preferred screen resolution / refresh rate from the list,
look for HDMI:EDID DMT or CEA mode.

5) Open /boot/config.txt as root. Uncomment out hdmi_group and hdmi_mode.
   If the reolution was CEA, write a 1 for group, if it was DMT write 2
   Write the number in brackets after the mode for hdmi_mode.

i.e) if you see:

HDMI:EDID best score mode is now DMT (27) 1280x800p @ 60 Hz with pixel clock 71 MHz (score 5184320)

Then write 2 for hdmi_group and 27 for mode for a result of:

# uncomment to force a specific HDMI mode (this will force VGA)
hdmi_group=2
hdmi_mode=27

6) Save the file and reboot the pi.
