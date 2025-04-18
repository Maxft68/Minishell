void    is_quoted(char *line)
{
    int sq;
    int dq;
    int i;

    sq = 0;
    dq = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '\'')
            sq++;
        if (line[i] == '\"')
            dq++;
        
    }
}