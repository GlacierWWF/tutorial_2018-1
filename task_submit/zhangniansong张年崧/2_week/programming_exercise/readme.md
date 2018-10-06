## IP Networks
- Author: Zhang Niansong
- Revised: Zhang Niansong
- Date: 2018-10-06
- Version: 1.0.0
- Abstract: Groups all input IP addresses into the minimum IP network and outputs network address and mask.

---

### File structure

```
timer_exercise
|- IP_networks.cpp (Source file)
|- IP_networks (Excecutable Application)
|- README.md
```

---

### Compile and Run

```
# compile
g++ -o IP_networks IP_networks.cpp

# run
./IP_networks
```

---

### Sample INPUT

```
3
194.85.160.177
194.85.160.183
194.85.160.178
```

### Expected OUTPUT

```
194.85.160.176
255.255.255.248
```
