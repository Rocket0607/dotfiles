let g:startify_session_dir = '~/.config/nvim/session'

let g:startify_lists = [
          \ { 'type': 'files',     'header': ['   Files']             },
          \ { 'type': 'dir',       'header': ['   Current Directory '. getcwd()]  },
          \ { 'type': 'sessions',  'header': ['   Sessions']        },
          \ { 'type': 'bookmarks', 'header': ['   Bookmarks']       },
          \ ]

let g:startify_bookmarks = [
            \ { 'i': '~/.config/nvim/init.vim'  },
            \ {'f': '~/.config/fish/config.fish'},
            \ {'a': '~/.config/alacritty/alacritty.yml'},
            \ {'wm': '~/.config/qtile/config.py'}
            \ ]

let g:startify_custom_header = [
  \ '  _  _  ___  _     _      ___         ___ ',
  \ ' | || || __|| |   | |    / _ \       | _ \',
  \ ' | __ || _| | |__ | |__ | (_) |      |   /',
  \ ' |_||_||___||____||____| \___/       |_|_\',
  \ ]
