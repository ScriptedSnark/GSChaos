# GSChaos

![20240227184438_1](https://github.com/ScriptedSnark/GSChaos/assets/51358194/9ecded52-34cc-4722-9441-3280cb7df228)


ASI plugin for GoldSrc Engine (steam_legacy / HL25). Adds "Chaos" in game (new chaotic effect every 30 seconds).

Inspired by Chaos mods from the GTA universe (by zolika1351), I decided to make my own for HL1 and GoldSrc in particular (you can run almost any mod with it).

**Download: [CLICK](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)**

Additional info:
- Chaos UI rendering is not visible in OBS scene if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)
- Save your game more often because of potential softlocks/crashes

## CVars and commands
- `chaos_activate` - activate effect (from 0 to (LATEST EFFECT NUM - 1)) | `sv_cheats 1` is required!
- `chaos_reset` - reset RNG, chaos bar (can be useful for potential runs)
- `chaos_version` - prints version and Chaos Mod details
- `chaos_effectname_ypos` - sets position of effect name text by vertical (Y coord)

## Twitch voting integration (WIP)
Chaos Mod supports voting feature via Twitch chat. You can setup it by editing `chaos/twitch.ini`. Get your OAuth pass **[here](https://twitchapps.com/tmi/)**. 
If you don't want to play with this feature, you can delete (or rename) `chaos/twitch.ini`.

## Effects
```
> New Game :tf:
> Audio Corrupt
> Set 1 HP
> I believe I can fly
> Remove Armor
> Zero Gravity
> Invisible entities
> Ohio
> Fake Crash
> Darkness
> Totem of Undying
> Forgot to install CS 1.6 :o
> X2 Gravity
> God Mode
> Everyone has God Mode!
> Create Explosion
> Ichthyosaur jumpscare
> Give Gauss
> Human grunt ambush!
> GTA 3 HUD
> player_weaponstrip
> Spawn Griefer Shephard
> Entity spin
> 2D Camera
> 1% chance of death
> Spawn random entity
> Sleepy
> Force 20 FPS
> BSP Dementia
> HEV Madness
> Negative Stepsize
> Lobotomy
> Upside Down
> Every NPC explodes
> Let's see Jeepy's lasagna
> Hyper Gravity Field
> Ice Skating
> Invert Velocity
> Need for Speed (500 ups curse)
> Combine Effects ( 3 in 1 )
```

Credits
==============
Author: ScriptedSnark

Special thanks to:
- zolika1351 for his great, inspiring Chaos mods
- anewnick (a.k.a codque) for designing HUDs
- SmileyAG for provided help about some aspects of hooking
- BlueNightHawk for late precache system
- un4seen (a.k.a. yanny) for supporting/playtesting
- Tankfird, StereoBucket, prolert, gatar and other people for suggesting effects, ideas
