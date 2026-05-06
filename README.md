# Contact Book — Week 5

A C-based command-line contact manager that stores entries in a CSV file. Add, list, and search contacts through a simple interactive terminal interface. Data persists between sessions via file storage.

## Features

- Add new contacts with name, address, email, and phone number  
- List all saved contacts from the CSV file  
- Search contacts by matching any field (name, address, email, phone)  
- Persistent storage using a CSV file  
- Simple command-driven interface with help menu  
- Cross-platform terminal clearing (Windows/Linux)

## Usage

Run the program and use the following commands:

- `a` — Add new contact  
- `l` — List all contacts  
- `s` — Search contacts  
- `c` — Clear the terminal  
- `h` — Show help menu  
- `q` — Quit  

## Build

Compile using `gcc`:

```bash
gcc main.c -o contact_book