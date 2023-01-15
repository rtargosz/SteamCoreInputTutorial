Background

This tutorial provides step-by-step instructions for how to implement Steam Input for games developed in Unreal Engine 5.1. I will mostly be covering how to do things in BluePrints using the EeelDev SteamCore plugin, but some C++ will be covered as well. The SteamCore plugin is just a wrapper for the Steam Input API, so going back and forth between C++ and BluePrints should be relatively simple.

While there are many references available for Steamworks and even a couple of Unreal Engine plug-ins that provide Steamworks API wrappers for C++ and Blueprints, I have so far not found any walkthroughs or examples for how to get Steamworks Steam Input API working with Unreal Engine. I'm sure plenty of people have done it, and I'm sure many of them will read this and shake their heads at my implementation but having spent a few days trying to figure this out on my own, I thought I'd try to save the next person some time and document how I got Steam Input working for my game.

The main reference page for Steam Input is available from Valve here: https://partner.steamgames.com/doc/features/steam_controller.

If you are shipping a game on Steam, the requirements for full controller support 'certification' can be difficult to attain without a lot of hard work. Steam Input is supposed to help simplify this, but the way it works with Unreal Engine can make life difficult. Unreal Engine has a few built-in input mechanisms, including the 'legacy' Input manager and the new Enhanced Input system. Steam Input works outside of these and doesn't provide a lot of the nice features UE provides like event-driven input signaling. Of course, Steamworks is a cross-platform and cross-engine system, so it should be no surprise that they provide APIs but no nice extensions to make them easier to use in any specific engine.

Caveats

Steam Input will take over the controller completely, so any attempts to use Input or Enhanced Input gamepad events will no longer work after implemeting this. Keyboard/Mouse will continue to work as usual.

Pre-requisites

For testing, you can use the Steam 480 test ID.

If you want to use your own game ID, you will need to have your game set up in the Steam Store to the point where you have a Steam app ID that you can use to create your Input configuration files. Rename the game_actions_480.vdf file to use your game's ID. Change the game ID in config/defaultengine.ini OR in the Project Settings under Game->SteamCore.

The SteamCore plugin is required (https://steamcore.eeldev.com/docfiles/getting_started/configuring-plugin) from the marketplace.

Steam must be installed on your development system and running in order for the SteamWorks APIs to work.

Setup Steps

Download and install the Epic Launcher then install Unreal Engine 5.1.

Note: as of this writing, Steamworks is at version 1.55 while UE 5.1 and the SteamCore plugin run on version 1.53. I didn't have any issues with this, but the further Steamworks drifts from the version supported by UE 5.1, the greater the chances that a depreciated or changed API may crop up.

Purchase the SteamCore plugin and install it to the 5.1 engine.

Launch UE 5.1 and open this project.

Go to Edit->Plugins, enable SteamCore and the Online Subsystem Steam. Make sure that the "Steam Controller Plugin" and "SteamVR" are NOT enabled since these are depreciated). Restart UE.

(Optional) Go to Edit->Project Settings and under Game->SteamCore Plugin, drop in your Steam App ID and Steam Dev App ID (these can be the same if you aren't live yet, but you should use a dev build if you're already live).

Creating Steam Input Configuration

I found the instructions on SteamWorks a bit arcane, but after going through them a few times and a bit of trial and error, I think I've figured out how it all works. You need a game_actions_N.vdf file and you need to setup your controls from the Steam controller settings for your game.

Copy the provided game_actions_480.vdf file to the Steam folder inside a (possibly non-existent) folder named "controller_config" (e.g. C:\Program Files (x86)\Steam\controller_config\game_actions_480.vdf).

Launch your game in Standalone Player Mode from UE 5.1. You should see the Steam menu come up in the bottom-right corner after a few seconds.

Press Shift-Tab (or whatever key sequence you set up to show the Steam Overlay) and open the Controller layout app.

You should see a blank configuration. The action names (Jump, Move, Camera) from the VDF file will be available to assign to each input, so go into Edit Layout and set it up. In this case, you'll only have one Action Set (In-game Controls) and only Jump, Move and Camera for the actions. Assign these to Button A (Jump), Joystick Left (Move) and Joystick Right (Camera) respectively.

You probably also want to turn down the sensitivity for the camera to something like 10% or it'll spin like crazy.

Click on the Gear icon beside "Edit Layout" from the main page on the Controller layout and export your layout to your personal settings.

You should now be able to control the player with both the Gamepad AND Keyboard/Mouse.