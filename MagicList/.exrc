if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <expr> <S-Tab> pumvisible() ? "\" : "\=BackwardsSnippet()\"
inoremap <silent> <C-ScrollWheelDown> <C-ScrollWheelDown>:call color_coded#moved()<Insert>
inoremap <silent> <C-ScrollWheelUp> <C-ScrollWheelUp>:call color_coded#moved()<Insert>
inoremap <silent> <S-ScrollWheelDown> <S-ScrollWheelDown>:call color_coded#moved()<Insert>
inoremap <silent> <S-ScrollWheelUp> <S-ScrollWheelUp>:call color_coded#moved()<Insert>
inoremap <silent> <ScrollWheelDown> <ScrollWheelDown>:call color_coded#moved()<Insert>
inoremap <silent> <ScrollWheelUp> <ScrollWheelUp>:call color_coded#moved()<Insert>
inoremap <silent> <SNR>18_AutoPairsReturn =AutoPairsReturn()
map! <S-Insert> <MiddleMouse>
snoremap <silent> 	 i<Right>=TriggerSnippet()
snoremap  b<BS>
snoremap % b<BS>%
snoremap ' b<BS>'
snoremap U b<BS>U
map Y y$
snoremap \ b<BS>\
map \w :w<NL>
snoremap ^ b<BS>^
snoremap ` b<BS>`
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <F9> :TagbarToggle
snoremap <Left> bi
snoremap <Right> a
snoremap <BS> b<BS>
snoremap <silent> <S-Tab> i<Right>=BackwardsSnippet()
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
nnoremap <silent> <C-ScrollWheelDown> <C-ScrollWheelDown>:call color_coded#moved()
nnoremap <silent> <C-ScrollWheelUp> <C-ScrollWheelUp>:call color_coded#moved()
nnoremap <silent> <S-ScrollWheelDown> <S-ScrollWheelDown>:call color_coded#moved()
nnoremap <silent> <S-ScrollWheelUp> <S-ScrollWheelUp>:call color_coded#moved()
nnoremap <silent> <ScrollWheelDown> <ScrollWheelDown>:call color_coded#moved()
nnoremap <silent> <ScrollWheelUp> <ScrollWheelUp>:call color_coded#moved()
map <S-Insert> <MiddleMouse>
inoremap <silent> <expr> 	 pumvisible() ? "\" : "\=TriggerSnippet()\" 
inoremap <silent> 	 =ShowAvailableSnips()
let &cpo=s:cpo_save
unlet s:cpo_save
set autowriteall
set background=dark
set backspace=eol,start,indent
set completefunc=ClangComplete
set completeopt=menuone,preview
set directory=~/.tmp
set fileencodings=ucs-bom,utf-8,default,latin1
set guifont=Monaco\ 11
set guifontwide=Ubuntu\ Mono\ 13
set guioptions=
set guitablabel=%-2.2N%{gettabvar(v:lnum,'title')}
set helplang=cn
set hidden
set hlsearch
set ignorecase
set incsearch
set infercase
set laststatus=2
set mouse=a
set path=.,/usr/include,,,/usr/include/glib-2.0/,/usr/lib/clang/3.8.0/include/
set ruler
set runtimepath=~/.vim,~/.vim/bundle/AutoComplPop,~/.vim/bundle/auto-pairs,~/.vim/bundle/c.vim,~/.vim/bundle/clang_complete,~/.vim/bundle/color-coded,~/.vim/bundle/gruvbox,~/.vim/bundle/nerdtree,~/.vim/bundle/snipmate.vim,~/.vim/bundle/tagbar,~/.vim/bundle/vim-hybrid,~/.vim/bundle/vim-instant-markdown,~/.vim/bundle/vim-project,~/.vim/bundle/vimcdoc,/usr/share/vim/vimfiles,/usr/share/vim/vim80,/usr/share/vim/vimfiles/after,~/.vim/bundle/vim-instant-markdown/after,~/.vim/bundle/snipmate.vim/after,~/.vim/bundle/color-coded/after,~/.vim/after
set showcmd
set showmatch
set smartcase
set statusline=%<%f\ %h%m%r%=%-14.(%l,%c%V%)\ %P\ \ \ \ %{strftime('%H:%M\ and\ %d.%m.%Y')}
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc,.png,.jpg
set termencoding=utf-8
set title
set titlestring=/home/programmatore/test
set viminfo='3,<0,s0,:0,/0,%0,n~/.vim/viminfo
set virtualedit=all
set window=35
" vim: set ft=vim :
