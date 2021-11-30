#ifndef AMPI_PARSER_H
#define AMPI_PARSER_H

enum _ParserStatus
{
    PARSER_SUCCESS,
    PARSER_ERROR
};
typedef enum _ParserStatus ParserStatus;

struct _Parser
{
    ParserStatus status;
};

#endif