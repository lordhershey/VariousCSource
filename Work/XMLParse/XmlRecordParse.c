#include<stdio.h>
#include<stdlib.h>
#include<string.h>


/*!
  \brief get a token between the stat and stop tag

  \param[in] start the start token, usually an xml or html start tag, cannot be NULL
  \param[in] stop the stop token, if NULL it will assume you are looking for a 
  xml like close tag and it will make one from the start token.
  \param[in] buf the file buffer
  \param[in] bufsiz the size of buf
  \param[out] val a 10 char buffer to put the true of false into
  \retval 0 a ok
  \retval -1 token not found
 */
int getTokenFromTags(char *start,
                     char *stop, char *buf, int bufsiz, char *val, int valsize)
{
    int i, j;
    int inToken = 0;
    char tmp_stop[300];

    memset(tmp_stop, '\0', sizeof(tmp_stop));
    if (NULL == stop)
    {
        /*implied xml end tag */
        snprintf(tmp_stop, sizeof(tmp_stop), "%c/%s", start[0], &start[1]);
        stop = tmp_stop;
    }

    for (i = 0, j = 0; (j < valsize) && (i < bufsiz - strlen(start) - 1); i++)
    {
        if (inToken)
        {
            if (strncasecmp(buf + i, stop, strlen(stop)) == 0)
            {
                break;
            }
            val[j] = buf[i];
            j++;
            continue;
        }
        if (strncasecmp(buf + i, start, strlen(start)) == 0)
        {
            inToken = 1;
            i += strlen(start) - 1;
        }
    }

    if (inToken)
    {
        return (0);
    }

    return (-1);
}
