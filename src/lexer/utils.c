int is_separator(char c)
{
    return (c == ' ' || c == '\t' || c == '|' || c == '&' || c == '\n'
            || c == '\0' || c == '<' || c == '>'
            || c == ';' || c == ')' || c == '(');
}

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

