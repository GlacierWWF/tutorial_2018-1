# Vim操作
## 之前就会的
> 主要还是一些基本操作
- `:q!`
- `i`
- `:x`
- `w`
- `h`、`l`、`j`、`k`
- `H`、`L`
- `b`
## 新了解的
- 编辑`.vimrc`文件（原理同`.zshrc`/`.bashrc`一致）
- 快速编译运行`.cpp`文件，在`.vimrc`中添加一行：
```
nnoremap <F6> <ESC>:w<CR>:!g++ -std=c++11 % -o /tmp/a.out && /tmp/a.out<CR> 
```
- 用Vandle来管理插件，并试了一些插件（代码补全/格式化等），还在探索中