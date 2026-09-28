#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_L 500
#define MAX_C 256

#ifdef _WIN32
#define strcasecmp _stricmp
#endif

typedef struct
{
    char lines[MAX_L][MAX_C];
    int count;
} Document;

Document doc, undo_stack;
int undo_avail = 0;

void save_undo()
{
    undo_stack = doc;
    undo_avail = 1;
}

int main()
{
    char in[MAX_C], cmd[20], a1[MAX_C], a2[MAX_C];
    int num;

    printf("=========================================\n Simple Line Editor (Minimal Edition)\n=========================================\nType HELP for available commands.\n\n");

    while (1)
    {
        printf("editor> ");
        if (!fgets(in, sizeof(in), stdin))
            break;
        in[strcspn(in, "\r\n")] = 0;
        if (!in[0])
            continue;

        cmd[0] = a1[0] = a2[0] = 0;
        sscanf(in, "%s %s %[^\n]", cmd, a1, a2);
        num = atoi(a1);

        if (!strcasecmp(cmd, "SHOW"))
        {
            if (!doc.count)
            {
                printf("[ Document is empty ]\n");
                continue;
            }
            printf("--- DOCUMENT START ---\n");
            for (int i = 0; i < doc.count; i++)
                printf("%3d | %s\n", i + 1, doc.lines[i]);
            printf("--- DOCUMENT END ---\n");
        }
        else if (!strcasecmp(cmd, "INS"))
        {
            if (num < 1 || num > doc.count + 1 || !a2[0] || doc.count >= MAX_L)
            {
                printf("Error/Usage: INS <1-%d> <text>\n", doc.count + 1);
                continue;
            }
            save_undo();
            for (int i = doc.count; i >= num; i--)
                strcpy(doc.lines[i], doc.lines[i - 1]);
            strncpy(doc.lines[num - 1], a2, MAX_C - 1);
            doc.lines[num - 1][MAX_C - 1] = 0;
            doc.count++;
            printf("Inserted line %d.\n", num);
        }
        else if (!strcasecmp(cmd, "DEL"))
        {
            if (num < 1 || num > doc.count)
            {
                printf("Error/Usage: DEL <1-%d>\n", doc.count);
                continue;
            }
            save_undo();
            for (int i = num - 1; i < doc.count - 1; i++)
                strcpy(doc.lines[i], doc.lines[i + 1]);
            doc.count--;
            printf("Deleted line %d.\n", num);
        }
        else if (!strcasecmp(cmd, "EDIT"))
        {
            if (num < 1 || num > doc.count || !a2[0])
            {
                printf("Error/Usage: EDIT <1-%d> <text>\n", doc.count);
                continue;
            }
            save_undo();
            strncpy(doc.lines[num - 1], a2, MAX_C - 1);
            doc.lines[num - 1][MAX_C - 1] = 0;
            printf("Updated line %d.\n", num);
        }
        else if (!strcasecmp(cmd, "SAVE"))
        {
            if (!a1[0])
            {
                printf("Usage: SAVE <filename>\n");
                continue;
            }
            FILE *f = fopen(a1, "w");
            if (!f)
            {
                printf("Error opening file for writing.\n");
                continue;
            }
            for (int i = 0; i < doc.count; i++)
                fprintf(f, "%s\n", doc.lines[i]);
            fclose(f);
            printf("Saved to %s.\n", a1);
        }
        else if (!strcasecmp(cmd, "LOAD"))
        {
            if (!a1[0])
            {
                printf("Usage: LOAD <filename>\n");
                continue;
            }
            FILE *f = fopen(a1, "r");
            if (!f)
            {
                printf("Error opening file.\n");
                continue;
            }
            save_undo();
            doc.count = 0;
            while (fgets(in, MAX_C, f) && doc.count < MAX_L)
            {
                in[strcspn(in, "\r\n")] = 0;
                strcpy(doc.lines[doc.count++], in);
            }
            fclose(f);
            printf("Loaded %d line(s).\n", doc.count);
        }
        else if (!strcasecmp(cmd, "FIND"))
        {
            char *phrase = strchr(in, ' ');
            if (!phrase || !*(++phrase))
            {
                printf("Usage: FIND <phrase>\n");
                continue;
            }
            int m = 0;
            for (int i = 0; i < doc.count; i++)
            {
                if (strstr(doc.lines[i], phrase))
                {
                    printf("Line %3d: %s\n", i + 1, doc.lines[i]);
                    m++;
                }
            }
            printf("Found %d match(es).\n", m);
        }
        else if (!strcasecmp(cmd, "REPLACE"))
        {
            if (!a1[0] || !a2[0])
            {
                printf("Usage: REPLACE <target> <replacement>\n");
                continue;
            }
            save_undo();
            int r = 0;
            char buf[MAX_C];
            for (int i = 0; i < doc.count; i++)
            {
                char *pos, *curr = doc.lines[i];
                if ((pos = strstr(curr, a1)))
                {
                    memset(buf, 0, sizeof(buf));
                    while ((pos = strstr(curr, a1)))
                    {
                        strncat(buf, curr, pos - curr);
                        strcat(buf, a2);
                        curr = pos + strlen(a1);
                        r++;
                    }
                    strcat(buf, curr);
                    strncpy(doc.lines[i], buf, MAX_C - 1);
                    doc.lines[i][MAX_C - 1] = 0;
                }
            }
            printf("Replaced %d occurrence(s).\n", r);
        }
        else if (!strcasecmp(cmd, "STATS"))
        {
            int w = 0, c = 0;
            for (int i = 0; i < doc.count; i++)
            {
                c += strlen(doc.lines[i]);
                char tmp[MAX_C];
                strcpy(tmp, doc.lines[i]);
                for (char *t = strtok(tmp, " \t"); t; t = strtok(NULL, " \t"))
                    w++;
            }
            printf("Lines: %d | Words: %d | Chars: %d\n", doc.count, w, c);
        }
        else if (!strcasecmp(cmd, "UNDO"))
        {
            if (!undo_avail)
                printf("Nothing to undo.\n");
            else
            {
                doc = undo_stack;
                undo_avail = 0;
                printf("Undone.\n");
            }
        }
        else if (!strcasecmp(cmd, "CLEAR"))
        {
            if (doc.count)
            {
                save_undo();
                doc.count = 0;
            }
            printf("Cleared.\n");
        }
        else if (!strcasecmp(cmd, "UPPER") || !strcasecmp(cmd, "LOWER"))
        {
            if (!doc.count)
                continue;
            save_undo();
            int up = !strcasecmp(cmd, "UPPER");
            for (int i = 0; i < doc.count; i++)
                for (int j = 0; doc.lines[i][j]; j++)
                    doc.lines[i][j] = up ? toupper((unsigned char)doc.lines[i][j]) : tolower((unsigned char)doc.lines[i][j]);
            printf("Converted to %s.\n", up ? "UPPERCASE" : "lowercase");
        }
        else if (!strcasecmp(cmd, "HELP"))
        {
            printf("Commands: INS, DEL, EDIT, SHOW, SAVE, LOAD, FIND, REPLACE, STATS, UNDO, CLEAR, UPPER, LOWER, EXIT\n");
        }
        else if (!strcasecmp(cmd, "EXIT"))
            break;
        else
            printf("Unknown command. Type HELP for usage.\n");
    }
    return 0;
}