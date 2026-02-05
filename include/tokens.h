#ifndef TOKENS_H
#define TOKENS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

enum Tokens {
    VAR_TOKEN,      /* var */
    PLUS_TOKEN,     /* "+" */
    MINUS_TOKEN,    /* "-" */
    MULTI_TOKEN,    /* "*" */
    DIV_TOKEN,      /* "/" */
    VOID_TOKEN,     /* void */
    U8_TOKEN,       /* uint8_t */
    U16_TOKEN,      /* uint16_t */
    U32_TOKEN,      /* uint32_t */
    U64_TOKEN,      /* uint64_t */
    NUM_TOKEN,      /* 0-9 */
    BRACKET_OPEN_TOKEN,     /* { */
    BRACKET_CLOSE_TOKEN,    /* } */
    PARENTHESIS_OPEN_TOKEN, /* ( */
    PARENTHESIS_CLOSE_TOKEN,/* ) */
    SEMICOLON_TOKEN,        /* ; */
    COMMA_TOKEN,            /* , */
};

#endif