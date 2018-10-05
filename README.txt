Alpaca - 1.30
Jonathan Vasquez <jon@xyinn.org>
Released under the GPLv3+
Project based off Yohann Nicolas' PlugY 11.02
Current Supported Version: 1.09b

=============
Synopsis
=============
Alpaca is a Diablo II infinite stash mod that is forked from
Yohann Nicolas' PlugY 11.02. My mod removes all excess components
and provides a much slimmer and maintainable mod that is easier
to upgrade to new Blizzard versions, through code reduction,
massive refactoring, and redesign.

In order to increase the maintainability of the mod and provide an
optimal experience, Alpaca now only supports a single Diablo II version.

Alpaca IS compatible with Cactus. So if you want to have separate stashes
while you are time traveling, you can. Just point Cactus to use "Alpaca.exe"
rather than "Game.exe". Cactus will automatically point the save directory
to the desired version of D2 you want to play (and Alpaca saves the stashes
with your characters as well).

Cactus Project Page - https://github.com/fearedbliss/Cactus

=============
Features
=============

Core Features
----------------
- Infinite stash storage space (Personal Stash)
- Infinite shared stash storage space (Shared Stash)
- Increase the stash to 10x10 squares.

Stash Management Commands:
   /renamepage name : Rename current page stash. (If empty, resets name)
   /setindex : Set current stash page as index.
   /unsetindex : Remove index flag on the current stash page.
   /setmainindex : Set current stash page as main index.
   /insertpage : Insert a new page after the current page.
   /deletepage : Delete current page if empty.
   /swap page : Swap the content of current stash page with the content of another page.
   /toggle page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.

=============
Known Bugs or Concerns
=============
- When using GlideWrapper, any message send operations that result in a visual change will look weird.
  > This affects the 'players 8' message (The message displayed is weird, workaround is to display above
    the head of the character).
  > The color that we set for an indexed page in the stash might be rendered differently in Glide.
    (Workaround: Use a color that is rendered the same in both Direct3D and Glide: Green).
- This isn't a bug but a concern, beware of using the shared stash in TCP/IP,
  the last person that saves the game (on the machine that has the particular shared stash)
  will win. Meaning that if you have a LAN game with two of your own characters, then the last
  character that leaves the game on your machine will trigger the stash saving code. If in doubt,
  always use the personal stash in a LAN game and transfer after you are done.

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

Tips for working with Alpaca (in Visual Studio 2017)
=============
- Release Mode and Debug Mode may yield different results!
  Debug Mode is what I use by default for my releases.
- Don't use /GS (Security Check)
- Don't use compiler optimizations
- Use the debugger and compile debugging symbols (.PDB)
- Use static classes and pointer to static functions in static classes
  if attempting to put naked functions in a class. C++ ISO standards
  does not support getting a function pointer to a instanced class function
  and calling it.
  
The reason for the above is because since the code uses a lot of
naked functions, there are times when the code directly maybe cause
an access violation, or something that could be perceived as an overflow.
Sometimes the code only works in Release mode but doesn't work in Debug mode.

Tips for updating to a new version of Diablo II
==============
- Look at each of the library header files and see what types of functions they declare.
  You can find all of the offsets currently being used by Alpaca in their corresponding
  implementation files.
- Search for all references of GetOffsetByAddition and GetOffsetByProc. That should further
  assist with offsets that need to be updated.
- Keep in mind that some offsets are constants and are not dynamically retrieved.
- There are still offsets scattered around the code that haven't yet been consolidated
  into a centralized location (Install Functions, etc, Look for: mem_seek)