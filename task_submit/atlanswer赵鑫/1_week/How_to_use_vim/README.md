# How to use vim

* Author: atlanswer
* Date: 2018-09-29

According to Wikipedia, Vim (Vi IMproved) is a popular text editor among programmers. Its fancy features are not based on menus, icons or key combinations but express through the command mode.

Vim has several modes, the two commonly used are insert mode and command mode. Vim starts at command mode, use `i`, `a` or `o` to enter insert mode.

* `i` - insert befor the cursor, `I` to insert it before the first non-blank in the line
* `a` - append after the cursor, `A` to append it at the end of the line
* `o` - begin a new line below the cursor then insert text, `O` to begin it above the cursor
* `R` - enter insert mode, but replacing characters rather than inserting

Press `ESC` to go back to command mode.

* `x` - delete the character under or after the cursor, `X` to delete the character before the cursor
* `u` - undo the last command, `U` to undo the whole line
* `CTRL-R` - redo
* `d{motion}` - delete text that moves over
* `{motion}` - k</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;h&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;l</br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;j
* `G` - move to bottom
* `gg` - move to start
* `dd` - delete line
* `p` - puts the previously deleted text after the cursor
* `D` - delete the characters under the cursor until the end of the line
* `r{char}` - replace the the character under the cursor with {char}
* `:/{pattern}` - search forward for {pattern}
* `?` - forward search
* `n` - search the next one
* `N` - search the previous one
* `:w` - write change
* `:q` - quit vim
* `:{command}!` - force

Combine the commands to do more complex things, add a number right after each command means repeat it that times.