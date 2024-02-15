import sys
import string
import binascii

def reverse_bytes(hex_string):
    # Split the string into groups of four characters
    groups = [hex_string[i:i+2] for i in range(0, len(hex_string), 2)]
    # Reverse the order of the groups
    reversed_groups = groups[::-1]
    # Join the groups back into a single string
    reversed_string = ''.join(reversed_groups)
    return reversed_string

def generate_pattern(size):
    # Generate the pattern
    pattern = ''.join(f'A{letter}{number}' for letter in string.ascii_lowercase for number in range(10))
    # Truncate or repeat the pattern to match the desired size
    return (pattern * (size // len(pattern)) + pattern[:size % len(pattern)])

def find_crash_size(crash_string):
    # Generate a large pattern
    pattern = generate_pattern(10000)
    # Find the crash string in the pattern

    reversed_string = reverse_bytes(crash_string)
    ascii_string = binascii.unhexlify(reversed_string).decode()

    index = pattern.find(ascii_string)
    if index == -1:
        print("Crash string not found in pattern.")
    else:
        print(f"Buffer crashed at size: {index}")

if __name__ == "__main__":
    if len(sys.argv) > 2 and sys.argv[1] == "--crash":
        find_crash_size(sys.argv[2])
    elif len(sys.argv) > 1:
        size = int(sys.argv[1])
        print(generate_pattern(size))
    else:
        print("Please provide a size or a crash string.")