# -*- coding: utf-8 -*-
import os
import re
import socket
import subprocess
from libqtile import qtile
from libqtile.config import KeyChord, Key, Screen, Group, Drag, Click, ScratchPad, DropDown
from libqtile.command import lazy
from libqtile import layout, bar, widget, hook
from libqtile.lazy import lazy
from typing import List  # noqa: F401

mod = "mod4"                                     # Sets mod key to SUPER/WINDOWS
myTerm = "alacritty"                             # My terminal of choice
myConfig = "/home/rohitk/.config/qtile/config.py"    # The Qtile config file location

keys = [
         ### The essentials
         Key([mod], "Return",
             lazy.spawn(myTerm),
             desc='Launches My Terminal'
             ),
         Key([mod, "shift"], "Return",
             lazy.spawn("dmenu_run"),
             # lazy.spawn("rofi -show drun -yoffset 5  -config ~/.config/rofi/themes/dt-dmenu.rasi -display-drun \"Run: \" -drun-display-format \"{name}\""),
             desc='Run Launcher'
             ),
         Key([mod], "Tab",
             lazy.next_layout(),
             desc='Toggle through layouts'
             ),
         Key([mod, "shift"], "z",
             lazy.window.kill(),
             desc='Kill active window'
             ),
         Key([mod, "shift"], "r",
             lazy.restart(),
             desc='Restart Qtile'
             ),
         Key([mod, "shift"], "q",
             lazy.spawn("arcolinux-logout"),
             desc='Shutdown Qtile'
             ),
         ### Window controls
         Key([mod], "k",
             lazy.layout.down(),
             desc='Move focus down in current stack pane'
             ),
         Key([mod], "j",
             lazy.layout.up(),
             desc='Move focus up in current stack pane'
             ),
         Key([mod, "shift"], "k",
             lazy.layout.shuffle_down(),
             desc='Move windows down in current stack'
             ),
         Key([mod, "shift"], "j",
             lazy.layout.shuffle_up(),
             desc='Move windows up in current stack'
             ),
         Key([mod], "h",
             lazy.layout.grow(),
             lazy.layout.increase_nmaster(),
             desc='Expand window (MonadTall), increase number in master pane (Tile)'
             ),
         Key([mod], "l",
             lazy.layout.shrink(),
             lazy.layout.decrease_nmaster(),
             desc='Shrink window (MonadTall), decrease number in master pane (Tile)'
             ),
         Key([mod], "n",
             lazy.layout.normalize(),
             desc='normalize window size ratios'
             ),
         Key([mod], "m",
             lazy.layout.maximize(),
             desc='toggle window between minimum and maximum sizes'
             ),
         Key([mod, "shift"], "f",
             lazy.window.toggle_floating(),
             desc='toggle floating'
             ),
         Key([mod, "shift"], "m",
             lazy.window.toggle_fullscreen(),
             desc='toggle fullscreen'
             ),
         ### Stack controls
         Key([mod, "shift"], "space",
             lazy.layout.rotate(),
             lazy.layout.flip(),
             desc='Switch which side main pane occupies (XmonadTall)'
             ),
         Key([mod], "space",
             lazy.layout.next(),
             desc='Switch window focus to other pane(s) of stack'
             ),
         Key([mod, "control"], "Return",
             lazy.layout.toggle_split(),
             desc='Toggle between split and unsplit sides of stack'
             ),
         ### Opening Apps
         Key([mod], "f",
             lazy.spawn(myTerm+" -e sh ranger"),
             desc='open ranger file manager'
             ),
         Key([mod], "a",
             lazy.spawn(myTerm+" -e pulsemixer"),
             desc='open pulsemixer'
             ),
        Key([mod], "e",
            lazy.spawn("emacsclient -c"),
            desc="open emacs"
            ),
        Key([mod], "d",
            lazy.group['5'].dropdown_toggle('term'),
            desc='Launches Dropdown'
            ),
        KeyChord([mod], "b", [
            Key([mod], "q",
                lazy.spawn("qutebrowser"),
                desc="open qutebrowser"),
            Key([mod], "f",
                lazy.spawn("firefox"),
                desc="open firefox"),
        ]),
        ### Dmenu Scripts
        Key([mod], "s",
            lazy.spawn("./dmscripts/dmsearch"),
            desc="search with dmenu"
            ),
        Key([mod], "c",
            lazy.spawn("./dmscripts/dmconf"),
            desc="search configs with dmenu"
            ),
        Key([mod], "p",
            lazy.spawn("./dmscripts/dmproj"),
            desc="search projects with dmenu"
            ),
        Key([mod, "shift"], "d",
            lazy.spawn("./dmscripts/dmkill"),
            desc="Kill programs with dmenu"
            ),
        Key([mod, "shift"], "s",
            lazy.spawn("./dmscripts/dmscrot"),
            desc="screenshot with dmenu"
            ),
        Key([mod, "shift"], "t",
            lazy.spawn("./dmscripts/dmtodo"),
            desc="list all todos with dmenu"
            ),
        ### Music
        Key(
            [], "XF86AudioPlay",
            lazy.spawn("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Play")
            ),
        Key(
            [], "XF86AudioPause",
            lazy.spawn("dbus-send --print-reply --dest=org.mpris.MediaPlayer2.spotify /org/mpris/MediaPlayer2 org.mpris.MediaPlayer2.Player.Pause")
            ),
        ### Special
        KeyChord(["mod1"], "space", [
            Key([], "f",
                lazy.group["1"].toscreen(),
                desc="easy access to work workspace")
        ])
]

