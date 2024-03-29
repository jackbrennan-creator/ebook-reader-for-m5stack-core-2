#pragma once

#include "ink_plate.hpp"

const unsigned long milliseconds = 1;
const unsigned long seconds      = 1000 * milliseconds;

enum orientation {portrait = 1, landscape = 2, inverted_portrait = 3, inverted_landscape = 4};

enum button {no_button, menu_button, previous_button, next_button};

extern ink_plate*   display;

void   init_screen();

void   set_orientation(orientation new_orientation);

int    font_height();

int    font_height(const GFXfont* font);

int    string_width(const char* s);

void   redisplay();

button get_button();

void   wait_for_any_button();

void   reduce_power(unsigned long interval_milliseconds);
