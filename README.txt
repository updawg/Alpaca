Gardenia - 1.20
Jonathan Vasquez <jon@xyinn.org>
Released under the GPLv3+
Project based off Yohann Nicolas' PlugY 11.02
Current Supported Version: 1.09b

=============
Synopsis
=============
Gardenia is a Diablo II infinite stash mod that is forked from
Yohann Nicolas' PlugY 11.02. My mod removes all excess components
and provides a much slimmer and maintainable mod that is easier
to upgrade to new Blizzard versions, through code reduction,
massive refactoring, and redesign.

In order to increase the maintainability of the mod and provide an
optimal experience for whatever version you are playing, Gardenia now
only supports a single Diablo II version. For my mod specifically, it only
supports 1.09b. I'm providing a 1.13d legacy branch that people can use to
improve their version of Gardenia if desired. Players wanting to play
older versions of Diablo II should use the older and corresponding Gardenia
version.

Gardenia IS compatible with Cactus. So if you want to have separate stashes
while you are time traveling, you can. Just point Cactus to use "Gardenia.exe"
rather than "Game.exe". Cactus will automatically point the save directory
to the desired version of D2 you want to play (and Gardenia saves the stashes
with your characters as well).

Cactus Project Page - https://github.com/fearedbliss/Cactus

=============
Features
=============
Each feature can be turned on/off via Gardenia.ini (see "COMMENTS ON THE CONFIGURATION FILE"):

- Disable access to Battle.net.
- Infinite stash storage space (Personal Stash)
- Infinite shared stash storage space (Shared Stash)
- Automatically execute /players X when you launch a new game.
- Launch any number of Diablo II games on the same computer.
- Extended stats available in the Character Page (i.e %MF, Gold Find, Crushing Blow, ...).
- Display item level in its popup.
- Increase the stash to 10x10 squares.
- Always display Mana and Life values above the globes.
- Can launch game in windowed mode with some options (lock mouse/resize/on top/noborder).
- Change the selected language.
- D2 can load all files, even those opened with Microsoft Excel (disabled by default).
- Added the following in-game commands:

Character Stats Commands:
   /page 1 : Show normal stats page (stats page must be opened).
   /page 2 : Show extra stats page (stats page must be opened).
   /page 3 : Show resistance stats page (stats page must be opened).

Windowing Commands:
   /lock : Lock mouse cursor in the window.
   /unlock : Unlock mouse cursor in the window.

Stash Management Commands:
   /renamepage name : Rename current page stash. (If empty, resets name)
   /setindex : Set current stash page as index.
   /setmainindex : Set current stash page as main index.
   /resetindex : Remove index flag on the current stash page.
   /insertpage : Insert a new page after the current page.
   /deletepage : Delete current page if empty.
   /swap page : Swap the content of current stash page with the content of another page.
   /toggle page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.

Other Commands:
   /dlm : Toggle always display mana and life mode.

=============
Known Bugs or Concerns
=============
- It seems that putting Diablo II in Full Screen will cause an exception in D2Direct3D.dll.
  So basically Gardenia only works in Window Mode.
- When using GlideWrapper, any message send operations that result in a visual change will look weird.
  > This affects the 'players 8' message (The message displayed is weird, workaround is to display above
    the head of the character).
  > The color that we set for an indexed page in the stash might be rendered differently in Glide.
    (Workaround: Use a color that is rendered the same in both Direct3D and Glide: Green).

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

Tips for updating to a new version of Diablo II
==============
- Look at each of the library header files and see what types of functions they declare.
  You can find all of the offsets currently being used by Gardenia in their corresponding
  implementation files.
- Search for all references of GetOffsetByAddition and GetOffsetByProc. That should further
  assist with offsets that need to be updated.
- Keep in mind that some offsets are constants and are not dynamically retrieved.