# cursus

* [libft](#libft)
* [get_next_line](#get_next_line)
* [ft_printf](#ft_printf)
* [ft_server](#ft_server)
* [ft_mini_ls](#ft_mini_ls)

## [libft](https://github.com/unlimish/libft) [![NormCI](https://github.com/unlimish/libft/actions/workflows/norminetteCI.yml/badge.svg)](https://github.com/unlimish/libft/actions/workflows/norminetteCI.yml)
*Reimplementation of libc*
### Usage
```bash
$ make
```
It will compile `libft.a`

## [get_next_line](https://github.com/unlimish/cursus/tree/master/get_next_line)
*Retruning new line from file descriptor*
### Prototype
```c
int get_next_line(int fd, char **line);
```
### Return value
|  Return Value  |    |
| ---- | ---- |
|  1  |  A end of line has been read  |
|  0  |  EOF has been reached end of line  |
|-1| Error |

## [ft_printf](https://github.com/unlimish/cursus/tree/master/ft_printf)
*Reimplementation of printf*
### Available format strings
|   |   |   |
|---|---|---|
|**Flag characters**|`0`|The value shuld be zero padded For `d`, `i`, `x` and `X`, the converted value is padded on the left width zeros rather than blanks.|
||`-`|The converted value is to be left|
|**Field width**|`Available`|The argment is procesed as `int`.|
|**Presicion**|`Available`||
|**Length modifier**|`Unavailable`|The argments is processed as `int`.|
|**Conversion Specifiers**|`d` `i`|The `int` argment is converted to `signed decimal`.|
|                         |`u`    |The `unsigned int` argment is converted to `unsigned decimal`.|
|                         |`c`    |The `int` argument is converted to `unsigned char`|
|                         |`s`    |The `char*` argument is expected to be a pointer and the char array has to and of `NULL`(`\0`).|
|                         |`p`    |The `void *` argument is printed in hexadecimal.|
|                         |`x` `X`|The `unsigned int` argument is converted to hexadecial if the conversion specifier is `X` it is printed with upper cases.|

### Usage
`make` then in c file's `main()`
```c
#include ./inc/ft_printf.h

main()
{
  ft_printf("%-10.4d", 123);
}
```
## [ft_server](https://github.com/unlimish/cursus/tree/master/ft_server)
### Usage
- Build contaioner then run with opening ports for HTTP`80` and SSL`443` (`-p Host's port:Container's port`)
- Default's autoindex is **off**. If you want to use autoindex, add `--env autoindex=off` when `docker run`.
```bash
docker build . -t CONTAINER_NAME
docker run -it -p 80:80 -p 443:443 --rm (--env autoindex=on) CONTAINER_NAME
```
#### What is `-it` option?
- `-i` `--interactive`: Keep STDIN open even if not attached. For example, it is used for when sending a signal `Ctrl+c`.
- `-t` `--tty`: Allocate a pseudo-TTY. It is for connecting to the interactive shell (e.g: zsh or bash).

🔗 `localhost/wordpress`</br>🔗 `localhost/phpmyadmin`

## [ft_mini_ls](https://github.com/unlimish/cursus/tree/master/ft_mini_ls)
*ls -1tr*
