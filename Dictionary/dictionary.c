//
//  dictionary.c
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

#pragma mark - Declarations

static size_t hash_key(DictionaryKeyType, size_t);
static void entry_set_value(EntryRef entry, DictionaryValueType val);

#pragma mark - Entry

EntryRef entry_create(DictionaryKeyType key, DictionaryValueType value){
    Entry * entry = (Entry*)malloc(sizeof(Entry));
    char* newKey = (char*)malloc(sizeof(char) * MAX_KEY_LENGTH);
    char* newValue = (char*)malloc(sizeof(char) * MAX_KEY_LENGTH);
    
    entry->key = newKey;
    entry->value = newValue;
    entry->next = NULL;
    
    
    strncpy(entry->key, key, MAX_KEY_LENGTH);
    strncpy(entry->value, value, MAX_VALUE_LENGTH);
    
    return entry;
}

void entry_destroy(EntryRef* entry){
    EntryRef e = *entry;
    
    memset(e->key, '\0', MAX_KEY_LENGTH);
    memset(e->value, '\0', MAX_VALUE_LENGTH);
    e->next = NULL;
    
    free(e->key);
    free(e->value);
    free(e);
    e = NULL;
    
    *entry = NULL;
}

void entry_print(EntryRef entry){
    if(NULL == entry){
        fprintf(stdout, " -> %s", "ø");
    } else {
        while(NULL != entry){
            fprintf(stdout, " -> ('%s', '%s')", entry->key, entry->value);
            entry = entry -> next;
        }
    }
}

void entry_set_value(EntryRef entry, DictionaryValueType val){
    assert(entry);
    
    strncpy(entry->value, val, MAX_VALUE_LENGTH);
}

#pragma mark - Table

TableRef table_create(const size_t size){
    TableRef table = NULL;
    
    table = (TableRef)malloc(sizeof(Table));
    if(NULL == table){
        return NULL;
    }
    
    table->size = size;
    table->entries = (EntryRef*)malloc(sizeof(Entry*) * size);
    if(NULL == table->entries){
        free(table);
        table = NULL;
        return table;
    }
    
    for(int iter = 0; iter < table->size; ++iter){
        table->entries[iter] = NULL;
    }
    
    return table;
}

void table_destroy(TableRef* table){
    TableRef t = *table;
    
    EntryRef* entries = t->entries;
    if(NULL != entries){
        for (size_t iter = 0; iter < t->size; ++iter) {
            EntryRef entry = entries[iter];
            while(NULL != entry){
                EntryRef next = entry->next;
                entry_destroy(&entry);
                entry = next;
            }
        }
        free(entries);
    }
    t->size = 0;
    t->entries = NULL;
    
    free(t);
    *table = NULL;
}

EntryRef table_get(const TableRef table, DictionaryKeyType key){
    assert(table && table->entries);
    
    size_t bucket = hash_key(key, table->size);
    
    EntryRef entry = table->entries[bucket];
    if(NULL == entry){
        return NULL;
    }
    
    if(strncmp(entry->key, key, MAX_KEY_LENGTH) == 0){
        return entry;
    }
    
    
    
    return entry;
}

void table_set(TableRef table, DictionaryKeyType key, DictionaryValueType value){
    assert(table && table->entries);
    
    size_t bucket = hash_key(key, table->size);
    
    EntryRef entry = table->entries[bucket];
    if(NULL == entry){
        table->entries[bucket] = entry_create(key, value);
    } else {
        EntryRef prev = NULL;
        while(entry != NULL){
            EntryRef next = entry->next;
            
            if(strncmp(entry->key, key, MAX_KEY_LENGTH) == 0){
                entry_set_value(entry, value);
                return;
            }
            
            prev = entry;
            entry = next;
        }
        prev->next = entry_create(key, value);
    }
}

void table_print(TableRef table){
    assert(table);
    
    for (size_t iter = 0; iter < table->size; ++iter) {
        fprintf(stdout, "[%lu]", iter);
        entry_print(table->entries[iter]);
        fprintf(stdout, "\n");
    }
}

static size_t hash_key(DictionaryKeyType key, size_t size){
    size_t bucket = 0;
    size_t sum = 0;
    char * head = (char *)key;
    
    while('\0' != *head){
        sum += (size_t)*head;
        head = (head+1);
    }
    
    bucket = (size_t)(sum % size);
    return bucket;
}

#pragma mark - Dictionary

DictionaryRef dict_create(size_t size){
    assert(size);
    
    DictionaryRef dict = NULL;
    
    dict = (DictionaryRef)malloc(sizeof(Dictionary));
    if(NULL == dict){
        return NULL;
    }
    
    dict->table = table_create(size);
    if(NULL == dict->table){
        free(dict);
        dict = NULL;
        return dict;
    }
    
    return dict;
}

void dict_set(DictionaryRef dict, DictionaryKeyType key, DictionaryValueType value){
    
    table_set(dict->table, key, value);
}

DictionaryValueType dict_get(DictionaryRef dict, DictionaryKeyType key){
    EntryRef entry = table_get(dict->table, key);
    
    if(NULL == entry){
        return NULL;
    }
    
    DictionaryValueType val = entry->value;
    
    return val;
}

void dict_print(DictionaryRef dict){
    assert(dict);
    fprintf(stdout, "%s\n", "\tDictionary");
    table_print(dict->table);
}

void dict_destroy(DictionaryRef *dict){
    assert(dict && "Trying to destroy <dict>, a NULL <DictionaryRef*>");
    
    DictionaryRef d = *dict;
    if(NULL != d){
    
        TableRef table = d->table;
        if(NULL != table){
            
            table_destroy(&table);
            table = NULL;
            
        }
        
        free(d);
        *dict = NULL;
    }
}














