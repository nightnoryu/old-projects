import matplotlib.pyplot as plt

import physical_functions as pf


class Plotter():
	"""Класс для построения графика траектории движения"""
	def init_plotter(self, speed, angle):
		self.init_values(speed, angle)
		self.init_plt()

	def init_values(self, speed, angle):
		"""Создание значений для графика"""
		self.x_values = []
		self.y_values = []
		for x in range(int(pf.get_x_max(speed, angle)) + 1):
			y = pf.trajectory_func(speed, angle, x)
			self.x_values.append(x)
			self.y_values.append(y)

	def init_plt(self):
		"""Настройки и построение графика"""
		# Размер окна графика
		plt.figure(figsize=(10, 6))
		# Настройки осей
		plt.xlabel("X")
		plt.ylabel("Y")
		plt.gca().set_ylim([0, 50])
		# Построение
		plt.plot(self.x_values, self.y_values)

	def show(self):
		"""Отображение графика"""
		plt.show()
