
# Web Crawler

**Author**: Chris Camberos

---

## Overview

The **Web Crawler** is a tool designed to recursively fetch webpages starting from a given URL, save their HTML content to disk, and scan for further URLs to crawl. It is useful for indexing and exploring the web, while handling different depths of crawling based on user input.

---

## Features

- Fetches webpages and stores their HTML content.
- Recursively scans for and processes URLs on each fetched page.
- Supports configurable crawling depth.
- Uses efficient data structures like hashtables and bags for URL management.
- Implements multithreading using `libcurl` for faster web page retrieval.

---

## Files Overview

The project is modularized into different components, each with a specific purpose:

### Core Functionality
- **`crawler.c`**: Contains the main logic for the web crawler, including functions for fetching webpages, parsing command-line arguments, and scanning for new URLs.
- **`crawler.h`**: Header file declaring functions and data structures used by `crawler.c`.

### Page Directory Management
- **`pagedir.c`**: Handles initializing page directories and saving fetched webpages to disk.
- **`pagedir.h`**: Header file for `pagedir.c`, defining relevant function declarations and structures.

### URL Handling
- **`url.c`**: Provides functions for normalizing, validating, and checking URLs for proper formatting.
- **`url.h`**: Header file for `url.c`, defining related function declarations and structures.

### Data Structures
- **`bag.c`**: Implements a bag (multi-set) data structure for storing pages that need to be crawled.
- **`bag.h`**: Header file for `bag.c`, declaring the functions and structures related to the bag data structure.
- **`hashtable.c`**: Implements a hashtable for storing and efficiently managing visited webpages.
- **`hashtable.h`**: Header file for `hashtable.c`, providing function declarations and data structures for the hashtable.

### Webpage Fetching
- **`curl.c`**: Contains functions for downloading webpages using the `libcurl` library for efficient network operations.
- **`curl.h`**: Header file for `curl.c`, defining function declarations and structures related to `libcurl` functionality.

---

## Compilation

To compile the Web Crawler, simply use the provided `Makefile`. Open your terminal, navigate to the project directory, and run the following command:

```bash
make
```

This will compile all necessary files and create the executable.

---

## Usage

Once the program is compiled, you can run the crawler with the following command:

```bash
./crawler seedURL pageDirectory maxDepth
```

- **`seedURL`**: The starting URL where the crawler begins.
- **`pageDirectory`**: The directory where fetched HTML pages will be stored.
- **`maxDepth`**: The maximum depth the crawler will explore from the seed URL.

### Example:
```bash
./crawler https://example.com pages 3
```
This command will crawl the website `https://example.com`, store the pages in the `pages` directory, and crawl up to a depth of 3.

---

## Requirements

- **libcurl**: The project uses the `libcurl` library for fetching web pages. You need to have it installed on your system.
  - On Linux/macOS:
    ```bash
    sudo apt-get install libcurl4-openssl-dev
    ```
  - On macOS with Homebrew:
    ```bash
    brew install curl
    ```

---

## Troubleshooting

- If the program cannot fetch a webpage, ensure the seed URL is valid and reachable.
- Verify that the `pageDirectory` exists and has write permissions for saving fetched HTML files.
- Check your internet connection if you encounter issues downloading pages.

