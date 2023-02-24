# Calculator

"Calculator" is a CUI application which is written in C++.

## Features

"Calculator" support parenthesis, operator '+', '-', '*', '/', '%', ':=' and variables.

When you use variables, its name should be started with '$' and comformed of 0~9 or a-z or A-Z such as '$hoge', '$hoge1', '$631hoge', '$631'

To use or initialize variables, use operator ':='.

Calculator support 'Commands'. You can use '@' to use Commands.

Commands support 8 commands.

- ### quit

usage

`exp>> @quit`

you can use 'quit' command to exit from Calculator application.

- ### help

usage

`exp>> @help [param]`

you can use 'help' command to call help of the calculator application.

To know about more, please type help in the application.

- ### set default font

`exp>> @set default font [param]*`

you can use `set default font` command to change the font of default string such as 'exp>>'.

the param support 'bold', 'half_bright', 'italic', 'under_bar', 'blink', 'none'.

- ### set newline font

`exp>> @set default font [param]*`

you can use `set default font` command to change the font of default string such as 'exp>>'.

the param support 'bold', 'half_bright', 'italic', 'under_bar', 'blink', 'none'.
