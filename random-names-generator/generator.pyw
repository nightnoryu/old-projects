from random import randint, choice
from tkinter import messagebox, ttk
import sys
import tkinter as tk

# Check for pyperclip
ppc_imported = True
try:
    import pyperclip
except ImportError:
    print("pyperclip is unavailable.")
    ppc_imported = False


class NamesGenerator(tk.Frame):
    """Main application class"""
    def __init__(self, master=None):
        # Initialization
        super().__init__()
        self.master = master
        self.pack()

        # Variables
        self.length = tk.StringVar(self, "6")
        self.number_selected = tk.BooleanVar(self, False)
        self.uppercase_selected = tk.BooleanVar(self, False)

        # The actual name variable
        self.name_label = ttk.Label(self, text="-" * int(self.length.get()))

        # Name length input
        self.length_label = ttk.Label(self, text="Length:")
        self.length_entry = ttk.Entry(self, width=15,
                textvariable=self.length)

        # Checkboxes
        self.numbers_checkbox = ttk.Checkbutton(self,
                variable=self.number_selected)
        self.numbers_label = ttk.Label(self, text="Include numbers")
        self.uppercase_checkbox = ttk.Checkbutton(self,
                variable=self.uppercase_selected)
        self.uppercase_label = ttk.Label(self, text="Include uppercase")

        # Buttons
        self.generate_button = ttk.Button(self, text="Generate",
                command=self.generate)
        self.clipboard_button = ttk.Button(self, text="Copy to clipboard",
                command=self.copy)

        # Pack all the stuff
        self.pack_elements()
        # Add bindings
        self.register_bindings()

    def pack_elements(self):
        """Packs all app's elements"""
        # The actual name
        self.name_label.grid(row=0, column=0, columnspan=2, padx=5, pady=5)

        # Name length
        self.length_label.grid(row=1, column=0, padx=5, pady=5, sticky=tk.E)
        self.length_entry.grid(row=1, column=1, padx=5, pady=5)

        # Checkboxes
        self.numbers_checkbox.grid(row=2, column=0, padx=5, pady=5,
                sticky=tk.E)
        self.numbers_label.grid(row=2, column=1, padx=5, pady=5,
                sticky=tk.W)
        self.uppercase_checkbox.grid(row=3, column=0, padx=5, pady=5,
                sticky=tk.E)
        self.uppercase_label.grid(row=3, column=1, padx=5, pady=5,
                sticky=tk.W)

        # Buttons
        self.generate_button.grid(row=4, column=0, padx=5, pady=5)
        self.clipboard_button.grid(row=4, column=1, padx=5, pady=5)

    def register_bindings(self):
        """Adds app's keyboard bindings"""
        self.master.bind("<Escape>", lambda e: sys.exit(0))
        self.master.bind("<Return>", lambda e: self.generate())
        self.master.bind("<Control-c>", lambda e: self.copy())

    def generate(self):
        """Function that generates a name"""
        # Error handling
        try:
            # Use default length value if not presented
            if self.length.get() == "":
                length = 6
            else:
                length = int(self.length.get())
        except ValueError:
            messagebox.showerror("Error", "Invalid input")
            return

        # Length limitations
        if length > 32:
            messagebox.showerror("Error", "Length can't be more than 32")
            return

        # Generating
        name = ""
        for _ in range(length):
            # Add numbers
            if self.number_selected.get() and randint(0, 1) == 1:
                name += str(randint(0, 9))
                continue
            # Add uppercase letters
            if self.uppercase_selected.get() and randint(0, 1) == 1:
                name += chr(randint(65, 90))
                continue
            # Plain boring letters
            name += chr(randint(97, 122))

        # Print the name
        self.name_label.configure(text=name)

    def copy(self):
        """Copies the name to the clipboard"""
        if ppc_imported:
            pyperclip.copy(self.name_label.cget("text"))


def main():
    """Entry point of the script"""
    # Initialize and launch a window
    root = tk.Tk()
    root.title("Random names generator")
    root.resizable(False, False)
    app = NamesGenerator(root)
    root.mainloop()


if __name__ == "__main__":
    main()
