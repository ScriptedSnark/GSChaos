# GSChaos

![gsch_banner](https://raw.githubusercontent.com/ScriptedSnark/GSChaos/master/gsch_banner.png)

</div>
ASI plugin for GoldSrc Engine. Adds "Chaos" in game (new chaotic effect every 30 seconds).

Inspired by Chaos mods from the GTA universe (by zolika1351), I decided to make my own for HL1 and GoldSrc in particular (you can run almost any mod with it).

Supports builds `9920` (HL25), `8684` (steam_legacy), `4554` (GoldSrc Package, 2009), `3248` (Half-Life 2005 WON package)

**Download via Github: [CLICK](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)**

Additional info:
- Chaos UI rendering is not visible in OBS scene (if chaos_draw_as_overlay is enabled) if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)
- Save your game more often because of potential softlocks/crashes

## CVars and commands
- `chaos_activate` - activate effect (from 0 to (LATEST EFFECT NUM - 1)) | `sv_cheats 1` is required!
- `chaos_reset` - reset RNG, chaos bar (can be useful for potential runs)
- `chaos_version` - prints version and Chaos Mod details
- `chaos_dmca_safe` - if enabled, it doesn't allow to play some sounds which are ©
- `chaos_effectname_ypos` - sets position of effect name text by vertical (Y coord)
- `chaos_show_voting` - draw voting progress in Chaos UI so you can see it without checking OBS
- `chaos_timer` - sets time until the next effect
- `chaos_draw_as_overlay` - if enabled, it draws Chaos UI as overlay and requires enabling 3rd-party overlays in OBS

## Twitch voting integration (WIP)
GSChaos supports Twitch chat voting. If you want to use it, then do some steps:
1. Download [latest continuous release](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)
2. Install it
3. Edit `chaos/twitch.ini`. It should have your [OAuth password](https://twitchapps.com/tmi/) and Twitch username
4. Add text element (GDI) to your OBS scene
5. Create file - `chaos/voting_progress.txt`
6. Pass a path of that file in text options
![obs_voting](https://github.com/ScriptedSnark/GSChaos/assets/51358194/b944b93a-f429-49e4-90e2-3da60d2d9026)

7. Run the game and check if everything is installed successfully (wait for 10 seconds in game after chaos bar activating so you can check voting system)

To vote, you need to type `NUMBER` in chat (for example, `2`).
If you don't want to play with this feature, rename `twitch.ini` to `twitch_DISABLED.ini`.

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
> Nothing
> Darkness
> Totem of Undying
> Forgot to install CS 1.6 :o
> X2 Gravity
> God Mode
> Everyone has God Mode!
> Create Explosion
> Ichthyosaur jumpscare
> Give random weapon
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
> Need for Speed (320 ups curse)
> Make It Bun Dem
> Bikini Bottom
> X10 Gravity
> Overwrite Quicksave
> Stop
> Get Noclip
> Give +100 HP
> HL2 Movement
> Give +100 armor
> Am I dead?
> Node Graph
> Spawn Extreme Griefer Shephard
> Insane Stepsize
> Delete random entity :xdd:
> Nuke player
> +duck
> monster_worldspawn
> Spawn fastrun.bsp
> World Hallucination
> Give +1 HP
> Take 1 HP
> Scientist Madness
> MLG Audio
> No HUD
> Quake Pro
> Negative Accelerate
> Spawn Squeak Shephard
> Squeak Shephard Ambush
> Boost
> Nice
> Notarget
> Half-Gravity
> Rollin'
> High
> Shake
> Slap
> Play AG
> Swap health and armor
> Combine Effects ( 3 in 1 )
> Let's make it more chaotic
```

Credits
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
