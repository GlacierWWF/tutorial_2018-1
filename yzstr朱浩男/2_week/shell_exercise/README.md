# Shell Exercises
- **Auther** : yzstr朱浩男
- **Revised** : yzstr朱浩男
- **Version** : 1.0.0
- **Date** : 2018-10-04
- **Abstrace** : Shell Exercises

## Task 1
### Description
- Pass two integers to the shell.
- show the amount, difference, product, division in order.
### Run&Output
```
➜  shell_exercise git:(aero_task) ✗ zsh task_1.sh 5 9
14
-4
45
0
```
## Task 2
### Description
- Make a directory `/tmp/scripts`.
- move to `/tmp/scripts`.
- copy `/etc/pam.d` to `/tmp/scripts` and rename it to `test`.
- change the owner of `test` and its content to `redhat`.
- Revoke the authority of `test` for anyone else.
### Run&Output
``` bash
➜  shell_exercise git:(aero_task) ✗ tree /tmp
/tmp
├── VSCode Crashes
├── a.out
├── appInsights-node
├── gnome-software-4PSVPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-HC8KPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-LCD1PZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-VXVLPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-Z86WPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── mozilla_root0
│   └── code_1.27.2-1536736588_amd64.deb
├── pulse-PKdhtXMmr18n
├── pulse-hn5F47vSvQ0r
├── runtime-root
├── tmp54e0qvir
│   └── apt.conf
└── tmpaddon

12 directories, 9 files
➜  shell_exercise git:(aero_task) ✗ zsh task_2.sh
mkdir: created directory '/tmp/scripts'$'\r'
➜  shell_exercise git:(aero_task) ✗ tree /tmp
/tmp
├── VSCode Crashes
├── a.out
├── appInsights-node
├── gnome-software-4PSVPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-HC8KPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-LCD1PZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-VXVLPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-Z86WPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── mozilla_root0
│   └── code_1.27.2-1536736588_amd64.deb
├── pulse-PKdhtXMmr18n
├── pulse-hn5F47vSvQ0r
├── runtime-root
├── scripts\015
│   └── test\015
│       ├── atd
│       ├── chfn
│       ├── chpasswd
│       ├── chsh
│       ├── common-account
│       ├── common-auth
│       ├── common-password
│       ├── common-session
│       ├── common-session-noninteractive
│       ├── cron
│       ├── cups
│       ├── gdm-autologin
│       ├── gdm-fingerprint
│       ├── gdm-launch-environment
│       ├── gdm-password
│       ├── gnome-screensaver
│       ├── login
│       ├── newusers
│       ├── other
│       ├── passwd
│       ├── polkit-1
│       ├── ppp
│       ├── runuser
│       ├── runuser-l
│       ├── sshd
│       ├── su
│       ├── sudo
│       ├── systemd-user
│       ├── unity
│       └── vmtoolsd
├── tmp54e0qvir
│   └── apt.conf
└── tmpaddon

14 directories, 39 files
```


## Task 3
### Description
- Show system time.
- Make directory `/tmp/lstest`.
- Move to `/tmp/lstest`.
- Make directory `a1d`，`b56e`，`6test`.
- Make empty file `xy`，`x2y`，`732`.
- List all the files or directory with filename starting by `a`,`x`,`6`.
- List all the files or directory with filename starting by a letter and followed by a digit.

### Run&Output
```bash
➜  shell_exercise git:(aero_task) ✗ tree /tmp
/tmp
├── VSCode Crashes
├── a.out
├── appInsights-node
├── gnome-software-4PSVPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-HC8KPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-LCD1PZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-VXVLPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-Z86WPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── mozilla_root0
│   └── code_1.27.2-1536736588_amd64.deb
├── pulse-PKdhtXMmr18n
├── pulse-hn5F47vSvQ0r
├── runtime-root
├── tmp54e0qvir
│   └── apt.conf
└── tmpaddon

12 directories, 9 files
➜  shell_exercise git:(aero_task) ✗ zsh task_3.sh
Thu Oct  4 19:17:29 DST 2018
mkdir: created directory '/tmp/lstest'
x2y  xy

6test:

a1d:
x2y

a1d:

b56e:


➜  shell_exercise git:(aero_task) ✗ tree /tmp
/tmp
├── VSCode Crashes
├── a.out
├── appInsights-node
├── gnome-software-4PSVPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-HC8KPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-LCD1PZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-VXVLPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── gnome-software-Z86WPZ
│   └── code_1.27.2-1536736588_amd64.deb
├── lstest
│   ├── 6test
│   ├── 732
│   ├── a1d
│   ├── b56e
│   ├── x2y
│   └── xy
├── mozilla_root0
│   └── code_1.27.2-1536736588_amd64.deb
├── pulse-PKdhtXMmr18n
├── pulse-hn5F47vSvQ0r
├── runtime-root
├── tmp54e0qvir
│   └── apt.conf
└── tmpaddon

16 directories, 12 files
➜  shell_exercise git:(aero_task) ✗
```

## Optional Task
### Description
I didn't get it very well in this part.  
I just tried to understand the Answer Key.