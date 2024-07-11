<<<<<<<< HEAD:keyboards/zeix/acidandco/stellaron/readme.md
# Stellaron TKL
========
# dnworks TKL (F12)
>>>>>>>> 34d061787d ([Keyboard] Rename dnworks/9973 to dnworks/tkl87 (#23692)):keyboards/dnworks/tkl87/readme.md

![PCB Compatibility](https://i.imgur.com/fIBX8kF.png)

<<<<<<<< HEAD:keyboards/zeix/acidandco/stellaron/readme.md
PCB that supports Stellaron TKL

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: Stellaron PCB
* Hardware Availability: Private Group Buy

Make example for this keyboard (after setting up your build environment):

    make zeix/acidandco/stellaron:default

Flashing example for this keyboard:

    make zeix/acidandco/stellaron:default:flash
========
PCB that supports the F12 TKLs designed by dnworks.

* Keyboard Maintainer: [Zeix](https://github.com/itsme-zeix)
* Hardware Supported: 997.3 Solder PCB rev1, 765LT Solder PCB rev1 and Best Friend Solder PCB Rev1.
* Hardware Availability: https://dnworks.co/products

Make example for this keyboard (after setting up your build environment):

    make dnworks/tkl87:default

Flashing example for this keyboard:

    make dnworks/tkl87:default:flash
>>>>>>>> 34d061787d ([Keyboard] Rename dnworks/9973 to dnworks/tkl87 (#23692)):keyboards/dnworks/tkl87/readme.md

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

<<<<<<<< HEAD:keyboards/zeix/acidandco/stellaron/readme.md
* **Bootmagic reset**: Hold down the top left key and plug in the keyboard.
* **Physical reset button**: Briefly press the `RESET` button twice or short the `USB_BOOT` and `GND` pads and plug in the keyboard.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`.
========
* **Bootmagic reset**: Hold down escape and plug in the keyboard
* **Physical reset button**: Short the 'USB_BOOT' button and plug in keyboard or press the 'RESET' button twice with the keyboard plugged in.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
>>>>>>>> 34d061787d ([Keyboard] Rename dnworks/9973 to dnworks/tkl87 (#23692)):keyboards/dnworks/tkl87/readme.md
