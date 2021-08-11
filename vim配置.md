
set expandtab一定要有，这个将tab变为空格的，如果没有，多人push的时候格式不对，tab不一样，不要tab符
其它工具可以设置前景色好看一点
```
set number
set hlsearch
set ts=4
set sw=4
set expandtab
nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>i :cs find i <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
let Tlist_WinWidth=50
set autoindent
set smartindent
nnoremap <silent> <F3> :TlistToggle<CR>
set nocscopeverbose


set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8
set fileformats=unix
set encoding=prc
```
这个是cygwin的bash的配置，颜色没有，还有cscope默认跳到vi不会跳到vim
```
alias grep='grep --color=auto'
alias ls='ls --color=auto'
alias d='cd /cygdrive/c/Users/Administrator/Desktop/'
export CSCOPE_EDITOR=vim
export EDITOR=vim
alias c='cscope -d'

```
