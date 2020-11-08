#include <libgen.h>

char *remove_ext (char* mystr, char dot, char sep) {
    char *retstr, *lastdot, *lastsep;

    if (mystr == NULL)
        return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;

    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, dot);
    lastsep = (sep == 0) ? NULL : strrchr (retstr, sep);

    if (lastdot != NULL) {

        if (lastsep != NULL) {
            if (lastsep < lastdot) {

                *lastdot = '\0';
            }
        } else {

            *lastdot = '\0';
        }
    }

    return retstr;
}
