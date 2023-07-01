#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max_lines 50
#define max_length 50

/// This function exits out of verification loops as soon as it sees an invalid argument
void InvalidExit()
{
    printf("Invalid Proof\n");
    exit(1);
}

/// This function compares the And Introduction Rule used in the User-inputted sequent and the the definition of And Introduction rule
void AndIntro(char *S, char *P, char *Q)
{
    char C[max_length];
    strcpy(C, "(");
    strcat(C, P);
    strcat(C, "^");
    strcat(C, Q);
    strcat(C, ")");
    if (strcmp(S, C) != 0)
    {
        InvalidExit();
    }
}

/// This function compares the And Elimination-1 Rule used in the User-inputted sequent and the definiton of And Elimination-1 Rule
void AndEli1(char *S, char *P)
{
    char C[max_length];
    int v = 0;
    for (int i = 1; i < max_length; i++)
    {
        if (P[i] == '\0')
        {
            InvalidExit();
        }
        else
        {
            C[i - 1] = P[i];
            if (P[i] == '(')
            {
                v++;
            }
            else if (P[i] == ')')
            {
                v--;
            }
            else if (P[i] == '^' && v == 0)
            {
                C[i - 1] = '\0';
                break;
            }
        }
    }
    if (strcmp(C, S) != 0)
    {
        InvalidExit();
    }
}

/// This function compares the And Elimination-2 Rule used in the User-inputted sequent and the definiton of And Elimination-2 Rule
void AndEli2(char *S, char *P)
{
    char C[max_length];
    int v = 0;
    for (int i = 1; i < max_length; i++)
    {
        if (P[i] == '\0')
        {
            InvalidExit();
        }
        else
        {
            if (P[i] == '(')
            {
                v++;
            }
            else if (P[i] == ')')
            {
                v--;
            }
            else if (P[i] == '^' && v == 0)
            {
                for (int j = i + 1; j < max_length; j++)
                {
                    if (P[j + 1] != '\0')
                    {
                        C[j - i - 1] = P[j];
                    }
                    else
                    {
                        C[j - i - 1] = '\0';
                        break;
                    }
                }
                break;
            }
        }
    }
    if (strcmp(C, S) != 0)
    {
        InvalidExit();
    }
}

/// This function applies the Or Introduction-1 rule based on its definition and compares it to the Or Introduction-1 rule used by the User in the input
void OrIntro1(char *S, char *P)
{
    char C[max_length];
    int v = 0;
    for (int i = 1; i < max_length; i++)
    {
        if (S[i] == '\0')
        {
            InvalidExit();
        }
        else
        {
            C[i - 1] = S[i];
            if (S[i] == '(')
            {
                v++;
            }
            else if (S[i] == ')')
            {
                v--;
            }
            else if (S[i] == 'v' && v == 0)
            {
                C[i - 1] = '\0';
                break;
            }
        }
    }
    if (strcmp(C, P) != 0)
    {
        InvalidExit();
    }
}

/// This function applies the Or Introduction-2 rule based on its definition and compares it to the Or Introduction-2 rule used by the User in the input
void OrIntro2(char *S, char *P)
{
    char C[max_length];
    int v = 0;
    for (int i = 1; i < max_length; i++)
    {
        if (S[i] == '\0')
        {
            InvalidExit();
        }
        else
        {
            if (S[i] == '(')
            {
                v++;
            }
            else if (S[i] == ')')
            {
                v--;
            }
            else if (S[i] == 'v' && v == 0)
            {
                for (int j = i + 1; j < max_length; j++)
                {
                    if (S[j + 1] != '\0')
                    {
                        C[j - i - 1] = S[j];
                    }
                    else
                    {
                        C[j - i - 1] = '\0';
                        break;
                    }
                }
                break;
            }
        }
    }
    if (strcmp(C, P) != 0)
    {
        InvalidExit();
    }
}

