#ifndef CRAWLER_H
#define CRAWLER_H

#include "bag.h"
#include "hashtable.h"


typedef struct webpage {
    char* url;
    int depth;
    char* html;        // HTML content of the page
    size_t html_size;  // Size of the HTML content
} webpage_t;


void parseArgs(const int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth);

void pageScan(webpage_t *page, bag_t *pagesToCrawl, hashtable_t *pagesSeen);

webpage_t* webpage_new(const char* url, int depth);

void webpage_delete(webpage_t* page);

#endif