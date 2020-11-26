#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>

#define FOREACH_FRUIT(FRUIT) \
        FRUIT(apple)   \
        FRUIT(orange)  \
        FRUIT(grape)   \
        FRUIT(banana)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum FRUIT_ENUM {
    FOREACH_FRUIT(GENERATE_ENUM)
};

static const char *FRUIT_STRING[] = {
    FOREACH_FRUIT(GENERATE_STRING)
};




main()
{
    printf("%s\n",FRUIT_STRING[apple]);
    printf("%s\n",FRUIT_STRING[orange]);
    //printf("%d", -1 < 0u);
    printf("%d", 0u > -1);
}
