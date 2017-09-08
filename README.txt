Gardenia is a fork of PlugY 11.02 by Yohann Nicolas that removes all
of the components that are not allowed in the Diablo II IncGamers SPF
forum and leaves the basics, primarily unlimited stash. 

This is compatible only with 1.09b and 1.13d.

Internally, I'm slowly trying to improve the design of the application by
using OOP best practices and removing the massive usage of the preprocessor.
The application was originally designed as a C application saved in a .cpp
file (and using the C++ compiler).

All code is published as GPL 3+ since that was the license that Yohann released it under.

This is not a stable version, so use at your own risk.

Gardenia IS compatible with Bliss Version Switcher. So if you want to have separate stashes
while you are time traveling, you can. Just point Bliss Version Switcher to use "Gardenia.exe"
rather than "Game.exe". Bliss Version Switcher will automatically point the save directory
to the desired version of D2 you want to play (and Gardenia saves the stashes with your
characters as well).

Bliss Version Switcher URL:
https://github.com/fearedbliss/Bliss-Version-Switcher

Compiled with Visual Studio 2017.

Features
====
Each features can be turn on/off via Gardenia.ini (see "COMMENTS ON THE CONFIGURATION FILE")
- Disable access to Battle.net.
- Infinite storage space in the stash.
- Shared storage space in the stash.
- Automatically execute /players X when you launch a new game.
- Launch any number of Diablo II games on the same computer.
- Added some pages for display more characters stats like %MF.
- Enabled the ladder only runewords out of realms.
- Display item level in its popup.
- Increase the stash to 10x10 squares.
- Always display Mana and Life values above the globes.
- Display the stats current value (without magical bonus) like Magic/gold find or maximum resistances.
- Can launch game in windowed mode with some options (lock mouse/resize/on top/noborder).
- Change the selected language.
- D2 can load all files, even those opened with Microsoft Excel (disabled by default).

- Add following commands (see "COMMENTS ON THE CONFIGURATION FILE") :
	/save : Save game without exit.
	/page 1 : Show normal stats page (stats page must be opened).
	/page 2 : Show extra stats page (stats page must be opened).
	/page 3 : Show resistance stats page (stats page must be opened).
	/page 4 : (beta) Show available runewords (stats page must be opened).
	/lockmouse : Lock mouse cursor in the window.
	/lock : Same as /lockmouse.
	/unlockmouse : Unlock mouse cursor in the window.
	/unlock : Same as /unlockmouse.
	/renamechar newname : Rename your character and save it.
	/renamepage name : Rename current page stash.
	/setindex : Set current stash page as index.
	/setmainindex : Set current stash page as main index.
	/resetindex : Remove index flag on the current stash page.
	/insertpage : Insert a new page after the current page.
	/deletepage : Delete current page if empty.
	/swap page : Swap the content of current stash page with the content of another page.
	/toggle page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.
	/dlm : Toggle always display mana and life mode.
	/dml : Same as /dlm.
	/dl : Toggle always display life mode.
	/dm : Toggle always display mana mode.
	/listcube : (beta) Create a "cube.txt" file in save directory containing all cube's receipts.

Removed
====
- Unassign assigned skills and stats points.
- Local World Event and Uber Quest for singleplayer and multiplayer off-realm !
- Can open Cow Level Portal even when player have kill the Cow King in that difficulty.
- Always regenerate maps in SinglePlayer like in MultiPlayer.
- Removed ability to change how much stat/skill points one receives per level
- Change the save path directory.


Other TODO
=====
- Make separate hardcore stashes non changable.
- Check to see why /page4 no longer works.
- Remove /dml alias, just keep /dlm.
- d2mod support can be removed since d2mod only supports 1.10 and we dont support 1.10 in this mod