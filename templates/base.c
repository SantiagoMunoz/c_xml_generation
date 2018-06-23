#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "{{prefix}}.h"
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>

char scratchpad[64];

/* --- TYPE DECLARATIONS --- */
{% set child = root %}
{% set parent = root %}
{% include 'templates/struct_definitions_.ji2' %}

/* --- FUNCTIONS IMPLEMENTATION --- */
{% set child = root %}
{% set parent = root %}
{% include 'templates/struct_function_impl_.ji2' %}

