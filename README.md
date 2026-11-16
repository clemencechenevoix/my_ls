<h1> 
<img style="width:75" src= "https://logos-marques.com/wp-content/uploads/2021/03/Linux-Logo.png">
My_ls
</h1>

my_ls is a simplify reproduction of the linux command ls

You can have more information on the original ls on its man page: <br>
https://man7.org/linux/man-pages/man1/ls.1.html

### Project organization :
---

This project code is contained in 2 folder: include and src.

include containe:

- `my_ls.h`
- `utils.h`

They contain the following category:
```
- include

- structure

- function
```
<br>
src containe:

<br>

- `main.c`
- `my_ls.c`
- `options.c`
- `utils.c`

They contain the following category:
```
- include

- function or main
```
### Tech stack :

---
- C
- Makefile

### Install guide :
---
You need to have the project files and the Makefile.

In order to use my_ls you need to compile the code, to do so you can use:
```
$> make
```
or
```
$> make re
```

if you want to remove the files the Makefile created you can use:
```
$> make clean
```
to remove my_ls.o <br>
or
```
$> make fclean
```
to remove all the files

### Usage guide :
---
In order to use my_ls enter in the terminal:
```
$> ./my_ls 
```
Without any argument, it will display in column every files in the opened folder(".") sorted by lexical order

3 types of arguments can be added in the order of your choice:

#### <u>The flags</u>
example:
```
$> ./my_ls -a
```
It will change the sorting method, the type of display or the printed information depending on the flag

authorize flag:
|name|action|
|:---|:-----|
|`-a`|print all the file even the hidden file  that start with '.'|
|`-t`|sort the files by last edit time|
|`-S`|sort the files by size|
|`-s`|print the size of the files|
|`-r`|reverse the printing order of the files and folders|
|`-1`|display in column|
|`-x`|display in rows|

#### <u> The folders</u>
example:
```
$> ./my_ls ..
```
It will print the name and information according to the given flags of the file inside the given folder

#### <u> The files</u>
example:
```
$> ./my_ls my_ls.c
```
It will print before the folder the name and information according to the given flags of the given file

### Example my_ls call :
---
```
$> ./my_ls -at
```

```
$> ./my_ls -a .. -t
```

```
$> ./my_ls .. . -a -Ss ../..
```

```
$> ./my_ls -a my_ls -t my_ls.c -1
```

```
$> ./my_ls .. -as ../.. . . my_ls.c -tr my_ls -x
```

```
$> ./my_ls
```

### Developer :
---
<a href="https://github.com/clemencechenevoix">Clemence Chenevoix</a>, 2nd year student in programming school

This project was created for a school exercice named MY_LS .