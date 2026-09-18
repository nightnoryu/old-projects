import tkinter as tk

from PIL import Image, ImageTk


class ImageCanvas():
    """Above-class for canvas (responsible only for image displaying)"""
    def __init__(self, master, mode):
        self.master = master
        self.default_width = 300
        self.default_height = 300

        self.init_canvas()
        self.set_mode(mode)

    def init_canvas(self):
        """Initializes and packs canvas"""
        self.canvas = tk.Canvas(self.master,
                width=self.default_width,
                height=self.default_height)
        self.canvas.pack(side=tk.LEFT, expand=True, fill=tk.BOTH)

    def set_mode(self, mode):
        """Changes image viewing mode"""
        self.mode = mode

    def prep_image(self, filename, height_limit):
        """Opens image and prepares it for displaying"""
        self.image = Image.open(filename)
        self.tk_image = ImageTk.PhotoImage(self.image)
        # Check for mode
        if self.mode:
            self.check_image_size(height_limit)

    def check_image_size(self, height_limit):
        """Checks if it's necessary to resize the image"""
        # TODO Fill canvas with black and display image in the center otherwise
        _, height = self.image.size
        if height > height_limit:
            self.resize_image(height_limit)

    def display_image(self):
        """Configures canvas for image and displays the image"""
        width, height = self.image.size
        self.canvas.configure(width=width,
                height=height,
                scrollregion=(0, 0, width, height))
        self.canvas.create_image(0, 0, anchor=tk.NW, image=self.tk_image)

    def resize_image(self, new_height):
        """Makes image fit"""
        width, height = self.image.size
        resize_rate = height / float(new_height)
        new_width = int(width / resize_rate)
        self.image = self.image.resize((new_width, new_height))
        self.tk_image = ImageTk.PhotoImage(self.image)

    def clear_image(self):
        """Removes image from canvas and resizes it to the default dimensions"""
        self.canvas.delete("all")
        self.canvas.configure(width=self.default_width,
                height=self.default_height)
