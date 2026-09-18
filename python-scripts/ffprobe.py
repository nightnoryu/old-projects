import json
import subprocess
import sys


def main(argv):
	if len(argv) != 1:
		print('USAGE: python ffprobe.py <file>')
		sys.exit(2)

	output = subprocess.check_output([
		'ffprobe',
		'-v', 'error',
		'-print_format', 'json',
		'-show_format',
		'-show_streams',
		argv[0]
	])
	data = json.loads(output)
	file_format, file_streams = [data[k] for k in ('format', 'streams')]

	for s in file_streams:
		print('Stream #{} {}'.format(s['index'], s['codec_type']))
		print('Codec: {}'.format(s['codec_name']))
		if s['codec_type'] == 'video':
			print('Resolution: {}x{}'.format(
				s.get('width', '?'), s.get('height', '?')
			))
		elif s['codec_type'] == 'audio':
			print('Sample rate: {}'.format(s.get('sample_rate', '?')))
		
		print('Duration: {}'.format(file_format['duration']))
		print()


if __name__ == "__main__":
		main(sys.argv[1:])
