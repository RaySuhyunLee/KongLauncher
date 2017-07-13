# Kongdole Micro Missile Launcher

## Protocols

Control protocols format is defined as below:

---|---|---|---|---|---
command(1 byte) | param1(2 byte) | param2(2 byte) | ... | paramN(2 byte) | 0xFF

name|command|description
---|---|---
arm|0x01|arm the launcher
disarm|0x02|disarm the launcher. `fire` command is ignored in this mode. 
move|0x10|move turret to desired angle
fire|0x20|fire!!
manual mode|0x30|control manually
automatic mode|0x31|launcher automatically tracks target(balloon)
