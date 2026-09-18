import qrcode
from pyzbar.pyzbar import decode
from PIL import Image


def encode_qr(data, file_name):
    qr = qrcode.QRCode(version=1, box_size=10, border=5)
    qr.add_data(data)
    qr.make(fit=True)
    img = qr.make_image(fill_color="black", back_color="white")
    img.save(file_name)


def decode_qr(file_name):
    img = Image.open(file_name)
    result = decode(img)[0]
    return result.data.decode('utf-8')


def main():
    """Main function"""
    encode_qr("Sneed's Feed and Seed", "test.png")
    print(decode_qr("test.png"))


# Entry point
if __name__ == "__main__":
    main()