groups = [
]

# FOR QWERTY KEYBOARDS
group_names = ["1", "2", "3", "4", "7", "8", "9", "0"]

# FOR AZERTY KEYBOARDS
#group_names = ["ampersand", "eacute", "quotedbl", "apostrophe", "parenleft", "section", "egrave", "exclam", "ccedilla", "agrave",]

#group_labels = ["1 ", "2 ", "3 ", "4 ", "5 ", "6 ", "7 ", "8 ", "9 ", "0",]
group_labels = ["WORK", "WORK2", "DEV", "DEV2", "NOTWORK", "CONFIG", "OTHER", "STORAGE"]
#group_labels = ["Web", "Edit/chat", "Image", "Gimp", "Meld", "Video", "Vb", "Files", "Mail", "Music",]

group_layouts = ["monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall", "monadtall"]
#group_layouts = ["monadtall", "matrix", "monadtall", "bsp", "monadtall", "matrix", "monadtall", "bsp", "monadtall", "monadtall",]

for i in range(len(group_names)):
    groups.append(
        Group(
            name=group_names[i],
            layout=group_layouts[i].lower(),
            label=group_labels[i],
        )
    )

groups.append(
        ScratchPad(
            name="5",
            dropdowns=[DropDown("term", "alacritty", opacity=1.0, height=0.5)]
        )
)

for i in groups:
    keys.extend([

#CHANGE WORKSPACES
        Key([mod], i.name, lazy.group[i.name].toscreen()),
        Key(["mod1"], "Tab", lazy.screen.next_group()),
        Key(["mod1", "shift"], "Tab", lazy.screen.prev_group()),

# MOVE WINDOW TO SELECTED WORKSPACE 1-10 AND STAY ON WORKSPACE
        #Key([mod, "shift"], i.name, lazy.window.togroup(i.name)),
# MOVE WINDOW TO SELECTED WORKSPACE 1-10 AND FOLLOW MOVED WINDOW TO WORKSPACE
        Key([mod, "shift"], i.name, lazy.window.togroup(i.name) , lazy.group[i.name].toscreen()),
    ])

layout_theme = {"border_width": 3,
                "margin": 4,
                "border_focus": "243e95",
                "border_normal": "191a23"
                }

layouts = [
    #layout.MonadWide(**layout_theme),
    #layout.Bsp(**layout_theme),
    ##layout.Stack(stacks=2, **layout_theme),
    #layout.Columns(**layout_theme),
    #layout.RatioTile(**layout_theme),
    #layout.VerticalTile(**layout_theme),
    #layout.Matrix(**layout_theme),
    layout.Zoomy(**layout_theme),
    layout.MonadTall(**layout_theme),
    layout.Max(**layout_theme),
    #layout.Tile(shift_windows=True, **layout_theme),
    #layout.Stack(num_stacks=2),
    #layout.TreeTab(
    #     font = "Ubuntu",
    #     fontsize = 10,
    #     sections = ["FIRST", "SECOND"],
    #     section_fontsize = 11,
    #     bg_color = "141414",
    #     active_bg = "90C435",
    #     active_fg = "000000",
    #     inactive_bg = "384323",
    #     inactive_fg = "a0a0a0",
    #     padding_y = 5,
    #     section_top = 10,
    #     panel_width = 320
    #     ),
]

