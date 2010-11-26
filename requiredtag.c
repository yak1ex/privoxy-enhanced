#include <assert.h>

#include "project.h"
#include "requiredtag.h"
#include "errlog.h"
#include "miscutil.h"

jb_err init_req_tag_list(struct req_tag_list *tags, const char* pattern)
{
   int errcode;
   char ebuf[BUFFER_SIZE];

   tags->next = NULL;

   tags->tag_regex = zalloc(sizeof(*tags->tag_regex));
   if (NULL == tags->tag_regex)
   {
      return JB_ERR_MEMORY;
   }

   errcode = regcomp(tags->tag_regex, pattern, (REG_EXTENDED|REG_NOSUB|REG_ICASE));

   if (errcode)
   {
      size_t errlen = regerror(errcode, tags->tag_regex, ebuf, sizeof(ebuf));
      if (errlen > (sizeof(ebuf) - (size_t)1))
      {
         errlen = sizeof(ebuf) - (size_t)1;
      }
      log_error(LOG_LEVEL_ERROR, "error compiling %s : %s",
         pattern, ebuf);

      return JB_ERR_PARSE;
   }

   return JB_ERR_OK;
}

void free_req_tag_list(struct req_tag_list *tags)
{
   struct req_tag_list *temp;

   if (tags == NULL) return;

   while(tags)
   {
      if (tags->tag_regex)
      {
         regfree(tags->tag_regex);
         freez(tags->tag_regex);
      }
      temp = tags;
      tags = tags->next;
      freez(temp);
   }
}

static int match_req_tag(struct req_tag_list *rtags, struct list *tags)
{
   struct list_entry *tag;

   for (tag = tags->first; tag != NULL; tag = tag->next)
   {
      if (0 == regexec(rtags->tag_regex, tag->str, 0, NULL, 0))
      {
         return 1;
      }
   }
   return 0;
}

int match_req_tag_list(struct req_tag_list *rtags, struct list *tags)
{
   assert(rtags);

   while(rtags)
   {
      if (0 == match_req_tag(rtags, tags))
      {
         return 0;
      }
      rtags = rtags->next;
   }
   return 1;
}
