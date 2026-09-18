import random
import tkinter as tk
from tkinter import messagebox as mb
from tkinter import ttk

from countries_scanner import CountriesScanner


class CountriesTest(tk.Frame):
	"""Main application class"""
	def __init__(self, master=None):
		super().__init__()
		self.master = master
		self.pack()

		self.filename = "countries.txt"
		self.delimiter = ":"

		# Initialize scanner
		self.countries_scanner = CountriesScanner(self.filename, self.delimiter)

		self.create_vars()
		self.create_widgets()
		self.pack_widgets()

		# Bindings
		self.master.bind("<Return>", lambda e: self.button_pressed())

		# Set focus on entry
		self.capital_entry.focus()

	def create_vars(self):
		"""Creates app's variables"""
		self.counter_var = tk.StringVar(self, "<Количество стран>")
		self.country_var = tk.StringVar(self, "<Название страны>")
		self.capital_var = tk.StringVar(self, "")
		# This is responsible for button's action on pressing (Начать, Ввод, Повторить)
		self.button_function = "Начать"

	def create_widgets(self):
		"""Creates app's widgets"""
		self.counter_label = ttk.Label(self, textvariable=self.counter_var)
		self.country_label = ttk.Label(self, textvariable=self.country_var)
		self.capital_entry = ttk.Entry(self, textvariable=self.capital_var)
		# Enter and repeat button
		self.button = ttk.Button(self, text=self.button_function, command=self.button_pressed)

	def pack_widgets(self):
		"""Puts widgets in the main frame"""
		self.counter_label.grid(row=0, column=0, columnspan=2, padx=5, pady=5)
		self.country_label.grid(row=1, column=0, padx=5, pady=5)
		self.capital_entry.grid(row=1, column=1, padx=5, pady=5)
		self.button.grid(row=2, column=0, columnspan=2, padx=5, pady=5)

	def button_pressed(self):
		"""Handles button pressing"""
		if self.button_function == "Начать" or self.button_function == "Повторить":
			self.button_function = "Ввод"
			self.start_test()
		elif self.button_function == "Ввод":
			self.check_answer()

	def change_button_function(self, func):
		"""Changes button function and updates button label"""
		self.button_function = func
		self.button.configure(text=self.button_function)

	def start_test(self):
		"""Start the quiz"""
		# Shuffle countries dictionary
		self.countries_dict = self.countries_scanner.get_countries_dict()
		self.keys = list(self.countries_dict.keys())
		random.shuffle(self.keys)

		# Set vars for test
		current_country = self.keys[-1]
		self.current_capital = self.countries_dict[self.keys.pop()]

		# Dict for countring wrong answers
		self.wrong_countries = {}

		# Set country and clear input
		self.counter_var.set(str(len(self.keys) + 1))
		self.country_var.set(current_country)
		self.capital_var.set("")
		self.change_button_function("Ввод")

	def check_answer(self):
		"""Checks user input and changes country if presented"""
		if self.current_capital != self.capital_var.get():
			mb.showinfo("Неверно", "Правильный ответ: %s" % self.current_capital)
			self.wrong_countries[self.country_var.get()] = self.current_capital

		if self.keys: # Check for leftover countries
			# Change country
			current_country = self.keys[-1]
			self.current_capital = self.countries_dict[self.keys.pop()]

			# Update widgets
			self.counter_var.set(str(len(self.keys) + 1))
			self.capital_var.set("")
			self.country_var.set(current_country)
		else: # Display results otherwise
			self.display_complete()

	def display_complete(self):
		"""Displays completement message"""
		# Display message
		string = "Нет ошибок. Nice."
		# Display wrong answers if presented
		if self.wrong_countries:
			string = "Неверно названные столицы:\n"
			for country, capital in self.wrong_countries.items():
				string += "%s - %s\n" % (country, capital)

		# Clear widgets
		self.counter_var.set("<Количество стран>")
		self.change_button_function("Повторить")
		self.country_var.set("<Название страны>")
		self.capital_var.set("")

		# Show final message (change da world my final message goodby)
		mb.showinfo("Тест завершен", string)



if __name__ == "__main__":
	root = tk.Tk()
	root.title("Тест на знание столиц")
	root.resizable(False, False)
	app = CountriesTest(root)
	root.mainloop()
