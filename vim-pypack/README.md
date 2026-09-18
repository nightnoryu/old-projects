# Vim pypack
This is a python script I created for managing [vim](https://www.vim.org/) plugins for those who use native vim plugin system.

## Requirements
* Python 3
* Git

## Usage
```
usage: vim-pypack.py [-h] {install,update,ls,remove} ...

positional arguments:
  {install,update,ls,remove}
                        available commands
    install             install a plugin
    update              update all installed plugins
    ls                  list installed plugins
    remove              uninstall a plugin

optional arguments:
  -h, --help            show this help message and exit
```
Call the program with the needed command and `-h` flag to learn more about this particular command.

### Install a plugin:
```
python vim-pypack.py install [git repository url]
```

### Remove an installed plugin:
```
python vim-pypack.py remove [plugin name]
```

### List all currently installed plugins:
```
python vim-pypack.py ls
```

### Update all plugins (runs `git pull` for each plugin):
```
python vim-pypack.py update
```

## Configuration
The default configuration is set for default pathogen path, but you can change it. `config.py` looks like this by default:

```
PACKAGES_DIR = r'%USERPROFILE%\vimfiles\bundle'
```

`PACKAGES_DIR` is the directory where your plugins are stored. For example, to change it to the built-in vim plugin system, you should edit the variable like this:

```
PACKAGES_DIR = r'%USERPROFILE%\vimfiles\pack\bundle\start'
```

`%USERPROFILE%` is a Windows environmental variable that stores your home directory. To use this program on Unix, change it to `$HOME` (also don't forget to use the forward slashes `/` instead of backward slashes `\`). Or you can simply specify the path manually, for example: `C:\Users\[your username]\vimfiles\bundle`.
