import sys

import pygame


def handle_events():
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit(0)


def update_screen(screen, settings, demotivator):
	screen.fill(settings.background_color)
	demotivator.blitme()
	pygame.display.flip()