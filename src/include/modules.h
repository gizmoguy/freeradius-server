/*
 * module.h	Interface to the RADIUS module system.
 *
 * Version:	$Id$
 *
 */

typedef struct module_t {
	const char	*name;
	int	type;			/* reserved */
	int	(*init)(int argc, char **argv);
	int	(*authorize)(REQUEST *request, 
			VALUE_PAIR **check_items, VALUE_PAIR **reply_items);
	int	(*authenticate)(REQUEST *request);
	int	(*preaccounting)(REQUEST *request);
	int	(*accounting)(REQUEST *request);
	int	(*detach)(void);
} module_t;

enum {
  RLM_AUTH_FAIL = -2,		/* Failed (don't reply) */
  RLM_AUTH_REJECT = -1,		/* authentication failed - reject */
  RLM_AUTH_OK = 0,		/* OK */
  RLM_AUTH_HANDLED = 1		/* OK, handled (don't reply) */
};
enum {
  RLM_AUTZ_REJECT = -3,		/* Reject user */
  RLM_AUTZ_FAIL = -2,		/* Failed (don't reply) */
  RLM_AUTZ_NOTFOUND = -1,	/* User not found - try next autorization */
  RLM_AUTZ_OK = 0,		/* OK */
  RLM_AUTZ_HANDLED = 1		/* OK, handled (don't reply) */
};
enum {
  RLM_PRAC_FAIL = -1,		/* Failed (don't reply) */
  RLM_PRAC_OK = 0		/* OK */
};
enum {
  RLM_ACCT_FAIL = -2,		/* Failed (don't reply) */
  RLM_ACCT_FAIL_SOFT = -1,	/* Failed, but who cares. Continue */
  RLM_ACCT_OK = 0,		/* OK */
  RLM_ACCT_HANDLED = 1		/* OK, handled (don't reply) */
};
#define RLM_ACCT_FAIL_HARD RLM_ACCT_FAIL

int read_modules_file(char *filename);
int module_authorize(REQUEST *request, 
	VALUE_PAIR **check_items, VALUE_PAIR **reply_items);
int module_authenticate(int type, REQUEST *request);
int module_preacct(REQUEST *request);
int module_accounting(REQUEST *request);

