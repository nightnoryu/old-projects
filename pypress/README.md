# Pypress
This little script can gradually compress jpg and png images with the help of ffmpeg.

## Requirements
* Python 3
* [FFmpeg](https://ffmpeg.org)

## Usage
```
usage: pypress.py [-h] [--output DIR] [--replace] [FILE [FILE ...]]

positional arguments:
  FILE                  file[s] to process (supports file masks)

optional arguments:
  -h, --help            show this help message and exit
  --output DIR, -o DIR  output directory. If it does not exist, it will be created (default: current)
  --replace, -r         force replace files if there's any conflicts
```
For file selecting, you can use file masks. For example, `*.jpg` will compress only files with jpg extension.

By default, the script won't replace existing images. Use `-r` to change this behavior.
