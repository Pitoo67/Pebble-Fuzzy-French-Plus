#pragma once

#include "pebble_app.h"
#include "mini-printf.h"

#define LINE_BUFFER_SIZE 50

void fuzzy_time(PblTm* t, char* str_line1, char* str_line2, char* str_line3);

void info_lines(PblTm* t, char* str_line1, char* str_line2);