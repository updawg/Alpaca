## Installation (Standalone)

1. Copy all the files in the **`Files`** folder to the root of your Diablo II directory.
2. Start up **`Alpaca.exe`**.
 
## Installation (D2GFEx)

1. Copy all the files in the **`Files`** folder to the root of your Diablo II directory.
2. Open **`D2GFEx.ini`** and add **`Alpaca.dll`** to one of the **`LoadDll`** lines.
3. Start up **`Game.exe`**.

## Installation (Other)

Follow the same steps as the **`D2GFEx`** installation, but add the **`Alpaca.dll`** to
whatever DLL loader you are using. Alpaca has only been tested for Standalone/D2GFEx/or Dark Alliance/Dreamlands
compatibility. It should work with other systems but compatibility is not guaranteed.

## Adding Custom DLLs

1. Open **`Alpaca.ini`**
2. Add the name of the DLL to one of the **`LoadDll`** lines.
3. Start up the game and verify it works.

Alpaca will safely load the DLLs, so if the DLL fails to load, Alpaca will just skip it
and continue attempting to load any remaining DLLs. Check the **`Alpaca.log`** for any
failure messages.

## Troubleshooting

### MSVCP140.dll is Missing or Alpaca seems to not load

If you get this error message, ensure you have the VC++ 2017 Redistributable installed.