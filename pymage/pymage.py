import os
import sys
import tkinter as tk
from tkinter import filedialog as fd
from tkinter import messagebox as mb

from image_canvas import ImageCanvas


class PyMage(tk.Frame):
    """Main application class"""
    def __init__(self, master=None):
        super().__init__()
        self.master = master
        self.pack()

        # Image viewing mode
        # True - image is scaled to have height 600 for comfortable viewing
        # False - image is displayed as-is
        self.mode = True
        # Filetypes for prompt opening
        self.filetypes = [
            ('all files', '.*'),
            ('JPG', '.jpg'),
            ('PNG', '.png'),
            ('BMP', '.bmp'),
            ('WEBP', '.webp'),
        ]
        # Create ImageCanvas object
        self.image_canvas = ImageCanvas(self, self.mode)
        # Default height limit for the 1st mode
        self.height_limit = 600

        self.get_filename()
        # This runs for every image
        if self.filename:
            self.display_image()
            self.get_file_list()

        # Bindings
        self.define_bindings()

    def define_bindings(self):
        """Defines the windows's hotkeys"""
        self.master.bind("<q>", lambda e: sys.exit(0))
        self.master.bind("<Right>", lambda e: self.switch_image(True))
        self.master.bind("<Left>", lambda e: self.switch_image(False))
        self.master.bind("<f>", lambda e: self.change_mode())
        self.master.bind("<o>", lambda e: self.prompt_open_image())

    def get_filename(self):
        """Get filename from input paramaters if presented"""
        self.filename = ""
        if len(sys.argv) > 1:
            self.filename = os.path.abspath(sys.argv[1])
            os.chdir(os.path.dirname(self.filename))

    def get_file_list(self):
        """Gets a list of all images in the folder of the opened image"""
        # TODO add filter only for images
        self.file_list = [os.path.abspath(file) for file in os.listdir('.')]
        self.image_index = self.file_list.index(self.filename)

    def display_image(self):
        """Function for all actions to display image"""
        try:
            self.image_canvas.prep_image(self.filename, self.height_limit)
            self.image_canvas.display_image()
            self.change_window_title(self.filename)
        except Exception: # Catch not supported format
            mb.showerror("Error",
                    "File format not supported for: {}".format(self.filename))

    def switch_image(self, direction):
        """Shows the next image in file list (True - next, False - previous)"""
        self.change_image_index(direction)
        self.filename = self.file_list[self.image_index]

        # Display image
        self.display_image()

    def change_image_index(self, direction):
        """Changes image_index according to direction"""
        if direction:
            self.image_index += 1
        else:
            self.image_index -= 1

        # Check index-out-of-range (loop images in current folder)
        if self.image_index + 1 > len(self.file_list):
            self.image_index = 0
        elif self.image_index < 0: # I want index to be always positive
            self.image_index = len(self.file_list) - 1

    def prompt_open_image(self):
        """Prompts for image file"""
        filename = fd.askopenfilename(parent=self,
            initialdir=os.getcwd(),
            title="Select an image to open",
            filetypes=self.filetypes)
        if filename:
            self.filename = os.path.normpath(filename)
            os.chdir(os.path.dirname(self.filename))

            # Display new image and get filelist
            self.display_image()
            self.get_file_list()

    def change_mode(self):
        """Toggles image viewing mode"""
        self.mode = not self.mode
        self.image_canvas.set_mode(self.mode)
        self.display_image()

    def change_window_title(self, msg):
        """Changes window title to 'msg - PyMage' """
        self.master.title("{} - PyMage".format(msg))

    def clear_window_title(self):
        """Sets window title to 'PyMage' """
        self.master.title("PyMage")


if __name__ == "__main__":
    root = tk.Tk()
    root.title("PyMage")
    app = PyMage(root)
    root.mainloop()
