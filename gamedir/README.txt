Chaos Mod for GoldSrc engine.

WARNING! Mod is unstable and can cause softlocks/crashes!

REQUIREMENTS
==============
GoldSrc: build 3248/4554/8684/9920
Graphics mode: OpenGL (Software is not supported)

INSTALLATION (FOR GOLDSRC PACKAGE / STEAM VERSION)
==============
1. Extract ZIP to your Half-Life directory (you can create backup for hl.exe)
2. Move resources from "MOD_DIR" folder to that game directory which you will use for playing (e.g, "valve", "valve_WON", "gearbox", "rewolf", etc.)
3. Run game
4. If you see progress bar on top, Chaos Mod is installed successfully!

INSTALLATION (FOR WON 2005)
==============
1. Extract ZIP to your Half-Life directory. DO NOT REPLACE HL.EXE!!!
2. Rename DemoPlayer.dll to any name (for backup)
3. Rename ASILoader_3248.dll to DemoPlayer.dll
4. Move resources from "MOD_DIR" folder to that game directory which you will use for playing (e.g, "valve_WON", "gearbox_WON", "rewolf", etc.)
5. Run game
6. If you see progress bar on top, Chaos Mod is installed successfully!

ADDITIONAL INFO
==============
- Chaos UI rendering is not visible in OBS scene if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)
- Save your game more often because of potential softlocks/crashes

TWITCH CHAT VOTING INTEGRATION
==============
GSChaos supports Twitch chat voting. If you want to use it, then do some steps:
1. Edit `chaos/twitch.ini`. It should have your [OAuth password](https://twitchapps.com/tmi/) and Twitch username
2. Add text element (GDI) to your OBS scene
3. Create file - `chaos/voting_progress.txt`
4. Pass a path of that file in text options
5. Run the game and check if everything is installed successfully (wait for 10 seconds in game after chaos bar activating so you can check voting system)

To vote, you need to type effectNUMBER in chat (for example, "effect2").
If you don't want to play with this feature, rename `twitch.ini` to `twitch_DISABLED.ini`.

CREDITS
==============
Author: ScriptedSnark

Special thanks to:
- zolika1351 for his great, inspiring Chaos mods
- anewnick (a.k.a codque) for designing HUDs and banner
- SmileyAG for provided help about some aspects of hooking
- BlueNightHawk for late precache system
- suXinjke for [Half-Payne](https://github.com/suXinjke/HalfPayne)
- un4seen (a.k.a. yanny) for supporting/playtesting
- Tankfird, StereoBucket, prolert, gatar and other people for suggesting effects, ideas
