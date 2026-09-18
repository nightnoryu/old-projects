"""
Программа для расчета характеристик баллистического движения и построения графика движения тела
13.02.20
"""


import tkinter as tk
from tkinter import ttk
from tkinter import messagebox as mb

import physical_functions as pf
from plotter import Plotter


class MvmtCalculator(tk.Frame):
	"""Главный класс приложения"""
	def __init__(self, master=None):
		super().__init__(master)
		self.master = master
		self.pack()

		# Отступы элементов по умолчанию
		self.default_padding = {'padx': 5, 'pady': 5}

		# Объект для построения графика
		self.plotter = Plotter()

		self.create_vars()
		self.create_widgets()
		self.pack_widgets()

	def create_widgets(self):
		"""Создает виджеты приложения"""
		# ЭЛЕМЕНТЫ ВВОДА
		# Ввод угла броска
		self.angle_label = ttk.Label(self, text="Угол броска (градусы):")
		self.angle_entry = ttk.Entry(self, width=10, textvariable=self.angle_var)
		# Ввод начальной скорости
		self.speed_label = ttk.Label(self, text="Начальная скорость (м/с):")
		self.speed_entry = ttk.Entry(self, width=10, textvariable=self.speed_var)

		# ЭЛЕМЕНТЫ ВЫВОДА
		# Вывод расстояния
		self.distance_label = ttk.Label(self, text="Расстояние (м):")
		self.distance_entry = ttk.Entry(self, width=10, state=tk.DISABLED, textvariable=self.distance_var)
		# Вывод максимальной высоты
		self.max_height_label = ttk.Label(self, text="Максимальная высота (м):")
		self.max_height_entry = ttk.Entry(self, width=10, state=tk.DISABLED, textvariable=self.max_height_var)
		# Вывод времени броска
		self.time_label = ttk.Label(self, text="Время полета (с):")
		self.time_entry = ttk.Entry(self, width=10, state=tk.DISABLED, textvariable=self.time_var)

		# КНОПКИ
		# Кнопка для расчета
		self.calc_button = ttk.Button(self, text="Рассчитать", command=self.calculate)
		# Кнопка для отображения графика
		self.graph_button = ttk.Button(self, text="График", command=self.show_graph)

	def pack_widgets(self):
		"""Расположение виджетов приложения"""
		# ЭЛЕМЕНТЫ ВВОДА
		self.angle_label.grid(row=0, column=0, **self.default_padding, sticky=tk.E)
		self.angle_entry.grid(row=0, column=1, **self.default_padding)

		self.speed_label.grid(row=1, column=0, **self.default_padding, sticky=tk.E)
		self.speed_entry.grid(row=1, column=1, **self.default_padding)

		# ЭЛЕМЕНТЫ ВЫВОДА
		self.distance_label.grid(row=0, column=2, **self.default_padding, sticky=tk.E)
		self.distance_entry.grid(row=0, column=3, **self.default_padding)

		self.max_height_label.grid(row=1, column=2, **self.default_padding, sticky=tk.E)
		self.max_height_entry.grid(row=1, column=3, **self.default_padding)

		self.time_label.grid(row=2, column=2, **self.default_padding, sticky=tk.E)
		self.time_entry.grid(row=2, column=3, **self.default_padding)

		# КНОПКИ
		self.calc_button.grid(row=2, column=0, **self.default_padding)
		self.graph_button.grid(row=2, column=1, **self.default_padding)

	def create_vars(self):
		"""Создание переменных tk"""
		# Переменные ввода
		self.angle_var = tk.StringVar(self, "")
		self.speed_var = tk.StringVar(self, "")

		# Переменные вывода
		self.distance_var = tk.StringVar(self, "")
		self.max_height_var = tk.StringVar(self, "")
		self.time_var = tk.StringVar(self, "")

	def calculate(self):
		"""Расчет и построение графика"""
		# Считывание введенных значений
		try:
			angle, speed = self.get_input_entries()
		except ValueError:
			return

		# Вычисление значений
		distance = pf.get_distance(speed, angle)
		max_height = pf.get_max_height(speed, angle)
		time = pf.get_time(speed, angle)

		# Разблокировка виджетов вывода
		self.change_entries_state(tk.NORMAL)
		# Вывод значений
		self.distance_var.set(str(round(distance, 4)))
		self.max_height_var.set(str(round(max_height, 4)))
		self.time_var.set(str(round(time, 4)))

	def get_input_entries(self):
		"""Возвращает значения полей ввода (угол, расстояние)"""
		try:
			angle = float(self.angle_var.get())
			speed = float(self.speed_var.get())
		except ValueError:               # Проверка на невалидные значения
			mb.showerror("Ошибка", "Неверные значения")
			raise ValueError()
		else:
			return (angle, speed)

	def change_entries_state(self, state):
		"""Переводит виджеты вывода в указанное состояние"""
		self.distance_entry.configure(state=state)
		self.max_height_entry.configure(state=state)
		self.time_entry.configure(state=state)

	def show_graph(self):
		"""Выводит отображение графика"""
		# Считывание введенных значений
		try:
			speed, angle = self.get_input_entries()
		except ValueError:
			return

		# Настройка плоттера и отображение
		self.plotter.init_plotter(speed, angle)
		self.plotter.show()

	
if __name__ == "__main__":
	root = tk.Tk()
	root.title("Movement Calculator")
	root.resizable(False, False)
	app = MvmtCalculator(root)
	root.mainloop()