Chaos Mod for GoldSrc engine.

WARNING! Mod is unstable and can cause softlocks/crashes!

REQUIREMENTS
==============
GoldSrc: build 3248/4554/8684/9920
Graphics mode: OpenGL (Software is not supported)

INSTALLATION (FOR GOLDSRC PACKAGE / STEAM VERSION)
==============
1. Extract ZIP to your Half-Life directory (you can create backup for hl.exe)
2. Run game
3. If you see progress bar on top, Chaos Mod is installed successfully!

INSTALLATION (FOR WON 2005)
==============
1. Extract ZIP to your Half-Life directory. DO NOT REPLACE HL.EXE!!!
2. Rename DemoPlayer.dll to any name (for backup)
3. Rename ASILoader_3248.dll to DemoPlayer.dll
4. Run game
5. If you see progress bar on top, Chaos Mod is installed successfully!

ADDITIONAL INFO
==============
- !!!Chaos UI rendering is not visible in OBS scene (if chaos_draw_as_overlay is enabled) if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)!!!
- Save your game more often because of potential softlocks/crashes

CVARS AND COMMANDS
==============
- `chaos_activate` - activate effect (from 0 to (LATEST EFFECT NUM - 1)) | `sv_cheats 1` is required!
- `chaos_reset` - reset RNG, chaos bar (can be useful for potential runs)
- `chaos_version` - prints version and Chaos Mod details
- `chaos_dmca_safe` - if enabled, it doesn't allow to play some sounds which are ©
- `chaos_effectname_ypos` - sets position of effect name text by vertical (Y coord)
- `chaos_show_voting` - draw voting progress in Chaos UI so you can see it without checking OBS
- `chaos_timer` - sets time until the next effect
- `chaos_draw_as_overlay` - if enabled, it draws Chaos UI as overlay and requires enabling 3rd-party overlays in OBS

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
