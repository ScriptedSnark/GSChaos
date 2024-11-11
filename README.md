# GSChaos

<a href="https://www.moddb.com/mods/gschaos" title="View GSChaos (Chaos Mod) on ModDB" target="_blank"><img src="https://button.moddb.com/popularity/medium/mods/61878.png" alt="GSChaos (Chaos Mod)" /></a>

![gsch_banner](https://raw.githubusercontent.com/ScriptedSnark/GSChaos/master/gsch_banner.png)

</div>
ASI plugin for GoldSrc Engine. Adds "Chaos" in game (new chaotic effect every 30 seconds).

Inspired by Chaos mods from the GTA universe (by zolika1351), I decided to make my own for HL1 and GoldSrc in particular (you can run almost any mod with it).

Supports builds `10210` (HL26), `9920` (HL25), `5936` (Cry of Fear), `8684` (steam_legacy), `4554` (GoldSrc Package, 2009), `3248` (Half-Life 2005 WON package)

**Download via Github: [CLICK](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)**

Additional info:
- Chaos UI rendering is not visible in OBS scene (if chaos_draw_as_overlay is enabled) if third-party overlays checkbox is unchecked (doesn't matter if you capture hl.exe as a window, not game)
- Save your game more often because of potential softlocks/crashes

## CVars and commands
- `chaos_activate` - activate effect (from 0 to (LATEST EFFECT NUM - 1)) | `sv_cheats 1` is required!
- `chaos_reset` - reset RNG and all states
- `chaos_version` - prints version and Chaos Mod details
- `chaos_dmca_safe` - if enabled, it doesn't allow to play some sounds which are ©
- `chaos_effectname_ypos` - sets position of effect name text by vertical (Y coord)
- `chaos_show_voting` - draw voting progress in Chaos UI so you can see it without checking OBS
- `chaos_timer` - sets time until the next effect
- `chaos_draw_as_overlay` - if enabled, it draws Chaos UI as overlay and requires enabling 3rd-party overlays in OBS
- `chaos_consistent_mode` - switches consistent mode. Consistent mode involves turning on certain effects for an unlimited amount of time without Chaos bar/timer.
- `chaos_consistent_effects_add` - activate consistent effect (works only with consistent mode enabled)
- `chaos_volume_multiplier` - increases volume from SoLoud sounds (volume->value * chaos_volume_multiplier->value)

## Twitch voting integration (WIP)
GSChaos supports Twitch chat voting. If you want to use it, then do some steps:
1. Download [latest continuous release](https://github.com/ScriptedSnark/GSChaos/releases/tag/continuous)
2. Install it
3. Edit `chaos/twitch.ini`. It should have your [OAuth password](https://twitchapps.com/tmi/) and Twitch username
4. Add text element (GDI) to your OBS scene
5. Pass a path of `chaos/voting_progress.txt` in text options
![obs_voting](https://github.com/ScriptedSnark/GSChaos/assets/51358194/b944b93a-f429-49e4-90e2-3da60d2d9026)

7. Run the game and check if everything is installed successfully (wait for 10 seconds in game after chaos bar activating so you can check voting system)

To vote, you need to type `NUMBER` in chat (for example, `2`).
If you don't want to play with this feature, rename `twitch.ini` to `twitch_DISABLED.ini`.

## Effects

<details><summary>HL effect list</summary>

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
> GTA HUD
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
> Need for Speed
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
> Teleport to random NPC
> Shuffle entities positions
> Wide NPCs
> Ultra wide NPCs
> Tiny NPCs
> Paper NPCs
> Give +1 armor
> Replace models with player
> Horror Audio
> Low FOV
> Disable Chaos UI
> Random fog
> Worst Bhop Cap
> Long Jump
> Reload Autosave
> He comes back.
> Mega Jump
> Spawn 5 random entities
> Give all weapons
> Water is a lie
> Quake jump sound
> +hook
> Teleport to spawn point
> rorriM
> "It's easier to aim", they said
> Creepypasta Mode
> Mess Up World
> Kick World
> Tall World
> Trap Player
> Third person
> Model Insanity
> Half Game Speed
> Standstill (1% game speed)
> Game Speedup
> Gambling
> Random Game Speed
> Turbulent Hell
> NA Aim
> Temp Entity Madness
> EU Aim
> Scrolling Hell
> Delete 5 random entities
> Kilometer
> Dinnerbone
> Minerals
> Move all NPCs to player
> Chipmunks
> Floating Point Inaccuracy
> Hold +USE to boost!
> View Offset Insanity
> Overwrite Autosave
> Overthinking
> Nightvision
> Voidclip
> Cheat Code Voting !!!(available with Twitch voting)!!!
> 3 Effects in 1
> Let's make it more chaotic
> Let's not make it more chaotic :3
```

</details>

## Effects (CRY OF FEAR)
<details><summary>CoF effect list</summary>

```
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
> Give random weapon
> GTA HUD
> player_weaponstrip
> Spawn Griefer Shephard
> Entity spin
> 2D Camera
> 1% chance of death
> Spawn random entity
> Sleepy
> Force 20 FPS
> VOICES IN YOUR HEAD
> Negative Stepsize
> Lobotomy
> Upside Down
> Let's see Jeepy's lasagna
> Hyper Gravity Field
> Ice Skating
> Invert Velocity
> Need for Speed
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
> Nuke player
> +duck
> monster_worldspawn
> World Hallucination
> Give +1 HP
> Take 1 HP
> Scientist Madness
> MLG Audio
> No HUD
> Negative Accelerate
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
> Teleport to random NPC
> Shuffle entities positions
> Wide NPCs
> Ultra wide NPCs
> Tiny NPCs
> Paper NPCs
> Give +1 armor
> Replace models with player
> Horror Audio
> Disable Chaos UI
> Random fog
> Worst Bhop Cap
> Long Jump
> He comes back.
> Mega Jump
> Spawn 5 random entities
> Give all weapons
> Water is a lie
> Quake jump sound
> +hook
> Teleport to spawn point
> rorriM
> "It's easier to aim", they said
> Creepypasta Mode
> Mess Up World
> Kick World
> Tall World
> Trap Player
> Third person
> Model Insanity
> Half Game Speed
> Standstill (1% game speed)
> Game Speedup
> Gambling
> Random Game Speed
> Turbulent Hell
> NA Aim
> Temp Entity Madness
> EU Aim
> Scrolling Hell
> Kilometer
> Dinnerbone
> Minerals
> Move all NPCs to player
> Chipmunks
> Floating Point Inaccuracy
> Hold +USE to boost!
> View Offset Insanity
> Overwrite Autosave
> Overthinking
> Nightvision
> Voidclip
> Cheat Code Voting !!!(available with Twitch voting)!!!
> 3 Effects in 1
> Let's make it more chaotic
> Let's not make it more chaotic :3
```

</details>

Credits
==============
Author: ScriptedSnark

Special thanks to:
- zolika1351 for his great, inspiring Chaos mods
- anewnick (a.k.a codque) for designing HUDs and banner
- SmileyAG for provided help about some aspects of hooking
- BlueNightHawk for late precache system
- suXinjke for [Half-Payne](https://github.com/suXinjke/HalfPayne)
- un4seen (a.k.a. yanny), JeepyGMI, Kalifron4ik for supporting/playtesting when GSChaos didn't have even 50 effects
- Tankfird, StereoBucket, JeepyGMI, prolert, gatar, Eold, Bartek(GMI) and other people for suggesting effects, ideas
- [Ryder Joestar](https://gamebanana.com/members/2142275) for modelling help (Jesus and Totem)
- YaLTeR for SPTLib
- Valve for Half-Life, GoldSrc engine