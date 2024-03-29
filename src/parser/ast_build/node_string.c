#include "../parser.h"

char *rule_id_to_string(enum rule_id id)
{
    switch (id)
    {
    case RULE_NONE:
        return "none";
    case RULE_INPUT:
        return "input";
    case RULE_LIST_DELIM:
        return "list_delim";
    case RULE_LIST_CONCAT:
        return "list_concat";
    case RULE_LIST:
        return "list";
    case RULE_COMPOUND_LIST_BREAK:
        return "compound_list_break";
    case RULE_COMPOUND_LIST_BREAK_DELIM:
        return "compound_list_break_delim";
    case RULE_COMPOUND_LIST_BREAK_CONCAT:
        return "compound_list_break_concat";
    case RULE_COMPOUND_LIST_BREAK_LINE:
        return "compound_list_break_empty_lines";
    case RULE_COMPOUND_LIST_DELIM:
        return "list_delim";
    case RULE_COMPOUND_LIST_CONCAT:
        return "list_concat";
    case RULE_COMPOUND_LIST:
        return "list";
    case RULE_COMPOUND_LIST_NEXT:
        return "list_next";
    case RULE_AND_OR:
        return "and|or";
    case RULE_OR:
        return "or";
    case RULE_AND_CONCAT:
        return "and_concat";
    case RULE_AND_LINEBREAK:
        return "and_linebreak";
    case RULE_OR_CONCAT:
        return "or_concat";
    case RULE_OR_LINEBREAK:
        return "or_linebreak";
    case RULE_PIPELINE:
        return "pipeline";
    case RULE_PIPE:
        return "pipe";
    case RULE_COMMAND:
        return "command";
    case RULE_COMMAND_NOT:
        return "command_not";
    case RULE_SIMPLE_COMMAND:
        return "simple_command";
    case RULE_SHELL_COMMAND:
        return "shell_command";
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
    case RULE_ELEMENT_SUBSHELL:
        return "element_subshell";
    case RULE_ELEMENT_EXPAND:
        return "element_expand";
    case RULE_ELEMENT_ARITHMETIC:
        return "element_arithmetic";
    case RULE_ELEMENT_TILDE:
        return "element_tilde";
    case RULE_ELEMENT_NO_SUBSTITUTION:
        return "element_no_substitution";
    case RULE_ELEMENT_ANY:
        return "element";
    case RULE_ELEMENT_LIST:
        return "element list";
    case RULE_ELEMENT_ANY_LIST:
        return "element list";
    case RULE_ARG_LIST:
        return "args";
    case RULE_IF:
        return "if";
    case RULE_THEN:
        return "then";
    case RULE_ELSE_CONCAT:
        return "else";
    case RULE_DO_GROUP:
        return "do_group";
    case RULE_WHILE:
        return "while";
    case RULE_UNTIL:
        return "until";
    case RULE_FUNCDEC:
        return "funcdec";
    case RULE_FUNCDEC_BODY:
        return "funcdec_body";
    case RULE_VARDEC:
        return "var_declaration";
    case RULE_CASE:
        return "case";
    case RULE_CASE_ITEM:
        return "case_item";
    case RULE_CASE_ITEM_CONCAT:
        return "case_item_concat";
    case RULE_CASE_CLAUSE:
        return "case_clause";
    case RULE_CASE_CLAUSE_CONCAT:
        return "case_clause";
    case RULE_FOR:
        return "for";
    case RULE_FOR_CLAUSE:
        return "for_clause";
    case RULE_FOR_DELIM:
        return "for_delim";
    case RULE_FOR_LINEBREAK:
        return "for_linebreak";
    case RULE_FOR_ELEMENT_LIST:
        return "for_element_list";
    default:
        return "unknown";
    }
}
