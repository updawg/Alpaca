Alpaca 1.4.1 [1.09b]
By Jonathan Vasquez (fearedbliss)
Released on Friday, October 12, 2018
----------------------------------------

Synopsis
=============
Alpaca is an Infinite Stash Mod for Diablo II: Lord of Destruction
that is based off Yohann Nicolas' PlugY 11.02. The main goal of Alpaca
is to be clean and maintainable core with no extra features. The Alpaca
core has been significantly redesigned by currently providing a completely
new module offset loader, drastically less code, and has been massively
refactored. Changes to the Alpaca architecture will continue to improve
over time as more code is refactored, removed, and re-architected. Another
major change is that in order to provide an optimal gaming experience and
improved maintainability, Alpaca only supports a single version of Diablo II.
If people want to use Alpaca on a different version, they only need to focus
on the particular version they want to support without having to worry about
any sort of backwards or forward compatibility.

Alpaca IS compatible with my Cactus (Version Switcher). If you want to use
Alpaca for your 1.09b install but also continue to play other mods or 1.14d,
etc, you can use my version switcher to easily do this. When using Alpaca with
Cactus, Simply point your Cactus profile to the "Alpaca.exe" when launching.
Cactus also automatically isolates your character save files and their stashes
as well (Including the Alpaca Stashes).

Requirements
=============
- Microsoft Visual C++ 2017 Redistributable (x86, x64)

License
=============
All code is licensed under the GPLv3+ since that was the license that Yohann
released PlugY 11.02 under.

Features
=============

Core Features
-----------
- Infinite Personal and Shared Stashes
- Increased Stash Size [10x10]

Stash Management Commands
-----------
/rename <name> : Renames the current stash page. (If left blank, deletes the page name).
/set : Marks the current stash page with an index.
/unset : Removes the current stash page's index.
/setmain : Marks the current stash page as the main index.
/insert : Inserts a new page after the current page.
/delete : Deletes the current stash page if empty.
/swap <page #> : Swaps the content of the current page with the content of the target page.
/toggle <page #> : Swaps the content of the current page with the content of
                   the target page in the opposing shared/personal stash.

Concerns
=============
- This isn't a bug but it is a warning, when playing a LAN game, you should
  avoid the use of the Shared Stash. This is because both players are essentially seeing
  a copy of the shared stash at the point that they joined the multi-player game.
  Since the stashes aren't automatically in-sync with each other, the last player to exit
  the game will be the stash that gets saved. Only use your personal stashes in LAN games
  if you don't want to lose any items.
  
Links
=============
Discord - https://discord.gg/B59qDKy
Cactus - https://github.com/fearedbliss/Cactus
Succulent - https://github.com/fearedbliss/Succulent
Bliss Complete Collection - https://xyinn.org/diablo/Bliss_Complete_Collection.7z