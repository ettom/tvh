# tvh
Keep track of your tv shows.

`tvh` is a simple ncurses program for keeping track of your tv show episodes. It
works by creating a .`tracker` file containing the last watched episode in every tv
show directory. It also keeps a log of the last watched shows.

## Usage
`tvh` is meant to be used as a wrapper for your video player.

Set `tvh` as your default video player or use it from the command line as follows:
```
tvh myvideo.mkv
```
Now, when you want to watch the next episode of that tv show, you no longer have to
navigate to the directory containing the files and try to remember which episode you
last watched.

When tvh is launched without arguments: <br/>
If there is a `.tracker` file in the current directory, the next episode of the
corresponding show is launched. Otherwise, a menu containing the latest tv shows you
watched pops up. Use vim/arrow keys to navigate, launch the next episode by pressing
`l` / right arrow. Other keybindings are:

• `p` - displays the name of the previously watched episode <br/>
• `n` - displays the name of the next episode <br/>
• `f` - opens the directory of the episode in a file manager <br/>
• `d` - deletes the entry from the history

## Configuration
Edit the core/config.h file and build the program.

You must change the `VIDEO_PLAYER` field to match your video player.
Additionally you can change the other fields to match your setup and needs. These are
pretty self-explanatory.

## Building
Dependencies:

```
cmake
g++-8
ncurses
```

For Ubuntu 18.04 all dependencies can be installed with this command:<br/>
`sudo apt install cmake g++-8 libncurses5-dev`<br/>
It also might be necessary to set g++-8 as the default C++ compiler. On Ubuntu this
can be done with:<br/>
`sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 60`

Installation:

```
git clone https://github.com/ettom/tvh.git
cd tvh
mkdir build && cd build
cmake ..
cmake --build .
cp app/tvh ~/.local/bin/tvh
```

## Naming scheme
By default, `tvh` expects your tv show directories to be structured as follows:
`series_name/season_number/episode_file`. A season directory is not necessarily
required, all the episodes can just be placed into the `series_name` directory.

Season directories and episodes should follow a naming scheme: <br/>
• Season directory names have to *start* with `S{season number:00}` eg. `S01`, `S10` <br/>
• Episode filenames have to *contain* `E{episode number:00}` eg. `S01E01`, `E01`, `S10E10`, `E10` <br/>

This is currently not configurable, but hopefully will be in the future.
