
---

# WebM to MP4 Converter

A simple terminal-based tool to convert `.webm` files in the current directory to `.mp4` using `ffmpeg`. The program lists available `.webm` files and allows the user to select one for conversion.

## Features

- Automatically detects `.webm` files in the current directory.
- Converts the selected `.webm` file to `.mp4` format using `ffmpeg`.
- Outputs the converted `.mp4` file in the same directory.

## Prerequisites

- **ffmpeg**: Ensure that `ffmpeg` is installed on your system. You can install it using the following commands:
  ```bash
  # For Ubuntu or Debian
  sudo apt update
  sudo apt install ffmpeg

  # For macOS (using Homebrew)
  brew install ffmpeg
  ```

- **GCC**: Ensure you have GCC installed for compiling the C program.
  ```bash
  # For Ubuntu or Debian
  sudo apt install build-essential
  ```

## Compilation

To compile the program, run the following command in the terminal:

```bash
gcc -o webm_to_mp4_converter webm_to_mp4_converter.c -lavformat -lavcodec -lavutil -lswscale
```

## Usage

1. After compilation, run the program with:
   ```bash
   ./webm_to_mp4_converter
   ```

2. The program will display a numbered list of all `.webm` files in the current directory. You can select a file by entering its corresponding number.

3. The selected `.webm` file will be converted to `.mp4`, and the output will be saved in the same directory.

## Example Output

```
Available .webm files in the current directory:
1. sample1.webm
2. sample2.webm
3. video3.webm
Select a file to convert by entering its number: 1
Converting sample1.webm to sample1.mp4...
Conversion successful! Output file: sample1.mp4
```

## Contributing

Feel free to contribute by submitting a pull request or by creating issues for bugs or feature requests.

---
