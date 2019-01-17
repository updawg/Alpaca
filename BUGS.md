## Known Bugs/Limitations

### Picked up item will be lost during character load (If stash contains an item)

If you have items in your stash, and then you pick up an item (and don't place it anywhere),
and save and exit, when you load the game it will be lost. This is an existing PlugY bug that
I wasn't able to fix. I spent a few hours looking around but it will take a way deeper
dive in order to resolve.

### Forwarding characters from previous versions of Diablo II (1.09b -> 1.13d)

If you get a "Unable to enter game. Bad generic file." when entering a game, it means
that you were trying to forward either a character from a previous version of the game
(Such as 1.09b), or a shared stash that was from a previous version, into this current version.
This is not supported. Even if you forward the character with Vanilla D2 (and are able to
play the char with Vanilla D2), the char will not open with this mod. Patches are welcomed
if you really want to support this. An empty character does forward, but I think there is something
going on with the items that character has since normally the normal code will migrate those items
forward (especially 1.09 -> 1.10+).
