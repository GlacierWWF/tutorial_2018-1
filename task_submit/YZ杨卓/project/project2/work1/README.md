# Program for group chat
-----

- **Author**: 杨卓
- **Revised**: 杨卓
- **Version**: 1.0.0
- **Date**:   2018-11-9
- **Abstract**: Code for group chat
- ----

## Required

- python >= 2.7

----------

## Description
            
- ###run:

            1. python server.py
            2. python telnet.py localhost 5000
            3. python telnet.py localhost 5000
            4. python telnet.py localhost 5000

- ### Depend Libraries:

            socket 
            select
            string
            sys

- Input:

       - ####Terminal1:
                member 1
       - #### Terminal2:
                member 2
       - ####Terminal3:
                menber 3

- Output:

       - ####Terminal1:
       
        Connected to remote host. Start sending messages
        
        <You> [127.0.0.1:48576] entered room
        
        <You> [127.0.0.1:48578] entered room
        
        <You> member 1
        
        <('127.0.0.1', 48576)> member 2
        
        <('127.0.0.1', 48578)> member 3
        
        <You> 

       - ####Terminal2:

        Connected to remote host. Start sending messages
        
        <You> [127.0.0.1:48578] entered room
        
        <('127.0.0.1', 48574)> member 1
        
        <You> member 2
        
        <('127.0.0.1', 48578)> member 3

       - ####Terminal3:

        Connected to remote host. Start sending messages
        
        <('127.0.0.1', 48574)> member 1
        
        <('127.0.0.1', 48576)> member 2

        <You> member 3




        
        





