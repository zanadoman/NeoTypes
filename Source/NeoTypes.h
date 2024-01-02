#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

//_____________________________________________NeoTypes.h____________________________________________//

#define true 1
#define false 0
/*Logical variable just like bool or boolean*/
typedef unsigned char logic;
typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;

#define ARRAY_SIZE (sizeof(void*) + sizeof(uint64))
/*Dynamically sized array, with insertion and deletion capabilities*/
typedef struct arrayStruct* array;
#define STRING_SIZE (sizeof(void*) + sizeof(uint64))
/*String that holds String and Length data*/
typedef struct stringStruct* string;

/*Universal data type for NeoTypes*/
typedef union
{
    logic Logic;

    uint64 uInt;
    sint64 sInt;
    double Double;

    array Array;
    string String;

    void* Pointer;
} NeoTypes;

//_____________________________________________NeoArray.c____________________________________________//

struct arrayStruct
{
    NeoTypes* Values;
    uint64 Length;
};

/*Creates a new Array with the given Length.
Returns the address of the newly allocated Array.
You must initialize every Array with this function before use.*/
array arrNew(uint64 Length);
/*Returns an Element from the Array at the given Index.
Assign a value to an Element: arrElement(Array, Index)->uInt = 10;
Get a value from an Element: uint8 a = arrElement(Array, Index)->uInt;*/
NeoTypes* arrElement(array Array, uint64 Index);
/*Inserts a new Element to the Array at the given Index.
Returns the address of the new Element.
The default value of the new Element is 0.
Set the value of the new Element: arrInsert(Array, Index)->uInt = 10;*/
NeoTypes* arrInsert(array Array, uint64 Index);
/*Removes an element from the Array at the given Index.*/
uint8 arrRemove(array Array, uint64 Index);
/*Frees the Array from the memory with all of its Elements.*/
uint8 arrPurge(array Array);

//____________________________________________NeoString.c____________________________________________//

struct stringStruct
{
    char* String;
    uint64 Length;
};

uint64 strLength(char* Characters);

string strNew();

uint8 strInit(string String, char* Characters);
uint8 strAppend(string String, char Character);

uint8 strConcat(string String, uint64 Count, char* Characters, ...);
uint8 strRead(string String);
uint8 strSplit(array Array, char* Characters, char Character);

logic strCompare(char* Characters1, char* Characters2);

uint8 strPurge(string String);

//____________________________________________NeoConvert.c___________________________________________//

uint64 STRtoUINT(char* Characters, logic* Success);
uint8 UINTtoSTR(uint64 Number, string String);

sint64 STRtoSINT(char* Characters, logic* Success);
uint8 SINTtoSTR(sint64 Number, string String);

double STRtoDOUBLE(char* Characters, logic* Success);
uint8 DOUBLEtoSTR(double Number, string String);

//_____________________________________________NeoFile.c_____________________________________________//

uint8 fileRead(char* FilePath, array Lines);
uint8 fileWrite(array Lines, char* FilePath);

//____________________________________________NeoMemory.c____________________________________________//

void* memCopy(void* Source, uint64 Size);
uint8 memCopyTo(void* Source, void* Destination, uint64 Size);

void* memLoad(char* FilePath, uint64 Size);
uint8 memLoadTo(char* FilePath, void* Destination, uint64 Size);
uint8 memSave(void* Source, uint64 Size, char* FilePath);