//
//  dictionary.h
//  Dictionary
//
//  Created by Will Salisbury on 5/24/14.
//  Copyright (c) 2014 Pattern, LLC. All rights reserved.
//

#ifndef Dictionary_dictionary_h
#define Dictionary_dictionary_h

#define  MAX_KEY_LENGTH 255
#define  MAX_VALUE_LENGTH 255

typedef char*  DictionaryKeyType;
typedef char*  DictionaryValueType;


# pragma mark - Entry

typedef struct entry_s {
    DictionaryKeyType key;
    DictionaryValueType value;
    struct entry_s* next;
} Entry;


typedef Entry* EntryRef;

EntryRef entry_create(DictionaryKeyType, DictionaryValueType);
void entry_destroy(EntryRef* entry);

void entry_print(EntryRef entry);

# pragma mark - Table


typedef struct table_s {
    EntryRef* entries;
    size_t size;
} Table;

typedef Table* TableRef;

TableRef table_create(const size_t size);
void table_destroy(TableRef* table);

EntryRef table_get(const TableRef table, DictionaryKeyType key);
void table_set(const TableRef table, DictionaryKeyType key, DictionaryValueType value);

void table_print(TableRef table);


# pragma mark - Dictionary

typedef struct dict_s {
    TableRef table;
} Dictionary;

typedef Dictionary* DictionaryRef;


DictionaryRef dict_create(size_t size);
void dict_set(DictionaryRef dict, DictionaryKeyType key, DictionaryValueType value);
DictionaryValueType dict_get(DictionaryRef dict, DictionaryKeyType key);
void dict_print(DictionaryRef dict);
void dict_destroy(DictionaryRef *dict);

#endif
