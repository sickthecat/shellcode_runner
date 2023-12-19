from Crypto.Random import get_random_bytes

def generate_rc4_key(key_length):
    """
    Generates a random key for RC4 encryption.

    :param key_length: Length of the key in bytes.
    :return: The generated key in hexadecimal format.
    """
    key = get_random_bytes(key_length)
    return key.hex()

# Example usage
key_length = 16  # You can choose the length of the key, e.g., 16 bytes (128 bits)
key = generate_rc4_key(key_length)
print(f"RC4 Key (Hex): {key}")
