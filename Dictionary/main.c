//
//  main.c
//  Dictionary
//
//  Created by Will Salisbury on 5/24/14.
//  Copyright (c) 2014 Pattern, LLC. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "dictionary.h"

int main(void)
{
    auto const size_t DICT_SIZE = 3;
    DictionaryRef dict = dict_create(DICT_SIZE);
    
    dict_set(dict, "a",  "foo");
    dict_set(dict, "b",  "bar");
    dict_set(dict, "c",  "alskjfal;skjf");
    dict_set(dict, "c",  "baz");
    dict_set(dict, "ab",  "qux");
    dict_set(dict, "ba",  "qux");
    
    dict_print(dict);
    
    DictionaryValueType val = dict_get(dict, "a");
    assert(val && "<val> does not exist after <dict_insert>.");
    assert((strncmp(val,"foo",MAX_VALUE_LENGTH) == 0 ) && "'a' not 'foo' after setting 'a'->'foo'.");
    
    dict_destroy(&dict);
    assert(!dict && "<dict> not NULL after <dict_destroy>");
    
    exit(EXIT_SUCCESS);
}

