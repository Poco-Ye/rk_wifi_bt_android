set expandtab一定要有，这个将tab变为空格的，如果没有，多人push的时候格式不对，tab不一样，不要tab符
其它工具可以设置前景色好看一点

这个是在java目录上进行过滤的
`find ./ -name "*"> cscope.files&&sed -i '/.git\|cscope.files/d' cscope.files`
`alias cs="find ./ -name \"*\" >cscope.files && sed -i '/.git\\|cscope.files/d' cscope.files"`
## 安装tab补全插件
```
https://www.vim.org/scripts/script.php?script_id=1643
下载supertab.vmb
vim supertab.vmb
:source %
安装
```
## vim配置注释
```
set number      //行号
set hlsearch    //按'/'查找的时候高亮
set ts=4        //按tab是4个空格
set sw=4        //按'>>'缩进指令是4个空格
set expandtab   //重点 这个必须要有，否则玩完，把tab变空格，在哪提交都不会看到格式不对
nmap <C-\>s :cs find s <C-R>=expand("<cword>")<CR><CR>  //这个是cscope用的 我其实不多用 因为没有记录 我还是喜欢cs find 的方式
nmap <C-\>g :cs find g <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>c :cs find c <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>t :cs find t <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>e :cs find e <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>f :cs find f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>i :cs find i <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>d :cs find d <C-R>=expand("<cword>")<CR><CR>
let Tlist_WinWidth=50  //这个是左边的列表宽度
set autoindent        //自动对齐 学习vs code先进工具
set smartindent       //自动对齐 学习vs code先进工具
nnoremap <silent> <F3> :TlistToggle<CR>  //按F3打开左边列表
map <F9> :!ctags -R&&cscope -Rb<CR>:cs reset<CR><CR>    //这个是刷新cscope数据库，改了很多的时候刷新一下
set nocscopeverbose //cygwin使用 不加 add不了cscoupe.out
let g:SuperTabDefaultCompletionType = "<c-n>"  //从头开始检索，学习先进cs code功能，类似ctrl + n 这个需要安装插件supertab.vim，直接按tab进行补全


set fileencodings=utf-8,gb2312,gbk,gb18030      //识别中文
set termencoding=utf-8
set fileformats=unix
set encoding=prc
```
## vim配置表
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
map <F9> :!ctags -R&&cscope -Rb<CR>:cs reset<CR><CR>
set nocscopeverbose
let g:SuperTabDefaultCompletionType = "<c-n>"


set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8
set fileformats=unix
set encoding=prc
```
## cygwin配置
这个是cygwin的bash的配置，颜色没有，还有cscope默认跳到vi不会跳到vim
```
alias grep='grep --color=auto'
alias ls='ls --color=auto'
alias d='cd /cygdrive/c/Users/Administrator/Desktop/'
export CSCOPE_EDITOR=vim
export EDITOR=vim
alias c='cscope -d'
alias cs="find ./ -name \"*\" >cscope.files && sed -i '/.git\\|cscope.files/d' cscope.files"

```
