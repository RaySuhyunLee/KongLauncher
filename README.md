# Kongdole Micro Missile Launcher

## Protocols

Control protocols format is defined as below:

command(1 byte) | param1(2 byte) | param2(2 byte) | ... | paramN(2 byte) | 0xFF(1 byte)
---|---|---|---|---|---

Available commands are shown below:

name|command|description
---|---|---
arm|0x01|arm the launcher
disarm|0x02|disarm the launcher. `fire` command is ignored. 
mode|0x10|change control mode
move|0x20|move turret to desired angle
fire|0x30|fire!!

### Command Parameter List
Some command requires parameters, though others do not. Those are commands and their required parameters list.

#### arm [0x01]
Arm the launcher and get ready to fire.

No parameter is required.

#### disarm [0x02]
Disarm the launcher. When the launcher is in disarmed state, `fire` command is ignored.

No parameter is required.

#### mode [0x10]
Change control mode. There are two modes currently available.
- manual mode: you can freely give input to move the turret, using `move` command.
- auto mode: turret automatically tracks target(balloon). `move` command is ignored in this mode.

_ | name | value
---|---|---
param1 | mode number | **0x01**: manual mode <br />**0x02**: auto mode

#### move [0x20]
Move turret to desired angle. The launcher can rotate it's turret in two axis:**pitch** and **yaw**.

_ | name | value
---|---|---
param1 | pitch | desired pitch value in degree, multiplied by 1000. <br />**ex)** 120.5deg => 120.5 * 1000 = **120500**(actual parameter value)
param2 | yaw | desired yaw value in degree. Same as pitch, it is multiplied by 1000.

#### fire [0x30]
Fire a missile immediatly, and automatically reload next missile.  
**Caution**: If you use this command while reloading, it will be ignored.

No parameter is required.
