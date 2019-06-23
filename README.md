# tvh
Keep track of your tv shows.

`tvh` is a simple ncurses program to keep track of your tv show episodes. It works by
creating a .`tracker` file containing the last watched episode in every tv show
directory. It also keeps a log of the last watched shows.

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

Installation:

```
git clone REPO
cd tvh
mkdir build && cd build
cmake ..
cmake --build .
cp app/tvh ~/.local/bin/tvh
```

## Usage
`tvh` is meant to be used as a wrapper for your video player.

Point your default video player to tvh or use it from the command line as follows:
```
tvh myvideo.mkv
```

When tvh is launched without arguments: <br/>
If there is a `.tracker` file in the current directory, launch the next episode of
the corresponding show. Otherwise, a menu containing the latest tv shows you watched
pops up. Use vim/arrow keys to navigate, launch the next episode by pressing
l/right arrow. Other keybindings are:

`p` - displays the name of the previously watched episode <br/>
`n` - displays the name of the next episode <br/>
`f` - opens the directory of the episode in a file manager <br/>

## Naming scheme
By default, `tvh` expects your tv shows directories to be structured and named as
follows: `series_name/season_number/episode_file`. For one-season shows the episode files
can be placed directly to the `series_name` folder, a season folder is not required.

Season folders and episodes should follow a naming scheme: <br/>
Season folder names have to *start* with `S{season number:00}` <br/>
eg. `S01`, `S10` <br/>
Episode filenames have to *contain* `E{episode number:00}` <br/>
eg. `S01E01`, `E01`, `S10E10`, `E10` <br/>

This is currently not configurable, but hopefully will be in the future.
