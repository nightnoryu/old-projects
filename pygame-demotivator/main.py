import pygame

from settings import Settings
from demotivator import Demotivator
import game_functions as gf


def main():
	# Main function
	pygame.init()
	pygame.display.set_caption("oh shit")
	settings = Settings()
	screen = pygame.display.set_mode((settings.screen_width, settings.screen_height))

	# Create demotivator
	demotivator = Demotivator(screen, settings)

	# Game cycle
	while True:
		gf.handle_events()
		gf.update_screen(screen, settings, demotivator)


if __name__ == "__main__":
	main()