=============
Synopsis
=============
Gardenia is a Diablo II 1.09b mod that is forked from Yohann Nicolas' PlugY 11.02.
My mod removes all excess components and provides a much slimmer and maintainable mod
through code reduction and massive refactoring and redesign.

In order to increase the maintainability of the mod and provide an
optimal experience for whatever version you are playing, Gardenia now
only supports a single Diablo II version. For my mod specifically, it only
support 1.09b. I'm providing a 1.13d legacy branch that people can use to
improve their version of Gardenia if desired.

Gardenia IS compatible with Bliss Version Switcher. So if you want to have separate stashes
while you are time traveling, you can. Just point Bliss Version Switcher to use "Gardenia.exe"
rather than "Game.exe". Bliss Version Switcher will automatically point the save directory
to the desired version of D2 you want to play (and Gardenia saves the stashes with your
characters as well).

Bliss Version Switcher URL:
https://github.com/fearedbliss/Bliss-Version-Switcher

=============
Features
=============
Each feature can be turned on/off via Gardenia.ini (see "COMMENTS ON THE CONFIGURATION FILE"):

- Disable access to Battle.net.
- Infinite storage space in the stash.
- Shared storage space in the stash.
- Automatically execute /players X when you launch a new game.
- Launch any number of Diablo II games on the same computer.
- Added some pages for display more characters stats like %MF.
- Display item level in its popup.
- Increase the stash to 10x10 squares.
- Always display Mana and Life values above the globes.
- Display the stats current value (without magical bonus) like Magic/gold find or maximum resistances.
- Can launch game in windowed mode with some options (lock mouse/resize/on top/noborder).
- Change the selected language.
- D2 can load all files, even those opened with Microsoft Excel (disabled by default).

- Add following commands (see "COMMENTS ON THE CONFIGURATION FILE"):
	/page 1 : Show normal stats page (stats page must be opened).
	/page 2 : Show extra stats page (stats page must be opened).
	/page 3 : Show resistance stats page (stats page must be opened).
	/lock : Lock mouse cursor in the window.
	/unlock : Unlock mouse cursor in the window.
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
	/listcube : (beta) Create a "cube.txt" file in save directory containing all cube's receipts.

=============
Development, Goals, Tips, License
=============
Internally, I'm slowly trying to improve the design of the application by
using OOP best practices and removing the massive usage of the preprocessor.
The application was originally designed as a C application saved in a .cpp
file (and using the C++ compiler).

License
=============
All code is published as GPL 3+ since that was the license that Yohann released it under.

Development
=============
Compiled with Visual Studio 2017.

Tips for working with Gardenia (in Visual Studio 2017)
=============
- Always use Release Mode
- Don't use /GS (Security Check)
- Don't use compiler optimizations
- Use the debugger and compile debugging symbols (.PDB)

The reason for the above is because since the code uses a lot of
naked functions, there are times when the code directly maybe cause
an access violation, or something that could be perceived as an overflow.
Sometimes the code only works in Release mode but doesn't work in Debug mode.