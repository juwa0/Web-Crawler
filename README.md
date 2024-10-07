# Assignment 6 : Web Crawler
Chris Camberos
cacamber@ucsc.edu

## Description:
Crawler is a web crawler that fetches webpages, saves their HTML content, and scans for URLs to crawl further.

## Files and what they do:
- `crawler.c`: the main web crawler logic and implementation, including functions for fetching webpages,
               parsing command-line arguments, and scanning for URLs.
- `crawler.h`: header file with function declarations and data structures used in `crawler.c`.
- `pagedir.c`: functions for initializing a page directory and saving webpages to disk.
- `pagedir.h`: header file containing function declarations and data structures used in `pagedir.c`.
- `url.c`: functions for normalizing and checking URLs.
- `url.h`: header file containing function declarations and data structures used in `url.c`.
- `bag.c`: functions for a bag data structure used to store webpages to be crawled.
- `bag.h`: header file containing function declarations and data structures used in `bag.c`.
- `hashtable.c`: functions for a hashtable data structure used to store visited webpages.
- `hashtable.h`: header file containing function declarations and data structures used in `hashtable.c`.
- `curl.c`: functions for downloading webpages using libcurl.
- `curl.h`: header file containing function declarations and data structures used in `curl.c`.

## How to compile it:
To compile the program, just type make into the terminal and the Makefile will run and compile the program

## How to run it:
After compiling, you can run the program with the following command:
./crawler seedURL pageDirectory maxDepth
Replace `seedURL` with the starting URL, `pageDirectory` with the directory to save webpages, and `maxDepth` 
with the maximum depth for crawling.