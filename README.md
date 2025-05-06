### VectorWar UE

A port of the GGPO sample game "VectorWar" for Unreal Engine, using [GGPOUE](https://github.com/BwdYeti/GGPOUE).

![screencap](vwscreen.png)

## Setup

1. Install [Unreal Engine 4.25](https://docs.unrealengine.com/en-US/GettingStarted/Installation/index.html), [Visual Studio](https://docs.unrealengine.com/en-US/Programming/Development/VisualStudioSetup/index.html), and any dependencies.
2. Clone the repo with ```git clone --recursive https://github.com/BwdYeti/VectorWarUE.git```, or after downloading run ```git submodule update --init --recursive``` to download the [GGPOUE](https://github.com/BwdYeti/GGPOUE) submodule.
3. (optional) Generate project files (Right click VectorWarUE.uproject, ```Generate Visual Studio project files```).
4. Open VectorWarUE.uproject

## Controls

* Arrow keys: Move
* D: Fire
* P: Network Performance Monitor

## Notes

Unreal Engine is not deterministic, which is required for netcode that only sends inputs between players, such as deterministic lockstep (delay based) or rollback. VectorWarUE gets around this by running the original VectorWar code as its own game state, separate from the UE game logic. It only uses UE for reading player inputs, maintaining the update tick frequency, and rendering the game state by matching Unreal actors to the game state objects they represent. Similar solutions will be required for your own projects.

Currently GGPOUE is only usable with Windows.
