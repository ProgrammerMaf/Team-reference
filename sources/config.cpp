//makefile
mkdir $1
cp -n ./template.cpp $1/$1.cpp
cd $1
vim "$1.cpp"

chmod +x mktask.sh

//vimrc
filetype on
filetype plugin on
filetype indent on
set nocompatible
set autoread
set encoding=utf-8
set fileencoding=utf-8
set termencoding=utf-8
set novisualvell
set t_vb=
set si
set tabstop=4
set shiftwidth=4
set expandtab
set smarttab
set number
set t_Co=256
set noeol
set showcmd
set autoindent
set cindent
set mouse=a
set clipboard=unnamedplus
set incsearch
set autowrite
set iminsert=0
set imsearch=0
syntax on
colorscheme darkblue
map <leader> gf :e <cfile><cr>
map <Space> :! <CR>
autocmd FileType python map <F5> :w\|!time python3 "%" <CR>
autocmd FileType cpp map <F9> :w\|!g++ -std=c++11 -Wall -Wextra -g -O2
	-Wno-unused-result -DLOCAL "%" -o "%:r" <CR>
autocmd FileType cpp map <C-F9> :w\|!g++ -std=c++11 -Wall -Wextra -g -O2
	-Wno-unused-result "%" -o "%:r" <CR>
autocmd FileType cpp map <F7> :! time ./":%r" < input.txt > output.txt <CR>
autocmd FileType cpp map <F8> :! time ./":%r" < input.txt <CR>
autocmd FileType cpp map <F5> :! time ./":%r" <CR>
highlight lCursor guifg=NONE guibg=Cyan

//template.cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long lint;
typedef long double ldouble;

#define sz(v) ((int) (v).size())
#define For(i, n) for (int (i) = 0; (i) < (n); (i)++)
#define all(v) (v).begin(), (v).end()

template <class T>
string to_string(T arr, int len = 1e9) {
    stringstream ss;
    int i = 0;
    for (auto item: arr) {
        ss << item << ' ';
        if (++i == len)
            break;
    }
    return ss.str();
}

int main() {
#ifndef LOCAL
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#endif
    
}
