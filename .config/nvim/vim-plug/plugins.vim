" auto-install vim-plug
if empty(glob('~/.config/nvim/autoload/plug.vim'))
	silent !curl -fLo ~/.config/nvim/autoload/plug.vim --create-dirs
		\ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
	"autocmd VimEnter * PlugInstall
	"autocmd VimEnter * PlugInstall | source $MYVIMRC
endif

call plug#begin('~/.config/nvim/autoload/plugged')

	" File Explorer
	Plug 'scrooloose/NERDTree'
	" Auto pairs for '(' '[' '{'
	Plug 'jiangmiao/auto-pairs'
  	" Intellisense
	Plug 'neoclide/coc.nvim', {'branch': 'release'}
	" Status Bar
	Plug 'vim-airline/vim-airline'
	Plug 'vim-airline/vim-airline-themes'
	" Highlighting Colours
	Plug 'ap/vim-css-color'
	" VimWiki
	Plug 'vimwiki/vimwiki'
	" Emmet
	Plug 'mattn/emmet-vim'
  " Sneak
  Plug 'justinmk/vim-sneak'  
  " Startify start screen
  Plug 'mhinz/vim-startify'
  " Dartlang support
  Plug 'dart-lang/dart-vim-plugin'
  " Flutter hot reload
  Plug 'reisub0/hot-reload.vim'
  call plug#end()
