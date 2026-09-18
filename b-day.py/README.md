# B-day-py
A minimalistic birthday manager for everyone who has bad memory for dates :)

## Usage
```
Usage: b-day.py [OPTIONS] MODE [MODE_OPTIONS]

MODE:
  Either 'show' or 'add', for displaying and adding the dates respectively

Options:
  -h,  --help      show help

'show' mode options:
  -d,  --days   display dates within the specified amount of days
```

### Adding a date
To add a new date, you simply use `py b-day.py add` and the program prompts you for the needed information: name and date. By default, the birthday file `bday_list.txt` is stored in the same directory as the script itself. You can edit it manually, **but don't forget to add a newline at the end of the file**. It depends on how the file is parsed.

### Showing dates
To see all dates that you've added use `py b-day.py show`. You can also show dates within the specified amounts of days using `-d` or `--days` parameter like this: `py b-day.py show -d 30`. This will print all birthdays within a month roughly.
