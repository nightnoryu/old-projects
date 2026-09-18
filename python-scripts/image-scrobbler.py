import sys

from bs4 import BeautifulSoup
import requests


def download_image(url, name):
	'''Saves an image with the specified name'''
	img_file = open(name, 'wb')
	for chunk in requests.get(url):
			img_file.write(chunk)
	img_file.close()


# Check input parameters
if len(sys.argv) != 2:
	print('USAGE: {} [url]'.format(sys.argv[0]))
	sys.exit(1)
# Get the URL
url = sys.argv[1]

# Extract the URL's base name
splitted = url.split('/')
base_url = '/'.join(splitted[:3])

# Get the html page
response = requests.get(url)
markup = response.text
page = BeautifulSoup(markup, 'html.parser')


# Get all images
imgs = page.find_all('img')
# Get the overall amount of the images
amount = len(imgs)

# Inform and user
print('{} images will be downloaded.'.format(amount))
choice = input('Proceed (Y/n)?')
if not (choice == 'y' or choice == 'Y' or choice == ''):
	print('As you wish.')
	sys.exit(0)

# Set up the counter
n = 1
# Download all the images
for i in imgs:
	# Get the name
	img_name = i['src'].split('/')[-1]
	# Get the path
	img_path = '{}/{}'.format(base_url, i['src'])
	# Log
	print('{}/{} saving {}...'.format(n, amount, img_name))
	# Save the image
	download_image(img_path, img_name)
	n += 1
