from glob import glob
import argparse
import os
import subprocess


def get_extension(filename):
    """Returns file's extension (without dot!)"""
    return filename.split(".")[-1]


def compress_jpg(filename, out_filename, replace):
    """Compresses a JPG image using ffmpeg"""
    cmd = ["ffmpeg"]
    # Replace files
    if replace:
        cmd += ["-y"]
    # Remaining arguments
    cmd += [
        "-i", filename,
        # TODO: Add compression level setting
        "-q:v", "3",
        out_filename
    ]
    subprocess.run(cmd)


def compress_png(filename, out_filename, replace):
    """Compresses a PNG image using ffmpeg"""
    cmd = ["ffmpeg"]
    # Replace files
    if replace:
        cmd += ["-y"]
    # Remaining arguments
    cmd += [
        "-i", filename,
        out_filename
    ]
    subprocess.run(cmd)


def parse_arguments():
    """Process input arguments"""
    parser = argparse.ArgumentParser(
        description="""A simple script for compressing jpg/png images with ffmpeg.
        Note that if the image is already compressed, using ffmpeg doesn't produce
        any results, or even enlarges the image. Applies both to jpg and png
        images.""")
    parser.add_argument("--output", "-o", metavar="DIR", default=".",
                        help="""output directory. If it doesn't exist, it'll be
                        created (default: current)""")
    parser.add_argument("--replace", "-r", action="store_true",
                        help="force replace files if there's any conflicts")
    parser.add_argument("FILE", nargs="*",
        help="file[s] to process (supports file masks)")
    return parser.parse_args()


def process_files(filenames, directory, replace):
    """Processes the files in the filenames list"""
    for filename in filenames:
        # Process each file
        for file in glob(filename):
            # Select the function according to the file type
            func = None
            if get_extension(file) in ["jpg", "jpeg"]:
                func = compress_jpg
            elif get_extension(file) == "png":
                func = compress_png
            func(file, os.path.join(directory, os.path.basename(file)), replace)


def main():
    """Entry point of the script"""
    # Get the inpur arguments
    args = parse_arguments()
    filenames = args.FILE
    directory = args.output
    replace = args.replace

    # Check the directory
    if not os.path.isdir(directory):
        os.mkdir(directory)

    # Process each pattern
    process_files(filenames, directory, replace)


# Entry point
if __name__ == "__main__":
    main()
