Introduction
While there are many references available for Steamworks and even a couple of Unreal Engine plug-ins that provide Steamworks API wrappers for C++ and Blueprints, I have so far not found any walkthroughs or examples for how to get Steamworks Steam Input API working with Unreal Engine. I'm sure plenty of people have done it, and I'm sure many of them will read this and shake their heads at my implementation but having spent some time trying to figure this out on my own, I thought I'd try to save the next person some time and document how I got Steam Input fully working for my game.

Background
If you are shipping a game on Steam, the requirements for full controller support 'certification' can be difficult to attain without a lot of hard work. Steam Input is supposed to help simplify this, but the way it works with Unreal Engine can make life difficult. Unreal Engine has a few built-in input mechanisms, including the 'legacy' Input manager and the new Enhanced Input system. Steam Input works outside of these and doesn't provide a lot of the nice features UE provides like event-driven input signaling. Of course, Steamworks is a cross-platform and cross-engine system, so it should be no surprise that they provide APIs but no nice extensions to make them easier to use in any specific engine.

For my game, I wanted to provide the best possible user experience for input, making sure that all input types are treated as first-class citizens. As a 2.5D platformer, I have no need for mouse input for the game itself, so I decided to do a complete implementation that was keyboard or gamepad only. Gameplay was relatively simple to implement since it only requires left/right movement, jump, crouch, shoot and interact inputs, along with options to pause/show in-game menu. Menu input was also relatively straightforward; the player only needs to navigate the menu using up/down and select/back inputs for the most part, then change settings using left/right. That being said, this tutorial can be used for nearly any kind of game that supports gamepad input, so there are no real limitations.

Caveats
I managed to crash Steam quite a few times during my testing. Simple things like running a local build by adding it as a non-Steam game then trying to launch the controller config crashed every time.
The Steam API will not load if you use the PIE modes. You MUST use the Standalone Game option for testing.
Control mappings for Xbox, Playstation and other controllers must be set up separately in Steam. Check out their instructions on the Steamworks pages above for details.
I had to restart Unreal Engine once in a while because Steam latched onto it and wouldn't let go. If you find that your non-Steam Input (i.e., Enhanced or Legacy Input) is no longer working in PIE mode, try exiting both UE and Steam.
Pre-requisites:
You can do all the work in this tutorial using the Steam the 480 test App ID, so you don't need to have your game registered on the Steam store.
I did most of my work using the SteamCore plugin (https://steamcore.eeldev.com/docfiles/getting_started/configuring-plugin) from the marketplace. Most of what I will show translates directly to C++ because the plugin is 'just' a wrapper that exposes the Steamworks APIs in Blueprints (at least it is for Input). There may be better/simpler ways to do things in C++, though, so be sure to plan ahead if you plan on going the source code route.
Steam must be installed on your development system and running in order for the SteamWorks APIs to work. Steam suggests using big picture mode for controller testing, and this definitely provides a better user experience.
Setup Steps
Download and install the Epic Launcher then install Unreal Engine 5.1.
Note: as of this writing, Steamworks is at version 1.55 while UE 5.1 and the SteamCore plugin run on version 1.53. I didn't have any issues with this, but the further Steamworks drifts from the version supported by UE 5.1, the greater the chances that a depreciated or changed API may crop up.
Launch UE 5.1 and create a new project based on the Third Person template (Blueprint or C++) with starter content.
If you plan to use Blueprints, purchase the SteamCore plugin and install it to the 5.1 engine.
Go to Edit->Plugins, enable SteamCore and the Online Subsystem Steam. Make sure that the "Steam Controller Plugin" and "SteamVR" are NOT enabled (since these are depreciated). Restart UE.
Go to Edit->Project Settings and under Game->SteamCore Plugin, drop in your Steam App ID and Steam Dev App ID (these can be the same if you aren't live yet, but you should use a dev build if you're already live).
Creating Steam Input Configuration
I found the instructions on SteamWorks a bit arcane, but after going through them a few times and a bit of trial and error, I think I've figured out how it mostly works. Thanks to the gaming community for sharing their insights as well! There are two steps to setting up input configuration for a new game:

Create a game_actions_N.vdf file where N is the app ID for your game (like 480 for the test game), set up the actions and save it in the Steam folder inside a (possibly non-existent) folder named "controller_config" (e.g. C:\Program Files (x86)\Steam\controller_config\game_actions_480.vdf).
Launch your game in Standalone Player Mode from UE 5.1. You should see the Steam menu come up in the bottom-right corner after a few seconds. Press Shift-Tab (or whatever key sequence you set up to show the Steam Overlay) and open the Controller layout app.
You should see a blank configuration. Your action names from the VDF file will be available to assign to each input, so go into Edit Layout and set it up. In this case, you'll only have one Action Set (In-game controls) and only Jump, Move and Camera for the actions. Assign these to Button A (Jump), Joystick Left (Move) and Joystick Right (Camera) respectively. You probably also want to turn down the sensitivity for the camera to something like 25% or it'll spin like crazy.
Click on the Gear icon beside "Edit Layout" from the main page on the Controller layout and export your layout to your personal settings.
Repeat this step for each controller type (Xbox, PS, Switch, etc.)
Here's the contents of the game_actions_N.vdf file I created for my game, including the menu system and level editor. Your action sets and actions will likely be different.