colors = [["#21242b", "#21242b"], # panel background
          ["#575d73", "#575d73"], # background for current screen tab
          ["#ffffff", "#ffffff"], # font color for group names
          ["#b50000", "#b50000"], # border line color for current tab
          ["#282c34", "#282c34"], # border line color for other tab and odd widgets
          ["#243e95", "#243e95"], # color for the even widgets
          ["#adb3bc", "#adb3bc"]] # window name

prompt = "{0}@{1}: ".format(os.environ["USER"], socket.gethostname())

##### DEFAULT WIDGET SETTINGS #####
widget_defaults = dict(
    font="Ubuntu Mono",
    fontsize = 12,
    padding = 2,
    background=colors[2]
)
extension_defaults = widget_defaults.copy()

def init_widgets_list():
    widgets_list = [
              widget.TextBox(
                       text="RK", 
                       background=colors[0],
                       foreground = colors[2],
                       font = "Ubuntu Bold",
                       fontsize = 15,
                       padding = 7,
                       mouse_callbacks = {'Button1': lambda: lazy.spawn('arcologout')},
                       ),
              widget.Sep(
                       linewidth = 1,
                       padding = 6,
                       foreground = colors[4],
                       background = colors[0]
                       ),
              widget.GroupBox(
                       font = "Ubuntu Bold",
                       fontsize = 9,
                       margin_y = 3,
                       margin_x = 0,
                       padding_y = 5,
                       padding_x = 3,
                       borderwidth = 3,
                       active = colors[2],
                       inactive = colors[2],
                       rounded = True,
                       highlight_color = colors[1],
                       highlight_method = "line",
                       this_current_screen_border = colors[5],
                       this_screen_border = colors [4],
                       other_current_screen_border = colors[0],
                       other_screen_border = colors[0],
                       foreground = colors[2],
                       background = colors[0]
                       ),
              widget.Prompt(
                       prompt = prompt,
                       font = "Ubuntu Mono",
                       padding = 10,
                       foreground = colors[3],
                       background = colors[1]
                       ),
              widget.Sep(
                       linewidth = 0,
                       padding = 175,
                       foreground = colors[2],
                       background = colors[0]
                       ),
              widget.WindowName(
                       foreground = colors[6],
                       background = colors[0],
                       padding = 0
                       ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.TextBox(
                       text = "🌡",
                       padding = 0,
                       foreground = colors[2],
                       background = colors[5],
                       fontsize = 11
                       ),
              widget.ThermalSensor(
                       foreground = colors[2],
                       background = colors[5],
                       threshold = 90,
                       padding = 10
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = -19,
                          width = 15
                      ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.TextBox(
                       text = " ⟳",
                       padding = 2,
                       foreground = colors[2],
                       background = colors[4],
                       fontsize = 14
                       ),
              widget.CheckUpdates(
                       update_interval = 1800,
                       distro = "Arch_checkupdates",
                       mouse_callbacks = {'Button1': lambda: qtile.cmd_spawn(myTerm + ' -e sudo pacman -Syu')},
                       display_format = "{updates} updates",
                       foreground = colors[2],
                       background = colors[4]
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = -11,
                          width = 19
                      ),
              widget.Sep(
                       linewidth = 0,
                       padding = 5,
                       foreground = colors[4],
                       background = colors[0]
              ),  
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.TextBox(
                       text = " 🖬",
                       foreground = colors[2],
                       background = colors[5],
                       padding = 0,
                       fontsize = 14
                       ),
              widget.Memory(
                       foreground = colors[2],
                       background = colors[5],
                       mouse_callbacks = {'Button1': lambda: qtile.cmd_spawn(myTerm + ' -e htop')},
                       padding = 10
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = -19,
                          width = 15
                      ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.TextBox(
                      text = " Vol:",
                       foreground = colors[2],
                       background = colors[4],
                       padding = 0
                       ),
              widget.Volume(
                       foreground = colors[2],
                       background = colors[4],
                       padding = 10
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = -19,
                          width = 15
                      ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.CurrentLayoutIcon(
                       custom_icon_paths = [os.path.expanduser("~/.config/qtile/icons")],
                       foreground = colors[0],
                       background = colors[5],
                       padding = 0,
                       scale = 0.7
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = -14,
                          width = 15
                      ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = 0,
                          width = 18
                      ),
              widget.Clock(
                       foreground = colors[2],
                       background = colors[4],
                       format = "%A, %B %d  [ %H:%M ]"
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[4],
                          background = colors[0],
                          fontsize = 59,
                          padding = -14,
                          width = 15
                      ),
              widget.Sep(
                       linewidth = 1,
                       padding = 10,
                       foreground = colors[4],
                       background = colors[0],
                       size_percent = 150
                       ),
              widget.TextBox(
                          text = u"\u25D6",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 49,
                          padding = 0,
                          width = 15
                      ),
              widget.Systray(
                       background = colors[5],
                       padding = 5
                       ),
              widget.TextBox(
                          text = u"\u25D7",
                          foreground = colors[5],
                          background = colors[0],
                          fontsize = 59,
                          padding = -12,
                          width = 14
                      ),
              ]
    return widgets_list

def init_widgets_screen1():
    widgets_screen1 = init_widgets_list()
    return widgets_screen1                       # Slicing removes unwanted widgets on Monitors 1,3

def init_widgets_screen2():
    widgets_screen2 = init_widgets_list()
    return widgets_screen2                       # Monitor 2 will display all widgets in widgets_list

def init_screens():
    return [Screen(top=bar.Bar(widgets=init_widgets_screen1(), opacity=1.0, size=24)),
            Screen(top=bar.Bar(widgets=init_widgets_screen2(), opacity=1.0, size=20)),
            Screen(top=bar.Bar(widgets=init_widgets_screen1(), opacity=1.0, size=20))]

if __name__ in ["config", "__main__"]:
    screens = init_screens()
    widgets_list = init_widgets_list()
    widgets_screen1 = init_widgets_screen1()
    widgets_screen2 = init_widgets_screen2()

def window_to_prev_group(qtile):
    if qtile.currentWindow is not None:
        i = qtile.groups.index(qtile.currentGroup)
        qtile.currentWindow.togroup(qtile.groups[i - 1].name)

def window_to_next_group(qtile):
    if qtile.currentWindow is not None:
        i = qtile.groups.index(qtile.currentGroup)
        qtile.currentWindow.togroup(qtile.groups[i + 1].name)

def window_to_previous_screen(qtile):
    i = qtile.screens.index(qtile.current_screen)
    if i != 0:
        group = qtile.screens[i - 1].group.name
        qtile.current_window.togroup(group)

def window_to_next_screen(qtile):
    i = qtile.screens.index(qtile.current_screen)
    if i + 1 != len(qtile.screens):
        group = qtile.screens[i + 1].group.name
        qtile.current_window.togroup(group)

def switch_screens(qtile):
    i = qtile.screens.index(qtile.current_screen)
    group = qtile.screens[i - 1].group
    qtile.current_screen.set_group(group)

mouse = [
    Drag([mod], "Button1", lazy.window.set_position_floating(),
         start=lazy.window.get_position()),
    Drag([mod], "Button3", lazy.window.set_size_floating(),
         start=lazy.window.get_size()),
    Click([mod], "Button2", lazy.window.bring_to_front())
]

dgroups_key_binder = None
dgroups_app_rules = []  # type: List
main = None
follow_mouse_focus = True
bring_front_click = False
cursor_warp = False

floating_layout = layout.Floating(float_rules=[
    {'wmclass': 'confirm'},
    {'wmclass': 'dialog'},
    {'wmclass': 'download'},
    {'wmclass': 'error'},
    {'wmclass': 'file_progress'},
    {'wmclass': 'notification'},
    {'wmclass': 'splash'},
    {'wmclass': 'toolbar'},
    {'wmclass': 'confirmreset'},  # gitk
    {'wmclass': 'makebranch'},  # gitk
    {'wmclass': 'maketag'},  # gitk
    {'wname': 'branchdialog'},  # gitk
    {'wname': 'pinentry'},  # GPG key password entry
    {'wmclass': 'ssh-askpass'},  # ssh-askpass
])
auto_fullscreen = True
focus_on_window_activation = "smart"

@hook.subscribe.startup_once
def start_once():
    home = os.path.expanduser('~')
    subprocess.call([home + '/.config/qtile/autostart.sh'])

# XXX: Gasp! We're lying here. In fact, nobody really uses or cares about this
# string besides java UI toolkits; you can see several discussions on the
# mailing lists, GitHub issues, and other WM documentation that suggest setting
# this string if your java app doesn't work correctly. We may as well just lie
# and say that we're a working one by default.
#
# We choose LG3D to maximize irony: it is a 3D non-reparenting WM written in
# java that happens to be on java's whitelist.
wmname = "LG3D"
