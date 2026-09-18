import os


class CountriesScanner():
	"""Class for reading countries from file"""
	def __init__(self, filename, delimiter):
		self.delimiter = delimiter
		self.file = open(os.path.abspath(filename), encoding='utf-8')

		self.read_from_file()

	def read_from_file(self):
		"""Reads text from file and counts lines"""
		self.text = self.file.read()
		self.file.seek(0)
		self.lines = len(self.file.readlines())

	def get_countries_dict(self):
		"""Returns a dictionary of country-capital city"""
		# Format text
		formatted_text = self.text.replace('\n', ':')
		data_list = list(map(lambda s: s.strip(), formatted_text.split(self.delimiter)))

		# Form the dictionary
		countries_dict = {}
		for i in range(0, self.lines * 2, 2):
			countries_dict[data_list[i]] = data_list[i+1]

		return countries_dict