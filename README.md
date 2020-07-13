# ProjectX
A cheat targeted at Fortnite, or rather it's engine UE4.

No further support will be provided with this project. This is a ugly PoC that was sold to a money hungry paster.

# Information / Features

- Aimbot
- Smoothing / Visibility checks
- Name visuals
- Objects in the game (Chests, Choppers, Sharks, Llamas, etc.)
- Bullet Teleportation
- First Person Mode (will fuck your sniper unless you fix it.)
- Player Teleportation (no bypass implemented, so client-sided)
- Boat / Helicopter speed / other features.

This cheat is detected by default on both commercial anti-cheats run by Fortnite (BattleEye and EasyAntiCheat)
Some parts are already outdated, if you plan on updating this you'll need to update the signatures and offsets being used.
Everything is mostly calculated using UE4 functions like ProjectWorldLocationToScreen, LineOfSight, and GetBoneMatrix.

# Usage
This can be compiled with Visual Studio 2019, with the c++ tools installed.

Just inject the DLL when in lobby, and you should be good

# Credits

To the Unknowncheats's Fortnite Reversal page,

@Mike024 - Developing most of the cheat (exclusing the maven pieces),

@Poorman24 / SDK - Providing useful information / reversal information calling multiple functions,

@Sinclairq (me) - Information / Research provided to complete the cheat

@dano20zombie - FortUpdater
