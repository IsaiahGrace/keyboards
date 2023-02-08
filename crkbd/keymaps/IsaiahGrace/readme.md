# Corne Light
This is the Corne Light, also known as CRKBD.
[Build guide from PCB creator.](https://github.com/foostan/crkbd/blob/main/corne-light/doc/v2/buildguide_low_edition_en.md) 

## Part selection:
* **Switches:** [Kailh Low Profile Choc Switches](https://mkultra.click/choc-switches) - You'll need 42 switches. The white "color" is the clicky one I have. I like it a lot, but it is the loudest of the switch types. The keyboard can also support Cherry switches, if you decide to go for a taller build.
* **Keycaps:** MBK profile, I love this profile. They are gently sculpted, and the "homing" keys for F and J feel great. You'll need: 38 x 1u, 2 x 1u homing, 2 x 2u.
	* [MBK Legend](https://mkultra.click/mbk-legend-keycaps/) - Nice colors, red/grey, black on white, white on black.
	* [MBK Factory Colors](https://mkultra.click/mbk-factory-colors/) - Dyed in the factory.
	* [MBK Colors](https://mkultra.click/mbk-colors/) - Dyed by hand by MKUltra. Probably not a nice as the factory dyed colors, but who knows!
	* [MBK Choc Keycaps](https://mkultra.click/mbk-choc-keycaps/) - The original MBK. This is what I have. White or Black.
* **Aux cable:** You'll need a short aux extension cable to connect the two keyboards together. It needs to be a TRRS cable to carry all the signals that the microcontrollers need to talk to each other. See this explanation of audio cable types: [35mm-audio-jack](https://components101.com/connectors/35mm-audio-jack).
* **USB C Magnetic quick release:** [Amazon link](https://www.amazon.com/gp/product/B0831KYRD2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&th=1) - Definitely optional, but it will prevent wear and tear on the keyboard if you plug and unplug it a lot (like if you take it to work everyday and bring it home too).

## Keymap:
[This](https://github.com/IsaiahGrace/keyboards/blob/master/crkbd/keymaps/IsaiahGrace/keymap.c) is my keymap for my Corne. I've chosen to do things the "hard" way an modify the C source files directly, but by using a combination of [QMK Configurator](https://config.qmk.fm/#/crkbd/rev1/LAYOUT_split_3x6_3) and [QMK Toolbox](https://github.com/qmk/qmk_toolbox) you should be able to change the layout, compile the firmware, and flash the keyboards all without messing about in the code too much...

## Cases:
There a many options, I just put small silicone feet around the edges of the PCB to lift it a few mm off the desk. It's a little more fragile this way, but very low profile. The build guide shows how to use foam and it looks much nicer! It might make the keyboard feel squishy, but I don't know...
* [3D print case files](https://www.thingiverse.com/thing:5029891) - This is just a random project I found. I have to idea if it's high quality or not...
* [High profile case](https://www.thingiverse.com/thing:4039133) - I don't like this style, feels like it's negating all the benefits from building a low profile keyboard. But it would look cool!
* [Low profile case](https://www.thingiverse.com/thing:4549765) - This one looks pretty cool. If I had a 3D printer, I thing I would try it out. Although I would probably modify it a little to reduce the tall lip near the controller.

