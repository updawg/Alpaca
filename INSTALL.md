## Installation (Standalone)

1. Copy all the files in the **`Files`** folder to the root of your Diablo II directory.
2. Start up **`Alpaca.exe`**.
 
## Installation (D2GFEx)

1. Copy all the files in the **`Files`** folder to the root of your Diablo II directory.
2. Open **`D2GFEx.ini`** and add **`Alpaca.dll`** to one of the **`LoadDll`** lines.
3. Start up **`Game.exe`**.

## Installation (Other)

Follow the same steps as the **`D2GFEx`** installation, but add the **`Alpaca.dll`** to
whatever DLL loader you are using. Alpaca has only been tested for compatibility with
the Alpaca Launcher and D2GFEx. It should work with other systems but compatibility
is not guaranteed.

## Troubleshooting

### MSVCP140.dll is Missing or Alpaca seems to not load

If you get this error message, ensure you have the VC++ 2017 Redistributable installed.