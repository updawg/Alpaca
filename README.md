## Alpaca 3.0.2 ([Discord](https://discord.gg/PNJsaPa), [Cactus](https://github.com/fearedbliss/Cactus))
##### Jonathan Vasquez (fearedbliss)
##### Released on Wednesday, January 16, 2019

## Synopsis

Alpaca is an Infinite Stash Mod for Diablo II: Lord of Destruction
that is based off Yohann Nicolas' PlugY 11.02. It is a cleaned up,
re-architected, and stabilized version of PlugY that is designed for
use exclusively with Necrolis' D2GFEx.

Finally, Alpaca IS compatible with my [Diablo II Version Switcher: Cactus](https://github.com/fearedbliss/Cactus).
If you want to use Alpaca for your 1.10f install (but also want to continue to play
other mods, versions, etc), you can use Cactus. When using Alpaca with Cactus,
Simply point your Cactus Platform to the "Alpaca.exe" when launching. Cactus also
automatically isolates your character save files and their stashes as well
(Including the Alpaca Stashes).

## Requirements

- Microsoft Visual C++ 2017 Redistributable (x86, x64)

## Features

### Alpaca Features

- Infinite Personal and Shared Stashes (Expansion)
- Increased Stash Size [10x10] (Expansion)
- Items will now display their Item Level.

### Stash Management Commands

- `/rename <name>` : Renames the current stash page. (If left blank, deletes the page name).
- `/set` : Marks the current stash page with an index.
- `/unset` : Removes the current stash page's index.
- `/setmain` : Marks the current stash page as the main index.
- `/insert` : Inserts a new page after the current page.
- `/delete` : Deletes the current stash page if empty.
- `/page <page #>` : Takes you to the corresponding page.
- `/swap <page #>` : Swaps the content of the current page with the content of the target page.
