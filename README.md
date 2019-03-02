## Alpaca 3.2.0 ([Discord](https://discord.gg/PNJsaPa), [Cactus](https://github.com/fearedbliss/Cactus))
##### Jonathan Vasquez (fearedbliss)
##### Released on Saturday, March 2, 2019

## Synopsis

Alpaca is an Infinite Stash for **`Diablo II: 1.10`** that was based off Yohann Nicolas'
**[PlugY](http://plugy.free.fr/en/index.html) 11.02**. It has been massively refactored,
stabilized, and various features have been implemented, such as full support for **`Diablo II Classic`**, and
compatibility with not only **[Dreamlands](https://d2mods.info/forum/viewtopic.php?t=62020)**,
but also Necrolis' Native OpenGL Diablo II Driver: **[D2GFEx](https://d2mods.info/forum/viewtopic.php?f=5&t=65312)**.

## Compatibility

- [Cactus](https://github.com/fearedbliss/Cactus) - Modern Diablo II Version Switcher
- [D2GFEx](https://d2mods.info/forum/viewtopic.php?f=5&t=65312) - Native OpenGL Driver For Diablo II
- [Dreamlands](https://d2mods.info/forum/viewtopic.php?t=62020) - Diablo II Platform Enhancer

## Requirements

- [Microsoft Visual C++ 2017 Redistributable (x86)](https://aka.ms/vs/15/release/VC_redist.x86.exe)

## License

Released under the GNU General Public License v3 or Later.

## Features

#### Core

- Increased Stash Size to **`(10x10)`**
- **`50`** Additional Stash Pages Per Character
- Custom Library Loading Support **`(Up to 3 Standalone DLLs)`**

#### Stash Management Commands

- **`/rename <name>`** : Renames the current stash page. (If left blank, deletes the page name).
- **`/set`** : Marks the current stash page with an index.
- **`/unset`** : Removes the current stash page's index.
- **`/swap <page #>`** : Swaps the content of the current page with the content of the target page.
- **`/page <page #>`** : Takes you to the corresponding page.