/// This function applies the Implication Elimination rule based on its definition and compares it to the Implication Elimination rule used by the User in the input
void ImpEli(char *S, char *P, char *Q)
{
    char C[max_length];
    strcpy(C, "(");
    strcat(C, Q);
    strcat(C, ">");
    strcat(C, S);
    strcat(C, ")");
    if (strcmp(C, P) != 0)
    {
        InvalidExit();
    }
}

/// This function compares the definition of the Modus Tollens rule and how it is used in the sequent that the User has proved
void ModusT(char *S, char *P, char *Q)
{
    char C[max_length];
    if (!((Q[0] == '~') && (S[0] == '~')))
    {
        InvalidExit();
    }
    strcpy(C, "(");
    int i;
    for (i = 1; i < max_length; i++)
    {
        if (S[i] == '\0')
        {
            break;
        }
        C[i] = S[i];
    }
    strcat(C, ">");
    for (int j = 1; j < max_length; j++)
    {
        C[i + j] = Q[j];
        if (Q[j] == '\0')
        {
            break;
        }
    }
    strcat(C, ")");
    if (strcmp(C, P) != 0)
    {
        InvalidExit();
    }
}

/// This function assimilates all the proof rules together.
///
/// It reads each line from the user input, which is stored as an array of strings (which themselves are arrays of characters) and verifies the vaidity of the proof rule corresponding to it
void checkvalidity(char S[max_lines][max_length], int N)
{
    char s[max_lines][max_length];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < max_length; j++)
        {
            if (S[i][j] == '/')
            {
                s[i][j] = '\0';
                j++;
                if (S[i][j] == '^')
                {
                    if (S[i][j + 1] == 'i' && S[i][j + 2] == '/')
                    {
                        int h = S[i][j + 3] - '0' - 1, k = S[i][j + 5] - '0' - 1;
                        AndIntro(s[i], s[h], s[k]);
                    }
                    else if (S[i][j + 1] == 'e')
                    {
                        if (S[i][j + 2] == '1' && S[i][j + 3] == '/')
                        {
                            int h = S[i][j + 4] - '0' - 1;
                            AndEli1(s[i], s[h]);
                        }
                        else if (S[i][j + 2] == '2' && S[i][j + 3] == '/')
                        {
                            int h = S[i][j + 4] - '0' - 1;
                            AndEli2(s[i], s[h]);
                        }
                        else
                        {
                            InvalidExit();
                        }
                    }
                    else
                    {
                        InvalidExit();
                    }
                }
                else if (S[i][j] == 'v' && S[i][j + 1] == 'i')
                {
                    if (S[i][j + 2] == '1' && S[i][j + 3] == '/')
                    {
                        int h = S[i][j + 4] - '0' - 1;
                        OrIntro1(s[i], s[h]);
                    }
                    else if (S[i][j + 2] == '2' && S[i][j + 3] == '/')
                    {
                        int h = S[i][j + 4] - '0' - 1;
                        OrIntro2(s[i], s[h]);
                    }
                    else
                    {
                        InvalidExit();
                    }
                }
                else if (S[i][j] == '>' && S[i][j + 1] == 'e' && S[i][j + 2] == '/')
                {
                    int h = S[i][j + 3] - '0' - 1, k = S[i][j + 5] - '0' - 1;
                    ImpEli(s[i], s[h], s[k]);
                }
                else if (S[i][j] == 'm' && S[i][j + 1] == 't' && S[i][j + 2] == '/')
                {
                    int h = S[i][j + 3] - '0' - 1, k = S[i][j + 5] - '0' - 1;
                    ModusT(s[i], s[h], s[k]);
                }
                else if (!(S[i][j] == 'p' || S[i][j] == 'P'))
                {
                    InvalidExit();
                }
                break;
            }
            else
            {
                s[i][j] = S[i][j];
            }
        }
    }
    printf("Valid Proof\n");
}

/// The regular main function from where the execution starts 
int main()
{
    int d;
    scanf("%d", &d);
    char s[max_lines][max_length];
    for (int i = 0; i < d; i++)
    {
        scanf("%*c%[^\n]", s[i]);
    }
    checkvalidity(s, d);
    return 1;
}