#! /usr/bin/python
# Isaiah Grace

# To access the keyboard, we need these four peices of info: 
#define VENDOR_ID       0x3297
#define PRODUCT_ID      0xC6CF
#define RAW_USAGE_PAGE  0xFF60
#define RAW_USAGE_ID    0x61

import hid
import pprint as pp
import random

# Wheelwriter30
VENDOR_ID = 0xFEED
PRODUCT_ID = 0x6060
INTERFACE_NUMBER = 1

# planck ez glow
#VENDOR_ID = 0x3297
#PRODUCT_ID = 0xC6CF
#INTERFACE_NUMBER = 1

# so the path i want is /dev/hidraw4 but that's not guaranteed to stay the same
# I will get this path by using the VENDOR_ID and the interface_numer
# But i'm not sure that the interface number is stable either...
# Ideally I'd like to find a way to be certain that I'm picking the RAW_HID interface that is controlled by my custom code within the QMK firmware
dev_info = [x for x in hid.enumerate() if x['vendor_id'] == VENDOR_ID and x['interface_number'] == INTERFACE_NUMBER][0]

pp.pprint(dev_info)

packet = random.choices(range(256),k=50)

dev = hid.device()
dev.open_path(dev_info['path'])
print('opened',dev_info['path'])


dev.write(packet)
num_sent = len(packet)
recv = []
while (num_sent > 32):
    recv = recv + dev.read(32)
    num_sent = num_sent - 32

recv = recv + dev.read(num_sent)
dev.close()

if recv != packet:
    print('recv != packet')
else:
    print('looks good')

packet = ['{:02x}'.format(n) for n in packet]
recv = ['{:02x}'.format(n) for n in recv]

packet = ' '.join([i+j for i,j in zip(packet[::2],packet[1::2])])
recv = ' '.join([i+j for i,j in zip(recv[::2],recv[1::2])])

print(packet)
print(recv)
    

