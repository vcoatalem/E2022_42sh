#include "../parser.h"

char *rule_id_to_string(enum rule_id id)
{
    switch (id)
    {
    case RULE_NONE:
        return "none";
    case RULE_INPUT:
        return "input";
    case RULE_AND_OR:
        return "and|or";
    case RULE_AND_CONCAT:
        return "and";
    case RULE_OR_CONCAT:
        return "or";
    case RULE_PIPELINE:
        return "|";
    case RULE_PIPE:
        return "|";
    case RULE_COMMAND:
        return "command";
    case RULE_REDIR:
        return "redirection";
    case RULE_REDIR_TO:
        return "redirection_to";
    case RULE_REDIR_SYMBOL:
        return "redirection_symbol";
    case RULE_REDIR_LIST:
        return "redirection_list";
    case RULE_IONUMBER:
        return "ionumber";
    case RULE_ELEMENT:
        return "element";
    case RULE_ARG_LIST:
        return "args";
    default:
        return "unknown";
    }
}
