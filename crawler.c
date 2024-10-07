#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "crawler.h"
#include "pagedir.h"
#include "url.h"
#include "bag.h"
#include "hashtable.h"
#include <stdbool.h>
#include "curl.h"
#include <libgen.h>

#define MAX_VISITS_PER_SUBSECTION 15
#define MAX_CRAWL_DEPTH 4

// gets html of webpage 
const char* webpage_getHTML(const webpage_t* page) {
    if (page == NULL) return NULL;
    return page->html;
}

// gets the URL of a webpage
const char* webpage_getURL(const webpage_t* page) {
    if (page == NULL) return NULL;
    return page->url;
}

// gets the depth of a webpage
int webpage_getDepth(const webpage_t* page) {
    if (page == NULL) return -1;
    return page->depth;
}

// fetches the HTML content for the given webpage
bool webpage_fetch(webpage_t* page) {
    if (page == NULL || page->url == NULL) return false;

    size_t html_size;
    char* html = download(page->url, &html_size);

    if (html == NULL) {
        fprintf(stderr, "Error: Failed to fetch URL %s\n", page->url);
        return false;
    }

    page->html = html;
    page->html_size = html_size;

    return true;
}

// makes a new webpage object
webpage_t* webpage_new(const char* url, int depth) {
    if (url == NULL) return NULL;

    webpage_t* page = malloc(sizeof(webpage_t));
    if (page == NULL) return NULL;

    page->url = strdup(url);
    page->depth = depth;
    page->html = NULL;

    return page;
}

// deletes the webpage object and frees its memory
void webpage_delete(webpage_t* page) {
    if (page != NULL) {
        free(page->url);
        free(page->html);
        free(page);
    }
}
// fixes type mismatch error
void webpage_delete_wrapper(void *item) {
    webpage_delete((webpage_t *)item);
}

/**
 * Parses command-line arguments, placing the corresponding values into the pointer arguments seedURL,
 * pageDirectory and maxDepth. argc and argv should be passed in from the main function.
 */
void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s seedURL pageDirectory maxDepth\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    *seedURL = strdup(argv[1]);
    *pageDirectory = strdup(argv[2]);
    *maxDepth = atoi(argv[3]);

    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "Invalid maxDepth value. It should be in the range [0, 10]\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Crawls webpages given a seed URL, a page directory and a max depth.
 */
static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    hashtable_t *pagesSeen = hashtable_new(100);
    bag_t *pagesToCrawl = bag_new();

    if (!pagedir_init(pageDirectory)) {
        exit(EXIT_FAILURE);
    }

    webpage_t *seedPage = webpage_new(seedURL, 0);
    hashtable_insert(pagesSeen, seedURL, seedURL);
    bag_insert(pagesToCrawl, seedPage);

    int documentID = 1;

    while (!bag_is_empty(pagesToCrawl)) {
        webpage_t *page = bag_extract(pagesToCrawl);

        if (webpage_fetch(page)) {
            pagedir_save(page, pageDirectory, documentID++);

            if (webpage_getDepth(page) < maxDepth) {
                pageScan(page, pagesToCrawl, pagesSeen);
            }
        }

        webpage_delete(page);
    }

    hashtable_delete(pagesSeen, NULL);
    bag_delete(pagesToCrawl, webpage_delete_wrapper);
}

/**
 * Scans a webpage for URLs.
 */
void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen) {
    static hashtable_t *subsectionCount = NULL;

    if (subsectionCount == NULL) {
        subsectionCount = hashtable_new(100);
    }

    const char *html = webpage_getHTML(page);
    char *start = (char *)html;
    char *end;
    char *url;

    while ((start = strstr(start, "<a ")) != NULL) {
        char *href_start = strstr(start, "href=");
        if (href_start != NULL) {
            href_start += 5;
            if (*href_start == '"' || *href_start == '\'') {
                char quote = *href_start;
                href_start++;
                end = strchr(href_start, quote);

            } else {
                end = strpbrk(href_start, " \t\n>");
            }

            if (end != NULL) {
                url = strndup(href_start, end - href_start);
                normalizeURL(url, webpage_getURL(page));
                if (url[0] != '#' && strcmp(url, "#") != 0 && !hashtable_find(pagesSeen, url)) {
                    if (isInternalURL(webpage_getURL(page), url)) {
                        char *subsection = dirname(strdup(url)); 
                        int *visitCount = hashtable_find(subsectionCount, subsection);
                        if (visitCount == NULL) {
                            visitCount = malloc(sizeof(int));
                            *visitCount = 1;
                            hashtable_insert(subsectionCount, subsection, visitCount);
                        } else {
                            (*visitCount)++;
                        }

                        if (*visitCount <= MAX_VISITS_PER_SUBSECTION) {
                            hashtable_insert(pagesSeen, url, url);
                            if (webpage_getDepth(page) + 1 <= MAX_CRAWL_DEPTH) {
                                webpage_t *newPage = webpage_new(url, webpage_getDepth(page) + 1);
                                bag_insert(pagesToCrawl, newPage);
                            } else {
                                free(url);
                            }
                        } else {
                            free(url);
                        }

                        free(subsection);
                    } else {
                        free(url);
                    }
                } else {
                    free(url);
                }
            }
        }
        start = end;
    }
}


int main(const int argc, char* argv[]) {
    char *seedURL, *pageDirectory;
    int maxDepth;

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);

    return 0;
}

