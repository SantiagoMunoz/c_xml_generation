#ifndef _{{opname.upper()}}_H_
#define _{{opname.upper()}}_H_

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/parser.h>


{% set child = root %}
{% set parent = root %}
{% include 'templates/struct_function_dec_.ji2' %}

#endif /* _{{opname.upper()}}_H_ */
