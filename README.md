## Alpaca
##### By: Jonathan Vasquez (fearedbliss)
##### Build: 2019-12-16-1702

## Synopsis

Alpaca is an Infinite Stash for **`Diablo II: 1.13d`** that was based off Yohann Nicolas'
**[PlugY](http://plugy.free.fr/en/index.html) 11.02**. It has been massively refactored,
stabilized, and has full support for **`Diablo II Classic`**.

## Compatibility

- [Cactus](https://github.com/fearedbliss/Cactus) -
  A Modern Diablo II Version Switcher (Contains: Singling/Succulent/Alpaca)
- [Singling](https://github.com/fearedbliss/Cactus/blob/master/README-SINGLING.md) -
  A collection of non-gameplay modifications and fixes in
  order to improve the Vanilla Diablo II Single Player Experience.
- [Succulent](https://github.com/fearedbliss/Cactus/blob/master/README-SUCCULENT.md) -
  A **`Diablo II: 1.13d`** Single Player Modification that tailors the game to the
  Single Player Experience. Succulent contains strong influence from a variety of
  games such as **`Diablo I`**, **`Diablo II (1.00 - 1.09b)`**, **`Diablo III`**,
  and **[`It Lurks Below`](http://www.itlurksbelow.com/)**.

## Requirements

- [Microsoft Visual C++ 2019 Redistributable (x86)](https://aka.ms/vs/16/release/VC_redist.x86.exe)

## License

Released under the [GNU General Public License v3](LICENSE.md) or Later.

## Features

#### Core

- Increased Stash Size to **`(10x10)`**
- **`100`** Additional Stash Pages Per Character
- Diablo II **`Classic`** and **`Expansion`** Support
- Display Item Level Support
- Tailored for **`Character-based Solo Self Found`**, thus no **`Shared Stash`**.
  - Read the **`Solo Self Found (SSF)`** section below to allow for a
    **`Player-based Solo Self Found`** workflow, which allows item transfers
    between your own characters.

#### Stash Management Commands

- **`/rename <name>`** : Renames the current stash page. (If left blank, deletes the page name).
- **`/set`** : Marks the current stash page with an index.
- **`/unset`** : Removes the current stash page's index.
- **`/swap <page #>`** : Swaps the content of the current page with the content of the target page.
- **`/page <page #>`** : Takes you to the corresponding page.

## Solo Self Found (SSF)

Alpaca has been tailored specifically for **`Character-based Solo Self Found`**,
and thus contains no shared stash. Another reason the shared stash was removed
was to prevent race conditions that could happen in LAN games in which you could
lose items. The definitions for **`Character-based`** and **`Player-based`** are
as follows:

### Character-based Solo Self Found

- You don't play with any other player or character (including yourself).
- You don't trade with any other player or character (including yourself).
- All the items your character has was found or crafted by that character
  specifically.

This means that all of your characters are completely isolated from each other
and each character alone determines their own fate through their own hard work
and struggle. No contact or sharing of items (or anything else) is allowed
between characters. **`Every character is in their own parallel world or
universe.`**

### Player-based Solo Self Found

- You don't play with any other player.
- You don't trade with any other player.
- All the items your character has was found or crafted by that character
  or by any other character you've played that has also followed these rules.

Thus this allows you to twink all of your characters with your own progress
as a player while making sure that none of them are tainted by stuff that
other players have done. Overall, in this mode, you are isolating yourself from
other players, but not from yourself. Since player progress is allowed to be
shared between your characters, this would logically mean that not only sharing
items between your characters is allowed, but also waypoint sharing, power
leveling, rushing is also allowed. **`Every character is sharing the same world
or universe and thus they can share tools, knowledge, and resources with each
other.`**

### Enabling Player-based Solo Self Found w/ Singling

Since Alpaca doesn't include a shared stash, you can still transfer items
between your characters by taking advantage of my Singling mod that allows you
to open up multiple instances of Diablo II (No extra cd-key needed since we are
not going to go online). This allows you to make a LAN game (**`127.0.0.1`** or
**`localhost`**) where all of your characters that want to transfer items can
join. The nice thing about this is that it is safe and no data loss will occur.
Singling only contains non-gameplay modifications (i.e: CPU Fix, Enabling
Hardcore Character Creation, Ladder Runewords, Multiple Instances of Diablo II,
etc). You can get the Singling files for 1.13d in the Cactus repo. For the full
list of Singling features, please visit the link for Singling listed in the
**`Compatibility`** section above. If you are playing my Succulent mod, Alpaca
and Singling are already included and working out of the box.

## Screenshots

![Main Menu](https://i.imgur.com/JMHvYZg.jpg)

![Classic](https://i.imgur.com/v8vPURk.jpg)

![Expansion](https://i.imgur.com/xGNrTai.jpg)

![Page Names / Indexed Pages](https://i.imgur.com/3GF3mJ5.jpg)

![Item Level](https://i.imgur.com/jMrFhK3.jpg)