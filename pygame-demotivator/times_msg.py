import pygame


class TimesMsg():
	def __init__(self, screen, settings, msg, heading=False):
		self.settings = settings
		self.screen = screen
		self.msg = msg

		# Set up font
		if heading:
			self.font = pygame.font.SysFont("Times New Roman", self.settings.heading_font_size, bold=True)
		else:
			self.font = pygame.font.SysFont("Times New Roman", self.settings.subheading_font_size)
		self.prep_msg()

	def prep_msg(self):
		"""Creates message image"""
		self.image = self.font.render(self.msg, True, self.settings.caption_color)
		self.image_rect = self.image.get_rect()

	def draw(self):
		"""Outputs message"""
		self.screen.blit(self.image, self.image_rect)