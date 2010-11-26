#ifndef REQUIREDTAG_H_INCLUDED
#define REQUIREDTAG_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

extern jb_err init_req_tag_list(struct req_tag_list *tags, const char* pattern);
extern void free_req_tag_list(struct req_tag_list *tags);
extern int match_req_tag_list(struct req_tag_list *rtags, struct list *tags);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ndef REQUIREDTAG_H_INCLUDED */

/*
  Local Variables:
  tab-width: 3
  end:
*/
