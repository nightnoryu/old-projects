import pygame

from times_msg import TimesMsg


class Demotivator():
	def __init__(self, screen, settings):
		self.settings = settings
		self.screen = screen
		self.screen_rect = screen.get_rect()

		# Load and scale image
		image = pygame.image.load("jak_fresko.jpg")
		self.image = pygame.transform.scale(
			image,
			(self.settings.image_width, self.settings.image_height))
		self.image_rect = self.image.get_rect()

		# Set image coords
		self.image_rect.centerx = self.screen_rect.centerx
		self.image_rect.centery = self.screen_rect.centery - 50

		# Create headings
		self.init_headings()
		# Create image border
		self.create_border()

	def create_border(self):
		"""Initializes border around image"""
		point_1 = (self.image_rect.left - self.settings.border_space,
			self.image_rect.top - self.settings.border_space)
		point_2 = (self.image_rect.right + self.settings.border_space,
			self.image_rect.top - self.settings.border_space)
		point_3 = (self.image_rect.right + self.settings.border_space,
			self.image_rect.bottom + self.settings.border_space)
		point_4 = (self.image_rect.left - self.settings.border_space,
			self.image_rect.bottom + self.settings.border_space)

		self.border_points = (point_1, point_2, point_3, point_4)

	def init_headings(self):
		"""Creates heading and subheading"""
		self.heading = TimesMsg(self.screen, self.settings, self.settings.heading, True)
		self.subheading = TimesMsg(self.screen, self.settings, self.settings.subheading)

		# Set headings coords
		self.heading.image_rect.centerx = self.image_rect.centerx
		self.heading.image_rect.top = self.image_rect.bottom + self.settings.border_space + 10

		self.subheading.image_rect.centerx = self.image_rect.centerx
		self.subheading.image_rect.top = self.heading.image_rect.bottom

	def blitme(self):
		"""Displays demotivator"""
		# Display image
		self.screen.blit(self.image, self.image_rect)
		# Display border
		pygame.draw.lines(self.screen,
			self.settings.border_color,
			True,
			self.border_points,
			self.settings.border_width)
		# Display captions
		self.heading.draw()
		self.subheading.draw()