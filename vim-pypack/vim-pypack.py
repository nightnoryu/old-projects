import argparse
import os
import shutil
import stat
import subprocess

from config import PACKAGES_DIR


# Expand the environmental variables in the package directory
PACKAGES_DIR = os.path.expandvars(PACKAGES_DIR)


def install_package(link):
	os.chdir(PACKAGES_DIR)
	try:
		subprocess.run([
			"git",
			"clone",
			link
		])
	except subprocess.CalledProcessError:
		# Catch the git error
		print("This plugin does not exist.")
	else:
		name = link.split("/")[-1]
		print("\n{} installed succesfully.".format(name))


def update_packages():
	# Get packages dirs
	dirs = os.listdir(PACKAGES_DIR)
	for plugin in dirs:
		print("Updating {0}...".format(plugin))
		# CD in the plugin directory
		os.chdir(os.path.join(PACKAGES_DIR, plugin))
		# Pull the updates
		subprocess.run(["git", "pull"])
	print("\nAll plugins updated succefully.")


def list_packages():
	print("Currently installed plugins:")
	print("\n".join(os.listdir(PACKAGES_DIR)))


def remove_readonly(func, path, _):
	"""Remove the readonly file with shutil"""
	os.chmod(path, stat.S_IWRITE)
	func(path)


def remove_package(name):
	os.chdir(PACKAGES_DIR)
	dirs = os.listdir(".")
	if name in dirs:
		shutil.rmtree(name, onerror=remove_readonly)
		print("{} removed successfully.")
	else:
		print("There is no such package. Try 'ls' command to see installed packages.")


def main():
    """Entry point of the script"""
    # Create a parser
    parser = argparse.ArgumentParser(description="Package manager for vim plugins.")
    subparsers = parser.add_subparsers(help="available commands")

    # Install a package (install URL)
    parser_install = subparsers.add_parser("install", help="install a plugin")
    parser_install.add_argument("link", metavar="LINK", help="plugin's github link")
    parser_install.set_defaults(func=lambda args: install_package(args.link))

    # Update packages (update)
    parser_update = subparsers.add_parser("update", help="update all installed plugins")
    parser_update.set_defaults(func=lambda args: update_packages())

    # List packages (ls)
    parser_ls = subparsers.add_parser("ls", help="list installed plugins")
    parser_ls.set_defaults(func=lambda args: list_packages())

    # Remove a package (remove NAME)
    parser_remove = subparsers.add_parser("remove", help="uninstall a plugin")
    parser_remove.add_argument("name", metavar="NAME", help="name of the plugin to remove")
    parser_remove.set_defaults(func=lambda args: remove_package(args.name))

    # Parse arguments and call the corresponding function
    args = parser.parse_args()
    args.func(args)


# Entry point
if __name__ == "__main__":
    main()
