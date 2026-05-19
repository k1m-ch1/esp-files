SEND_0_CODE = r"""
LED_PORT |= (1 << LED_PIN);
__asm__("nop\nnop\nnop\nnop\n");
LED_PORT &= ~(1 << LED_PIN);
__asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
"""

SEND_1_CODE = r"""
 LED_PORT |= (1 << LED_PIN);
__asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
LED_PORT &= ~(1 << LED_PIN);
__asm__("nop\nnop\nnop\nnop\nnop\n");
"""

send_code = [
    SEND_0_CODE,
    SEND_1_CODE
]

def send_byte(byte_to_send):
    print(f"// sending byte 0x{hex(byte_to_send)[2:]:08}")
    for i in range(7, -1, -1):
        bit_to_send = (byte_to_send >> i) & 0b1
        print(f"// sending {bit_to_send}")
        print(send_code[bit_to_send])

if __name__ == "__main__":
    color = 0xff00ff
    # a nibble is 4 bits
    red_byte = (color >> (2*8)) & 0xff
    green_byte = (color >> (1*8)) & 0xff
    blue_byte = color & 0xff
    #print(f"redByte: {red_byte}")
    #print(f"greenByte: {green_byte}")
    #print(f"blueByte: {blue_byte}")
    # order is GRB
    #send_byte(red_byte)
    send_byte(green_byte)
    send_byte(red_byte)
    send_byte(blue_byte)
